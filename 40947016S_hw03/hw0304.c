#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#define i32 int32_t
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

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;

} __attribute__((__packed__)) rgba;

typedef struct _sBmpHeader sBmpHeader;

int main()
{
    char name1[100] = {0}, name2[100] = {0};
    FILE *open = NULL, *write = NULL;
    printf("Please enter the input image name: ");
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
    if (header.bpp != 24)
    {
        printf("Input file is not a 24-bit depth bmp file.\n");
        fclose(open);
        return 0;
    }
    header.bpp = 32;
    header.offset = 70;
    header.header_size = 56;
    // header.bitmap_size += (header.width * header.height) * 4;
    header.compression = 3;
    printf("Please enter the output image name: ");
    fgets(name2, 99, stdin);
    name2[strcspn(name2, "\n")] = '\0';
    if ((write = fopen(name2, "wb")) == NULL)
    {
        perror("Can't open file :");
        return 0;
    }
    //output file processing
    //---------------------------------------------------
    uint32_t mask[4] = {0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF};
    fwrite(&header, sizeof(header), 1, write);
    fwrite(mask, sizeof(uint32_t) * 4, 1, write);
    rgba pixel;
    uint8_t alpha;
    printf("Alpha (0-31): ");
    scanf("%hhu", &alpha);
    if (alpha < 0 || alpha > 31)
    {
        fclose(open);
        fclose(write);
        printf("Invalid alpha input.\n");
        return 0;
    }

    while (!feof(open))
    {
        fread(&pixel, sizeof(rgba), 1, open);
        uint32_t tmp = (alpha) + (pixel.r << 8) + (pixel.g << 16) + (pixel.b << 24);
        fwrite(&tmp, sizeof(tmp), 1, write);
    }
    fclose(open);
    fclose(write);
    printf("Done!\n");
    return 0;
}

//1101 0001 209
//1100 0110 198
//1010 0000 160
//0001 1010 26
//0101 0011 83