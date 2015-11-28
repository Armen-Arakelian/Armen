#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    struct Coor
    {
        int x;
        int y;
    };
    int i;
    char pread[100] = "D:\\Program Files (x86)\\CodeBlocks_projects\\sr\\pread.txt";
    struct Coor a[20];
    FILE * fp;
    if (fp = fopen(pread, "rb") == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (i=0;i<20;i++)
    {
        fscanf(fp, "%d", (a+i)->x);
        fscanf(fp, "%d", (a+i)->y);
    }
    return 0;
}

void isOnCir (struct Coor ** a)
{
    int i;
    int count;
    for (i=0;i<20;i++)
    {        if ((int)(pow((a + i)->x,2) +  pow((a + i)->y, 2)) == 5)
        {
            count++;
        }
        printf("%i", count);
    }

}



