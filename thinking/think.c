#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct _sBmpHeader
{
    char bm[2];
    uint32_t size;
    uint32_t reserve;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    int32_t height;
    int16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t bitmap_size;
    int32_t hres;
    int32_t vres;
    uint32_t used;
    uint32_t important;
} __attribute__((__packed__));
typedef struct _sBmpHeader sBmpHeader;
int main()
{
    FILE *file1 = NULL;
    FILE *file2 = NULL;

    if ((file1 = fopen("test.bmp", "rb")) == NULL)
    {
        perror("Something is wrong : ");
        return 0;
    }
    if ((file2 = fopen("result.bmp", "wb")) == NULL)
    {
        perror("Something is wrong : ");
        return 0;
    }
    /*  if ((pFile = fopen("maldives.bmp", "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    if ((pFile2 = fopen("result.bmp", "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }*/

    sBmpHeader header;
    fread(&header, sizeof(header), 1, file1);
    fwrite(&header, sizeof(header), 1, file2);
    //fread(&header, sizeof(header), 1, pFile);
    //fwrite(&header, sizeof(header), 1, pFile2);

    while (!feof(file1))
    {
        uint8_t original[999] = {0};
        uint8_t modified[999] = {0};

        size_t cnt = fread(original, 1, 999, file1);
        //for (size_t i = 0; i < count; i = i + 3)
        for (size_t i = 0; i < cnt; i = i + 3)
        {
            uint8_t V = 0.299 * original[i + 2] + 0.587 * original[i + 1] + 0.114 * original[i];

            for (size_t j = 0; j < 3; j++)
            {
                modified[i + j] = V;
            }
        }
        fwrite(modified, cnt, 1, file2);
    }
    fclose(file1);
    fclose(file2);
    //fclose(pFile);
    //fclose(pFile2);
    return 0;
}