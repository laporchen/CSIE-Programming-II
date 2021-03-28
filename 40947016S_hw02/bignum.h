#pragma once
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define i32 int32_t

#define bigSize 1024
typedef struct _sBigNum
{
    i32 sign; //0 for negative,1 for positive
    char number[bigSize];
} sBigNum;

void print(const sBigNum num);
int32_t set(sBigNum *pNum, char *str);
int32_t compare(const sBigNum num01, const sBigNum num02);
int32_t digits(const sBigNum num);
void add(sBigNum *pResult, const sBigNum num01, const sBigNum num02);
void subtract(sBigNum *pResult, const sBigNum num01, const sBigNum num02);
void multiply(sBigNum *pResult, const sBigNum num01, const sBigNum num02);
void divide(sBigNum *pQuotient, sBigNum *pRemainder, const sBigNum num01, const sBigNum num02);
int32_t power(sBigNum *pResult, int32_t n, int32_t k);
int32_t combine(sBigNum *pResult, int32_t n, int32_t k);
void removeLeadingZero(sBigNum *n);
sBigNum combineBig(sBigNum *r, sBigNum n, sBigNum k);
void print(const sBigNum num)
{
    //printf("%p", num.number);
    const sBigNum input = num;
    if (!input.sign)
    {
        printf("-");
    }
    char *ptr = strrchr(input.number, ' ');
    ptr++;
    //printf("%s\n", num.number);
    printf("%s\n", ptr);
    return;
}

int32_t set(sBigNum *pNum, char *str)
{
    char *space;
    if (strchr(str, '-') != NULL)
    {
        pNum->sign = 0;
        /*space = strrchr(str, ' ');
        if (space != NULL)
            str += space - str;*/
        str++;
    }
    else
    {
        /*space = strrchr(str, ' ');
        if (space != NULL)
        str += space - str;*/
        pNum->sign = 1;
    }
    i32 len = strlen(str);
    i32 offset = bigSize - len - 1;
    memset(pNum->number, ' ', bigSize - 1);
    pNum->number[bigSize - 1] = '\0';
    for (i32 i = 0; i < bigSize; i++)
    {
        if (*(str + i) == '\0')
            break;
        pNum->number[i + offset] = *(str + i);
    }
}

