#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_SP_NUM 10


typedef struct Sputnik
{
    char name[50];
    double mass; // in Earth masses
    int radius; // in kilometers
} Sputnik;

typedef struct Planet
{
    char name[50];
    double mass; // in Earth masses
    int radius;  // in kilometers
    int perOfRot; // Period of rotation in days
    int numOfSp; // Number of sputniks
    Sputnik *sputnik;
} Planet;



int main()
{
    Sleep(1000);
    char * filename  = "saves.bin";
    char check[50];
    int memSize = 20;
    int numOfPl = 0;
    Planet * planets;
    planets = (Planet *)malloc(memSize*(sizeof(Planet)));
    memSize++;
    planets = realloc (planets, memSize*sizeof(Planet));
    deserialization(planets, &numOfPl, filename);
    while(1)
    {
        printPlanets(planets, &numOfPl);
        putCursor(50, 1);
        puts("Enter your command");
        putCursor(50, 2);
        printf(">>");
        scanf("%s", check);
        if (!strcmp(check, "addPl"))
            addPlanet(planets, &numOfPl, &memSize);
            else
        if (!strcmp(check, "addSp"))
            addSputnik(planets, &numOfPl);
            else
        if (!strcmp(check, "removePl"))
            removePlanet(planets, &numOfPl);
            else
        if (!strcmp(check, "removeSp"))
            removeSputnik(planets, &numOfPl);
            else
        if (!strcmp(check, "changePl"))
            changePlanet(planets, &numOfPl);
            else
        if (!strcmp(check, "changeSp"))
            changeSputnik(planets, &numOfPl);
            else
        if (!strcmp(check, "help"))
        {
            putCursor(50, 3);
            puts("List of commands :");
            putCursor(50, 4);
            puts("addPl - Adding a new planet");
            putCursor(50, 5);
            puts("addPl - Adding a new sputnik");
            putCursor(50, 6);
            puts("removePl - Removing some planet");
            putCursor(50, 7);
            puts("removeSp - Removing some sputnik");
            putCursor(50, 8);
            puts("changePl - Changing parameter of some planet");
            putCursor(50, 9);
            puts("changeSp - Changing parameter of some sputnik");
            putCursor(50, 10);
            puts("exit - Stop the program");
            getch();
        }
            else
        if (!strcmp(check, "exit"))
            {
                freeAll(planets, &numOfPl);
                exit(EXIT_SUCCESS);
            }
            else
            {
                putCursor(120, 3);
                puts("ERROR, enter correct command");
            }
        save(planets, &numOfPl, filename);
        system("cls");
        }


        freeAll(planets, &numOfPl);
        return 0;

    }

void addPlanet(Planet *planets,int * numOfPl, int * memSize)
{
    if (*numOfPl >= *memSize)
    {
        (*memSize)++;
        planets = (Planet *)realloc(planets, (*memSize)*(sizeof(Planet)));
    }
    putCursor(50, 3);
    printf("Enter parameters of new planet (name, mass, period of rotating, radius)\n");
    putCursor(50, 4);
    scanf("%s", ((planets + *numOfPl)->name));
    scanf("%lf", &((planets + *numOfPl)->mass));
    scanf("%d", &((planets + *numOfPl)->radius));
    scanf("%d", &((planets + *numOfPl)->perOfRot));

    (planets + (*numOfPl))->numOfSp = 0;
    (planets+ (*numOfPl))->sputnik = (Sputnik *)malloc(sizeof(Sputnik));
    (*numOfPl)++;
}

int addSputnik(Planet * planets, int* numOfPl)
{
    int number;
    putCursor(50, 3);
    puts("Enter number of planet you want to add sputnik to");
    putCursor(50, 4);
    scanf("%d", &number);
    if (number > *numOfPl || number < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of planet");
            return addSputnik(planets, numOfPl);
        }
    (planets+number-1)->sputnik = (Sputnik *)realloc((planets+number-1)->sputnik, ((planets+number-1)->numOfSp+1)*sizeof(Sputnik));
    putCursor(50, 5);
    puts("Enter parameters of new sputnik (name, mass, radius)");
    putCursor(50, 6);
    scanf("%s",(((planets+number-1)->sputnik+(planets+number-1)->numOfSp)->name));
    scanf("%lf", &((((planets+number-1)->sputnik+(planets+number-1)->numOfSp)->mass)));
    scanf("%d", &((((planets+number-1)->sputnik+(planets+number-1)->numOfSp)->radius)));
    (planets+number-1)->numOfSp++;
    return 0;
}

int removePlanet(Planet * planets, int * numOfPl)
{
    int number,i;
    putCursor(50, 3);
    puts("Enter number of planet you want to remove");
    putCursor(50, 4);
    scanf("%d", &number);
    if (number > *numOfPl || number < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of planet");
            return removePlanet(planets, numOfPl);
        }
        for (i=number;i<=*numOfPl-1;i++)
        {
            planets[i-1] = planets[i];
        }
        (*numOfPl)--;
        return 0;
}

int removeSputnik(Planet *planets, int *numOfPl)
{
    int plNum, i, spNum;
    putCursor(50, 3);
    puts("Enter number of planet you want to remove sputnik from");
    putCursor(50, 4);
    scanf("%d", &plNum);
    if (plNum > *numOfPl || plNum < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of planet");
            return removeSputnik(planets, numOfPl);
        }
        putCursor(50, 3);
        puts("Enter number of sputnik you want to remove");
        putCursor(50, 4);
        scanf("%d", &spNum);
        if (spNum >= (planets+plNum-1)->numOfSp || spNum < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of sputnik");
            return removeSputnik(planets, numOfPl);
        }
        for (i=spNum;i<(planets+plNum-1)->numOfSp;i++)
        {
            (planets+plNum-1)->sputnik[i-1] = (planets+plNum-1)->sputnik[i];
        }
        (planets+plNum-1)->numOfSp--;
        return 0;
}

