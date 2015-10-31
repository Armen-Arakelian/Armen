#include <stdio.h>
#include <stdlib.h>

int numOfLet()
{

    int countH = 0, countP = 0, i;
    for (i =0;i<strlen(st); i++)
    {
        if (st[i] == "a" || st[i] == "e" || st[i] == "y" || st[i] == "u" || st[i] == "i" || st == "o" || st == "A" || st == "E" || st == "Y" || st == "U" || st == "I" || st == "O" )
            countH++;
        if (st == "q" || st == "w" || st == "r" || st == "t" || st == "p" || st == "s" || st == "d" || st == "f" || st == "g" || st == "h" || st == "j" || st == "k" || st == "l" || st == "z" || st == "x" || st == "c" || st == "v" || st == "b" || st =="n" || st ==  "m" )
            countP++;
    printf("%i", countH);
    printf("%i", countP);
    return 0;
    }
}

int numOfnum()
{
    int i, count;
     for (i =0;i<strlen(st); i++)
    {
        if(st[i] == "1" || st[i] == "12" || st[i] == "3"  || st[i] == "4" || st[i] == "5" || st[i] == "6" || st[i] == "7" || st[i] == "8" || st[i] == "9" || st[i] == "0" )
            count++;
            printf("%i", count);

    }
}
