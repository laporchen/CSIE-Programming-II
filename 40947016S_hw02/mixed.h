#pragma once
#include "stdint.h"
#include "stdio.h"

typedef struct _sMixedNumber
{
    int32_t integer;
    int32_t denominator;
    int32_t numerator;
} sMixedNumber;

int gcd(int32_t a, int32_t b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        gcd(b, a % b);
    }
}
int mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c);
// return -1 if invalid; otherwise , return 0.
int mixed_print(const sMixedNumber number);
// in the form of (a,b,c)
void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 + r2
void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 - r2
void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 * r2
void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 / r2

int mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c)
{
    pNumber->denominator = 0;
    pNumber->numerator = 0;
    pNumber->integer = 0;
    if (c == 0 && b != 0)
    {
        return -1;
    }
    else if ((c == 0 && b == 0) || (c != 0 && b == 0))
    {
        pNumber->denominator = 0;
        pNumber->numerator = 0;
        pNumber->integer = a;
    }
    else
    {
        pNumber->denominator = b % c;
        pNumber->numerator = c;
        pNumber->integer = a + b / c;
        int32_t g = gcd(pNumber->denominator, pNumber->numerator);
        pNumber->denominator /= g;
        pNumber->numerator /= g;
    }
    return 0;
}
int mixed_print(const sMixedNumber number)
{
    printf("(%d,%d,%d)\n", number.integer, number.denominator, number.numerator);
    return 0;
}
void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int32_t deno = r1.denominator * r2.numerator + r2.denominator * r1.numerator;
    int32_t num = r1.numerator * r2.numerator;
    mixed_set(pNumber, r1.integer + r2.integer, deno, num);
    return;
}
void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    sMixedNumber sub1 = r1;
    sub1.denominator = sub1.integer * sub1.numerator + sub1.denominator;
    sMixedNumber sub2 = r2;
    sub2.denominator = sub2.integer * sub2.numerator + sub2.denominator;
    sub2.denominator *= -1;
    sub1.integer = 0;
    sub2.integer = 0;
    //mixed_print(sub1);
    //mixed_print(sub2);
    mixed_add(pNumber, sub1, sub2);
    return;
}
void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int32_t deno = (r1.integer * r1.numerator + r1.denominator) * (r2.integer * r2.numerator + r2.denominator);
    int32_t num = r1.numerator * r2.numerator;
    printf("%d,%d\n", deno, num);
    mixed_set(pNumber, 0, deno, num);
    return;
}
void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    sMixedNumber div = r2;
    div.denominator += div.numerator * div.integer;
    div.integer = 0;
    int32_t tmp1 = div.numerator;
    div.numerator = div.denominator;
    div.denominator = tmp1;
    sMixedNumber tmp = r1;
    tmp.denominator = r1.numerator * r1.integer + r1.denominator;
    tmp.integer = 0;
    mixed_mul(pNumber, tmp, div);
    return;
}