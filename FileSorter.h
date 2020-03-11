#ifndef MAIN_H
#define MAIN_H

#include "LinkedList.h"

/* Function declarations */
/* prints "usage" message when program is executed incorrectly */
void printUsage();

/* 
    User input
    returns index of column to sort
*/
int menu(LinkedList* list, int* sortType);

#endif