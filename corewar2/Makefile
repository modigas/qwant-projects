# Please add your object dependancies into OBJECTS variable
# Please add $(SOURCES) variable before .c file, but not as a target
# Source files must be saved in "sources" directory
# Header files must be saved in "headers" directory
# within .c file, include "../headers/" before your header filename 
# (until I find a way to optimize it; currently, there is an issue with a text editor)

VPATH=sources headers
CC=gcc
CFLAGS=-g3 -fsanitize=address -Wall -Wextra -O -pipe -Iheaders
OBJECTS=main.o getFileNameOption.o myString.o openFiles.o cursors.o gamearena.o
SOURCES=sources/

default: corewar

corewar: $(OBJECTS)
	$(CC) $(CFLAGS) -o corewar $(OBJECTS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $(SOURCES)main.c 

getFileNameOption.o: getFileNameOption.c getFileNameOption.h
	$(CC) $(CFLAGS) -c $(SOURCES)getFileNameOption.c 

myString.o: myString.c myString.h
	$(CC) $(CFLAGS) -c $(SOURCES)myString.c

openFiles.o: openFiles.c openFiles.h
	$(CC) $(CFLAGS) -c $(SOURCES)openFiles.c

cursors.o: cursors.c cursors.h
	$(CC) $(CFLAGS) -c $(SOURCES)cursors.c

gamearena.o: gamearena.c gamearena.h
	$(CC) $(CFLAGS) -c $(SOURCES)gamearena.c

re: clean corewar

clean:
	rm -f *.o