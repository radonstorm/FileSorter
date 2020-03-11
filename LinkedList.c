/*
** Name: Jack Lardner
** Student ID: 183*****
**
** Contains methods related to linked list operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

/* allocates and sets up a linked list struct */
LinkedList* createLinkedList(int inNumAttributes)
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    (*list).head = NULL;
    (*list).tail = NULL;
    (*list).numAttributes = inNumAttributes;
    return list;
}

/* creates a new node */
LinkedListNode* createNode(LinkedList* list, char** inData)
{
    int ii;
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    node->data = (char**)malloc((list->numAttributes) * sizeof(char*));

    for (ii = 0; ii < list->numAttributes; ii++)
    {
        node->data[ii] = (char*)malloc(strlen(inData[ii]) * sizeof(char) + 1);
        strcpy(node->data[ii], inData[ii]);
    }
    (*node).next = NULL;
    return node;
}

/* adds a node at the end of a linked list */
void addNode(LinkedList* list, char** inData)
{
    LinkedListNode* newNode = createNode(list, inData);

    if ((*list).head == NULL)
    {
        (*list).head = newNode;
        (*list).tail = newNode;
    }
    else
    {
        (*(*list).tail).next = newNode;
        (*list).tail = newNode;
    }
}

/* traverses list, freeing each node, then the list itself */
void freeList(LinkedList* list)
{
    LinkedListNode *node, *nextNode;
    int ii;

    node = (*list).head;
    while(node != NULL)
    {
        nextNode = (*node).next;
        for (ii = 0; ii < list->numAttributes; ii++)
        {
            free(node->data[ii]);
        }
        free((*node).data);
        free(node);
        node = nextNode;
    }
    free(list);
}

/* used for debugging */
void printList(LinkedList* list)
{
    int ii;
    LinkedListNode* current;

    current = list->head;
    while (current != NULL)
    {
        for (ii = 0; ii < list->numAttributes; ii++)
        {
            printf("%s\n", current->data[ii]);
        }
        current = current->next;
    }
}

/*
    Insertion sort method
    Returns a pointer to the new sorted linked list
*/
LinkedList* insertionSort(LinkedList* oldList, int column, int sortType)
{
    LinkedList* newList;
    LinkedListNode *oldCurrentNode, *newCurrentNode, *nextNode;

    newList = createLinkedList(oldList->numAttributes);
    oldCurrentNode = oldList->head;

    /* go through the old list */
    while (oldCurrentNode != NULL)
    {
        nextNode = oldCurrentNode->next;
        if (sortType == 1)
        {
            /* if the new list is empty OR oldCurrentNode is smaller than the head node */
            if (newList->head == NULL || strcmp(newList->head->data[column], oldCurrentNode->data[column]) >= 0)
            {
                /* replace head of new list with oldCurrentNode */
                oldCurrentNode->next = newList->head;
                newList->head = oldCurrentNode;
            }
            else
            {
                /* go through the new list to find a place to put oldCurrentNode */
                newCurrentNode = newList->head;
                while (newCurrentNode->next != NULL && strcmp(newCurrentNode->next->data[column], oldCurrentNode->data[column]) < 0)
                {
                    newCurrentNode = newCurrentNode->next;
                }

                /* place oldCurrentNode after newCurrentNode in the new list */
                oldCurrentNode->next = newCurrentNode->next;
                newCurrentNode->next = oldCurrentNode;
            }
            oldCurrentNode = nextNode;
        }

        /* same as above, but with the comparison reversed for the opposite order*/
        else
        {
            if (newList->head == NULL || strcmp(newList->head->data[column], oldCurrentNode->data[column]) <= 0)
            {
                oldCurrentNode->next = newList->head;
                newList->head = oldCurrentNode;
            }
            else
            {
                newCurrentNode = newList->head;
                while (newCurrentNode->next != NULL && strcmp(newCurrentNode->next->data[column], oldCurrentNode->data[column]) > 0)
                {
                    newCurrentNode = newCurrentNode->next;
                }
                oldCurrentNode->next = newCurrentNode->next;
                newCurrentNode->next = oldCurrentNode;
            }
            oldCurrentNode = nextNode;
        }
    }

    /* 
        free the oldList pointer, but not the nodes (using freeList()) 
        because they are still being used in newList
    */
    free(oldList);
    return newList;
}