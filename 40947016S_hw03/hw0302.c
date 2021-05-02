#include "math.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define i32 int32_t
#define u32 uint32_t
typedef struct _teaminfo
{
    char name[50];
    u32 goal;
    u32 goaled;
    u32 w;
    u32 l;
    u32 d;
    u32 wh;
    u32 wa;
    u32 red;
    u32 score;
} teaminfo;
typedef struct _date
{
    u32 year;
    u32 month;
    u32 day;
} date;

typedef struct _gameinfo
{
    date gamedate;
    char h[50];
    char a[50];
    u32 FTHG;
    u32 FTAG;
    char FTR[2];
    u32 HHG;
    u32 HTAG;
    char HTR[2];
    char Referee[30];
    u32 HS;
    u32 AS;
    u32 HST;
    u32 AST;
    u32 HF;
    u32 AF;
    u32 HC;
    u32 AC;
    u32 HY;
    u32 AY;
    u32 HR;
    u32 AR;

} gameinfo;

i32 findTeamIndex(teaminfo t[20], gameinfo g, char stat);
void readLine(gameinfo games[380], u32 gi, char line[1000]);
void printMenu();
void win(teaminfo t[20], gameinfo g[380]), sc(teaminfo t[20], gameinfo g[380]), rc(teaminfo t[20], gameinfo g[380]), wh(teaminfo t[20], gameinfo g[380]), wa(teaminfo t[20], gameinfo g[380]), gap(teaminfo t[20], gameinfo g[380]), st(teaminfo t[20], gameinfo g[380]);
int main()
{
    printf("Please open a season record: ");
    FILE *sr = NULL;
    char filename[50] = "a.csv";
    memset(filename, 0, sizeof(filename));
    fgets(filename, 49, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    const char *dot = strrchr(filename, '.');
    const char csv[5] = ".csv";
    if (strncmp(dot, csv, 4) != 0)
    {
        printf("Input is not a .csv file.\n");
        return 0;
    }
    if ((sr = fopen(filename, "r")) == NULL)
    {
        perror("Can't open this file :");
        return 0;
    }
    char line[1000];
    memset(line, 0, sizeof(line));
    fgets(line, 999, sr);
    memset(line, 0, sizeof(line));
    u32 gi = 0;
    gameinfo games[380];
    memset(games, 0, sizeof(games));

    while (!feof(sr))
    {
        if (gi == 380)
            break;
        fgets(line, 999, sr);
        readLine(games, gi, line);
        gi++;
    }
    u32 counts = 0;
    teaminfo teams[20];
    memset(teams, 0, sizeof(teams));
    fclose(sr);
    i32 gameindex = 0;
    while (counts < 20)
    {
        while (gameindex < 380)
        {
            i32 found = 0;
            for (i32 j = 0; j < counts; j++)
            {
                if (strncmp(teams[j].name, games[gameindex].h, sizeof(teams[j].name)) == 0)
                {
                    found = 1;
                    gameindex++;
                    break;
                }
            }

            if (!found)
            {
                strncpy(teams[counts].name, games[gameindex].h, sizeof(games[gameindex].h));
                counts++;
                gameindex++;
                break;
            }
        }
    }
    for (i32 i = 0; i < 380; i++)
    {
        i32 hindex = findTeamIndex(teams, games[i], 'H');
        i32 aindex = findTeamIndex(teams, games[i], 'A');
        if (strncmp(games[i].FTR, "D", 1) == 0)
        {
            teams[hindex].d++;
            teams[aindex].d++;
        }
        else if (strncmp(games[i].FTR, "A", 1) == 0)
        {
            teams[hindex].l++;
            teams[aindex].wa++;
        }
        else
        {
            teams[hindex].wh++;
            teams[aindex].l++;
        }
        teams[hindex].red += games[i].HR;
        teams[aindex].red += games[i].AR;
        teams[hindex].goal += games[i].FTHG;
        teams[hindex].goaled += games[i].FTAG;
        teams[aindex].goal += games[i].FTAG;
        teams[aindex].goaled += games[i].FTHG;
    }
    for (i32 i = 0; i < 20; i++)
    {
        teams[i].w = teams[i].wa + teams[i].wh;
        teams[i].score = (teams[i].w * 3) + teams[i].d;
        //printf("%s,red : %u,goal %u, ga %u\n", teams[i].name, teams[i].red, teams[i].goal, teams[i].goaled);
    }
    //storing games stat into teams
    u32 opi = -1;
    void (*f[7])(teaminfo t[20], gameinfo g[380]) = {win, sc, rc, wh, wa, gap, st};
    printMenu();
    while (1)
    {
        printf("Choice (1-7, 8:exit): ");
        scanf("%d", &opi);
        while (opi < 1 || opi > 8)
        {
            printf("Invalid choice,please try again.\n");
            printf("Choice (1-7, 8:exit): ");
            scanf("%d", &opi);
        }
        if (opi == 8)
            break;
        else if (opi >= 1 && opi < 8)
        {
            f[opi - 1](teams, games);
        }
    }
    return 0;
}

void printMenu()
{
    printf("1) Who is the winner in this season?\n2) Which team gets the most scores?\n3) Which team gets the most red cards?\n4) Which team wins the most games at home?\n5) Which team wins the most games away from home?\n6) Which game has the most scoring gap?\n7) Team information.\n8) Exit \n");

    return;
}

void win(teaminfo t[20], gameinfo g[380])
{
    u32 maxwin = 0;
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].w > maxwin)
            maxwin = t[i].w;
    }
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].w == maxwin)
            printf("The winner is %s\n", t[i].name);
    }
    return;
}

