/*
** Name: Jack Lardner
** Student ID: 183*****
**
** Defines methods relating to file IO
*/
#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H
#include "LinkedList.h"

/* reads inFile and returns contents in linked list */
LinkedList* readFile(char* inFile, int* exitCode);

/* writes contents of a linked list to outFile. Returns int for error code */
int writeFile(LinkedList* list, char* outFile, char* inFile);

#endif