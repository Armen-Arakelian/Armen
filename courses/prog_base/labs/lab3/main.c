#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>

int main()
{
   int size ,i,j, nothing = 0;
   char c;
   int fAqua = FOREGROUND_BLUE|FOREGROUND_GREEN;
   int aqua = BACKGROUND_BLUE|BACKGROUND_GREEN;
   int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
   int green = FOREGROUND_GREEN;
   int blue = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
   int black = 0;
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD pos;
   srand(time(NULL));
   SetConsoleCursorPosition(hConsole, pos);
   for(;;)
   {
       printFrame(10, 5, 61, 15);
        pos.X = 15;
        pos.Y = 6;
        SetConsoleCursorPosition(hConsole, pos);
       SetConsoleTextAttribute(hConsole, aqua);
       printf("Put the size of matrix (from 0 to 10)\n");
        pos.X = 15;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);
        scanf("%i", &size);
   if (size>=0 && size<11)
       break;
   else
    {
        pos.X = 15;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);
         putError();
         pos.X = 15;
        pos.Y = 8;
        SetConsoleTextAttribute(hConsole, aqua);
        SetConsoleCursorPosition(hConsole, pos);
        printf("put correct size\n");
        getch(c);
        SetConsoleTextAttribute(hConsole, 0);
        system("cls");
    }
   }
   SetConsoleTextAttribute(hConsole, 0);
   system("cls");
   double mat[size][size];
   for(i=0;i<size;i++)
   {
       for(j=0;j<size;j++)
       {
           mat[i][j] = 0;
       }
   }
   SetConsoleTextAttribute(hConsole, black|white);
   char  check[16];
   char * help = "help";
   char * Break = "break";
   char * checkcleanAll = "cleanAll";
    char * checkfillRand = "fillRand";
    char * checkflipH = "flipH";
    char * checkflipDiag = "flipDiag";
    char * checkrotateCW180 = "rotateCW180";
    char * checksumOfAll = "sumOfAll";
    char * checksumOfColumn ="sumOfColumn";
    char * checksumOfElemUndDiag = "sumOfElemUndDiag";
    char * checkrepFirstMinMax = "repFirstMinMax";
    char * checkrepLastMinMax = "repLastMinMax";
    char * checkrepColumn = "repColumn";
    char * fuck = "fuck you";
    pos.X = 0;
    pos.Y = 0;
   for (;;)
   {
       printFrame(10, 1, size*12+10, size+3);
        pos.X = 10;
        pos.Y = 1;
        SetConsoleTextAttribute(hConsole, aqua);
    for (i = 0;i<size;i++)
    {
        pos.X = 10;
        pos.Y++;
        for (j=0;j<size;j++)
        {
            SetConsoleCursorPosition(hConsole, pos);
            printf("%10f", mat[i][j]);
            pos.X+=12;
        }
    }
     SetConsoleTextAttribute(hConsole, black|white);
    puts("\n");
    puts("\n");
    puts("Put the command");
    SetConsoleTextAttribute(hConsole, green);
    printf(">>");
    SetConsoleTextAttribute(hConsole, white);
    SetConsoleTextAttribute(hConsole, fAqua);
    scanf("%s", check);
    SetConsoleTextAttribute(hConsole, white);
    if (!strcmp(check, checkcleanAll))
        cleanAll(size,  mat);
    else
    if (!strcmp(check, checkfillRand))
        fillRand(size,  mat);
    else
    if (!strcmp(check, checkflipH))
        flipH(size,  mat);
    else
    if (!strcmp(check, checkflipDiag))
        flipDiag(size,  mat);
    else
    if (!strcmp(check, checkrotateCW180))
        rotateCW180(size,  mat);
    else
    if (!strcmp(check, checksumOfAll))
        sumOfAll(size,  mat);
    else
    if (!strcmp(check, checksumOfColumn))
        sumOfColumn(size,  mat);
    else
    if (!strcmp(check, checksumOfElemUndDiag))
        sumOfElemUndDiag(size,  mat);
    else
    if (!strcmp(check, checkrepFirstMinMax))
        repFirstMinMax(size,  mat);
    else
    if (!strcmp(check, checkrepLastMinMax))
        repLastMinMax(size,  mat);
    else
    if (!strcmp(check, checkrepColumn))
        repColumn(size,  mat);
    else
    if (!strcmp(check, help))
        {
            printf("List of commands : \n");
            SetConsoleTextAttribute(hConsole, green);
            printf("cleanAll ");
            SetConsoleTextAttribute(hConsole, white);
            printf("- Making all the elements 0\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("fillRand ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Filling matrix of real random elements in some range\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("flipH ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Horizontal flip of matrix\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("flipDiag ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Secondary diagonal flip of matrix\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("rotateCW180 ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Rotating 180 degrees\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("sumOfAll ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Sum of all elements\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("sumOfColumn ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Sum of elements from exact column\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("sumOfElemUndDiag");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Sum of elements under main diagonal(with diagonal)\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("repFirstMinMax ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Replacing first min and first max elements from all matrix\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("repLastMinMax ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Replacing last min and last max elements from all matrix\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("repColumn ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Replacing columns with max and min sums of elements\n");
            SetConsoleTextAttribute(hConsole, green);
            printf("break ");
            SetConsoleTextAttribute(hConsole, white);
            printf(" - Stop the program\n");
            getch(c);
        }
        else
        if(!strcmp(check, fuck))
        printf("GO FUCK YOURSELF!");
        else
        if (!strcmp(check, Break))
        return 0;
        else
        {
            putError();
            puts("Put correct command");
            getch(c);
        }
        system("cls");

   }
    return 0;
}

void cleanAll(int size, double mat[size][size])
{
    int i,j;
    for (i = 0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            mat[i][j] = 0;
        }
    }
}

int fillRand(int size, double mat[size][size])
{
    int leftBorder, rightBorder,i,j,a;
    double k;
    char c;
    printf("put range of elements (left > -101 and right < 101 borders)\n");
    scanf("%i%i", &leftBorder, &rightBorder);
    if (rightBorder<=leftBorder || leftBorder < -100 || rightBorder > 100)
    {
        putError();
        puts("put correct borders\n");
        getch(c);
        return 0;
    }
    for (i = 0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            a = rand()%3 -2;
            if (!a) a = 1;
            if (a == -2) a = -1;
            k = 1.*rand()/(rand()+1);
            if (k>1) k = 1/k ;
            if (rightBorder<= 0 && leftBorder < 0)
                mat[i][j] = -1*(rand() % (abs(leftBorder) - abs(rightBorder)) + abs(rightBorder) + k);
            else
                if (leftBorder < 0)
                    {
                        if (abs(rightBorder)> abs(leftBorder))
                        {
                             mat[i][j] = rand() %abs(rightBorder) + k;
                             if (mat[i][j]<abs(leftBorder)) mat[i][j] = a*mat[i][j];
                        }
                         if (abs(rightBorder) < abs(leftBorder))
                            {
                                mat[i][j] = -1*(rand() % abs(leftBorder) + k);
                                if (mat[i][j] < rightBorder && mat[i][j] > -rightBorder) mat[i][j] = a*mat[i][j];
                            }
                            if (abs(rightBorder) == abs(leftBorder))
                        {
                             mat[i][j] = a*(rand() % rightBorder + k);
                        }
                    }
            else
                mat[i][j] = rand() % (rightBorder - leftBorder) +leftBorder + k;

        }
    }
    return 0;
}

void flipH(int size, double mat[size][size])
{
    int i,j;
    double a;
     for (i = 0;i<size;i++)
    {
        for (j=0;j<size/2;j++)
        {
            a = mat[i][j];
            mat[i][j] = mat[i][size-j-1];
            mat[i][size-j-1] = a;
        }
    }
}

void flipDiag(int size, double mat[size][size])
{
    int i, j, g = 0;
    double a;
     for (i = 0;i<size;i++)
    {
        for (j=0;j<size-g;j++)
        {
            a = mat[i][j];
            mat[i][j] = mat[size-1-i][size-1-j];
            mat[size-1-i][size-1-j] = a;
        }
        g++;
    }
}

void rotateCW180(int size, double mat[size][size])
{
    int i, j;
    double a;
     for (i = 0;i<size/2;i++)
    {
        for (j=0;j<size;j++)
        {
            a = mat[i][j];
            mat[i][j] = mat[size-1-i][size-j-1];
            mat[size-1-i][size-j-1] = a;
        }
    }
}


void sumOfAll(int size, double mat[size][size])
{
    int i,j;
    char c;
    double sum = 0;
         for (i = 0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            sum +=mat[i][j];
        }
    }
    putResult();
    printf("Sum of all elements is %f", sum);
    getch(c);
}

int sumOfColumn(int size, double mat[size][size])
{
    int i, j;
    char c;
    double sum = 0;
    printf("Put number of column \n");
    scanf("%i", &j);
    if (j>=size || j < 0)
    {
        putError();
        puts("Put correct number of column");
        getch(c);
        return 0;
    }
    for (i = 0;i<size;i++)
    {
        sum += mat[i][j];
    }
    putResult();
    printf("Sum of elements from column %i", j);
    printf(" is %f", sum);
    getch(c);
    return 0;
}

void sumOfElemUndDiag(int size, double mat[size][size])
{
    int i, j, g = size-1;
    char c;
    double sum = 0;
    for (i = 0;i<size;i++)
    {
        for (j=0;j<size - g;j++)
        {
           sum += mat[i][j];
        }
        g--;
    }
    putResult();
    printf("Sum of elements under main diagonal is %f", sum);
    getch(c);
}

void repFirstMinMax(int size, double mat[size][size])
{
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i,j, minI,minJ,maxI,maxJ,check = 0;
    int green = FOREGROUND_GREEN;
    int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
    double min = mat[0][0], max = mat[0][0], a;
    for (i = 0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            if (i == 0 && j == 0)
                continue;
           if (mat[i][j] > max)
           {
               max = mat[i][j];
               maxI = i;
               maxJ = j;
           }
           if (mat[i][j] < min)
           {
               min = mat[i][j];
               minI = i;
               minJ = j;
           }
        }
    }
    a = mat[minI][minJ];
    mat[minI][minJ] = mat[maxI][maxJ];
    mat[maxI][maxJ] = a;
    if (minJ) check++;
    if (check)
        pos.X = 10 + 11*minJ;
    else
        pos.X = 10 + minI;
        puts(" ");
    pos.Y = minJ;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, green);
    pos.X = maxI;
    pos.Y = maxJ;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, white);
}

