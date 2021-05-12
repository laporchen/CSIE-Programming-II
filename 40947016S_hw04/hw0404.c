#include "getopt.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define i32 int32_t
#define i64 int64_t
#define i16 int16_t
#define i8 int8_t
#define u32 uint32_t
#define u64 uint64_t
#define u16 uint16_t
#define u8 uint8_t

typedef struct _LFHeader //30bytes
{
    u32 PK;
    u16 version;
    u16 bitFlag;
    u16 method;
    u16 time;
    u16 date;
    u32 uncompressed;
    u32 cSize;
    u32 uCSize;
    u16 nameLength;
    u16 FieldLength;
} __attribute__((__packed__)) LFHeader;

typedef struct _CDHeader //46 bytes
{
    u32 PK;
    u16 version;
    u16 verion2extract;
    u16 bitFlag;
    u16 method;
    u16 time;
    u16 date;
    u32 crc32;
    u32 cSize;
    u32 uCSize;
    u16 nameLength;
    u16 FieldLength;
    u16 commentLength;
    u16 diskNum;
    u16 internalFileAttribute;
    u32 externalFileAttribute;
    u32 relativeOffset;
} __attribute__((__packed__)) CDHeader;

i32 slashcount(char a[], i32 len);

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Too much arguments\n");
        return 0;
    }
    char filename[30] = {0};
    strncpy(filename, argv[1], sizeof(filename));
    char *ptr = NULL;
    if ((ptr = strrchr(filename, '.')) != NULL)
    {
        if (strcmp(ptr, ".zip") != 0)
        {
            printf("Input file is not a zip file\n");
            return 0;
        }
    }
    else
    {
        printf("Input file is not a zip file\n");
        return 0;
    }

    FILE *zip = NULL;
    if ((zip = fopen(filename, "rw")) == NULL)
    {
        perror("Can't open this file ");
        return 0;
    }
    fseek(zip, 0, SEEK_END);
    u64 filesize = (unsigned long)ftell(zip);
    rewind(zip);
    while (1)
    {
        if (feof(zip))
            break;
        LFHeader read = {0};
        fread(&read, sizeof(LFHeader), 1, zip);
        //printf(" %d\n", read.PK);
        i32 isPK = 0;
        if (read.PK != 0x04034b50)
            continue;
        char a[300] = {0};
        //printf("%d\n", read.nameLength);
        fread(a, read.nameLength, 1, zip);
        char *slash = a;
        i32 tabcnt = slashcount(a, strlen(a));
        // printf("Before Parse %s\n", slash);
        if (strlen(a) != 0 && a[strlen(a) - 1] == '/')
            tabcnt--;
        for (i32 i = 0; i < tabcnt; i++)
        {
            if (i == 0)
                printf("+--");
            if (i != 0)
                printf("---");
            slash = strchr(slash, '/');
            slash++;
        }
        printf("%s\n", slash);
        if (!read.cSize)
            continue;
        u64 current = ftell(zip);
        if (current + read.cSize > filesize)
            break;
        fseek(zip, read.cSize, SEEK_CUR);
    }

    return 0;
}

i32 slashcount(char a[], i32 len)
{
    i32 cnt = 0;
    for (i32 i = 0; i < len; i++)
    {
        if (a[i] == '/')
            cnt++;
    }
    return cnt;
}