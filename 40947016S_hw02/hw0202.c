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
    char ex[12] = "";
    char frac[53] = "";
    printf("Please enter a floating -point number (\e[0;34mdouble\e[0m precision): ");
    fgets(a, 99, stdin);
    a[strcspn(a, "\n")] = '\0';
    double input = strtod(a, ptr);
    if (ptr != '\0')
    {
        printf("ERROR\n");
        return 0;
    }
    while (input)
    {
        printf("%d");
    }
}