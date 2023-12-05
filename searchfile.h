#ifndef SEARCHFILE_H
#define SEARCHFILE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <dirent.h>
void searchFile(char *dirPath, char *filename,int d_flag,int e_flag,int f_flag,char** files,int* index);


#endif