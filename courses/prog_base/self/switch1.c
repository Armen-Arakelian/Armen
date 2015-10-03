#include <stdio.h>
#include <stdlib.h>

int main()
{
    int h = 2, m = 43, code;
    float count, t;
    t = 60*h + m;
    code = 692;
    if (code < 10 || code > 999) return 0;
    switch(code)
    {
    case 44 :
    count = t*0.77;
    break;
    case 62:
      count = t*0.8;
    break;
    case 32:
        count = t*0.95;
    break;
    case 692:
    case 697:
        count = t*1.5;
    break;
    default:
    count = t;
    }
    printf("%.2f", count);
    return 0;
}

