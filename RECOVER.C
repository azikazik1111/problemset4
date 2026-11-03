#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Использование: ./recover image\n");
        return 1;
    }
FILE *input = fopen(argv[1], "r");
if (input == NULL)
{
    printf("Не удалось открыть входной файл.\n");
    return 1;   
}
//для хранения данных из файла
unsigned char buffer[512];
FILE *img = NULL;
char filename[8];
int count = 0;

while (fread(buffer, 1, 512, input) == 512)
{
    //проверяем наличие заголовка JPEG
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        //если уже открыт файл изображения, закрываем его
        if (img != NULL)
        {
            fclose(img);
        }
        //создаем новый файл изображения
        sprintf(filename, "%03i.jpg", count);
        img = fopen(filename, "w");
        if (img == NULL)
        {
            printf("Не удалось создать файл изображения.\n");
            fclose(input);
            return 1;
        }
        count++;
    }
    //если файл изображения открыт, записываем данные в него
    if (img != NULL)
    {
        fwrite(buffer, 1 , 512, img);
    }

}
//закрываем последний файл изображения, если он был открыт
if (img != NULL)
{
    fclose(img);
}
fclose(input);
return 0;
}

  
  