void changePlanet(Planet *planets, int *numOfPl)
{
    int plNum;
    char check[100];
    putCursor(50, 3);
    puts("Enter number of planet you want to change");
    putCursor(50, 4);
    scanf("%d", &plNum);
    if (plNum > *numOfPl || plNum < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of planet");
            changePlanet(planets, numOfPl);
            return ;
        }
    putCursor(50, 3);
    puts("Enter parameter you want to change (name, mass, radius or period of rotation)");
    putCursor(50, 4);
    scanf("%s", check);
    if(!strcmp(check, "name"))
        {
            putCursor(50, 5);
            scanf("%s",(planets + plNum-1)->name);
        }
        else
    if (!strcmp(check, "mass"))
    {
        putCursor(50, 5);
        scanf("%lf", &((planets+plNum-1)->mass));
    }
        else
    if (!strcmp(check, "radius"))
        {
            putCursor(50, 5);
            scanf("%d", &((planets + plNum-1)->radius));
        }
        else
    if (!strcmp(check, "period of rotation"))
        {
            putCursor(50, 5);
            scanf("%d", &((planets + plNum-1)->perOfRot));
        }
        else
        {
            putCursor(120, 5);
            puts("ERROR, enter correct parameter");
            changePlanet(planets, numOfPl);
            return ;
        }
}

int changeSputnik(Planet *planets, int *numOfPl)
{
    int plNum, spNum;
    char check[50];
    putCursor(50, 3);
    puts("Enter number of planet witch includes sputnik you want to change");
    putCursor(50, 4);
    scanf("%d", &plNum);
    if (plNum > *numOfPl || plNum < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of planet");
            return changeSputnik(planets, numOfPl);
        }
    putCursor(50, 5);
    puts("Enter number of sputnik you want to remove");
    putCursor(50, 6);
    scanf("%d", &spNum);
    if (spNum > (planets+plNum-1)->numOfSp || spNum < 0)
        {
            putCursor(120, 3);
            puts("ERROR, enter correct number of sputnik");
            return changeSputnik(planets, numOfPl);
        }
    putCursor(50, 7);
    puts("Enter parameter you want to change (name, mass, radius)");
    putCursor(50, 8);
    scanf("%s",check);
    if(!strcmp(check, "name"))
        {
            putCursor(50, 9);
            scanf("%s",((planets+plNum-1)->sputnik+spNum-1)->name);
        }
        else
    if (!strcmp(check, "mass"))
        {
            putCursor(50, 9);
            scanf("%lf", &(((planets+plNum-1)->sputnik+spNum-1)->mass));
        }
        else
    if (!strcmp(check, "radius"))
        {
            putCursor(50, 9);
            scanf("%d", &(((planets+plNum-1)->sputnik+spNum-1)->radius));
        }
        else
        {
            putCursor(120, 3);
            puts("ERROR, enter correct parameter");
            return changeSputnik(planets, numOfPl);
        }
        return 0;
}

void printPlanets(Planet * planets, int * numOfPl)
{
    int i,j;
    for (i = 0;i<*numOfPl;i++)
    {
       printf("Planet called %s", (planets + i)->name);
       printf("\nMass of planet is %f", (planets+ i)->mass);
       printf("\nRadius of planet is %d", (planets+ i)->radius);
       printf("\nPeriod of rotation of planet is %d", (planets +i)->perOfRot);
       printf("\nNumber of sputniks of planet is %d", (planets+ i)->numOfSp);
       if ((planets+i)->numOfSp)
       {
           for (j = 0;j < (planets+i)->numOfSp;j++)
           {
               printf("\n    Sputnik called %s", ((planets +i)->sputnik+j)->name);
               printf("\n    Mass of sputnik is %f", ((planets + i)->sputnik+j)->mass);
               printf("\n    Radius of sputnik is %d", ((planets+ i)->sputnik+j)->radius);
               puts(" ");
           }
       }
       puts("\n");
       }
    }

void save(Planet* planets, int * numOfPl, char * filename)
{
    FILE * fp;
    int i,j;
    if ((fp = fopen(filename, "wb")) == NULL)
        exit(EXIT_FAILURE);
    fwrite(numOfPl, sizeof(int), 1, fp);
    for (i=0;i<*numOfPl;i++)
    {
        fwrite((planets+i), sizeof(Planet), 1, fp);
        if ((planets+i)->numOfSp);
        {
            for (j=0;j<(planets+i)->numOfSp;j++)
           fwrite(((planets+i)->sputnik+j), sizeof(Sputnik), 1, fp);
        }
    }
    fclose(fp);
}

void deserialization(Planet * planets, int * numOfPl, char * filename)
{
    FILE * fp;
    int i,j;
    if ((fp = fopen(filename, "rb")) == NULL)
        fclose(fp);
   fread(numOfPl, sizeof(int), 1, fp);
    for (i=0;i<*numOfPl;i++)
    {
        fread((planets+i), sizeof(Planet), 1, fp);
        if ((planets+i)->numOfSp)
        {
            (planets+i)->sputnik = (Sputnik *)malloc((planets+i)->numOfSp*sizeof(Sputnik));
            for (j=0;j<(planets+i)->numOfSp;j++)
           fread(((planets+i)->sputnik+j), sizeof(Sputnik), 1, fp);
        }
        else
            (planets+i)->sputnik = NULL;
    }
    fclose(fp);
}

void freeAll(Planet * planets, int *plNum)
{
    int i;
    for (i=0;i<*plNum;i++)
    {
        if ((planets + i)->numOfSp)
            free((planets+i)->sputnik);
    }
    free(planets);
}

void putCursor(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}


