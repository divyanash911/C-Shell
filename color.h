#ifndef COLOR_H
#define COLOR_H

#include <sys/stat.h>
void print_in_color(char* string,char* print_string);
void print_permissions(mode_t mode);
void perrorf(char* s);
#endif