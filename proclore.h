#ifndef PROCLORE_H
#define PROCLORE_H

#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void get_executable_path(const char *pid_str);
void exec_proclore(char* newtoken,int* check_flag,int* argument_flag);
void exec_shell_proclore(char* string_pid);


#endif