#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double long2double(long long a)
{
    int i, e=0, check = 0 ;
    double d = 0;
    int bits[64];
    if (a >= 0)
    {
        bits[0] = 0;

    }

    else
    {
         bits[0] = 1;
         a = a + 9223372036854775808LL;

    }
       for (i=63; i > 0;i--)
        {
            bits[i] = a%2;
            a /=2;
        }
    for (i=11; i>0;i--)
    {
       e += bits[i]*pow(2,11-i);
    }
   if (e == 0)
    {
      for (i=12; i<63; i++)
        {
            d += bits[i]*pow(2, -1022);
        }
   }

    else
    if (e == 2047)
    {
        for (i = 12; i<63; i++)
        {
            if (bits[i])
                {
                check =1;
                break;
               }
        }
        if (check) d = NAN;
        else
            d = INFINITY;
    }
    else
    {
        for (i=12; i<63; i++)
        {
            d += bits[i]*pow(2, e-1023-i+11);
        }
        d += pow(2, e - 1023);
    }
    if (bits[0]) d = -d;
    return d;

}
