#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_space(int spaces);

int get_height(void);

int main(void)
{
    int n = get_height();

    for (int i = 0; i < n; i++)
    {
        print_space(n - i);
        print_row(i + 1);
    }
}

int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);
    return n;
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

void print_space(int spaces)
{
    for (int i = 1; i < spaces; i++)
    {
        printf(" ");
    }
}
