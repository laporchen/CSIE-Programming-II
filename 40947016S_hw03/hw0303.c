#include "math.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#define i32 int32_t
#define PI 3.141592654
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

int main()
{
    char name1[100] = {0}, name2[100] = {0};
    FILE *open = NULL, *write = NULL;
    printf("Please input a BMP file: ");
    fgets(name1, 99, stdin);
    name1[strcspn(name1, "\n")] = '\0';
    if ((open = fopen(name1, "rb")) == NULL)
    {
        perror("Can't open this file :");
        return 0;
    }
    //input file processing
    //---------------------------------------------------
    sBmpHeader header;
    fread(&header, sizeof(header), 1, open);
    //print_bmp_header(&header);
    if (header.bm[0] != 'B' || header.bm[1] != 'M')
    {
        fclose(open);
        printf("%c %c\n", header.bm[0], header.bm[1]);
        printf("Error,this is not a bmp file.\n");
        return 0;
    }
    printf("Please input the output BMP file name: ");
    fgets(name2, 99, stdin);
    name2[strcspn(name2, "\n")] = '\0';
    if ((write = fopen(name2, "wb")) == NULL)
    {
        perror("Can't open file :");
        return 0;
    }

    printf("Angle (0-90): ");
    char inputangle[5] = {0};
    fgets(inputangle, 4, stdin);
    i32 angel = strtol(inputangle, NULL, 10);
    if (angel < 0 || angel > 90)
    {
        printf("Invalid angle.\n");
        fclose(open);
        fclose(write);
        return 0;
    }

    if (angel == 90)
    {
        rewind(open);
        sBmpHeader ver;
        memset(&ver, 0, sizeof(sBmpHeader));
        fread(&ver, sizeof(ver), 1, open);
        fwrite(&ver, sizeof(ver), 1, write);
        while (!feof(open))
        {
            uint8_t r[128] = {0};
            size_t cnt = fread(r, 1, 128, open);
            fwrite(r, cnt, 1, write);
        }
        fclose(open);
        fclose(write);
        printf("Done!\n");
        return 0;
    }
    i32 originalWidth = header.width;
    double cot = 1.0 / tan(PI * angel / 180.0);
    i32 shift = (i32)(header.height * (cot));
    header.width += shift;
    size_t size = header.width * header.height * 3;
    header.size = header.width * header.height * 3 + header.header_size;

    fwrite(&header, sizeof(header), 1, write);
    uint8_t w = 255;
    i32 pad = (4 - ((header.width * 3) % 4)) % 4;
    i32 p = 0;
    uint8_t padding = 0x00;
    while (size--)
    {
        fwrite(&w, 1, 1, write);
        if (p % header.width == 0)
        {
            p = 0;
            fwrite(&padding, 1, pad, write);
        }
        p++;
    }
    fseek(write, sizeof(header), SEEK_SET);
    i32 ch = 0;

    i32 i = 0;
    while (!feof(open))
    {
        uint8_t buf[4096] = {0};
        uint32_t cnt;
        cnt = fread(buf, 1, originalWidth * 3, open);
        i32 shifting = i * cot;
        fseek(write, sizeof(header) + (i * ((header.width) * 3)) + shifting * 3 + pad * i, SEEK_SET);
        fwrite(buf, 1, cnt, write);
        i++;
    }

    fclose(open);
    fclose(write);
    printf("Done!\n");
    return 0;
}
