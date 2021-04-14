CC = gcc
TARGET = my_mouse
INCLUDE = -I../inc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -O -pipe -Iheaders
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXEC_PATH = ../

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $(EXEC_PATH)$@

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $^ -o $@

.PHONY: clean re

clean:
	rm *.o

re:
	rm *.o
	make