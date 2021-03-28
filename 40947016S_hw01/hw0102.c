#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define i32 int32_t

void printBefore(char *s, const char *k, i32 slen, i32 klen);
void printAfter(char *s, const char *k, const char *n, i32 slen, i32 nlen);
int main()
{
    char input[1025], key[129], new[129], re[1025];
    {
        printf("Please enter the original text:\n");
        fgets(input, 1024, stdin);
        printf("Key word:\n");
        fgets(key, 128, stdin);
        printf("New word:\n\e[0;31m");
        fgets(new, 128, stdin);
    }
    input[strcspn(input, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';
    new[strcspn(new, "\n")] = '\0';
    printBefore(input, key, strlen(input), strlen(key));
    printAfter(input, key, new, strlen(input), strlen(key));
    return 0;
}

void printBefore(char *s, const char *k, i32 slen, i32 klen)
{
    printf("\e[0m\nBefore:\n");
    char *a = s;
    i32 lencount = 0;
    while (*s != '\0')
    {
        char *ch = strstr(s, k);
        if (s == ch)
        {
            printf("\e[0;34m%s\e[0m", k);
            if (lencount + klen >= slen)
                break;
            s += klen;
        }
        else
        {
            printf("%c", *s);
            s++;
            lencount++;
        }
    }
    printf("\n");
    return;
}
void printAfter(char *s, const char *k, const char *n, i32 slen, i32 klen)
{
    printf("\e[0m\nAfter:\n");
    char *a = s;
    i32 lencount = 0;
    while (*s != '\0')
    {
        char *ch = strstr(s, k);
        if (s == ch)
        {
            printf("\e[0;31m%s\e[0m", n);
            if (lencount + klen >= slen)
                break;
            s += klen;
        }
        else
        {
            printf("%c", *s);
            s++;
            lencount++;
        }
    }
    printf("\n");
    return;
}