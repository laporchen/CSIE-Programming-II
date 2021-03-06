#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define i32 int32_t

i32 getCC(char);
int main()
{
    char s = 'K';
    printf("Please enter the hex string: ");
    i32 finished;
    size_t count = 1;
    i32 c = 0;
    while (s != '\0')
    {
        s = getchar();
        if (!(count % 2))
        {

            c += getCC(s);
            //printf("%d\n", c);
            if (getCC(s) == -1)
            {
                printf("ERROR. The string contains illegal character.\n");
                break;
            }
            if (c == 0)
            {
                break;
            }
            if (c < 32 || c > 126)
            {
                printf("ERROR. The string converts to unprintable character.\n");
                break;
            }
            printf("%c", c);
            c = 0;
        }
        else
        {
            c += getCC(s) * 16;
            if (getCC(s) == -1)
            {
                printf("ERROR. The string contains illegal character.\n");
                break;
            }
        }
        count++;
    }
    printf("\n");
    return 0;
}

i32 getCC(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return -1;
    }
}