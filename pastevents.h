#ifndef PASTEVENTS_H
#define PASTEVENTS_H

struct file_buffer{
    int count;
    char commands[MAX_COMMANDS_PAST][MAX_LEN];
    int end_index;
    int start_index;
};


void insert(struct file_buffer* f,char* string);
void loadfile(struct file_buffer* f);
void write_queue(struct file_buffer* f,char* dir);
void print_queue(struct file_buffer* f);
int check_valid(struct file_buffer* f,char* new_command);


#endif