#ifndef NEONATE_H
#define NEONATE_H

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include<signal.h>

void die(const char *s);

void disableRawMode();
void enableRawMode();
void e_neonate(char ic,int n);


#endif