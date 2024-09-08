#ifndef FG_H
#define FG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <netdb.h>


void exec_fg(char* pid);
void exec_bg(char* pid);

#endif