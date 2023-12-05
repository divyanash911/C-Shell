#ifndef PEEK_H 
#define PEEK_H

#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int compare(const void *a, const void *b);
void peek_execution(char* newtoken,int a_flag,int l_flag,char* directory,char* prev_dir);


#endif