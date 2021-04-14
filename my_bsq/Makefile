CC=gcc
CFLAGS=-g3 -fsanitize=address -Wall -Wextra -O -pipe -Iheaders
OBJECTS=main.o readFile.o setupBitfield.o findBsq.o printBsq.o structs.o utils.o

default: my_bsq

my_bsq: $(OBJECTS)
	$(CC) $(CFLAGS) -o my_bsq $(OBJECTS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

readFile.o: readFile.c readFile.h
	$(CC) $(CFLAGS) -c readFile.c

setupBitfield.o: setupBitfield.c setupBitfield.h
	$(CC) $(CFLAGS) -c setupBitfield.c

findBsq.o: findBsq.c findBsq.h
	$(CC) $(CFLAGS) -c findBsq.c

printBsq.o: printBsq.c printBsq.h
	$(CC) $(CFLAGS) -c printBsq.c

structs.o: structs.c structs.h
	$(CC) $(CFLAGS) -c structs.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

re: clean my_bsq

clean:
	rm -f *.o