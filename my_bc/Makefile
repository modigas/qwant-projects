CC=gcc
CFLAGS=-g3 -fsanitize=address -Wall -Wextra -O -pipe -Iheaders
OBJECTS=main.o getTokens.o infixToPostfix.o utils.o checkers.o stack.o postfixEvaluator.o

default: my_bc

my_bc: $(OBJECTS)
	$(CC) $(CFLAGS) -o my_bc $(OBJECTS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

getTokens.o: getTokens.c getTokens.h
	$(CC) $(CFLAGS) -c getTokens.c

infixToPostfix.o: infixToPostfix.c infixToPostfix.h
	$(CC) $(CFLAGS) -c infixToPostfix.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

checkers.o: checkers.c checkers.h
	$(CC) $(CFLAGS) -c checkers.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

postfixEvaluator.o: postfixEvaluator.c postfixEvaluator.h
	$(CC) $(CFLAGS) -c postfixEvaluator.c

re: clean my_bc

clean:
	rm -f *.o
