## Name: Jack Lardner
## Student ID: 183*****
##
## Make file for UCP Assignment Semester 2 2016
## Add -DDEBUG to CFLAGS to enable debug messages

CC = gcc
CFLAGS = -Wall -ansi -pedantic -c
OBJ = FileSorter.o LinkedList.o FileFunctions.o
EXCE = FileSorter
default : $(EXCE)

$(EXCE) : $(OBJ)
	$(CC) $(OBJ) -o $(EXCE)

FileSorter.o : FileSorter.c FileSorter.h LinkedList.c LinkedList.h FileFunctions.c FileFunctions.h
	$(CC) $(CFLAGS) FileSorter.c

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) LinkedList.c

FileFunctions.o : FileFunctions.c
	$(CC) $(CFLAGS) FileFunctions.c

clean :
	rm -f $(OBJ) $(TEST_OBJ)

cleanall :
	rm -f $(OBJ) $(EXCE)