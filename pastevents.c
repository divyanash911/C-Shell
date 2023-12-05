#include "headers.h"


void insert(struct file_buffer* f,char* string){

    if(string[0]=='\0')return;
    if(f->count<MAX_COMMANDS_PAST){

        strcpy(f->commands[f->end_index],string);
        f->end_index=(f->end_index+1)%MAX_COMMANDS_PAST;
        f->count++;
}
    else{
        strcpy(f->commands[f->start_index],string);
        f->start_index=(f->start_index+1)%MAX_COMMANDS_PAST;
    }
    

}

void loadfile(struct file_buffer* f){
    
    FILE* file_object = fopen("pastevents.txt","r");
    if(file_object){
    char command[MAX_LEN];
    while(fgets(command,sizeof(command),file_object)){
        
        command[strcspn(command,"\n")]='\0';
        insert(f,command);
        
    }
    fclose(file_object);
    }
}





void write_queue(struct file_buffer* f,char* dir){

    FILE* file_obj=fopen(dir,"w");
    int ind=f->start_index;
    // printf("Total %d %d\n",f->start_index,f->end_index);
    if(file_obj){
    for(int i=0;i<f->count;i++){
        
        fprintf(file_obj,"%s\n",f->commands[ind]);
        
        // printf("%s",f->commands[ind]);
        ind= (ind+1)%MAX_COMMANDS_PAST;
    }
    fclose(file_obj);
    }
    else{
        printf("file open error!\n");
    }
    

}

void print_queue(struct file_buffer* f){
    int ind=f->start_index;
    for(int i=0;i<f->count;i++){
        if(f->commands[ind][0]!='\0'){
        printf("%s\n",f->commands[ind]);
        ind=(ind+1)%MAX_COMMANDS_PAST;}
    }

}


int check_valid(struct file_buffer* f,char* new_command){
    if(f->count<MAX_COMMANDS_PAST){
        if(strcmp(f->commands[f->count-1],new_command)==0)return 0;

    }
    else{
        if(strcmp(f->commands[f->start_index],new_command)==0)return 0;
    }
    return 1;
}
