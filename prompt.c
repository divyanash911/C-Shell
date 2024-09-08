#include "headers.h"

void prompt(char* directory,int* flag,char* name,int time){
    // Do not hardcode the prmopt
    
    
    char* sysname=(char*)malloc(sizeof(char)*LEN);
    char* usname=(char*)malloc(sizeof(char)*LEN);
    char* directory_new=(char*)malloc(sizeof(char)*LEN);
    char* temp=(char*)malloc(sizeof(char)*LEN);

    
    
    int t=gethostname(sysname,LEN);
    int p=getlogin_r(usname,LEN);
    directory_new=getcwd(directory_new,LEN);
    
    if(strcmp(directory,directory_new)==0){
        temp="~";
    }
    else if(strstr(directory_new,directory)!=NULL){
        char temporary_directory[strlen(directory_new)+1];
        for(int i=0;i<strlen(directory_new);i++){
            temporary_directory[i]='\0';
        }
        int position_of_home=0;
        for(int i=0;i<strlen(directory_new);i++){
            temporary_directory[i]=directory_new[i];
            
            if(strcmp(temporary_directory,directory)==0){
                position_of_home=i+1;
                break;
            }
            }
        
        char relative_string[strlen(directory_new)];
        for(int i=0;i<strlen(directory_new);i++){
            relative_string[i]='\0';
        }
        
        for(int i=position_of_home;i<strlen(directory_new);i++){
            relative_string[i-position_of_home]=directory_new[i];
        }
        
        strcpy(temp,"~");
        strcat(temp,relative_string);
        
        // printf("%s\n",temp);
    }
    
    else strcpy(temp,directory_new);

    
    // printf("Aaj kamayinga to kal baithkar khayenga\n");
    printf(MAG"<"reset);
    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET,usname );
    printf(ANSI_COLOR_RED "@" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET,sysname);
    printf(":");
    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET,temp);
    if((*flag)==0){
    printf(ANSI_COLOR_GREEN ">" ANSI_COLOR_RESET);}
    else{
        printf("%s : %d s>",name,time);
        (*flag)=0;
    }    

    

}


