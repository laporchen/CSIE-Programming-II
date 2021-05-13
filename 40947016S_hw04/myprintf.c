#include "myprintf.h"
#define i32 int32_t
int myprintf(const string re, ...)
{
    i32 len = strlen(re);
    i32 printCnt = 0;
    for (int i = 0; i < len; i++)
        if (*(re + i) == '%')
            printCnt++;
    va_list ap;
    va_start(ap, re);
    int32_t arg1;
    uint32_t arg2;
    string output;
    char *arg3;
    for (i32 i = 0; i < len; i++)
    {
        if (*(re + i) == '\0')
            break;
        if (*(re + i) == '%')
        {
            memset(output, 0, sizeof(output));
            char type = *(re + i + 1);
            re++;
            if (type == 'i' || type == 'd')
            {
                arg1 = va_arg(ap, int32_t);
                int2str(output, arg1);
                for (i32 i = 0; i < strlen(output); i++)
                {
                    fputc(*(output + i), stdout);
                }
            }
            else if (type == 'x')
            {
                arg2 = va_arg(ap, uint32_t);
                u2h(output, arg2, 'x');
                for (i32 i = 0; i < strlen(output); i++)
                {
                    fputc(*(output + i), stdout);
                }
            }
            else if (type == 'X')
            {
                arg2 = va_arg(ap, uint32_t);
                u2h(output, arg2, 'X');
                for (i32 i = 0; i < strlen(output); i++)
                {
                    fputc(*(output + i), stdout);
                }
            }
            else if (type == 's')
            {
                arg3 = va_arg(ap, char *);
                for (i32 i = 0; i < strlen(arg3); i++)
                {
                    fputc(*(arg3 + i), stdout);
                }
            }
        }
        else
        {
            fputc(*(re + i), stdout);
        }
    }
}
void int2str(string s, i32 n)
{
    i32 i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return;
}
void u2h(string s, uint32_t n, char mode)
{
    i32 i;
    if (mode == 'X')
    {
        do
        {
            s[i++] = (n % 16) % 10 + '0' + ((n % 16) / 10) * ('A' - '0');
        } while ((n /= 16) > 0);
    }
    else
    {
        do
        {
            s[i++] = (n % 16) % 10 + '0' + ((n % 16) / 10) * ('a' - '0');
        } while ((n /= 16) > 0);
    }
    reverse(s);
    return;
}
void reverse(string s)
{
    int i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    return;
}