/*
** Name: Jack Lardner
** Student ID: 183*****
**
** Defines linked list structs and methods related to linked list operations
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
/* Linked list structs */

/* 
    LinkedListNode struct:
    data: array of char pointers to be malloc'd
    next: points to next entry
*/
typedef struct LinkedListNode
{
    char** data;
    struct LinkedListNode* next;
} LinkedListNode;

/* 
    LinkedList struct:
    head: points to start of list
    tail: points to end of list
    numAttributes: stores length of data array in all nodes in the list
*/
typedef struct LinkedList
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int numAttributes;
} LinkedList;

/* Function declarations */

/* allocates and returns a LinkedList struct */
LinkedList* createLinkedList(int inNumAttributes);

/* adds inData to a node using createNode() to the end of list */
void addNode(LinkedList* list, char** inData);

/* goes through list, freeing each node and then the LinkedList pointer */
void freeList(LinkedList* list);

/* used to put inData into a LinkedListNode struct */
LinkedListNode* createNode(LinkedList* list, char** inData);

/* prints contents of linked list. Used for debugging */
void printList(LinkedList* list);

/* 
    Insertion sort method
    adds nodes into a new linked list in a sorted order
    uses strcmp to compare data[column] 
    returns pointer to the new sorted linked list
*/
LinkedList* insertionSort(LinkedList* oldList, int column, int sortType);

#endif