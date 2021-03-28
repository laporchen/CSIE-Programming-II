#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#define i32 int32_t

typedef struct _link
{
    char key[2048];
    char value[2048];
    struct _link *next;

} link;

void inJSON(char *i);

int main()
{
    char input[2049];
    printf("Please enter the JSON string:\n");
    fget(input, 2048, stdin);
    char *ptr = *input;
    while (*ptr != '\0')
    {
        if (*ptr == '{')
        {
            inJSON(*(ptr + 1));
        }
    }
    i32 choice = 1;
    char key[2049];
    while (!choice)
    {
        printf("Choice (0:Exit ,1:Get) : ");
        char *in;
        fgets(in, 2, stdin);
        choice = strtol(in, NULL, 10);
        if (choice != 1 && choice != 0)
        {
            printf("ERROR\n");
            break;
        }
        printf("Key : ");
        fgets(key, 2048, stdin);
        char *value;
        value = findKey();
        printf("Value : %s\n", value);
    }
    printf("Bye\n");
    return 0;
}

void inJSON(char *i)
{
    while (*i != '}')
    {
        char key = strchr(i, '"');
    }
}