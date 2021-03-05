#pragma once
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#define i32 int32_t

char *mystrchr(const char *s, int c)
{
    char *ptr = NULL;
    int index = 0;
    while (*(s + index) != '\0')
    {
        if (*(s + index) == c)
        {
            ptr = (char *)(s + index);
            break;
        }
        index++;
    }
    return ptr;
}
char *mystrrchr(const char *s, int c)
{
    char *ptr = NULL;
    i32 index = 0;
    while (*(s + index) != '\0')
    {
        if (*(s + index) == c)
        {
            ptr = (char *)(s + index);
        }
        index++;
    }
    return ptr;
}
size_t mystrspn(const char *s, const char *accept)
{
    i32 count = 0;
    while (*(s + count) != '\0')
    {
        i32 i = 0;
        int found = 0;
        while (*(accept + i) != '\0')
        {
            if (*(s + count) == *(accept + i))
            {
                found = 1;
                break;
            }
            i++;
        }
        if (found)
        {
            count++;
        }
        else
        {
            break;
        }
    }
    return count;
}
size_t mystrcspn(const char *s, const char *reject)
{
    i32 count = 0;
    while (*(s + count) != '\0')
    {
        i32 i = 0;
        int found = 0;
        while (*(reject + i) != '\0')
        {
            if (*(s + count) == *(reject + i))
            {
                found = 1;
                break;
            }
            i++;
        }
        if (found)
        {
            break;
        }
        else
        {
            count++;
        }
    }
    return count;
}
char *mystrpbrk(const char *s, const char *accept)
{
    char *ptr = NULL;
    i32 count = 0;
    while (*(s + count) != '\0')
    {
        i32 i = 0;
        int found = 0;
        while (*(accept + i) != '\0')
        {
            if (*(s + count) == *(accept + i))
            {
                found = 1;
                break;
            }
            i++;
        }
        //printf("count = %d,s is %c\n", count, *(s + count));
        count++;
        if (found)
        {
            ptr = (char *)(s + count - 1);
            return ptr;
        }
    }
    return NULL;
}
char *mystrstr(const char *haystack, const char *needle)
{
    char *ptr = NULL;
    i32 count = 0;
    while (*(haystack + count) != '\0')
    {
        i32 diff = 0;
        i32 i = 0;
        while (*(needle + i) != '\0' && *(haystack + count + i) != '\0')
        {
            //printf("%c %c ", *(needle + i), *(haystack + count + i));
            if (*(needle + i) != *(haystack + count + i))
            {
                diff = 1;
                break;
            }
            i++;
        }
        if (diff)
        {
            count++;
            continue;
        }
        else
        {
            ptr = (char *)(haystack + count);
            return ptr;
        }
    }
    return NULL;
}
char *mystrtok(char *str, const char *delim)
{
    static char *ptr = NULL;
    if (str == NULL)
    {
        i32 count = 1;
        //printf("%c \n", *(ptr + count));
        if (*(ptr) == '\0')
        {
            ptr = NULL;
            return NULL;
        }
        while (*(ptr + count) != '\0')
        {
            i32 i = 0;
            while (*(delim + i) != '\0')
            {
                if (*(ptr + count) == *(delim + i))
                {
                    *(ptr + count) = '\0';
                    char *tmp = (char *)(ptr);
                    ptr = (char *)(ptr + count + 1);
                    return tmp;
                }
                i++;
            }

            count++;
        }
        char *tmp = (char *)(ptr);
        ptr = (char *)(ptr + count);
        return tmp;
    }
    else
    {
        ptr = str;
        i32 count = 0;
        while (*(str + count) != '\0')
        {
            i32 i = 0;
            while (*(delim + i) != '\0')
            {
                if (*(str + count) == *(delim + i))
                {
                    *(str + count) = '\0';
                    ptr = (char *)(str + count + 1);
                    return str;
                }
                i++;
            }
            count++;
        }
        return NULL;
    }
}