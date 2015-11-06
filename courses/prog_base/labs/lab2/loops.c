#include <stdio.h>
#include <stdlib.h>

double calc(int n, int m)
{
    int i, j;
    double result = 0, result1 = 0;
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=m; j++)
        {
            result += 1.0/j;
        }
        result1 += i*result;
        result = 0;
    }
    return result1;
}



