#include <stdio.h>
#include <stdlib.h>

const char *defaultCapName = "Barbossa";
const char * defaultShipName = "A";

typedef struct Ship
{
    char name[100];
    int age;
    float weight;
} Ship;

typedef struct Captain
{
    char name[100];
    int age;
    int workAge;
    Ship *ship;

} Captain;

int main()
{
    Ship * fregat;
    Captain * captain;
    return 0;
}

void fillStruct(Ship * fregat, Captain * captain)
{
    strcpy(fregat->name, defaultShipName);
    fregat->age = 15;
    fregat->weight = 100.65;
    strcpy(captain->name, defaultCapName);
    captain->age = 50;
    captain->workAge = 30;
    captain->ship = *fregat;
}

void newCaptain(Captain * captain, int* CapCount)
{
    puts("Enter your captain ( cap name, cap age, cap work age)");
    scanf("%s", &(captain->name));
    scanf("%d", &(captain->age));
    scanf("%d", &(captain->workAge));
    *CapCount++;
}

void newCaptain(Captain * captain, Ship * fregat, int *ShipCount)
{
    puts("Enter your captain ( cap name, cap age, cap work age)");
    scanf("%s", &(captain->ship->name));
    scanf("%d", &(captain->ship->age));
    scanf("%f", &(captain->ship->weight));
    *ShipCount++;
}

Ship * dymStructShip(Ship * fregat)
{
    fregat = (Ship*)malloc(5*(sizeof(Ship)));
    return fregat;
}

Captain * dymStructShip(Ship * fregat)
{
    captain = (Captain*)malloc(5*(sizeof(Captain)));
    return captain;
}

void freeShip(Ship * fregat)
{
    free(fregat);
}

void freeCap(Captain * captain)
{
    free(captain);
}

void printStr(Ship * fregat, Captain * captain)
{
    puts("Captain");
    printf("%s", captain->name);
    printf("\n%d", captain->age);
    printf("\n%d", captain->workAge);
    puts("ship");
    printf("\n%s", captain->ship->name);
    printf("\n%d", captain->ship->age);
    printf("\n%f", captain->ship->weight);
}

void printArrStr(Ship * fregat, Captain * captain, int *CapCount)
{
    int i;
    for(i = 0;i<*CapCount;i++)
    {
        puts("Captain");
        printf("%s", (captain+i)->name);
        printf("\n%d", (captain+i)->age);
        printf("\n%d", (captain+i)->workAge);
        puts("ship");
        printf("\n%s", (captain+i)->ship->name);
        printf("\n%d", (captain+i)->ship->age);
        printf("\n%f", (captain+i)->ship->weight);
        *CapCount++;
    }
}

void equalsStr(Ship * fregat, Captain * captain)
{

}

