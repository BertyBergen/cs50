#include "helpers.h"
#include <math.h>
#define MAX_COLOR 255

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

            image[i][j].rgbtRed = (sepiaRed > MAX_COLOR) ? MAX_COLOR : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > MAX_COLOR) ? MAX_COLOR : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > MAX_COLOR) ? MAX_COLOR : sepiaBlue;
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

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int directions[9][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 0}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
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

            for (int k = 0; k < 9; k++)
            {
                int new_i = i + directions[k][0];
                int new_j = j + directions[k][1];

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
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Create copy of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int gx_kernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy_kernel[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;


                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        gx_red += copy[ni][nj].rgbtRed * gx_kernel[di + 1][dj + 1];
                        gx_green += copy[ni][nj].rgbtGreen * gx_kernel[di + 1][dj + 1];
                        gx_blue += copy[ni][nj].rgbtBlue * gx_kernel[di + 1][dj + 1];

                        gy_red += copy[ni][nj].rgbtRed * gy_kernel[di + 1][dj + 1];
                        gy_green += copy[ni][nj].rgbtGreen * gy_kernel[di + 1][dj + 1];
                        gy_blue += copy[ni][nj].rgbtBlue * gy_kernel[di + 1][dj + 1];
                    }

                }
            }

            int g_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int g_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int g_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));


            g_red = (g_red > MAX_COLOR) ? MAX_COLOR :g_red;
            g_green = (g_green > MAX_COLOR) ? MAX_COLOR : g_green;
            g_blue = (g_blue > MAX_COLOR) ? MAX_COLOR : g_blue;

            image[i][j].rgbtRed = g_red;
            image[i][j].rgbtGreen = g_green;
            image[i][j].rgbtBlue = g_blue;
        }
    }
}
