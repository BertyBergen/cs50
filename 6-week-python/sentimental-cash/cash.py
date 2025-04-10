from cs50 import get_float

def get_change():
    change = 0
    while change <= 0:
        change = int(get_float("Change: ")*100)

    count = 0
    coins = [25, 10, 5, 1]

    for coin in coins:
        count += change // coin
        change %= coin


    print(int(count))

def main():
    get_change()

main()