int32_t compare(const sBigNum num01, const sBigNum num02)
{
    if (num01.sign > num02.sign)
    {
        return 1;
    }
    else if (num01.sign < num02.sign)
    {
        return -1;
    }
    else if (!strcmp(num01.number, num02.number))
    {
        return 0;
    }
    else
    {
        if (num01.sign == 1)
        {
            if (digits(num01) > digits(num02))
                return 1;
            else if (digits(num01) < digits(num02))
                return -1;
            else
            {
                char *a = strrchr(num01.number, ' ');
                a++;
                char *b = strrchr(num02.number, ' ');
                b++;
                while (1)
                {
                    if (*a > *b)
                    {
                        return 1;
                    }
                    else if (*a < *b)
                    {
                        return -1;
                    }
                    else
                    {
                        a++;
                        b++;
                    }
                }
            }
        }
        else
        {
            if (digits(num01) > digits(num02))
                return -1;
            else if (digits(num01) < digits(num02))
                return 1;
            else
            {
                char *a = strrchr(num01.number, ' ');
                a++;
                char *b = strrchr(num02.number, ' ');
                b++;
                while (1)
                {
                    if (*a > *b)
                    {
                        return -1;
                    }
                    else if (*a < *b)
                    {
                        return 1;
                    }
                    else
                    {
                        a++;
                        b++;
                    }
                }
            }
        }
    }
}
int32_t digits(const sBigNum num)
{
    char *ptr = strrchr(num.number, ' ');
    ptr++;
    return strlen(ptr);
}
void add(sBigNum *pResult, const sBigNum num01, const sBigNum num02)
{
    if (num01.sign == num02.sign)
    {
        char result[bigSize];
        memset(result, ' ', bigSize - 1);
        result[bigSize - 1] = '\0';
        i32 c = 0;
        for (i32 i = bigSize - 2; i > 0; i--)
        {
            if ((num01.number[i] == ' ' && num02.number[i] == ' ') && c == 0)
            {

                break;
            }
            if (num01.number[i] == ' ' && num02.number[i] == ' ')
                result[i] = c + '0';
            else if (num01.number[i] == ' ')
                result[i] = num02.number[i] + c;
            else if (num02.number[i] == ' ')
                result[i] = num01.number[i] + c;
            else
                result[i] = num01.number[i] + num02.number[i] + c - '0';
            c = 0;
            if (result[i] > '9')
            {
                c = 1;
                result[i] -= 10;
            }
        }
        char *start;
        start = strrchr(result, ' ');
        start++;
        if (num01.sign == 0)
        {
            *strrchr(result, ' ') = '-';
            start = strrchr(result, '-');
        }

        set(pResult, start);
    }
    else
    {
        if (num01.sign == 0)
        {
            sBigNum sub = num01;
            sub.sign = 1;
            subtract(pResult, num02, sub);
        }
        else
        {
            sBigNum sub = num02;
            sub.sign = 1;
            subtract(pResult, num01, sub);
        }
    }
    return;
}
void subtract(sBigNum *pResult, const sBigNum num01, const sBigNum num02)
{
    if (num01.sign == num02.sign)
    {
        char result[bigSize];
        i32 neg = 0;
        memset(result, ' ', bigSize - 1);
        result[bigSize - 1] = '\0';
        sBigNum n1, n2;
        if (compare(num01, num02) == 0)
        {
            set(pResult, "0");
            return;
        }
        else if (digits(num01) > digits(num02))
        {
            n1 = num01;
            n2 = num02;
            if (n1.sign == 0)
                neg = 1;
            else
                neg = 0;
        }
        else if (digits(num01) < digits(num02))
        {
            n2 = num01;
            n1 = num02;
            if (n1.sign == 0)
                neg = 0;
            else
                neg = 1;
        }
        else
        {
            n1 = num01;
            n2 = num02;
            if (compare(n1, n2) == -1)
            {
                sBigNum tmp = n2;
                if (n1.sign == 0)
                {
                    neg = 0;
                }
                else
                {
                    neg = 1;
                    n2 = n1;
                    n1 = tmp;
                }
            }
            else
            {
                if (n1.sign == 0)
                    neg = 1;
                else
                    neg = 0;
            }
        }
        i32 c = 0;
        for (i32 i = bigSize - 2; i > 0; i--)
        {
            if ((n1.number[i] == ' ' && n2.number[i] == ' ') && c == 0)
                break;
            if (n1.number[i] == ' ' && n2.number[i] == ' ')
                result[i] = c + '0';
            else if (n2.number[i] == ' ')
                result[i] = n1.number[i] + c;
            else
                result[i] = n1.number[i] - n2.number[i] + c + '0';
            c = 0;
            if (result[i] < '0')
            {
                c = -1;
                result[i] += 10;
            }
        }
        char *start;
        start = strrchr(result, ' ');
        start++;
        if (neg)
        {
            *strrchr(result, ' ') = '-';
            start = strrchr(result, '-');
        }
        set(pResult, start);
    }
    else
    {
        if (num02.sign == 0)
        {
            sBigNum ad = num02;
            ad.sign = 1;
            add(pResult, num01, ad);
        }
        if (num01.sign == 0)
        {
            sBigNum ad = num01;
            ad.sign = 0;
            add(pResult, num02, ad);
        }
    }
    removeLeadingZero(pResult);
}
void multiply(sBigNum *pResult, const sBigNum num01, const sBigNum num02)
{
    sBigNum zero;
    set(&zero, "0");
    if (compare(num01, zero) == 0 || compare(num02, zero) == 0)
    {
        set(pResult, "0");
        return;
    }
    char result[bigSize];
    memset(result, '0', bigSize - 1);
    result[bigSize - 1] = '\0';
    sBigNum n1, n2;
    if (digits(num01) > digits(num02))
    {
        n1 = num01;
        n2 = num02;
    }
    else
    {
        n2 = num01;
        n1 = num02;
    }
    i32 neg;
    if (num01.sign == num02.sign)
        neg = 0;
    else
        neg = 1;
    i32 digit1, digit2;
    i32 len1 = bigSize - (strrchr(n1.number, ' ') - n1.number + 2);
    i32 len2 = bigSize - (strrchr(n2.number, ' ') - n2.number + 2);
    i32 maxindex = bigSize;

    i32 a, b, index;

    for (i32 q = len1; q > 0; q--)
    {
        digit1 = len1 - q + 1;
        a = n1.number[bigSize - digit1 - 1] - '0';
        for (i32 p = len2; p > 0; p--)
        {
            digit2 = len2 - p + 1;
            index = bigSize - (digit1 + digit2);

            b = n2.number[bigSize - digit2 - 1] - '0';
            i32 test = a * b;
            i32 c = test / 10;
            result[index] += test % 10;
            result[index - 1] += c;

            if (result[index] > '9')
            {
                i32 shift = (result[index] - '0') / 10;
                result[index] -= 10 * shift;
                result[index - 1] += shift;
            }
            if (index < maxindex)
                maxindex = index;
        }
    }

    for (i32 i = 0; i < maxindex - 1; i++)
        result[i] = ' ';
    char *start;
    start = strrchr(result, ' ');
    start++;
    set(pResult, start);
    removeLeadingZero(pResult);
    if (neg)
    {
        pResult->sign = 0;
    }
    return;
}
void divide(sBigNum *pQuotient, sBigNum *pRemainder, const sBigNum num01, const sBigNum num02)
{
    i32 neg = 0;
    sBigNum max, two, base, tmp, q, one, zero, nego;
    sBigNum n1 = num01;
    sBigNum n2 = num02;
    set(&two, "2");
    set(&q, "1");
    set(&one, "1");
    set(&zero, "0");
    set(&nego, "-1");
    if (num01.sign == num02.sign)
        neg = 1;
    if (compare(num01, num02) == -1)
    {
        set(pQuotient, "0");
        set(pRemainder, n1.number);
        return;
    }
    else if (compare(num01, num02) == 0)
    {
        set(pQuotient, "1");
        set(pRemainder, "0");
        return;
    }
    else if (compare(num02, one) == 0)
    {
        set(pQuotient, n1.number);
        set(pRemainder, "0");
        return;
    }
    else if (compare(num02, zero) == 0)
    {
        printf("Divider can't be zero. Aborting divide()\n");
        return;
    }
    else if (compare(num02, nego) == 0)
    {
        set(pQuotient, n1.number);
        if (n1.sign == 1)
            pQuotient->sign = 0;
        else
            pQuotient->sign = 1;
        set(pRemainder, "0");
        return;
    }

    i32 mul = 1, adder = 0;

    max = num02;
    base = num02;
    while (1)
    {
        tmp = max;
        if (mul)
        {
            sBigNum qtmp = q;
            multiply(&max, tmp, two);
            multiply(&q, q, two);
            if (compare(num01, max) == -1)
            {
                q = qtmp;
                max = tmp;
                adder = 1;
                mul = 0;
            }
        }
        else if (adder)
        {
            sBigNum qtmp = q;
            add(&max, max, base);
            add(&q, q, one);
            if (compare(num01, max) == -1)
            {
                max = tmp;
                q = qtmp;
                break;
            }
        }
        else
            break;
    }
    set(pQuotient, q.number);
    sBigNum remain;
    subtract(&remain, num01, max);
    set(pRemainder, remain.number);
    if (!neg)
        pQuotient->sign = 0;
    removeLeadingZero(pRemainder);
    removeLeadingZero(pQuotient);
    return;
}
int32_t power(sBigNum *pResult, int32_t n, int32_t k)
{
    sBigNum base;
    char nchar[20];
    memset(nchar, ' ', 18);
    nchar[19] = '\0';
    i32 index = 18;
    while (n)
    {
        nchar[index] = n % 10 + '0';
        n /= 10;
        index--;
    }
    char *start = strrchr(nchar, ' ');
    start++;
    set(&base, start);
    set(pResult, "1");
    while (k != 0)
    {
        if (k & 1)
            multiply(pResult, *pResult, base);
        multiply(&base, base, base);
        k >>= 1;
    }
}
int32_t combine(sBigNum *pResult, int32_t n, int32_t k)
{
    sBigNum pn, pk;
    set(pResult, "0");
    char nchar[20], kchar[20];
    memset(nchar, ' ', 18);
    memset(kchar, ' ', 18);
    nchar[19] = '\0';
    kchar[19] = '\0';
    i32 index = 18;
    while (n)
    {
        nchar[index] = n % 10 + '0';
        n /= 10;
        index--;
    }
    char *start = strrchr(nchar, ' ');
    start++;
    set(&pn, start);
    index = 18;
    while (k)
    {
        kchar[index] = k % 10 + '0';
        k /= 10;
        index--;
    }
    start = strrchr(kchar, ' ');
    start++;
    set(&pk, start);
    combineBig(pResult, pn, pk);
    return 0;
}

void removeLeadingZero(sBigNum *n)
{
    sBigNum zero;
    set(&zero, "0");
    if (compare(*n, zero) == 0)
        return;
    for (i32 i = 0; i < bigSize; i++)
    {
        if (n->number[i] != ' ' && n->number[i] != '-' && n->number[i] != '0')
            return;
        else
            n->number[i] = ' ';
    }
}
sBigNum combineBig(sBigNum *r, sBigNum n, sBigNum k)
{
    static sBigNum zero, one;
    set(&zero, "0");
    set(&one, "1");
    if (compare(n, zero) == 0)
        return zero;
    if (compare(n, k) == 0)
        return one;
    if (compare(one, k) == 0)
        return n;
    sBigNum tk = k, tn = n;
    sBigNum pk, pn;
    set(&pk, "0");
    set(&pn, "0");
    subtract(&tn, tn, one);
    subtract(&tk, tk, one);
    add(r, combineBig(&pn, tn, tk), combineBig(&pk, tn, k));
    return *r;
}