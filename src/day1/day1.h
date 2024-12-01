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

void day1Task1()
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
        char buffer[bufferSize];

        // Read until whitespace
        while(string[i] != ' ')
        {
            buffer[bufferIndex] = string[i];
            i++;
            bufferIndex++;
        }
        // Convert value from string to int
        int leftValue = atoi(buffer);
        // Insert into tree
        insertNode(&leftTree, leftValue);

        // Reset buffer index
        bufferIndex = 0;

        // Skip whitespace
        while(string[i] == ' ')
        {
            i++;
        }
        
        // Read until line end
        while(string[i] != '\n')
        {
            buffer[bufferIndex] = string[i];
            i++;
            bufferIndex++;
        }
        // Convert value from string to int
        int rightValue = atoi(buffer);
        // Insert into tree
        insertNode(&rightTree, rightValue);

        // Reset buffer index
        bufferIndex = 0;
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

    printf("%ld\n", differenceSum);
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

#endif //DAY_1_H