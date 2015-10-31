#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int i,g;
    char st[] = "-5389,654";
    g = strlen(st);
    for (i=0; i<g; i++)
    {
        if (st[i] == ",")
        {
            return 1;
            break;
        }
        else
            return 0;
    }
    return 0;
}
