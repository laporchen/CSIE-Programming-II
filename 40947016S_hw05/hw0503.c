#include "curl/curl.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "unistd.h"
#include "getopt.h"
#include "string.h"
#include "assert.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#define i32 int32_t
#define u32 uint32_t

typedef char string[300];
struct option long_options[] =
    {
        {"query", 1, NULL, 'q'},
        {"help", 0, NULL, 'h'},
        {0, 0, 0, 0},
};
void getQuery();
uint64_t getFDSize(i32 fd);
const char *bufferFile = "AFH5334B998C123AFF.buf";
int main(i32 argc, char *argv[])
{
    i32 c = -1, help = 0, terminate = 1, index; //mode 1 decrypt 0 encrypt
    char *urlWithKeyword = NULL;
    const char *url = "https://dblp.org/search?q=";
    u32 size = 0;
    while ((c = getopt_long(argc, argv, "q:h", long_options, &index)) != -1)
    {
        switch (c)
        {
        case 'h':
            help = 1;
            break;
        case 'q':
            if (optarg)
            {
                terminate = 0;
                size = strlen(optarg) + strlen("https://dblp.org/search?q=") + 3;
                urlWithKeyword = (char *)calloc(size, sizeof(char));
                strncpy(urlWithKeyword, "https://dblp.org/search?q=", strlen(url));
                strncat(urlWithKeyword, optarg, strlen(optarg));
                char *ptr = NULL;
                while((ptr = strchr(urlWithKeyword, ' '))!= NULL)
                    *ptr = '-';
            }
            else
                terminate = 1;
            break;
        case '?':
            terminate = 1;
            break;
        default:
            terminate = 1;
            break;
        }
    }
    if (help)
    {
        printf("\t./hw0503 -q keyword\n");
    }
    else if (terminate)
    {

        printf("Exiting...\n");
    }
    else
    {
        CURL *curl = curl_easy_init();
        CURLcode res;
        if (curl)
        {

            curl_easy_setopt(curl, CURLOPT_URL, urlWithKeyword);
            FILE *buf = fopen(bufferFile, "w");
            assert(buf);
            printf("Getting results of %s ...\n", urlWithKeyword);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                printf("curL_easy_perform() failed.\n");
            }
            fclose(buf);

            getQuery();
        }
        else
        {
            printf("Something went wrong with libcurl.\nExiting...\n");
        }
        curl_easy_cleanup(curl);

        remove(bufferFile);
    }
    free(urlWithKeyword);
    return 0;
}

void getQuery() //<cite class="data" itemprop="headline">
{
    const char *parser = "<cite class=\"data\" itemprop=\"headline\">";
    const char *authorParser = "<span itemprop=\"name\" title=\"";
    const char *titleParser = "<span class=\"title\" itemprop=\"name\">";
    const char *dateParser = "<span itemprop=\"datePublished\">";
    const char *sourceParser = "<span itemprop=\"name\">";
    i32 fd = 0;
    fd = open(bufferFile, O_RDWR);

    uint64_t fileSize = getFDSize(fd);
    char *p = NULL;
    p = mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    char *str = NULL;

    str = strstr(p, parser);
    i32 index = 0; //article number
    if (str == NULL)
        printf("No match.\n");
    else
    {
        while (str != NULL)
        {
            if (index >= 10)
                break;
            str = str + strlen(parser);
            char *endOfStr = strstr(str, parser);

            if (endOfStr != NULL)
            {
                *(endOfStr - 1) = 0;
            }
            //Get authors
            string author[100] = {0};
            char *ptr = strstr(str, authorParser);
            char *token = NULL;
            i32 authorIndex = 0;
            if (ptr == NULL)
            {
                strncpy(author[0], "No author was found.", sizeof(string) - 5);
                authorIndex = 1;
            }
            {
                while (ptr != NULL)
                {
                    ptr += strlen(authorParser);
                    token = strtok(ptr, "\"");
                    strncpy(author[authorIndex], token, sizeof(string) - 5);
                    ptr = token + 1 + strlen(token);
                    *(ptr - 1) = '\"';
                    ptr = strstr(ptr, authorParser);
                    authorIndex++;
                }
            }
            ptr = NULL;
            token = NULL;
            //Get title
            string title = {0};
            ptr = strstr(str, titleParser);
            if (ptr == NULL)
            {
                strncpy(title, "No title was found.", sizeof(string) - 5);
            }
            {
                ptr += strlen(titleParser);
                token = strtok(ptr, "<");
                strncpy(title, token, sizeof(string) - 5);
                *(token + strlen(token)) = '<';
                ptr = NULL;
                token = NULL;
            }
            //Get date
            string date = {0};
            ptr = strstr(str, dateParser);
            if (ptr == NULL)
            {
                strncpy(date, "No date was found.", sizeof(string) - 5);
            }
            else
            {
                *(ptr - 1) = 0;
                ptr += strlen(dateParser);
                token = strtok(ptr, "<");
                strncpy(date, token, sizeof(string) - 5);

            }
            //Get source
            string source = {0};
            ptr = strstr(str, sourceParser);
            if (ptr == NULL)
            {
                strncpy(source, "No source was found.", sizeof(string) - 5);
            }
            else
            {
                ptr += strlen(sourceParser);
                token = strtok(ptr, "<");
                while (token != NULL)
                {
                    strncat(source, token, sizeof(string) - 5);
                    token = strtok(NULL, "<");
                    if (token == NULL)
                        break;
                    token = strchr(token, '>');
                    if (token != NULL)
                        token++;
                }
            }
            //print result;
            printf("Paper %2d\n", index + 1);
            printf("\tTitle : %s\n", title);
            printf("\tAuthor : ");
            for (i32 i = 0; i < authorIndex; i++)
            {
                printf("%s", author[i]);
                if (i != authorIndex - 1)
                    printf(", ");
            }
            printf("\n\tSource : %s\n", source);
            printf("\tDate : %s\n", date);
            //printf("%s\n", str);
            index++;
            if (endOfStr == NULL)
                break;
            else
                str = strstr(endOfStr, parser);
        }
    }
    munmap(p, fileSize);
    close(fd);
    return;
}

uint64_t getFDSize(i32 fd)
{
    struct stat statBuf;
    if (fstat(fd, &statBuf) < 0)
    {
        return -1;
    }
    return statBuf.st_size;
}