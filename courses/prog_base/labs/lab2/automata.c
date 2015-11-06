#include <stdio.h>
#include <stdlib.h>

int run(int moves[], int movesLen, int res[], int resLen)
{
    enum commands{ Break = -4,Continue, repeat, pop};
    int i,ind, curState = 0, count = 0;
    struct Commands
     {
        int comm;
        int state;
     } ;
            struct Commands stracts[4][4];
            stracts[0][0].comm = 1;
            stracts[0][0].state = 1;
            stracts[0][1].comm = repeat;
            stracts[0][1].state = 1;
            stracts[0][2].comm = 8;
            stracts[0][2].state = 0;
            stracts[0][3].comm = Break;
            stracts[0][3].state = NULL;
            stracts[1][0].comm = pop;
            stracts[1][0].state = 3;
            stracts[1][1].comm = 2;
            stracts[1][1].state = 2;
            stracts[1][2].comm = Break;
            stracts[1][2].state = NULL;
            stracts[1][3].comm = 5;
            stracts[1][3].state = 1;
            stracts[2][0].comm = 6;
            stracts[2][0].state = 2;
            stracts[2][1].comm = Continue;
            stracts[2][1].state = 1;
            stracts[2][2].comm = 3;
            stracts[2][2].state = 3;
            stracts[2][3].comm = pop;
            stracts[2][3].state = 0;
            stracts[3][0].comm = Break;
            stracts[3][0].state = NULL;
            stracts[3][1].comm = 7;
            stracts[3][1].state = 3;
            stracts[3][2].comm = Break;
            stracts[3][2].state = NULL;
            stracts[3][3].comm = 4;
            stracts[3][3].state = 0;
    for (i =0; i< resLen; i++)
    {
        res[i] = 0;
    }

    for (i=0;i<movesLen;i++)
    {
        switch(moves[i])
        {
    case 2 :
        ind = 0;
        break;
    case 6 :
        ind = 1;
        break;
    case 11 :
        ind = 2;
        break;
    case 101 :
        ind = 3;
        break;
    default :
           return count;
        }
            if (stracts[curState][ind].comm < 0)
            {
                switch(stracts[curState][ind].comm)
                {
                case Break :
                        return count;
                case pop :
                        if (!count) return count;
                        count--;
                        res[count] = 0;
                        break;
                case repeat :
                        i--;
                        break;
                    case Continue : break;
                    default :
                        return count;
                        }
                }
            if (stracts[curState][ind].comm > 0)
            {
                res[count] = stracts[curState][ind].comm;
                count++;
            }
            curState = stracts[curState][ind].state;
        }
        return count;
    }






