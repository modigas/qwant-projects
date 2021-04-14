#include "../headers/tar.h"

size_t my_strlen(char* str)
{
    size_t i = -1;
    while(str[++i] != '\0');
    return i;
}

char* my_strncpy(char* dest, const char* src, int size)
{
    while(size-- && (*dest++ = *src++))
        ;
    return dest;
}

char* my_strcpy(char* dest, const char* src)
{
    while((*dest++ = *src++))
        ;
    return dest;
}