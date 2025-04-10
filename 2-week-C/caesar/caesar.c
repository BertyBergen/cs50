#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if ('0' > argv[1][i] || argv[1][i] > '9')
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("Enter text to encrypt: ");

    printf("ciphertext: ");
    // For each character in the plaintext:
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char letter = plaintext[i];
        // Rotate the character if it's a letter
        if ('a' <= letter && letter <= 'z')
        {
            letter = (letter - 'a' + key) % 26 + 'a';
        }
        else if ('A' <= letter && letter <= 'Z')
        {
            letter = (letter - 'A' + key) % 26 + 'A';
        }

        printf("%c", letter);
    }
    printf("\n");
}
