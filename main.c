#include "headers.h"
// #include "prompt.c"
// #include "searchfile.c"
// #include "peek.c"
// #include "pastevents.c"
// #include "stringhelper.c"
// #include "proclore.c"

int inter=1;
int proc_stat=0;
struct background_struct{
    char* name;
    pid_t pid;
    struct background_struct* next;
};

void sighandler(int sig){

    inter= 0;

}

void print_bg(struct background_struct* bg){
        struct background_struct* head=bg;

        while(head->next){
            int status;
            waitpid(head->next->pid,&status,0);

            if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                printf("%s Process ended normally (%d).\n",head->next->name,head->next->pid);
            } else {
                printf("%s Process ended abnormally (%d).\n",head->next->name,head->next->pid);
            }
        } else {
            printf("%s Process ended abnormally (%d).\n",head->next->name,head->next->pid);
        }
        // printf("%s\n",head->next->name);
        head->next=head->next->next;
        }}


int main()
{
    // Keep accepting commands
    struct file_buffer* f=(struct file_buffer*)malloc(sizeof(struct file_buffer));
        f->end_index=0;
        f->count=0;
        f->start_index=0;
        for(int i=0;i<MAX_COMMANDS;i++){
            f->commands[i][0]='\0';
    }
    
    loadfile(f);
    signal(SIGINT,sighandler);

    int prompt_flag=0;
    char* fg_process=(char*)malloc(sizeof(char)*LEN);
    int fg_time;
    char copy_command[4096];
    char* directory=(char*)malloc(sizeof(char)*LEN);

    directory=getcwd(directory,LEN);
    char* prev_dir=(char*)malloc(sizeof(char)*LEN);
    strcpy(prev_dir,directory);
    char prev_input[4096];
    int pastevents_flag=0;
    char pastevents_command[4096];
    char* pastevents_dir=(char*)malloc(sizeof(char)*LEN);
    strcpy(pastevents_dir,directory);
    
    strcat(pastevents_dir,"/pastevents.txt");
    struct background_struct* bg_processes=(struct background_struct*)malloc(sizeof(struct background_struct));
    bg_processes->next=NULL;
    
    
    
    // printf("%s\n",directory);
    while (inter)
    {

      
        // Print appropriate prompt with username, systemname and directory before accepting input
        char* current_directory=(char*)malloc(sizeof(char)*LEN);
        current_directory=getcwd(current_directory,LEN);
             
        
        
        prompt(directory,&prompt_flag,fg_process,fg_time);
        char input_raw[4096];
        char processed_input[4096];
        int i=0,j=0;
        
        if(pastevents_flag==0)
        fgets(input_raw, 4096, stdin);
        else{
            strcpy(input_raw,pastevents_command);
            pastevents_flag=0;
        }
            // strcpy(input_raw,pastevents_command);
            // pastevents_flag=0;
        if(input_raw==NULL){
            continue;
        }
        else{
        input_raw[strcspn(input_raw,"\n")]='\0';
        

        
        if(input_raw[0]!='\n' && check_valid(f,input_raw) && strstr(input_raw,"pastevents")==NULL)
        insert(f,input_raw);
        
        

        // print_queue(f);
        print_bg(bg_processes);
        strcpy(copy_command,input_raw);
        char* input=strtok(input_raw,"\n");
        
        // write_to_file(input_raw,prev_dir);
       

        char* token;
        char* saveptr_one;
        
        char** command_array=(char**)malloc(sizeof(char*)*MAX_COMMANDS);
        for(int i=0;i<MAX_COMMANDS;i++){
            command_array[i]=(char*)malloc(sizeof(char)*LEN);
        }
        int index_of_array=0;
        token = strtok_r(input,";",&saveptr_one);
        while(token){
            strcpy(command_array[index_of_array++],token);
            
            token=strtok_r(NULL,";",&saveptr_one);

        }
        // for(int i=0;i<index_of_array;i++){
        //     printf("%s\n",command_array[i]);
        // }
        for(int i=0;i<index_of_array;i++){
            char* saveptr_two;
            int check_flag=0;
            int argument_flag=0;
            char* command_array_tokeniser=(char*)malloc(sizeof(char)*LEN);
            strcpy(command_array_tokeniser,command_array[i]);
            char* newtoken=strtok_r(command_array_tokeniser," ",&saveptr_two);

            if(strstr(command_array[i],"warp")){
            while(newtoken){     

            
                if(strstr(newtoken,"warp")){
                    check_flag=1;
                }
                else if(check_flag==1){argument_flag=1;
                    

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

                        chdir(absolutepath);
                        char* print_dir=(char*)malloc(sizeof(char)*LEN);
                        print_dir=getcwd(print_dir,LEN);
                        printf("%s\n",print_dir);
                        strcpy(prev_dir,current_directory);

                     }

                    
                    else if(strcmp(newtoken,"-")==0){
                        chdir(prev_dir);
                        char* print_dir=(char*)malloc(sizeof(char)*LEN);
                        print_dir=getcwd(print_dir,LEN);
                        printf("%s\n",print_dir);
                        strcpy(prev_dir,current_directory);
                    }
                    

  
                    else {chdir(newtoken);
                    char* print_dir=(char*)malloc(sizeof(char)*LEN);
                        print_dir=getcwd(print_dir,LEN);
                        printf("%s\n",print_dir);
                    strcpy(prev_dir,current_directory);}
                }
                newtoken=strtok_r(NULL," ",&saveptr_two);
            }
            if(check_flag==1&&argument_flag==0){
                chdir(directory);
            }}
            else if(strstr(command_array[i],"peek")){
                int a_flag=0;
                int l_flag=0;
                int check_flag=0;
                int argument_flag=0;
                while(newtoken){
                    
                    if(strstr(newtoken,"peek")){
                        check_flag=1;
                    }

                    else if(check_flag==1){
                        if(strstr(newtoken,"-a")){
                            a_flag=1;
                        }
                        else if(strstr(newtoken,"-l")){
                            l_flag=1;
                        }
                        else if(strstr(newtoken,"-al")||strstr(newtoken,"-la")){
                            a_flag=1;
                            l_flag=1;
                        }

                        else{
                            argument_flag=1;
             
                    
                    peek_execution(newtoken,a_flag,l_flag,directory,prev_dir);
}
                    }               
                newtoken=strtok_r(NULL," ",&saveptr_two);
                
                
            }}
            else if(strstr(command_array[i],"pastevents")){
                int check_flag=0;
                int argument_flag=0;
                int exec_flag=0;
                while(newtoken){

                    if(strstr(newtoken,"pastevents")){
                        check_flag=1;
                        
                    }
                    else if(check_flag==1&&exec_flag==0){
                        argument_flag=1;
                        
                        if(strstr(newtoken,"purge")){
                            
                            f->count=0;
                            f->end_index=0;
                            f->start_index=0;
                        }
                        else if(strstr(newtoken,"execute")){
                            exec_flag=1;

                        }
                    }
                    else if(check_flag==1&&exec_flag==1){
                        pastevents_flag=1;
                        int execution_number=atoi(newtoken);
                        // printf("%d\n",execution_number);
                        // int read_file_descriptor_exec=open("pastevents.txt",O_CREAT | O_RDWR);
                        // char read_buffer_exec[4096];
                        // int read_status_exec=read(read_file_descriptor_exec,read_buffer_exec,4096);

                        FILE* read_file=fopen(pastevents_dir,"r");
                        if(read_file==NULL)perror("File couldn't be opened!");

                        else{
                            
                            int count=0;
                            int ind=f->start_index;

                            while(count<execution_number-1){
                                ind=(ind+1)%MAX_COMMANDS_PAST;
                                count++;
                            }
                            strcpy(pastevents_command,f->commands[ind]);
                        }

                        
                    }
                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }
                if(check_flag==1&&argument_flag==0){
                    print_queue(f);
                }
            }
            else if(strstr(command_array[i],"proclore")){
                int check_flag=0;
                int argument_flag=0;
                
                while(newtoken){
                    exec_proclore(newtoken,&check_flag,&argument_flag);
                    newtoken=strtok_r(NULL," ",&saveptr_two);}
                if(check_flag==1&&argument_flag==0){
                    pid_t pid_shell = getpid();
                    char string_pid[5];
                    sprintf(string_pid,"%d",pid_shell);
                    exec_shell_proclore(string_pid);
                }
               
            }
            else if(strstr(command_array[i],"seek")){
                
                // printf("entered seek\n");
                
                int check_flag=0;
                int argument_flag=0;
                int d_flag=0;
                int f_flag=0;
                int e_flag=0;
                
                char** seek_array=(char**)malloc(sizeof(char*)*3);
                    for(int j=0;j<3;j++){
                        seek_array[j]=(char*)malloc(sizeof(char)*4096);
                    }
                int k=0;
                while(newtoken){

                    if(strstr(newtoken,"-d"))d_flag=1;
                    else if(strstr(newtoken,"-f"))f_flag=1;
                    else if(strstr(newtoken,"-e"))e_flag=1;

                    else{
                    
                    strcpy(seek_array[k++],newtoken);}

                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }

                char** files=(char**)malloc(sizeof(char*)*TOTAL_PATHS);
                for(int j=0;j<TOTAL_PATHS;j++){
                    files[i]=(char*)malloc(sizeof(char)*MAX_PATH_LENGTH);

                }
                int ind_of_files=0;
                
                searchFile(seek_array[2],seek_array[1],d_flag,e_flag,f_flag,files,&ind_of_files);
                if(d_flag==1&&f_flag==1){
                    printf("Invalid flags!\n");
                    break;
                }
                int file_count=0;
                for(int j=0;j<ind_of_files;j++){
                    // printf("%s\n",files[j]);
                    struct stat file_info;

                    if(stat(files[j],&file_info)==0){
                        
                        if(e_flag==0){
                            if(d_flag==0&&f_flag==0){
                                printf("%s\n",files[j]);
                                file_count=1;
                            }
                            else if(d_flag&&S_ISDIR(file_info.st_mode)){
                                    printf("%s\n",files[j]);
                                    file_count=1;
                            }
                            else if(f_flag&&S_ISREG(file_info.st_mode)){
                                printf("%s\n",files[j]);
                                file_count=1;
                            }
                            
                        }
                        else{
                            if(ind_of_files!=1)break;
                            if(access(files[j],R_OK | X_OK)!=0)printf("Missing permissions for task!\n");
                            else{
                                
                                    if(S_ISDIR(file_info.st_mode)){
                                        chdir(files[j]);
                                    }
                                    else{
                                        if(f_flag==1 || (d_flag==0&&f_flag==0)){
                                        char* file_content=(char*)malloc(sizeof(char)*LEN);
                                        FILE* f_c=fopen(files[j],"r");
                                        while(fgets(file_content,LEN,f_c)){
                                            printf("%s\n",file_content);
                                            file_count=1;
                                        }
                                        }

                                    }


                            }

                        }

                    }

                }
                if(file_count==0)printf("No match found!\n");

            }
        
            else{
                // printf("%s\n",command_array[i]);
                char tokenize_copy_command[4096];
                strcpy(tokenize_copy_command,command_array[i]);
                
                char** background_command_array=(char**)malloc(sizeof(char*)*MAX_COMMANDS);
                for(int j=0;j<MAX_COMMANDS;j++){
                    background_command_array[j]=(char*)malloc(sizeof(char)*4096);

                }
                char* save_In_one;
                
                
                int bg_index=0;
                int count=0;
                removeChar(tokenize_copy_command,'\n');
                char* prev_string=(char*)malloc(sizeof(char)*LEN);
                strcpy(prev_string,tokenize_copy_command);
                char* token_copy=strtok_r(tokenize_copy_command,"&",&save_In_one);
                // printf("%s\n",token_copy);

                while(token_copy){
                   
                    int bg_flag=0;
                    if(strstr(prev_string,"&")){bg_flag=1;}
                     
                        char** command_array_proc=(char**)malloc(sizeof(char*)*5);
                        for(int j=0;j<5;j++){
                            command_array_proc[j]=(char*)malloc(sizeof(char)*15);
                        }

                        char* command_string_proc=(char*)malloc(sizeof(char)*4096);
                        strcpy(command_string_proc,token_copy);
                        char* command_token=strtok(command_string_proc," ");
                        int command_index=0;
                        while(command_token){
                            if(command_token[0]!=' ')
                            strcpy(command_array_proc[command_index++],command_token);
                            command_token=strtok(NULL," ");
                        }
                        
                        // printf("%d\n",command_index);
                        command_array_proc[command_index]=NULL;
                        struct timeval start_time, end_time;
                        gettimeofday(&start_time, NULL);
                        pid_t pid=fork();

                        if(pid<0)perror("Error spawning process");
                        else if(pid==0){
                            // printf("child\n");
                           
                            
                            execvp(command_array_proc[0],command_array_proc);
                            proc_stat=1;
                            // perror("execvp");
                            printf("'%s' is not a valid command!\n",command_array_proc[0]);
                            exit(EXIT_FAILURE);
                            }
                        else if(pid>0){

                        if(bg_flag==1){
                        struct background_struct* new=(struct background_struct*)malloc(sizeof(struct background_struct));
                        strcpy(new->name,command_array_proc[0]);
                        new->pid=pid;
                        new->next=bg_processes->next;
                        bg_processes->next=new;

                        
                        printf("%d\n",pid);
                    
                        
                        }

                    
                    
                        
                        
                        else{

                            int status;
                            wait(&status); // Wait for the child to finish
                            
                            gettimeofday(&end_time, NULL);

                            long long start_usec = start_time.tv_sec * 1000000LL + start_time.tv_usec;
                            long long end_usec = end_time.tv_sec * 1000000LL + end_time.tv_usec;
                            
                            double elapsed_time = (end_usec - start_usec) / 1000000.0;
                            if(elapsed_time>5){
                                prompt_flag=1;
                                strcpy(fg_process,command_array_proc[0]);
                                fg_time=elapsed_time;
                            }
                          
                        }
                        

                    }
                    strcpy(prev_string,save_In_one);
                    token_copy=strtok_r(NULL,"&",&save_In_one);
                    }
                    
            }}
        }
        
        
        
    
    
    write_queue(f,pastevents_dir);}
}
