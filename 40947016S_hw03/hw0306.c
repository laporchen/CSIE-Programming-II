#include <stdint.h>
#include <stdio.h>

void max(int32_t a, int32_t b)
{
    int32_t result = a ^ (-(a < b) & (a ^ b));
    printf("%d is bigger\n", result);
    return;
}

int main()
{
    int32_t a = 224, b = 3;
    printf("Give me an integer : ");
    scanf("%d", &a);
    printf("Give me another integer : ");
    scanf("%d", &b);
    max(a, b);
    return 0;
}