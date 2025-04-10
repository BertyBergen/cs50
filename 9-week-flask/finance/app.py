import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute("""SELECT name, symbol, price, SUM(shares) as total_shares
                        FROM transactions WHERE user_id = ?
                        GROUP BY symbol HAVING total_shares > 0 """, user_id)
    portfolio = []
    total_value = 0
    for stock in stocks:

        quote = lookup(stock["symbol"])

        current_price = quote["price"] if quote else stock["price"]

        old_price = stock["price"]
        total = stock["total_shares"] * current_price
        profit = total - stock['total_shares'] * old_price

        total_value += total

        portfolio.append(
            {
                "name": stock["name"],
                "symbol": stock["symbol"],
                "shares": stock["total_shares"],
                "old_price": old_price,
                "current_price": current_price,
                "total": total,
                "profit": profit
            }
        )

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    grand_total = total_value + cash

    return render_template("index.html", portfolio=portfolio, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("There is no symbol here, pleeease enter stock symbol")

        if not shares:
            return apology("Count of shares must be more that nothing")

        try:
            shares = int(shares)
        except ValueError:
            return apology("Invalid number, shares must be positive integer")

        if shares <= 0:
            return apology("Invalid number, shares must be positive integer")

        stock = lookup(symbol)

        if not stock:
            return apology("Invalid stock symbol")

        user_id = session["user_id"]

        create_transactions()

        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        cash = rows[0]["cash"]

        total_price = stock["price"]*shares
        stock_name = stock["name"].removesuffix("Common Stock")

        if cash < total_price:
            return apology("You have no enough money for transaction")

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, user_id)

        db.execute("""
            INSERT INTO transactions (user_id, name, symbol, shares, price, action)
            VALUES( ?, ?, ?, ?, ?, ?)""",
                   user_id, stock_name, symbol, shares, stock["price"], 'Buy'
                   )

        flash(
            f"Successfully bought {shares} shares of {stock_name} for a total of ${total_price:.2f}!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT * FROM transactions WHERE :id ORDER BY timestamp DESC", id=user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("You logged in")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form

    flash("You're logged out")
    return render_template('login.html')


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Missing symbol")

        stock = lookup(symbol)
        if not stock:
            return apology("INVALID SYMBOL")

        return render_template("quoted.html", stock=stock)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Please enter a username")

        if not password:
            return apology("Please enter a password")

        if password != confirmation:
            return apology("Password dosen't match")
        # Password validation
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) > 0:
            return apology("Username already exist")

        hashed_password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

        rows = db.execute("SELECT id FROM users WHERE username = ?", username)

        session["user_id"] = rows[0]["id"]

        flash("You're registered.")
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares:
            return apology("Choose symbol and qty of shares")
        rows = db.execute("""
            SELECT symbol, SUM(shares) as total_shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
                          """, user_id, symbol)

        shares = int(shares)

        if len(rows) == 0 or rows[0]["total_shares"] < shares:
            return apology("Not enough shares")

        stock = lookup(symbol)
        price = stock["price"]
        stock_name = stock["name"].removesuffix("Common Stock")

        db.execute("""
            INSERT INTO transactions (user_id, name, symbol, shares, price, action)
            VALUES (:user_id, :name, :symbol, :shares, :price, 'Sell')
            """,
                   user_id=user_id, name=stock_name, symbol=symbol, shares=-shares, price=price
                   )
        cash_change = price * shares
        db.execute("""
            UPDATE users
            SET cash = cash + :cash_change
            WHERE id = :user_id
        """, cash_change=cash_change, user_id=user_id)

        flash('You\'ve sold your shares')
        return redirect('/')

    else:

        stocks = db.execute(
            "select symbol, SUM(shares) as total_shares from transactions where user_id = ? group by symbol", user_id)

        return render_template("sell.html", stocks=stocks)


def create_transactions():
    db.execute("""
        CREATE TABLE IF NOT EXISTS transactions(
                   id INTEGER PRIMARY KEY AUTOINCREMENT,
                   user_id INTEGER NOT NULL,
                   name TEXT NOT NULL,
                   symbol TEXT NOT NULL,
                   shares INTEGER NOT NULL,
                   price REAL NOT NULL,
                   action TEXT NOT NULL,
                   timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
                   FOREIGN KEY(user_id) REFERENCES users(id)
                   )
        """)


if __name__ == "__main__":
    create_transactions()
    app.run(debug=True, use_reloader=True)
