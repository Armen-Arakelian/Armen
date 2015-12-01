#include <stdio.h>
#include <stdlib.h>

 struct monitor
    {
        int diag;  // in inch
        int price;
        char * name;
    };

int main()
{
    int size = 5, j;
    struct monitor * pnew;
    struct monitor monitors[5];
    monitors[0].diag = 19;
    monitors[0].name = "Amsung";
    monitors[0].price = 2000;
    monitors[1].diag = 15;
    monitors[1].name = "G";
    monitors[1].price = 1450;
    monitors[2].diag = 24;
    monitors[2].name = "Ell";
    monitors[2].price = 3100;
    monitors[3].diag = 40;
    monitors[3].name = "Amsung";
    monitors[3].price = 5000;
    monitors[4].diag = 32;
    monitors[4].name = "Hilips";
    monitors[4].price = 3900;
    for (int i = 0;i<5;i++)
    {
        printf("Monitor number %d", i+1);
        puts("\n");
        printf("Name of monitor is %s", monitors[i].name);
        puts("\n");
        printf("Length of diagonal is %d", monitors[i].diag);
        puts("\n");
        printf("Price of monitor is %d", monitors[i].price);
        puts("\n");
    }
    printf("Number of monitors with diagonal more then 17 inch is %d", count(size, monitors));
    puts("\n");
    j = check();
    pnew = &monitors[j];
    change(pnew, "EnQ");
    print(pnew);
    return 0;
}

int check()
{
    int j = 0;
    printf("Enter the number of monitor");
    puts("\n");
    scanf("%i", &j);
    j--;
    if (j<0 || j>=5)
    {
        printf("There is not monitor with this number");
        puts("\n");
        return check();
    }
    return j;
}

int count(int size, struct monitor monitors[size])
{
    int counter = 0;
    for (int i = 0;i<size;i++)
    {
        if (monitors[i].diag > 17)
            counter++;
    }
    return counter;
}

void change(struct monitor * pVar, const char * newValue)
{
    pVar->name = newValue;
}

void print(struct monitor * pVar)
{
    puts("\n");
    printf("Name of monitor is %s", pVar->name);
    puts("\n");
    printf("Length of diagonal is %d", pVar->diag);
    puts("\n");
    printf("Price of monitor is %d", pVar->price);
    puts("\n");
}


