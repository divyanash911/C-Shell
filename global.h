#ifndef GLOBAL_H
#define GLOBAL_H

#include "headers.h"

extern int inter;
extern int z_inter;
extern int d_inter;
extern int proc_stat;
extern struct background_struct* bg_processes;
extern struct processes* list_proc;
extern int fore0;
extern char* directory;
extern char* prev_dir;
extern struct file_buffer* f;
extern int pastevents_flag;
extern char pastevents_command[4096];
extern char* pastevents_dir;


#endif