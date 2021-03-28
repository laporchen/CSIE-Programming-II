
#include "hw0103.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#define i32 int32_t

int main()
{
    char *ptrtmp = pStr01;
    pStr01 = pStr02;
    pStr02 = ptrtmp;
    print_answers();
}