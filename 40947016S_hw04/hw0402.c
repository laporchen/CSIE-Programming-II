#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include <getopt.h>
#include <unistd.h>
#define i32 int32_t
#define _R read[0]
typedef struct _var
{
    char original[32];
    char new[32];
} var;
struct option long_options[] =
    {
        {"help", 0, NULL, 'h'},
        {"level", 1, NULL, 'l'},
        {"input", 1, NULL, 'i'},
        {"ouput", 1, NULL, 'o'},
        {0, 0, 0, 0},
};
typedef char string[300];
const string keyword[2] = {"int ", "char "};
i32 varCount = 0;
FILE *buf = NULL, *buf2 = NULL;
string bufferFileName = "hw0402buf_X2323F7.buf";
string bufferFileName2 = "hw0402buf_X4422F7.buf";
int openFile(char *path, FILE *fileptr, char *mode);
void obfusion(string a);
void printHelpMenu();
void level1(FILE *i);
void level2(FILE *i);
void level3(FILE *i);
void level4(FILE *i);
void (*func[4])(FILE *i) = {level1, level2, level3, level4};
int main(int argc, char *argv[])
{
    srand(time(NULL));
    i32 index, c = -1;
    FILE *write = NULL, *read = NULL;
    string writeFileName = {0};
    string readFileName = {0};
    i32 help = 0, level = -1, terminate = 0, inputName = 0, outputName = 0;
    while ((c = getopt_long(argc, argv, "hl:i:o:", long_options, &index)) != -1)
    {
        switch (c)
        {
        case 'h':
            help = 1;
            break;
        case 'l':
            level = strtol(optarg, NULL, 10);
            break;
        case 'i':
            inputName = 1;
            strncpy(readFileName, optarg, 29);
            break;
        case 'o':
            strncpy(writeFileName, optarg, 29);
            outputName = 1;
            break;
        case '?':
            printf("Argument is not defined\n");
            terminate = 1;
            break;
        default:
            printf("Argument is not defined\n");
            terminate = 1;
            break;
        }
    }
    if (help)
    {
        printHelpMenu();
        return 0;
    }
    if (terminate || !inputName || !outputName)
    {
        printf("Something is wrong\n");
        return 0;
    }
    if ((write = fopen(writeFileName, "w")) == NULL)
    {
        printf("Failed to open file %s\n", writeFileName);
        return 0;
    }
    if ((read = fopen(readFileName, "r")) == NULL)
    {
        printf("Failed to open file %s\n", readFileName);
        return 0;
    }

    if (level > 4 || level < 1)
    {
        printf("%d is not a valid level\n", level);
        return 0;
    }
    printf("%s\n%s\n", readFileName, writeFileName);
    func[level - 1](read);
    buf = fopen(bufferFileName, "r");
    while (1)
    {
        if (feof(buf))
            break;
        char readByte[1024] = {0};
        i32 cnt = fread(readByte, 1, 1024, buf);
        fwrite(readByte, cnt, 1, write);
    }
    fclose(write);
    fclose(buf);
    remove(bufferFileName);
    return 0;
}

void level1(FILE *i)
{
    buf = fopen(bufferFileName, "w");
    int inString = 0, define = 0;
    uint8_t space[1] = {' '};
    uint8_t nl[1] = {'\n'};
    while (1)
    {
        if (feof(i))
            break;
        uint8_t read[1];
        if (!fread(&read, 1, 1, i))
            break;
        if ((_R == '#' && !define))
            define = 1;
        else if ((_R == '\n') && define)
            define = 0;
        if ((_R == '\"' || _R == '\'') && inString)
        {
            inString = 0;
        }
        else if (_R == '\"' || _R == '\'')
            inString = 1;
        if (_R == ' ' && !inString)
        {
            i32 r = rand() % 10;
            for (i32 i = 0; i < r; i++)
            {
                if (rand() % 5)
                {
                    fwrite(&space, 1, 1, buf);
                }
                else
                {
                    if (!define)
                        fwrite(&nl, 1, 1, buf);
                }
            }
        }
        fwrite(&read, 1, 1, buf);
    }
    fclose(buf);
    fclose(i);
    return;
}
void level2(FILE *i)
{
    buf2 = fopen(bufferFileName2, "w");

    while (1)
    {
        if (feof(i))
            break;
        string readline = {0};
        while (1)
        {
            char c = fgetc(i);
            strncat(readline, &c, 1);
            if (c == '(' || c == ')' || c == ';')
            {
                break;
            }
        }
        char *ptr = NULL;
        while ((ptr = strstr(readline, keyword[0])) != NULL)
        {
        }
        fwrite(readline, sizeof(readline), 1, buf2);
    }

    fclose(buf);
    fclose(buf2);
    fclose(i);
    buf2 = fopen(bufferFileName2, "r");
    level1(buf2);
    return;
}
void level3(FILE *i)
{
    buf = fopen(bufferFileName2, "w");

    fclose(buf);
    fopen(bufferFileName, "r");
    level2(buf);
    return;
}
void level4(FILE *i)
{
    buf2 = fopen(bufferFileName2, "w");

    fclose(buf2);
    fopen(bufferFileName2, "r");
    level3(buf2);
}
void printHelpMenu()
{
    printf("./hw0402 -l [options] -i [input file] -o [output file]\n./hw0402 -h\n./hw0402 --help\n");
    return;
}
void obfusion(string a)
{
    char generate[17] = {0};
    if (rand() % 2)
        generate[0] = 'a' + rand() % 26;
    else
        generate[0] = 'A' + rand() % 26;
    for (i32 i = 1; i < 16; i++)
    {
        if (rand() % 2)
        {
            if (rand() % 2)
                generate[i] = 'a' + rand() % 26;
            else
                generate[i] = 'A' + rand() % 26;
        }
        else
        {
            generate[i] = '0' + rand() % 10;
        }
    }
    strncpy(a, generate, sizeof(char) * strlen(a));

    return;
}