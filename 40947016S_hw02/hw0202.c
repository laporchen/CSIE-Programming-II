#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#define i32 int32_t

int main()
{
    char a[100];
    char *ptr;
    char sign = '0';
    i32 ex = 1023;
    char cex[12];
    char frac[53] = "";
    char full[64];
    memset(full, ' ', 63);
    memset(cex, '0', 11);
    full[63] = '\0';
    cex[10] = '\0';
    printf("Please enter a floating -point number (\e[0;34mdouble\e[0m precision): ");
    fgets(a, 99, stdin);
    a[strcspn(a, "\n")] = '\0';
    double input = strtod(a, &ptr);
    i32 manti = (int)input;
    double fra = input - manti;
    if (*ptr != '\0')
    {
        printf("ERROR\n");
        return 0;
    }
    if (strrchr(a, '-') != NULL)
    {
        sign = '1';
        full[0] = '1';
        manti *= -1;
        input *= -1;
    }
    else
    {
        full[0] = '0';
    }

    i32 index = 0;
    while (1)
    {
        if (manti == 0)
            break;
        frac[index] = manti / 2;
        manti >> 1;
        index++;
    }
    i32 explen = strchr(frac, ' ') - frac;
    while (1)
    {
        fra *= 2;
        i32 dot = (int)fra;
        frac[index] = '0' + dot;
        if (dot)
            fra -= 1;
        index++;
        if (fra == 1.0)
            break;
    }
    printf("%s\n", frac);
}
