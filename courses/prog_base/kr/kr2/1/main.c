#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    files("D:\\Program Files (x86)\\CodeBlocks_projects\\KR2(1)\\testR.txt", "D:\\Program Files (x86)\\CodeBlocks_projects\\KR2(1)\\testW.txt");
    //files(argv[1], argv[2]);
    return 0;
}

void files(char * Rfilename, char * Wfilename)
{
    char change;
    char str[100];
    char str1[100];
    int str1C = 0;
    int count=0,i,j,g;
    char ch;
    FILE * fp;
    FILE * fp1;
    if ((fp = fopen(Rfilename, "r")) == NULL)
        exit(EXIT_FAILURE);
    while(feof(fp) != EOF)
    {
        ch = fgetc(fp);
        if (ch == '\n')
            count++;
    }
    for(i = 0;i<count;i++)
    {
        fgets(str, strlen(str), fp);
        for (j = 0;j<str;j++)
        {
            if (issapce(str[j]))
                continue;
            str1[str1C] = str[j];
            str1C++;
        }
        str1C = 0;
        for(j=0;j<strlen(str);j++)
        {
            if(isdigit(str[g]))
                {
                    str1[str1C] = str[g];
                    str1C++;
                }
        }
        for(j=0;j<strlen(str);j++)
        {
            if (ispunct(str[g]))
                continue;
            str1[str1C] = str[g];
            str1C++;
        }
        for (j=0;j<strlen(str);j++)
        {
             if (ispunct(str[g]))
             {
                str1[str1C] = str[g];
                str1C++;
             }
        }
        if ((fp = freopen(Wfilename, "w", stdout)) == NULL)
            exit(EXIT_FAILURE);
        printf("\n%s", str1);
    }
    fclose(fp);
    fclose(fp1);
}


