#ifndef PING_H
#define PING_h

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

void exec_ping(char** ping_array);

void activities_b(struct background_struct* head);

#endif