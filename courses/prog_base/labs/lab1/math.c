#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double x, double y, double z)
{
    double a;
    if (!(x - y) || !z || !(x+y) || !sin(y)) return NAN;
    a = (pow(y, x+1))/(pow(x-y, (1/z))) + y/(2*(abs(x+y))) + pow(x, 1/abs(sin(y)));
    return a;
}
