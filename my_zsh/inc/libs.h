#ifndef ZSH_H
#define ZSH_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <queue.h>
#include <utils.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>

#define YELLOW_B "\033[01;33m"
#define RESET_COLOR "\033[0m"
#define RED_B "\033[1;31m"
#define GREEN_B "\033[1;32m"

#define INIT_SIZE 1000
#define unused __attribute__((unused))

#define CONTROL_OPERATOR '\n'
#define BLANK "\t "
#define BUILT_IN 'B'
#define OS_COMMAND 'O'
#define EXECUTABLE 'E'
#define OPT_EXIST 'Y'
#define OPT_NONE 'N'

#endif