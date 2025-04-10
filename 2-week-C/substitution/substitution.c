#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int KEY_LENGTH = 26;

bool validate_key(string key);
void convert_key_to_uppercase(string key);
void encrypt_plaintext(string plaintext, string key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // validate key
    if (!validate_key(key))
    {
        return 1;
    }

    convert_key_to_uppercase(key);
    // get plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Encrypt it
    encrypt_plaintext(plaintext, key);

    printf("\n");
}

bool validate_key(string k)
{
    string key = k;
    int length = strlen(key);

    // Check key length
    if (length != KEY_LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    bool seen[KEY_LENGTH] = {false};

    for (int i = 0; i < length; i++)
    {
        char letter = tolower(key[i]);

        // Check for non-alohabetic characters
        if (!isalpha(letter))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }
        int index = letter - 'a';

        // Check for repeated characters(Case-insensitive)
        if (seen[index])
        {
            printf("Key must not contain repeated characters.\n");
            return false;
        }

        seen[index] = true;
    }
    return true;
}

void convert_key_to_uppercase(string key)
{
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        key[i] = toupper(key[i]);
    }
}

void encrypt_plaintext(string plaintext, string key)
{
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        char letter = plaintext[i];

        // For each alphabetic character, determine what letter it maps to
        if (isupper(letter))
        {
            printf("%c", key[letter - 'A']);
        }
        else if (islower(letter))
        {
            printf("%c", key[letter - 'a'] + 32);
        }
        else
        {
            printf("%c", letter);
        }
    }
}

// I've spent a lot of time solving this problem—several hours. At first glance, it didn’t seem so
// hard, but it turned out to be quite challenging.
