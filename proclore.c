#include "headers.h"



void get_executable_path(const char *pid_str) {
    int pid = atoi(pid_str);
    if (pid <= 0) {
        printf("Invalid PID.\n");
        return;
    }

    char proc_exe_path[MAX_PATH_LENGTH];
    snprintf(proc_exe_path, sizeof(proc_exe_path), "/proc/%d/exe", pid);

    char exe_path[MAX_PATH_LENGTH];
    ssize_t len = readlink(proc_exe_path, exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0';
        printf("Executable Path: %s\n", exe_path);
    } else {
        perror("readlink");
    }
}


void exec_proclore(char* newtoken,int* check_flag,int* argument_flag){
                
        if(strstr(newtoken,"proclore")){
                        (*check_flag)=1;
                    }

                    else if((*check_flag)==1){
                        (*argument_flag)=1;
                        
                        
                        char* stat_path=(char*)malloc(sizeof(char)*LEN);
                        strcpy(stat_path,"/proc/");
                        strcat(stat_path,newtoken);
                        strcat(stat_path,"/status");
                        
                        int stat_file=open(stat_path,O_RDONLY);
                        char* read_buffer=(char*)malloc(sizeof(char)*BUFFER_LEN);
                        int read_file=read(stat_file,read_buffer,BUFFER_LEN);
                        int pid_flag=0;
                        char* pid = (char*)malloc(sizeof(char)*10);
                        strcpy(pid,newtoken);
                        char* stat_token=strtok(read_buffer,"\n");
                        while(stat_token){
                            if(strstr(stat_token,"NSpgid")){
                                printf("Process Group :");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                printf("%s\n",stat_token_value);
                            }

                            else if(strstr(stat_token,"VmSize")){
                                printf("Virtual Memory : ");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')&&(stat_token[j]!='\t')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                printf("%s\n",stat_token_value);
                            }
                            else if(strstr(stat_token,"Pid")&&pid_flag==0){
                                pid_flag=1;
                                printf("Pid : ");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')&&(stat_token[j]!='\t')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                
                                printf("%s\n",stat_token_value);
                            }
                            else if(strstr(stat_token,"State")){
                                printf("Status : ");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')&&(stat_token[j]!='\t')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                printf("%s\n",stat_token_value);
                            }
                            stat_token=strtok(NULL,"\n");
                        }
                        get_executable_path(pid);
                    }
                
                
}

void exec_shell_proclore(char* string_pid){
                    
                    // printf("%s\n",string_pid);
                    char* stat_path=(char*)malloc(sizeof(char)*LEN);
                        strcpy(stat_path,"/proc/");
                        strcat(stat_path,string_pid);
                        strcat(stat_path,"/status");
                        
                        int stat_file=open(stat_path,O_RDONLY);
                        
                        char* read_buffer=(char*)malloc(sizeof(char)*BUFFER_LEN);
                        int read_file=read(stat_file,read_buffer,BUFFER_LEN);
                        int pid_flag=0;
                        // char* pid = (char*)malloc(sizeof(char)*10);
                        // strcpy(pid,newtoken);
                        char* stat_token=strtok(read_buffer,"\n");
                        while(stat_token){
                            if(strstr(stat_token,"NSpgid")){
                                printf("Process Group :");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                printf("%s\n",stat_token_value);
                            }

                            else if(strstr(stat_token,"VmSize")){
                                printf("Virtual Memory : ");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')&&(stat_token[j]!='\t')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                printf("%s\n",stat_token_value);
                            }
                            else if(strstr(stat_token,"Pid")&&pid_flag==0){
                                pid_flag=1;
                                printf("Pid : ");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')&&(stat_token[j]!='\t')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                
                                printf("%s\n",stat_token_value);
                            }
                            else if(strstr(stat_token,"State")){
                                printf("Status : ");
                                char stat_token_value[25];
                                for(int j=0;j<25;j++){
                                    stat_token_value[j]='\0';
                                }
                                int stat_token_index=0;
                                int stat_token_flag=0;
                                // printf("%s\n",newtoken);
                                for(int j=0;j<strlen(stat_token);j++){
                                    if(stat_token[j]==':'){stat_token_flag=1;}
                                    // printf("yes\n");}

                                    if((stat_token_flag)&&(stat_token[j]!=':')&&(stat_token[j]!=' ')&&(stat_token[j]!='\t')){
                                        stat_token_value[stat_token_index++]=stat_token[j];
                                    }
                                }
                                printf("%s\n",stat_token_value);
                            }
                            stat_token=strtok(NULL,"\n");
                        }
                        get_executable_path(string_pid);

}