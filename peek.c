
#include "headers.h"



int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void peek_execution(char* newtoken,int a_flag,int l_flag,char* directory,char* prev_dir){
                        char* og_dir=(char*)malloc(sizeof(char)*LEN);
                        og_dir=getcwd(og_dir,LEN);

                        if(strstr(newtoken,"~")!=NULL){
                        char buffertoken[strlen(newtoken)];
                        for(int i=1;i<strlen(newtoken);i++){
                            buffertoken[i-1]=newtoken[i];
                        }
                        buffertoken[strlen(newtoken)-1]='\0';
                        // printf("%s\n",buffertoken);

                        char absolutepath[strlen(buffertoken)+strlen(directory)+1];
                        strcpy(absolutepath,directory);
                        strcat(absolutepath,buffertoken);

                        strcpy(newtoken,absolutepath);
                        
                     }

                     if(strcmp(newtoken,"-")==0){

                        strcpy(newtoken,prev_dir);

                     }
                           struct dirent** directory_struct;
                           int n;
                           
                              n=scandir(newtoken,&directory_struct,NULL,alphasort);
                              chdir(newtoken);
                           if(n<0){
                              perror("Directory invalid!");
                           }
                            
                            if(l_flag==0){


                           for(int i=0;i<n;i++){
                              if(a_flag==1){
                              printf("%s\n",directory_struct[i]->d_name);}
                              else{
                                 if(directory_struct[i]->d_name[0]!='.'){
                                    // printf("%s\n",directory_struct[i]->d_name);
                                    char* current_dir=(char*)malloc(sizeof(char)*LEN);
                                    current_dir=getcwd(current_dir,LEN);
                                    strcat(current_dir,"/");
                                    strcat(current_dir,directory_struct[i]->d_name);
                                    strcat(current_dir,"/");
                                    print_in_color(current_dir,directory_struct[i]->d_name);
                                    printf("\n");
                                 }
                              }
                           }
                           
                            
                            }
                            else{


                              for(int i=0;i<n;i++){
                                 
                              char* home_directory=(char*)malloc(sizeof(char)*LEN);

                                home_directory=getcwd(home_directory,LEN);
                                strcat(home_directory,"/");
                                strcat(home_directory,directory_struct[i]->d_name);
                              //   printf("%s\n",home_directory);
                                struct stat file_info;

                                if(stat(home_directory,&file_info)==0){
                                 if(a_flag==0){
                                    if(directory_struct[i]->d_name[0]!='.'){
                                    
                                    print_permissions(file_info.st_mode);
                                 
                                    printf("\t%ld\t", file_info.st_nlink);

                                    struct passwd *pw = getpwuid(file_info.st_uid);
                                    struct group *gr = getgrgid(file_info.st_gid);
                                    printf("%-8s\t%-8s\t", pw ? pw->pw_name : "", gr ? gr->gr_name : "");

                                    printf("%8lld\t", (long long)file_info.st_size);

                                    char date_buffer[20];
                                    strftime(date_buffer, sizeof(date_buffer), "%b %d %H:%M", localtime(&file_info.st_mtime));
                                    printf("%s\t", date_buffer);
                                    char* current_dir=(char*)malloc(sizeof(char)*LEN);
                                    current_dir=getcwd(current_dir,LEN);
                                    strcat(current_dir,"/");
                                    strcat(current_dir,directory_struct[i]->d_name);
                                    
                                    print_in_color(current_dir,directory_struct[i]->d_name);
                                    printf("\n");
}}
                                    else{
                                    print_permissions(file_info.st_mode);
                                    printf("\t%ld\t", file_info.st_nlink);

                                    struct passwd *pw = getpwuid(file_info.st_uid);
                                    struct group *gr = getgrgid(file_info.st_gid);
                                    printf("%-8s\t%-8s\t", pw ? pw->pw_name : "", gr ? gr->gr_name : "");

                                    printf("%8lld\t", (long long)file_info.st_size);

                                    char date_buffer[20];
                                    strftime(date_buffer, sizeof(date_buffer), "%b %d %H:%M", localtime(&file_info.st_mtime));
                                    printf("%s\t", date_buffer);
                                    char* current_dir=(char*)malloc(sizeof(char)*LEN);
                                    current_dir=getcwd(current_dir,LEN);
                                    strcat(current_dir,"/");
                                    strcat(current_dir,directory_struct[i]->d_name);
                                    
                                    print_in_color(current_dir,directory_struct[i]->d_name);
                                    printf("\n");
                                    }
                                }

                              }
                             
                                

                                }
   chdir(og_dir);
}