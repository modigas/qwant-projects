VPATH = sources headers

NAME = my_tar

SRCS =	sources/

CFLAGS = -g3 -Wall -Wextra -fsanitize=address
# CFLAGS = -g3 -Wall -Wextra
OBJECTS = tar.o append_by_time.o conversion.o creat_file.o file_manipulation.o get_opt.o recursion_of_dir_files.o write_content.o extract_files.o list_files.o utility_functions.o

default: $(NAME)

$(NAME): $(OBJECTS)
	gcc $(CFLAGS) -o $(NAME) $(OBJECTS)

tar.o: tar.c tar.h
	gcc $(CFLAGS) -c $(SRCS)tar.c

append_by_time.o: append_by_time.c tar.h
	gcc $(CFLAGS) -c $(SRCS)append_by_time.c

conversion.o: conversion.c tar.h
	gcc $(CFLAGS) -c $(SRCS)conversion.c

creat_file.o: creat_file.c tar.h
	gcc $(CFLAGS) -c $(SRCS)creat_file.c

file_manipulation.o: file_manipulation.c tar.h
	gcc $(CFLAGS) -c $(SRCS)file_manipulation.c

get_opt.o: get_opt.c tar.h
	gcc $(CFLAGS) -c $(SRCS)get_opt.c

recursion_of_dir_files.o: recursion_of_dir_files.c tar.h
	gcc $(CFLAGS) -c $(SRCS)recursion_of_dir_files.c 

write_content.o: write_content.c tar.h
	gcc $(CFLAGS) -c $(SRCS)write_content.c

extract_files.o: extract_files.c tar.h
	gcc $(CFLAGS) -c $(SRCS)extract_files.c

list_files.o: list_files.c tar.h
	gcc $(CFLAGS) -c $(SRCS)list_files.c

utility_functions.o: utility_functions.c tar.h
	gcc $(CFLAGS) -c $(SRCS)utility_functions.c

re: clean $(NAME)

clean:
	rm -f *.o