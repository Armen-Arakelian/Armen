#include <stdio.h>
#include <stdlib.h>

char * process(char * resultStr, const char * textLines[],
    int linesNum, const char * extraStr)
    {
        char * pres = 0;
        int i, max = 0, g,count1 = 0;
        int count[linesNum];
        for(i=0;i<linesNum;i++)
        {
            count[i] = 0;
        }
        for (i=0;i<linesNum;i++)
        {
            pres = textLines[i];

            for (pres = strstr(pres, extraStr); pres!=NULL; count[i]++)
            {
               pres = strstr(pres + strlen(extraStr), extraStr);
            }

            if (count[i]>max)
            {
                max = count[i];
                g = i;
            }
        }
        for (i=0;i<linesNum;i++)
        {
            if (max == count[i]) count1++;
            if (count1>1)
            {
                sprintf(resultStr, "0 NULL %s", extraStr);
                return  resultStr;
            }
        }
        if (!max)
        {
            sprintf(resultStr, "0 NULL %s", extraStr);
            return  resultStr;
        }
        sprintf(resultStr, "%i %s", max, textLines[g]);
        return  resultStr;
    }

