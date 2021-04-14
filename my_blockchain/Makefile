
CC=gcc
CFLAGS=-g3 -fsanitize=address -Wall -Wextra -O -pipe
LIBS=libs.h structs.h

default: my_blockchain

my_blockchain: main.o createBlockchain.o readAndWriteFile.o fillInput.o stateAndSync.o addNodeBlock.o rmNodeBlock.o
	$(CC) $(CFLAGS) -o my_blockchain main.o createBlockchain.o readAndWriteFile.o fillInput.o stateAndSync.o addNodeBlock.o rmNodeBlock.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

createBlockchain.o: createBlockchain.c createBlockchain.h
	$(CC) $(CFLAGS) -c createBlockchain.c

readAndWriteFile.o: readAndWriteFile.c readAndWriteFile.h
	$(CC) $(CFLAGS) -c readAndWriteFile.c

fillInput.o: fillInput.c fillInput.h
	$(CC) $(CFLAGS) -c fillInput.c

stateAndSync.o: stateAndSync.c stateAndSync.h
	$(CC) $(CFLAGS) -c stateAndSync.c

addNodeBlock.o: addNodeBlock.c addNodeBlock.h
	$(CC) $(CFLAGS) -c addNodeBlock.c

rmNodeBlock.o: rmNodeBlock.c rmNodeBlock.h
	$(CC) $(CFLAGS) -c rmNodeBlock.c

re: clean my_blockchain

clean:
	rm -f count *.o *~
