#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *loadFileToBuffer(long *fileSize, long *lineCount, const char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    char *string;
    if(file == NULL)
    {
        printf("Error loading file\n");
        return NULL;
    }
    else
    {
        fseek(file, 0, SEEK_END);
        *fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        string = malloc(*fileSize + 1);
        fread(string, *fileSize, 1, file);
        fclose(file);

        long lines = 0;
        size_t i;
        for(i = 0; i < *fileSize; i++)
        {
            if(string[i] == '\n')
            {
                lines++;
            }
        }

        *lineCount = lines;

        string[*fileSize] = 0;

        return string;
    }
}

void terminateFile(char *string)
{
    free(string);
}

#endif //UTILS_H