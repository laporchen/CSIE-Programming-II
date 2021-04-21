#include <stdint.h>
#include <stdio.h>

void max(int32_t a, int32_t b)
{
    int32_t result = a ^ (-(a < b) & (a ^ b));
    printf("%d\n", result);
    return;
}

int main()
{
    int32_t a = 224, b = 3;
    max(a, b);
    return 0;
}