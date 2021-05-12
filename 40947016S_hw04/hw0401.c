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
#define block 4096
typedef struct _header
{
    u32 offset;
    u32 fileorder;
    u32 size;
} __attribute__((__packed__)) header;

struct option long_options[] =
    {
        {"split", 1, NULL, 's'},
        {"recover", 1, NULL, 'r'},
        {"size", 2, NULL, 'z'},
        {0, 0, 0, 0},
};
typedef char string[200];
const char *helpMenu = "Split:\n./hw0401 -s [file] --size [Small File Size]\nThe default small file size is 1000 bytes.\nRecover :\n./ hw0401 - r[output file][small files] 10 The input small files may not be in order.";

void recover(string f, string s[], i32 cnt);
void split(string f, i32 size);
void printMenu()
{
    printf("%s\n", helpMenu);
    return;
}
int main(i32 argc, char *argv[])
{
    i32 c = -1, index = 0, help = 0, mode = -1, terminate = 0, size = 1000, filecnt = 0, arg = 0;
    i32 getsize = 0;
    string fileName;
    string input[100];
    while ((c = getopt_long(argc, argv, "s:r:hz::", long_options, &index)) != -1)
    {
        switch (c)
        {
        case 'h':
            help = 1;
            break;
        case 's':
            mode = 0;
            if (optarg)
                strncpy(fileName, optarg, sizeof(fileName));
            break;
        case 'r':
            mode = 1;
            arg = index;
            if (optarg)
                strncpy(fileName, optarg, sizeof(fileName));
            break;
        case 'z':
            getsize = 1;
            break;
        case '?':
            terminate = 1;
            break;
        default:
            terminate = 1;
            break;
        }
    }
    if (getsize)
    {
        for (i32 i = 0; i < argc; i++)
        {
            if (strncmp("--size", argv[i], sizeof(argv[i])))
            {
                if (i < argc - 1)
                {
                    size = strtol(argv[i + 1], NULL, 10);
                }
            }
        }
    }
    if (terminate)
        return 0;
    if (help)
    {
        printMenu();
        return 0;
    }
    if (mode == -1)
    {
        printf("No mode was selected\n");
        return 0;
    }
    if (mode)
    {
        for (i32 i = 0; i < argc; i++)
        {
            if (i == arg || i == arg + 1)
                continue;
            strncpy(input[filecnt], argv[i], sizeof((input[filecnt])));
            filecnt++;
        }
        recover(fileName, input, filecnt);
    }
    else
    {
        split(fileName, size);
    }
    return 0;
}

void recover(string f, string s[], i32 fcnt)
{
    FILE *w = fopen(f, "w");
    for (i32 i = 0; i < fcnt; i++)
    {
        FILE *r = NULL;
        if ((r = fopen(s[i], "r")) == NULL)
        {
            perror("File can't be open ");
            return;
        }
        header head;
        fread(&head, sizeof(head), 1, r);
        fseek(w, (head.fileorder - 1) * head.size, SEEK_SET);
        printf("%d\n", (head.fileorder - 1) * head.size);
        while (1)
        {
            if (feof(r))
                break;
            u8 read[block] = {0};

            u32 cnt = fread(read, 1, block, r);
            printf("%d\n", cnt);
            fwrite(read, cnt, 1, w);
            printf("write\n");
        }
    }
    return;
}
void split(string f, i32 size)
{
    printf("\n%d\n", size);
    FILE *s = NULL;
    i32 order = 1;
    i32 writeTime = size / block;
    i32 lastSize = size % block;
    if ((s = fopen(f, "r")) == NULL)
    {
        perror("File can't be open ");
        return;
    }
    while (1)
    {
        if (feof(s))
            break;
        string extend;
        string filename;
        strncpy(filename, f, sizeof(filename));
        snprintf(extend, sizeof(extend) - 1, ".%d", order);
        strcat(filename, extend);
        FILE *write = NULL;
        write = fopen(filename, "w");
        header head;
        head.fileorder = order;
        head.offset = sizeof(head);
        head.size = size;
        fwrite(&head, sizeof(head), 1, write);
        for (i32 i = 0; i < writeTime; i++)
        {
            if (feof(s))
                break;
            char read[block] = {0};
            u32 cnt = fread(read, 1, block, s);
            printf("%d\n", cnt);
            fwrite(&read, cnt, 1, write);
        }
        if (feof(s))
            break;
        u8 read[block] = {0};
        u32 cnt = fread(read, 1, lastSize, s);
        fwrite(read, cnt, 1, write);
        order++;
        fclose(write);
    }
    return;
}