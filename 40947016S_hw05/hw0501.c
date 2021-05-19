#include "string.h"
#include "getopt.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "stdint.h"

#define i32 int32_t
#define u32 int32_t
#define u8 uint8_t

#define b1 63 //00111111
#define b2 48 //00110000
#define b3 15 //00001111
#define b4 60 //00111100
#define b5 3  //00000011

#define o1 252 //11111100
#define o2 3   //00000011
#define o3 240 //11110000
#define o4 15  //00001111
#define o5 192 //11000000
#define o6 63  //00111111
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/', '='};

struct option long_options[] =
    {
        {"enc", 1, NULL, 'e'},
        {"dec", 1, NULL, 'd'},
        {"output", 1, NULL, 'o'},
        {"help", 0, NULL, 'h'},
        {0, 0, 0, 0},
};

void encrypt(char[], char[]);
void decrypt(char[], char[]);
int main(i32 argc, char *argv[])
{
    i32 c = -1, help = 0, mode = -1, terminate = 0, index; //mode 1 decrypt 0 encrypt
    char fileName[100] = {0}, outputName[100] = {0};
    while ((c = getopt_long(argc, argv, "e:d:o:h", long_options, &index)) != -1)
    {
        switch (c)
        {
        case 'h':
            help = 1;
            break;
        case 'e':
            mode = 0;
            if (optarg)
                strncpy(fileName, optarg, sizeof(fileName));
            else
                terminate = 1;
            break;
        case 'd':
            mode = 1;
            if (optarg)
                strncpy(fileName, optarg, sizeof(fileName));
            else
                terminate = 1;
            break;
        case 'o':
            if (optarg)
                strncpy(outputName, optarg, sizeof(outputName));
            else
                terminate = 1;
            break;
        case '?':
            terminate = 1;
            break;
        default:
            terminate = 1;
            break;
        }
    }
    if (help)
    {
        printf("./hw0501 [options]\n\t-e, --enc Encode a file to a text file.\n\t-d, --dec Decode a text file to a file.\n\t-o, --output Output file name.\n");
        return 0;
    }
    if (terminate)
    {
        return 0;
    }

    if (mode)
    {
        decrypt(fileName, outputName);
    }
    else
    {
        encrypt(fileName, outputName);
    }
    return 0;
}

void encrypt(char filename[], char out[])
{
    FILE *input = NULL, *output = NULL;
    if ((input = fopen(filename, "r")) == NULL || (output = fopen(out, "w")) == NULL)
    {
        perror("Something is wrong:");
        return;
    }
    while (1)
    {
        uint8_t read[3] = {0};
        u8 cnt = fread(read, sizeof(u8), 3, input);
        if (feof(input))
            break;
        uint8_t bit[4] = {0};
        if (cnt == 3)
        {
            bit[0] = (read[0] >> 2) & b1;
            bit[1] = (((read[0] << 4) & b2) | ((read[1] >> 4) & b3));
            bit[2] = (((read[1] << 2) & b4) | ((read[2] >> 6) & b5));
            bit[3] = ((read[2]) & b1); //00010110 22
        }
        else if (cnt == 2)
        {
            bit[0] = (read[0] >> 2) & b1;
            bit[1] = (((read[0] << 4) & b2) | ((read[1] >> 4) & b3));
            bit[2] = (((read[1] << 2) & b4) | ((read[2] >> 6) & b5));
            bit[3] = 64;
        }
        else if (cnt == 1)
        {
            bit[0] = (read[0] >> 2) & b1;
            bit[1] = (((read[0] << 4) & b2) | ((read[1] >> 4) & b3));
            bit[2] = 64;
            bit[3] = 64;
        }
        char a[5] = {encoding_table[bit[0]], encoding_table[bit[1]], encoding_table[bit[2]], encoding_table[bit[3]]};
        fwrite(a, sizeof(u8), strlen(a), output);
    }
    fclose(input);
    fclose(output);
    return;
}
void decrypt(char filename[], char out[])
{
    FILE *input = NULL, *output = NULL;
    if ((input = fopen(filename, "r")) == NULL || (output = fopen(out, "w")) == NULL)
    {
        perror("Something is wrong:");
        return;
    }
    while (1)
    {
        uint8_t read[4] = {0};

        u8 cnt = fread(read, sizeof(u8), 4, input);
        if (feof(input))
            break;
        uint8_t outs[4] = {0};
        char result[3] = {0};
        i32 index = 0;
        for (i32 i = 0; i < cnt; i++)
        {
            for (i32 j = 0; j < 65; j++)
            {
                if (read[i] == encoding_table[j])
                {
                    outs[index] = j;
                    if(outs[index] == 64)
                        outs[index] = 0;
                    index++;
                    break;
                }
            }
        }
        result[0] = ((outs[0] << 2) & o1) | ((outs[1] >> 4) & o2);
        result[1] = ((outs[1] << 4) & o3) | ((outs[2] >> 2) & o4);
        result[2] = ((outs[2] << 6) & o5) | ((outs[3]) & o6);
        //printf("%d %d %d\n", result[0], result[1], result[2]);
        fwrite(result, 1,sizeof(result), output);
    }
    fclose(output);
    fclose(input);
    return;
}