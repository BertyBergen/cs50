#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int coin_counter = 0;

    // Calculate how many quarters you should give customer
    coin_counter += cents / 25;
    // Subtract the value of those quarters from cents
    cents %= 25;

    // Calculate how many dimes you should give customer
    coin_counter += cents / 10;
    // Subtract the value of those dimes from remaining cents
    cents %= 10;

    // Calculate how many nickels you should give customer
    coin_counter += cents / 5;
    // Subtract the value of those nickels from remaining cents
    cents %= 5;

    // Sum the number of quarters, dimes, nickels, and pennies used
    coin_counter += cents;

    // Print total number of coins
    printf("%i\n", coin_counter);
}
