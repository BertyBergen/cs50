from cs50  import get_string

def luhn_check(card_number):
    total = 0
    reverse_card = card_number[::-1]

    for i in range(len(reverse_card)):
        num = int(reverse_card[i])

        if i % 2 == 1:
            num *= 2
            if num > 9:
                num -= 9
        total += num
    return total % 10 == 0

def get_card(card_number):
    cards = {
        "34": "AMEX",
        "37": "AMEX",
        "4": "VISA",
        "51": "MASTERCARD",
        "52": "MASTERCARD",
        "53": "MASTERCARD",
        "54": "MASTERCARD",
        "55": "MASTERCARD"

    }

    for card in cards:
        if card_number.startswith(card):

            if cards[card] == "VISA":
                if len(card_number) == 13 or len(card_number) == 16:
                    if luhn_check(card_number):
                        return cards[card]
                    else:
                        return "INVALID"
                else:
                    return "INVALID"


            return cards[card]

    return "INVALID"

def main():
    card_number = get_string("Number: ")
    print(get_card(card_number))

main()
