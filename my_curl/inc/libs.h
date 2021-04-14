#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <utils.h>

#define HTTP_PORT 80
#define INIT_SIZE 200
#define CONNECT_ERROR -1
#define READ_SIZE 100
#define TOKEN_SIZE 100
#define HTTP_200 "HTTP/1.1 200"