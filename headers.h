#ifndef HEADERS_H_
#define HEADERS_H_
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
#define MAX_PATH_LENGTH 256
#define PATH_MAX 4096
#define TOTAL_PATHS 10
#define MAX_COMMANDS 10
#define BUFFER_LEN 10000
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define PATH_MAX 4096
#define LEN 4096
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAX_COMMANDS_PAST 15
#define MAX_LEN 100
#define MAX_BUFFER_SIZE 4096
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define reset "\e[0m"
#include "prompt.h"
#include "color.h"
#include "pastevents.h"
#include "peek.h"
#include "proclore.h"
#include "searchfile.h"
#include "stringhelper.h"
#include "iman.h"
#include "pipe.h"
#include "fg.h"
#include "neonate.h"
#include "global.h"
#include "ping.h"
// void activities_b(struct background_struct* bg_processes);
// void print_in_color(char* string,char* print_string);
// void print_permissions(mode_t mode);
// void sighandler(int sig);
// void print_bg(struct background_struct* bg);
// void insert(struct file_buffer* f,char* string);
// void loadfile(struct file_buffer* f);
// void write_queue(struct file_buffer* f,char* dir);
// void print_queue(struct file_buffer* f);
// int check_valid(struct file_buffer* f,char* new_command);
// int compare(const void *a, const void *b);
// void peek_execution(char* newtoken,int a_flag,int l_flag,char* directory,char* prev_dir);
// void get_executable_path(const char *pid_str);
// void exec_proclore(char* newtoken,int* check_flag,int* argument_flag);
// void exec_shell_proclore(char* string_pid);
// void prompt(char* directory);
// void searchFile(char *dirPath, char *filename,int d_flag,int e_flag,int f_flag,char** files,int* index);
// void removeChar(char *str, char target);



#endif