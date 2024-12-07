#ifndef DAY_3_H
#define DAY_3_H

#include "utils.h"
#include <string.h>

void day3Task1(void)
{
    long fileSize;
    long lineCount;

    char *string = loadFileToBuffer( &fileSize, &lineCount, "C:\\Users\\leonv\\Documents\\AdventOfCode24\\src\\day3\\input");
    size_t i;

    int isMulValid = 0;
    long result = 0;

    char buffer1[16];
    char buffer2[16];
    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));

    for(i = 0; i < fileSize; i++)
    {
        if(string[i] == 'm' || string[i] == 'M')
        {
            i++;
            if(string[i] == 'u' || string[i] == 'U')
            {
                i++;
                if(string[i] == 'l' || string[i] == 'L')
                {
                    isMulValid = 1;
                }
                else
                {
                    isMulValid = 0;
                }
            }
            else
            {
                isMulValid = 0;
            }
        }
        else
        {
            isMulValid = 0;
        }

        if(isMulValid == 1)
        {
            memset(buffer1, 0, sizeof(buffer1));
            memset(buffer2, 0, sizeof(buffer2));
            i++;
            if(string[i] == '(')
            {
                i++;
                int bufferIdx = 0;
                while(string[i] >= '0' && string[i] <= '9')
                {
                    buffer1[bufferIdx] = string[i];
                    bufferIdx++;
                    i++;
                }
                bufferIdx = 0;
                if(string[i] == ',')
                {
                    i++;
                    while(string[i] >= '0' && string[i] <= '9')
                    {
                        buffer2[bufferIdx] = string[i];
                        bufferIdx++;
                        i++;
                    }
                    if(string[i] == ')')
                    {
                        int value1 = atoi(buffer1);
                        int value2 = atoi(buffer2);

                        result += value1 * value2;
                    }
                }
            }
        }
    }
    
    printf("%ld\n", result);
}

#endif //DAY_3_H