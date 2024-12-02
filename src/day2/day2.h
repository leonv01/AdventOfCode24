#ifndef DAY_2_H
#define DAY_2_H

#include "utils.h"

typedef struct Node_t
{
    int value;
    struct Node_t *next;
} Node_t;

typedef struct List_t
{
    Node_t *root;
    size_t count;
} List_t;

typedef struct TestReport_t
{
    List_t *list;
} TestReport_t;

List_t *addTestResults(char *string, size_t *i);
void freeList(List_t *list);
void printList(List_t *list);
int isTestReportValid(List_t *list);

void day2Task1()
{
    long fileSize;
    long lineCount;

    char *string = loadFileToBuffer( &fileSize, &lineCount, "C:\\Users\\leonv\\Documents\\AdventOfCode24\\src\\day2\\input");
    size_t i;
    size_t validCount = 0;

    for(i = 0; i < fileSize; i++)
    {
        List_t *list = addTestResults(string, &i);
        if(isTestReportValid(list) == 1)
        {
            validCount++;
        }
        freeList(list);
    }

    printf("Day 2 Task 1 result: %lld\n", validCount);
}

List_t *addTestResults(char *string, size_t *i)
{
    char buffer[16];
    memset(&buffer, 0, sizeof(buffer));
    char c;
    size_t bufferIndex = 0;

    List_t *list = (List_t*)(malloc(sizeof(List_t)));
    Node_t *currentNode = NULL;
    int nodeCount = 0;

    while((c = string[*i]) != '\n')
    {
        c = string[*i];
        while((c != ' ') && (c != '\n'))
        {
            buffer[bufferIndex] = c;
            bufferIndex++;
            (*i)++;
            c = string[*i];
        }
        while((c = string[*i]) == ' ')
        {
            (*i)++;
        }

        bufferIndex = 0;
        int num = atoi(buffer);
        Node_t *node = (Node_t*)(malloc(sizeof(Node_t)));
        node->value = num;
        node->next = NULL;

        if(currentNode == NULL)
        {
            currentNode = node;
            nodeCount++;
        }
        else
        {
            Node_t *nodePtr = currentNode;
            while(1)
            {
                if(nodePtr->next == NULL)
                {
                    nodePtr->next = node;
                    nodeCount++;
                    break;
                }
                else
                {
                    nodePtr = nodePtr->next;
                }
            }
        }

        memset(&buffer, 0, sizeof(buffer));
    }

    list->root = currentNode;
    list->count = nodeCount;
    return list;
}

void printList(List_t *list)
{
    Node_t *ptr = list->root;

    while(ptr != NULL)
    {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");

}

int isTestReportValid(List_t *list)
{
    int valid = 0;

    Node_t *ptr = list->root;

    int lastValue = list->root->value;
    ptr = list->root->next;

    while(ptr != NULL)
    {
        if(lastValue < ptr->value)
        {
            int diff = lastValue - ptr->value;
            if(diff <= -1 && diff >= -3)
            {
                lastValue = ptr->value;
                valid = 1;
            }
            else
            {
                valid = 0;
                break;
            }
        }
        else
        {
            valid = 0;
            break;
        }
        ptr = ptr->next;
    }

    if(valid == 0)
    {
        lastValue = list->root->value;
        ptr = list->root->next;
        
        while(ptr != NULL)
        {
            if(lastValue > ptr->value)
            {
                int diff = lastValue - ptr->value;
                if(diff >= 1 && diff <= 3)
                {
                    lastValue = ptr->value;
                    valid = 1;
                }
                else
                {
                    valid = 0;
                    break;
                }
            }
            else
            {
                valid = 0;
                break;
            }
            ptr = ptr->next;
        }
    }

    return valid;
}

void freeList(List_t *list)
{
    Node_t *ptr = list->root;
    while(ptr != NULL)
    {
        Node_t *nextPtr = ptr->next;
        free(ptr);
        ptr = nextPtr;
    }
}

#endif //DAY_2_H