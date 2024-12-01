#ifndef DAY_1_H
#define DAY_1_H

#include "utils.h"

/* -------------------------- Tree node definition -------------------------- */
typedef struct Node_t
{
    int value;
    struct Node_t *leftChild;
    struct Node_t *rightChild;
} Node_t;

/* ---------------------- Binary search tree definition --------------------- */
typedef struct BinarySearchTree_t
{
    Node_t *root;
} BinarySearchTree_t;

/* --------------------------- Tree help functions -------------------------- */
/**
 * @brief Inserts a node with the passed value
 * 
 * @param tree 
 * @param value 
 */
static void insertNode(BinarySearchTree_t *tree, int value);

/**
 * @brief Get the Lowest Node object
 * 
 * @param tree 
 * @return Node_t* 
 */
static Node_t *getLowestNode(BinarySearchTree_t *tree);

/**
 * @brief Get the Occurance object
 * 
 * @param tree 
 * @param value 
 * @return int 
 */
static int getOccurance(BinarySearchTree_t *tree, int value);

static void getValuesOfLine(char *string, size_t *index, int *value1, int *value2);

void day1Task1(void)
{
    long fileSize;
    long lineCount;

    char *string = loadFileToBuffer( &fileSize, &lineCount, "C:\\Users\\leonv\\Documents\\AdventOfCode24\\src\\day1\\input.txt");
    size_t i;

    long differenceSum = 0;

    const int bufferSize = 16;
    int bufferIndex = 0;

    BinarySearchTree_t leftTree = { 0 };
    BinarySearchTree_t rightTree = { 0 };

    leftTree.root = NULL;
    rightTree.root = NULL;

    // Iterate through each character
    for(i = 0; i < fileSize; i++)
    {
        int leftValue;
        int rightValue;
        getValuesOfLine(string, &i, &leftValue, &rightValue);

        insertNode(&leftTree, leftValue);
        insertNode(&rightTree, rightValue);
    }

    // Iterate for each line
    for(i = 0; i < lineCount; i++)
    {
        Node_t *leftNode = getLowestNode(&leftTree);
        Node_t *rightNode = getLowestNode(&rightTree);

        int difference = leftNode->value - rightNode->value;
        if(difference < 0)
        {
            difference *= (-1);
        }
        differenceSum += difference;
    }

    printf("Day 1 Task 1 result: %ld\n", differenceSum);
}

void day1Task2(void)
{
    long fileSize;
    long lineCount;

    char *string = loadFileToBuffer( &fileSize, &lineCount, "C:\\Users\\leonv\\Documents\\AdventOfCode24\\src\\day1\\input2.txt");
    size_t i;

    long occuranceSum = 0;

    const int bufferSize = 16;
    int bufferIndex = 0;

    BinarySearchTree_t leftTree = { 0 };
    BinarySearchTree_t rightTree = { 0 };

    leftTree.root = NULL;
    rightTree.root = NULL;

    // Iterate through each character
    for(i = 0; i < fileSize; i++)
    {
        int leftValue;
        int rightValue;
        getValuesOfLine(string, &i, &leftValue, &rightValue);

        insertNode(&leftTree, leftValue);
        insertNode(&rightTree, rightValue);
    }

    // Iterate for each line
    int lastValue = 0;
    int lastOccurance = 0;
    for(i = 0; i < lineCount; i++)
    {
        Node_t *leftNode = getLowestNode(&leftTree);
        int occurance = 0;

        int result = 0;
        if(lastValue != leftNode->value)
        {
            occurance = getOccurance(&rightTree, leftNode->value);
            lastValue = leftNode->value;
            lastOccurance = occurance;
        }
        
        result = lastOccurance * lastValue;

        occuranceSum += result;
    }

    printf("Day 2 Task 2 result: %ld\n", occuranceSum); 
}


void insertNode(BinarySearchTree_t *tree, int value)
{
    Node_t *node = (Node_t*)(malloc(sizeof(Node_t)));
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;

    if(tree->root == NULL)
    {
        tree->root = node;
        return;
    }

    Node_t *nodePtr = tree->root;
    do
    {
        if(node->value >= nodePtr->value)
        {
            if(nodePtr->rightChild == NULL)
            {
                nodePtr->rightChild = node;
                break;
            }
            else
            {
                nodePtr = nodePtr->rightChild;
            }
        }
        else
        {
            if(nodePtr->leftChild == NULL)
            {
                nodePtr->leftChild = node;
                break;
            }
            else
            {
                nodePtr = nodePtr->leftChild;
            }
        }
    } while (1);
}

static Node_t *getLowestNode(BinarySearchTree_t *tree)
{
    Node_t *node;

    int isDone = 0;

    Node_t *nodePtr = tree->root;
    Node_t *prevNodePtr = NULL;

    while(nodePtr != NULL)
    {
        // If no left child exist: Check if either right child exist or return childless node
        if(nodePtr->leftChild == NULL)
        {
            // If root has no children
            if(prevNodePtr == NULL)
            {
                node = nodePtr;
                tree->root = nodePtr->rightChild;
                node->rightChild = NULL;
                nodePtr = NULL;
            }
            else
            {
                // If Node Pointer has right child, switch with node in previous pointer
                if(nodePtr->rightChild != NULL)
                {
                    prevNodePtr->leftChild = nodePtr->rightChild;
                }
                else
                {
                    prevNodePtr->leftChild = NULL;
                }

                node = nodePtr;
                node->rightChild = NULL;
                nodePtr = NULL;
            }
        }
        else
        {
            prevNodePtr = nodePtr;
            nodePtr = nodePtr->leftChild;
        }
    }

    return node;
}

static int getOccurance(BinarySearchTree_t *tree, int value)
{
    int occurance = 0;
    Node_t *nodePtr = tree->root;

    while(nodePtr != NULL)
    {
        if(nodePtr->value == value)
        {
            occurance++;
        }
        if(value >= nodePtr->value)
        {
            if(nodePtr->rightChild == NULL)
            {
                break;
            }
            else
            {
                nodePtr = nodePtr->rightChild;
            }
        }
        if(value < nodePtr->value)
        {
            if(nodePtr->leftChild == NULL)
            {
                break;
            }
            else
            {
                nodePtr = nodePtr->leftChild;
            }
        }
    }

    return occurance;
}

static void getValuesOfLine(char *string, size_t *index, int *value1, int *value2)
{
    const int bufferSize = 16;
    int bufferIndex = 0;

    char buffer[bufferSize];

    // Read until whitespace
    while(string[*index] != ' ')
    {
        buffer[bufferIndex] = string[*index];
        (*index)++;
        bufferIndex++;
    }
    // Convert value from string to int
    *value1 = atoi(buffer);

    // Reset buffer index
    bufferIndex = 0;

    // Skip whitespace
    while(string[*index] == ' ')
    {
        (*index)++;
    }
    
    // Read until line end
    while(string[*index] != '\n')
    {
        buffer[bufferIndex] = string[*index];
        (*index)++;
        bufferIndex++;
    }
    // Convert value from string to int
    *value2 = atoi(buffer);
}

#endif //DAY_1_H