void repLastMinMax(int size, double mat[size][size])
{
    int i,j, minI,minJ,maxI,maxJ;
    double min = mat[0][0], max = mat[0][0], a;
    for (i = 0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            if (i == 0 && j == 0)
                continue;
           if (mat[i][j] >= max)
           {
               max = mat[i][j];
               maxI = i;
               maxJ = j;
           }
           if (mat[i][j] <= min)
           {
               min = mat[i][j];
               minI = i;
               minJ = j;
           }
        }
    }
    a = mat[minI][minJ];
    mat[minI][minJ] = mat[maxI][maxJ];
    mat[maxI][maxJ] = a;
}

void repColumn(int size, double mat[size][size])
{
    int i,j, minJ,maxJ;
    double a, minSum, maxSum, sum = 0;
    for (j = 0;j<size;j++)
    {
        sum = 0;
        for (i=0;i<size;i++)
        {
           sum += mat[i][j];
        }
         if (j)
           {
           if (minSum <= sum)
           {
               minSum = sum;
               minJ = j;
           }
           if (maxSum >= sum)
           {
               maxSum = sum;
               maxJ = j;
           }
           }
        minSum = sum;
        maxSum = sum;
    }
    for (i =0;i<size;i++)
    {
      a = mat[i][minJ];
      mat [i][minJ] = mat[i][maxJ];
      mat[i][maxJ] = a;
    }
}

