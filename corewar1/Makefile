# Please add your object dependancies into OBJECTS variable
# Please add $(SOURCES) variable before .c file, but not as a target
# Source files must be saved in "sources" directory
# Header files must be saved in "headers" directory
# within .c file, include "../headers/" before your header filename 
# (until I find a way to optimize it; currently, there is an issue with a text editor)

VPATH=sources headers
CC=gcc
CFLAGS=-g3 -fsanitize=address -Wall -Wextra -O -pipe -Iheaders
OBJECTS=main.o isProperFilename.o readFile.o fillHeader.o deleteComments.o fillCode.o linkedList.o isLiveToXor.o getOpAndArg.o isZjmpToAff.o fillLabel.o codeToString.o toStringHeader.o toStringCodeHeader.o
SOURCES=sources/

default: myrcc

myrcc: $(OBJECTS)
	$(CC) $(CFLAGS) -o myrcc $(OBJECTS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $(SOURCES)main.c 

isProperFilename.o: isProperFilename.c isProperFilename.h
	$(CC) $(CFLAGS) -c $(SOURCES)isProperFilename.c

readFile.o: readFile.c readFile.h
	$(CC) $(CFLAGS) -c $(SOURCES)readFile.c

fillHeader.o: fillHeader.c fillHeader.h
	$(CC) $(CFLAGS) -c $(SOURCES)fillHeader.c

deleteComments.o: deleteComments.c deleteComments.h
	$(CC) $(CFLAGS) -c $(SOURCES)deleteComments.c

fillCode.o: fillCode.c fillCode.h
	$(CC) $(CFLAGS) -c $(SOURCES)fillCode.c

linkedList.o: linkedList.c linkedList.h
	$(CC) $(CFLAGS) -c $(SOURCES)linkedList.c

isLiveToXor.o: isLiveToXor.c isLiveToXor.h
	$(CC) $(CFLAGS) -c $(SOURCES)isLiveToXor.c

getOpAndArg.o: getOpAndArg.c getOpAndArg.h
	$(CC) $(CFLAGS) -c $(SOURCES)getOpAndArg.c

isZjmpToAff.o: isZjmpToAff.c isZjmpToAff.h
	$(CC) $(CFLAGS) -c $(SOURCES)isZjmpToAff.c

fillLabel.o: fillLabel.c fillLabel.h
	$(CC) $(CFLAGS) -c $(SOURCES)fillLabel.c

codeToString.o: codeToString.c codeToString.h
	$(CC) $(CFLAGS) -c $(SOURCES)codeToString.c

toStringHeader.o: toStringHeader.c toStringHeader.h
	$(CC) $(CFLAGS) -c $(SOURCES)toStringHeader.c

toStringCodeHeader.o: toStringCodeHeader.c toStringCodeHeader.h
	$(CC) $(CFLAGS) -c $(SOURCES)toStringCodeHeader.c

re: clean myrcc

clean:
	rm -f *.o