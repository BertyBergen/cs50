#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_space(int spaces);

int get_height(void);

int main(void)
{
    // get height
    int height = get_height();

    for (int i = 0; i < height; i++)
    {
        // print spaces before bricks
        print_space(height - i);
        // print birck rows
        print_row(i + 1);
        // print spaces between bricks
        printf("  ");
        // another bricks
        print_row(i + 1);
        // go to new row
        printf("\n");
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
}

void print_space(int spaces)
{
    for (int i = 1; i < spaces; i++)
    {
        printf(" ");
    }
}
