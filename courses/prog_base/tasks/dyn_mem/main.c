#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char *min;
    char * str;
    str = (char *)malloc(100*sizeof(char));
    if (!str)
        exit(EXIT_FAILURE);
    scanf("%s", str);
    strcat(str, "\0");
    min = str;
    str++;
    while(*str != '\0')
    {
        if (*str < *min) min = str;
        str++;
    }
    printf("%c", *min);
    free(str);
    return 0;
}