void sc(teaminfo t[20], gameinfo g[380])
{
    u32 maxsc = 0;
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].goal > maxsc)
            maxsc = t[i].goal;
    }
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].goal == maxsc)
            printf("%s, ", t[i].name);
    }
    printf("%u\n", maxsc);
    return;
}
void rc(teaminfo t[20], gameinfo g[380])
{
    u32 maxrc = 0;
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].red > maxrc)
            maxrc = t[i].red;
    }
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].red == maxrc)
            printf("%s, ", t[i].name);
    }
    printf("%u\n", maxrc);
    return;
}
void wh(teaminfo t[20], gameinfo g[380])
{
    u32 maxwh = 0;
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].wh > maxwh)
            maxwh = t[i].wh;
    }
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].wh == maxwh)
            printf("%s, ", t[i].name);
    }
    printf("%u\n", maxwh);
    return;
}
void wa(teaminfo t[20], gameinfo g[380])
{
    u32 maxwa = 0;
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].wa > maxwa)
            maxwa = t[i].wa;
    }
    for (i32 i = 0; i < 20; i++)
    {
        if (t[i].wa == maxwa)
            printf("%s, ", t[i].name);
    }
    printf("%u\n", maxwa);
    return;
}

void gap(teaminfo t[20], gameinfo g[380])
{
    u32 maxgap = 0;
    for (i32 i = 0; i < 380; i++)
    {
        if (abs(g[i].FTHG - g[i].FTAG) > maxgap)
        {
            maxgap = abs(g[i].FTHG - g[i].FTAG);
        }
    }
    for (i32 i = 0; i < 380; i++)
    {
        if (abs(g[i].FTHG - g[i].FTAG) == maxgap)
            printf("%u-%u-%u,%s(%u) vs %s(%u)\n", g[i].gamedate.year, g[i].gamedate.month, g[i].gamedate.day, g[i].h, g[i].FTHG, g[i].a, g[i].FTAG);
    }
    return;
}

void st(teaminfo t[20], gameinfo g[380])
{

    char input[100];
    memset(input, 0, 100);
    printf("Team : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    i32 index = -1;
    for (i32 i = 0; i < 20; i++)
    {
        if (strlen(t[i].name) != strlen(input))
        {
            continue;
        }
        if (strncmp(t[i].name, input, strlen(input)) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Invalid input,please try again.\n");
        st(t, g);
    }
    else
    {
        printf("Points : %u\nWin/Draw/Lose: %u/%u/%u\nGoals Scored/Goals Against: %u/%u\n", t[index].score, t[index].w, t[index].d, t[index].l, t[index].goal, t[index].goaled);
    }
    return;
}
i32 findTeamIndex(teaminfo t[20], gameinfo g, char stat)
{
    if (stat == 'A')
    {
        for (i32 i = 0; i < 20; i++)
        {
            if (strlen(t[i].name) != strlen(g.a))
            {
                continue;
            }
            if (strncmp(t[i].name, g.a, strlen(g.a)) == 0)
            {
                return i;
            }
        }
    }
    else
    {
        for (i32 i = 0; i < 20; i++)
        {
            if (strlen(t[i].name) != strlen(g.h))
            {
                continue;
            }
            if (strncmp(t[i].name, g.h, strlen(g.h)) == 0)
            {
                return i;
            }
        }
    }
    return -1;
}

void readLine(gameinfo games[380], u32 gi, char line[1000])
{
    char *lptr = NULL;
    games[gi].gamedate.year = strtol(line, &lptr, 10);
    lptr++;
    games[gi].gamedate.month = strtol(lptr, &lptr, 10);
    lptr++;
    games[gi].gamedate.day = strtol(lptr, &lptr, 10);
    lptr++;

    char *token = strtok(lptr, ",");
    strncpy(games[gi].h, token, strlen(token));
    token = strtok(NULL, ",");
    strncpy(games[gi].a, token, strlen(token));
    token = strtok(NULL, ",");
    games[gi].FTHG = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].FTAG = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    strncpy(games[gi].FTR, token, strlen(token));
    token = strtok(NULL, ",");
    games[gi].HHG = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].HTAG = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    strncpy(games[gi].HTR, token, strlen(token));
    token = strtok(NULL, ",");
    strncpy(games[gi].Referee, token, strlen(token));
    token = strtok(NULL, ",");
    games[gi].HS = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].AS = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].HST = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].AST = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].HF = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].AF = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].HC = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].AC = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].HY = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].AY = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].HR = strtol(token, &lptr, 10);
    token = strtok(NULL, ",");
    games[gi].AR = strtol(token, &lptr, 10);
}
