#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHUNK 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("INVALID");
        return 1;
    }
    //Open memory card
    FILE *input = fopen(argv[1], "r");

    int counter = 0;
    typedef uint8_t BYTE;
    BYTE buffer[512];
    char filename[8];
    FILE *image = NULL;

    // Main loop to iterate over BYTES
    while (fread(buffer, sizeof(BYTE), CHUNK, input) == CHUNK)
    {
        // If the bytes are the ones equivalent to a JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it is the first JPG found
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                image = fopen(filename, "w");
                counter++;
            }
            // If a JGP has already beewn found
            else
            {
                sprintf(filename, "%03i.jpg", counter);
                fclose(image);
                image = fopen(filename, "w");
                counter++;
            }
            fwrite(&buffer, sizeof(BYTE), CHUNK, image);
        }
        // If no JPG header has been found
        else if (counter > 0)
        {
            fwrite(&buffer, sizeof(BYTE), CHUNK, image);
        }
    }

    fclose(input);
    fclose(image);
}

