#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0;
    // Lopping through cols and rows.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            int rounded = round(avg);
            // Assigning values
            image[i][j].rgbtBlue = rounded;
            image[i][j].rgbtGreen = rounded;
            image[i][j].rgbtRed = rounded;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // The number can't be greater than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Assigning the values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE t = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][width - 1 - j] = t;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Full grid
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            int average_r = 0;
            int average_g = 0;
            int average_b = 0;
            int squares = 0;

            // 9x9
            for (int k = i - 1; k <= i + 1; k++)
            {

                for (int l = j - 1; l <= j + 1; l++)
                {
                    // Only add existing squares
                    if (l < width && k < height && k >= 0 && l >= 0)
                    {
                        average_r += copy[k][l].rgbtRed;
                        average_g += copy[k][l].rgbtGreen;
                        average_b += copy[k][l].rgbtBlue;
                        squares++;
                    }

                }
            }
            // Averaging and assigning
            image[i][j].rgbtRed = (int) round(average_r / (float) squares);
            image[i][j].rgbtGreen = (int) round(average_g / (float) squares);
            image[i][j].rgbtBlue = (int) round(average_b / (float) squares);
        }
    }

    return;

}

// Used math just to round