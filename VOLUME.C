#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEADER_SIZE 44


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Использование:./volume input.wav output.wav factor\n");
        return 1;
    }


    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Не удалось открыть входной файл.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Не удалось создать выходной файл.\n");
        fclose(input);
        return 1;
    }
    float factor = atof(argv[3]);
    uint8_t header[HEADER_SIZE];
    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) != HEADER_SIZE)
    {
        printf("Не удалось прочитать заголовок WAV-файла.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {

    
    float scaled = buffer * factor;
    if (scaled > INT16_MAX)
    {buffer = INT16_MAX;}
    else if (scaled < INT16_MIN)
    {buffer = INT16_MIN;}
    else
    {buffer = (int16_t)(scaled); }

    fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    fclose(input);
    fclose(output);

    return 0;
}