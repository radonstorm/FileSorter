/*
** Name: Jack Lardner
** Student ID: 183*****
**
** Contains main method, user input menu and insertion sort method
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileSorter.h"
#include "LinkedList.h"
#include "FileFunctions.h"

int main(int argc, char* argv[])
{
    /* 
       Return values:
        0: Success
       -1: Invalid command line arguments
       -2: FileIO error (file does not exist, unable to write, etc)
    */

    int retVal = 0;

    /* checking validity of command line arguments */
    /* if there aren't 5 arguments then the program has been used incorrectly */
    if (argc < 5)
    {
        retVal = -1;
        printf("Not enough arguments\n");
        printUsage();
    }
    else if (argc > 5)
    {
        retVal = -1;
        printf("Too many arguments\n");
        printUsage();
    }

    /* checking the 1st argument is a valid switch */
    else if ((strcmp(argv[1], "i") != 0) && (strcmp(argv[1], "o") != 0))
    {
        retVal = -1;
        printf("%s is an invalid switch\n", argv[1]);
        printUsage();
    }

    /* checking the 3rd argument is a valid switch */
    else if ((strcmp(argv[3], "i") != 0) && (strcmp(argv[3], "o") != 0))
    {
        retVal = -1;
        printf("%s is an invalid switch\n", argv[3]);
        printUsage();
    }

    /* checking there is exactly one input and output file */
    else if (strcmp(argv[1], argv[3]) == 0)
    {
        retVal = -1;
        printf("Too many input/output files\n");
        printUsage();
    }

    /* continue with program */
    else
    {
        /* variable declarations */
        LinkedList* list;
        char *inFile, *outFile;
        int readExitCode, writeExitCode, sortType, sortColumn;

        #ifdef DEBUG
            int ii;
            printf("\n~ Command line arguements passed:\n");
            for (ii = 0; ii < argc; ii++)
            {
                printf("~ argv[%d]: %s\n", ii, argv[ii]);
            }
            printf("\n\n");
        #endif

        /* Warn the user if the input and output file are the same */
        if (strcmp(argv[2], argv[4]) == 0)
        {
            printf("WARNING: The input file will be overwritten\n");
        }

        /* if/else statement to correctly assign inFile and outFile variables */
        if (strcmp(argv[1], "i") == 0)
        {
            inFile = argv[2];
            outFile = argv[4];
        }
        else
        {
            inFile = argv[4];
            outFile = argv[2];
        }
        #ifdef DEBUG
            printf("\n~ inFile: %s\n~ outFile: %s\n\n", inFile, outFile);
        #endif

        /* read file and store in linked list */
        list = readFile(inFile, &readExitCode);
        #ifdef DEBUG
            printf("\n~ readFile exit code: %d\n\n", readExitCode);
        #endif
        /* error handling */
        if (readExitCode != 0)
        {
            retVal = -2;
        }
        else
        {            
            /* asks for user input */
            sortColumn = menu(list, &sortType);

            /* create a sorted list */
            list = insertionSort(list, sortColumn, sortType);

            /* write linked list to file */
            writeExitCode = writeFile(list, outFile, inFile);
            if (writeExitCode != 0)
            {
                retVal = -2;
            }
            
            #ifdef DEBUG
                printf("\n~ writeFile exit code: %d\n\n", writeExitCode);
            #endif

            freeList(list);
        }
    }
    return retVal;    
}

/* 
    Prints usage method
    Neater to have one method to print it
    than repeat lines in argv[] check in main()
*/
void printUsage()
{
    printf("Usage: FileSorter [OPTION] [FILE] [OPTION] [FILE]\n");
    printf("  i\tFlag for input file to sort\n");
    printf("  o\tFlag for output file to put sorted contents of input file\n");
    #ifdef DEBUG
        printf("\n~ Return values:\n");
        printf("~ 0: Success\n");
        printf("~ -1: Incorrect command line arguments passed\n");
        printf("~ -2: FileIO error\n");
    #endif
}

/*
    menu for user input
    asks for column to sort and how to sort it
*/
int menu(LinkedList* list, int* sortType)
{
    int ii;
    int column;
    char numbers[] = "1234567890";
    printf("Which column would you like sorted?: \n");
    do
    {
        for (ii = 0; ii < list->numAttributes; ii++)
        {
            printf("(%d): Column %d\n", ii + 1, ii + 1);
        }
        scanf("%d", &column);
    }
    while (column > list->numAttributes || column <= 0);

    do
    {
        /* 
            if column is a string datatype, swap sortType around
            this is because of the way strcmp compares strings
        */
        if (strpbrk(list->head->data[column - 1], numbers) == NULL)
        {
            printf("(1): Descending order\n");
            printf("(2): Ascending order\n");
            scanf("%d", sortType);
        }
        else
        {
            printf("(1): Ascending order\n");
            printf("(2): Descending order\n");
            scanf("%d", sortType);
        }
    }
    while (*sortType > 2 || *sortType < 1);
    return column - 1;
}