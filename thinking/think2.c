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
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t bitmap_size;
    uint32_t hres;
    uint32_t vres;
    uint32_t used;
    uint32_t important;
} __attribute__((__packed__));

typedef struct _sBmpHeader sBmpHeader;

void print_bmp_header(sBmpHeader *pHeader)
{
    printf("ID: %c%c\n", pHeader->bm[0], pHeader->bm[1]);
    printf("Size: %u\n", pHeader->size);
    printf("Reserve: %u\n", pHeader->reserve);
    printf("Offset: %u\n", pHeader->offset);
    printf("Header Size: %u\n", pHeader->header_size);
    printf("Width: %u\n", pHeader->width);
    printf("Height: %u\n", pHeader->height);
    printf("Planes: %u\n", pHeader->planes);
    printf("Bits Per Pixel: %u\n", pHeader->bpp);
    printf("Compression: %u\n", pHeader->compression);
    printf("Bitmap Data Size: %u\n", pHeader->bitmap_size);
    printf("H-Resolution: %u\n", pHeader->hres);
    printf("V-Resolution: %u\n", pHeader->vres);
    printf("Used Colors: %u\n", pHeader->used);
    printf("Important Colors: %u\n", pHeader->important);

    return;
}

int main()
{
    FILE *pFile = NULL;
    FILE *pFile2 = NULL;

    if ((pFile = fopen("maldives.bmp", "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    if ((pFile2 = fopen("result.bmp", "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    sBmpHeader header;
    fread(&header, sizeof(header), 1, pFile);
    fwrite(&header, sizeof(header), 1, pFile2);

    while (!feof(pFile))
    {
        uint8_t original[999] = {0};
        uint8_t modified[999] = {0};

        size_t count = fread(original, 1, 999, pFile);

        for (size_t i = 0; i < count; i = i + 3)
        {
            uint8_t gray = 0.299 * original[i + 2] + 0.587 * original[i + 1] + 0.114 * original[i];

            for (size_t j = 0; j < 3; j++)
            {
                modified[i + j] = gray;
            }
        }

        fwrite(modified, count, 1, pFile2);
    }

    fclose(pFile);
    fclose(pFile2);

    return 0;
}