void putError(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int red = FOREGROUND_RED;
    int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
    SetConsoleTextAttribute(hConsole, red);
    printf("ERROR \n");
    SetConsoleTextAttribute(hConsole, white);
}

void putResult(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
    int green = FOREGROUND_GREEN;
    SetConsoleTextAttribute(hConsole, green);
    puts("\n");
    puts("Result : \n");
    SetConsoleTextAttribute(hConsole, white);
}

void printFrame(int xB, int yB, int xE, int yE)
{
    int aqua = BACKGROUND_BLUE|BACKGROUND_GREEN;
    int blue = FOREGROUND_BLUE;
    int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
    int black = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    SetConsoleTextAttribute(hConsole, aqua);
     for(pos.Y=yB;pos.Y<yE;pos.Y++)
    {
       for(pos.X=xB;pos.X<xE;pos.X++)
       {
           SetConsoleCursorPosition(hConsole, pos);
           putchar(' ');
       }
   }
   SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
    for(pos.Y=yB-1;pos.Y<=yE;pos.Y++)
    {
        pos.X = xB - 1;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('|');
        pos.X = xE;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('|');
    }
    for(pos.X=xB-1;pos.X<=xE;pos.X++)
 {
        pos.Y = yB - 1;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('-');
        pos.Y = yE;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('-');
    }
    SetConsoleTextAttribute(hConsole, black);
    SetConsoleTextAttribute(hConsole, white);
   }


