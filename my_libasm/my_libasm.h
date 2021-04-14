#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

ssize_t my_read(int fd, void* buf, size_t count);
ssize_t my_write(int fd, const void* buf, size_t count);
size_t my_strlen(const char* str);
char* my_strchr(const char* str, int c);
void* my_memset(void*str, int c, size_t n);
void* my_memcpy(void* dest, const void* src, size_t n);
int my_strcmp(const char* str1, const char* str2);
void* my_memmove(void* str1, const void* str2, size_t n);
int my_strncmp(const char* str1, const char* str2, size_t n);
int my_strcasecmp(const char* s1, const char* s2);
char* my_index(const char *string, int c);