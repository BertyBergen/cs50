#include <cs50.h>
#include <stdio.h>

bool luhn_algoritm_check(long cart_number);
void define_card_type(long cart_number);

int main(void)
{
    // get a card number
    long cart_number = get_long("Enter card Number: ");

    // check luhn algoritm
    if (luhn_algoritm_check(cart_number))
    {
        // define card type
        define_card_type(cart_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool luhn_algoritm_check(long cart_number)
{
    int sum = 0;
    int count = 0;

    while (cart_number > 0)
    {
        int last_number = cart_number % 10;

        if (count % 2 == 1)
        {
            last_number *= 2;
            if (last_number > 9)
            {
                last_number = (last_number % 10) + (last_number / 10);
            }
        }

        sum += last_number; // add to summ
        cart_number /= 10;  // dispose last number
        count++;
    }
    return (sum % 10 == 0);
}

void define_card_type(long cart_number)
{
    int length = 0;
    long temp_cart_number = cart_number;

    while (temp_cart_number > 0) // count digits
    {
        temp_cart_number /= 10;
        length++;
    }

    // define first 2 digits
    long first_two_digits = cart_number;
    while (first_two_digits >= 100)
    {
        first_two_digits /= 10;
    }

    // checking card
    if ((length == 15) && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if ((length == 16) && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (first_two_digits / 10 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
