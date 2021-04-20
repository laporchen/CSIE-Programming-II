#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <unistd.h>
#define i32 int32_t

#define p1 "\e[1;31m"
#define p2 "\e[1;32m"
#define p3 "\e[1;33m"
#define p4 "\e[1;34m"
#define p5 "\e[1;35m"
#define p6 "\e[1;36m"
#define p7 "\e[1;41m"
#define p8 "\e[1;45m"
#define reset "\e[0;0m"

typedef struct _lrc
{
    i32 color;
    char lyric[99];
    useconds_t time;
    useconds_t offset;
} lrc;

typedef struct _ppl
{
    char name[30];
} ppl;

int main()
{
    char *colors[8] = {p1, p2, p3, p4, p5, p6, p7, p8};
    printf("Open a LRC file: ");
    FILE *ly = NULL;
    char filename[100] = "0";
    fgets(filename, 99, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    char *dot = strrchr(filename, '.');
    if (!dot || strncmp(dot, ".lrc", 4) != 0)
    {
        printf("File is not a .lrc file!\n");
        return 0;
    }
    if ((ly = fopen(filename, "r")) == NULL)
    {
        perror("Couldn't open the file :");
        return 0;
    }

    i32 used = 0;     // store how many singers
    i32 singing = -1; // index the one is singing
    i32 cnt = 0;      // lyrics count
    lrc lyrics[300];  // store lyrics information
    memset(lyrics, 0, sizeof(lrc));
    char input[300];
    memset(input, 0, sizeof(input));
    ppl names[8];
    memset(names, 0, sizeof(ppl));
    i32 firstline = 1;
    while (!feof(ly))
    {
        fgets(input, 299, ly);
        while (firstline)
        {
            i32 len = strlen(input);
            //printf("%d\n", len);
            if ((input[2] - '0' >= 0 && input[2] - '0' <= 9) || input[len - 3] == ':')
            {
                firstline = 0;
                break;
            }

            else
            {
                fgets(input, 299, ly);
            }
        }
        if (strchr(input, '[') == NULL && strchr(input, ':') == NULL)
        {
            //printf("cnt=%d\n", cnt);
            continue;
        }

        if (strchr(input, '[') == NULL)
        {
            //printf("1\n");
            i32 found = 0;
            for (i32 i = 0; i < used + 1; i++)
                if (strncmp(names[i].name, input, 29) == 0)
                {
                    found = 1;
                    singing = i;
                    break;
                }
            if (!found)
            {
                //printf("%d -> %d\n", singing, used);
                strncpy(names[used].name, input, strlen(input));
                singing = used;
                //printf("%d\n\n", singing);
                used++;
            }
        }
        else
        {
            lyrics[cnt].time = 0;
            lyrics[cnt].color = singing;
            char *ptr = NULL;
            i32 time = 0;
            time += strtol(&input[1], &ptr, 10) * 60;
            ptr++;
            time += strtol(ptr, &ptr, 10);
            time *= 100;
            ptr++;
            time += strtol(ptr, &ptr, 10);
            ptr++;
            lyrics[cnt].time = time;
            lyrics[cnt].offset = time;
            if (cnt != 0)
                lyrics[cnt].time -= lyrics[cnt - 1].offset;
            strncpy(lyrics[cnt].lyric, ptr, strlen(ptr));
            cnt++;
        }
    }
    for (i32 i = 0; i < cnt; i++)
    {
        usleep(lyrics[i].time * 10000);
        //printf("%d\n", lyrics[i].color);
        printf("%s%s", colors[lyrics[i].color], lyrics[i].lyric);
    }
    printf(reset);
    return 0;
}
