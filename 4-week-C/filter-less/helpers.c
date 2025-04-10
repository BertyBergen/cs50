#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round((0.393*image[i][j].rgbtRed) + (0.769*image[i][j].rgbtGreen)+(0.189*image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349*image[i][j].rgbtRed) + (0.686*image[i][j].rgbtGreen)+(0.168*image[i][j].rgbtBlue));
            int sepiaBlue = round((0.272*image[i][j].rgbtRed) + (0.534*image[i][j].rgbtGreen)+(0.131*image[i][j].rgbtBlue));

            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE bf;
            bf = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width-j-1] = bf;


        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Directions for the 3x3 neighboring pixels (including the current pixel)
    int directions[9][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Top row (left, middle, right)
        {0, -1}, {0, 0}, {0, 1},     // Middle row (left, center, right)
        {1, -1}, {1, 0}, {1, 1}      // Bottom row (left, middle, right)
    };

    // Process each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int count = 0;

            // Check all 9 neighbors in the 3x3 grid
            for (int k = 0; k < 9; k++)
            {
                int new_i = i + directions[k][0];
                int new_j = j + directions[k][1];

                // Ensure the neighbor is within bounds
                if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                {
                    redSum += copy[new_i][new_j].rgbtRed;
                    greenSum += copy[new_i][new_j].rgbtGreen;
                    blueSum += copy[new_i][new_j].rgbtBlue;
                    count++;
                }
            }

            // Calculate the average color values and assign them to the current pixel
            image[i][j].rgbtRed = round((float)redSum / count);
            image[i][j].rgbtGreen = round((float)greenSum / count);
            image[i][j].rgbtBlue = round((float)blueSum / count);
        }
    }
}
