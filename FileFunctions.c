/*
** Name: Jack Lardner
** Student ID: 183*****
**
** Contains methods relating to file IO
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LinkedList.h"

/* 
    uses int pointer for error codes
    0 for success
   -1 for file open fail
*/
LinkedList* readFile(char* inFile, int* exitCode)
{
    FILE* file = fopen(inFile, "r");
    LinkedList* list;
    if (file == NULL)
    {
        perror("Error opening input file");
        *exitCode = -1;
    }
    else
    {
        char temp[500];
        char letter;
        char* token;
        char delimiters[] = ",\n";
        char** array;
        int ii, numAttributes = 0;

        /* finds how many attributes and stores in numAttributes
           then create linked list */
        fgets(temp, 500, file);
        for (ii = 0; ii < strlen(temp); ii++)
        {
            letter = temp[ii];
            if (letter == ',')
            {
                numAttributes++;
            }
        }
        numAttributes++;
        
        /* declaring list and allocating temp array */
        list = createLinkedList(numAttributes);
        array = (char**)malloc((numAttributes) * sizeof(char*));

        /* storing entries into linked list */
        while (fgets(temp, 500, file) != NULL)
        {
            token = strtok(temp, delimiters);
            ii = 0;
            while (token != NULL)
            {
                array[ii] = malloc(strlen(token) * sizeof(char) + 1);
                strcpy(array[ii], token);

                token = strtok(NULL, delimiters);
                ii++;
            }
            addNode(list, array);
            
            for (ii = 0; ii < numAttributes; ii++)
            {
                free(array[ii]);
            }
            
        }

        #ifdef DEBUG
            printf("\n~ Number of attributes: %d\n~ Number of entries: %d\n", numAttributes, numEntries);
            printf("\n~ Output of linked list:\n\n");
            printList(list);
            printf("\n");
        #endif

        free(array);
        *exitCode = 0;
        fclose(file);
    }

    return list;
}

/* Returns int for error code
   0 for success
  -1 for file write fail
*/
int writeFile(LinkedList* list, char* outFileName, char* inFileName)
{
    int retVal = 0;
    FILE* outFile = fopen(outFileName, "w");

    /* error checking */
    if (outFile == NULL)
    {
        perror("Error writing to output file");
        retVal = -1;
    }
    else
    {
        FILE* inFile;
        char temp[500];
        LinkedListNode* current;
        int ii;

        /* 
            writes the first line of the input file
            to the first line of the output file
        */ 
        inFile = fopen(inFileName, "r");
        fgets(temp, 500, inFile);
        fclose(inFile);
        fputs(temp, outFile);

        /* traverse through linked list */
        current = list->head;
        while (current != NULL)
        {
            for (ii = 0; ii < list->numAttributes; ii++)
            {
                fputs(current->data[ii], outFile);
                /*
                    write a comma at the end of
                    each attribute except for the last one
                */
                if (ii != list->numAttributes - 1)
                {
                    fputc(',', outFile);
                }    
            }
            fputc('\n', outFile);
            current = current->next;
        }
        fclose(outFile);
    }
    return retVal;
}