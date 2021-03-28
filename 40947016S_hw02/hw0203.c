#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#define i32 int32_t
#define b1 byte.bits.charb1
#define b2 byte.bits.charb2
#define b3 byte.bits.charb3
#define b4 byte.bits.charb4
#define b5 byte.bits.charb5
#define b6 byte.bits.charb6
#define b7 byte.bits.charb7
#define b8 byte.bits.charb8

typedef union
{
    struct
    {
        unsigned charb1 : 1;
        unsigned charb2 : 1;
        unsigned charb3 : 1;
        unsigned charb4 : 1;
        unsigned charb5 : 1;
        unsigned charb6 : 1;
        unsigned charb7 : 1;
        unsigned charb8 : 1;
    } bits;
    unsigned charbyte;
} uByte;

i32 bits2num(char a[8], i32 *mod, uByte byte);

int main()
{
    uByte byte;
    char input[8] = "";
    printf("Please enter a byte (0-255): ");
    fgets(input, 4, stdin);
    char *ptr;
    i32 check = strtol(input, &ptr, 10);
    if ((check < 0 || check > 255) || (*ptr != '\n' && *ptr != '\0'))
    {
        //printf("%c\n", *ptr);
        printf("ERROR\n");
        return 0;
    }
    byte.charbyte = check;
    i32 flip;
    char buf[64];
    do
    {

        printf("Data: %d %d%d%d%d%d%d%d%d\n", byte.charbyte, b8, b7, b6, b5, b4, b3, b2, b1);
        printf("Flip bit (1-8, 0: exit): ");
        scanf("%d", &flip);
        while (flip < 0 || flip > 8)
        {
            printf("Invalid Input. Try again.");
            scanf("%d", &flip);
        }
        if (flip > 0 && flip < 9)
        {
            if (flip == 8)
                b1 = !b1;
            if (flip == 7)
                b2 = !b2;
            if (flip == 6)
                b3 = !b3;
            if (flip == 5)
                b4 = !b4;
            if (flip == 4)
                b5 = !b5;
            if (flip == 3)
                b6 = !b6;
            if (flip == 2)
                b7 = !b7;
            if (flip == 1)
                b8 = !b8;
        }
    } while (flip != 0);

    printf("Bye\n");
    return 0;
}
