#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <unistd.h>
#include "stdlib.h"
#define i32 int32_t
#define u32 uint32_t

int main(int argC, char *argV[])
{
    const char *command = "cat /proc/stat";
    FILE *stat = NULL;
    i32 lastSum = 0;
    i32 lastIdle = 0;
    while (1)
    {
        stat = popen(command, "r");
        if (stat == NULL)
        {
            printf("Error occured.\n");
            break;
        }
        char *lineptr = NULL;
        size_t buf = 300;
        lineptr = calloc(buf, sizeof(char));
        getline(&lineptr, &buf, stat);

        i32 sum = 0;
        i32 idle = 0;
        i32 index = 0;
        char *token = strtok(lineptr, " ");
        while (token != NULL)
        {
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                sum += strtol(token, NULL, 10);
                if (index == 3)
                    idle = strtol(token, NULL, 10);
                index++;
            }
        }
        long double usage = 100 - ((idle-lastIdle) * 100.0 / (sum-lastSum));
        printf("CPU usage : %.4Lf %%\n", usage);
        sleep(1);
        pclose(stat);
        printf("\e[1;1H\e[2J");
        lastIdle = idle;
        lastSum = sum;
    }

    return 0;
}