#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CLASTER_SIZE 512

const uint8_t start_jpeg[3] = {0xff, 0xd8, 0xff};

int is_jpeg_start(uint8_t buffer[CLASTER_SIZE]);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[CLASTER_SIZE];

    // Counter for numbering files
    int file_counter = 0;

    // Pointer to save img
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, CLASTER_SIZE, card) == CLASTER_SIZE)
    {
        if (is_jpeg_start(buffer))
        {
            // Create JPEGs from the data
            if (img != NULL)
            {
                fclose(img);
            }

            // Format img name
            char bf_name[8];
            sprintf(bf_name, "%03d.jpg", file_counter);
            img = fopen(bf_name, "w");

            if (img == NULL)
            {
                printf("Could not create %s.\n", bf_name);
                fclose(card);
                return 3;
            }

            file_counter++;
        }

        if (img != NULL)
        {
            fwrite(buffer, 1, CLASTER_SIZE, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);

    return 0;
}

int is_jpeg_start(uint8_t buffer[CLASTER_SIZE])
{
    return buffer[0] == start_jpeg[0] && buffer[1] == start_jpeg[1] && buffer[2] == start_jpeg[2];
}
