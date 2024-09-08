#include "headers.h"
#include<termios.h>

int inter=1;
int z_inter=0;
int d_inter=0;
int proc_stat=0;
struct background_struct{
    char* name;
    pid_t pid;
    struct background_struct* next;
};
struct background_struct* bg_processes;
struct processes* list_proc;
struct file_buffer* f;
int fore=0;
char* directory;
char* prev_dir;
int pastevents_flag;
char pastevents_command[4096];
char* pastevents_dir;

struct processes{

    char* name;
    pid_t pid;
    struct processes* next;

};

void sighandler(int sig){

    

    struct processes* l=list_proc;
    struct background_struct* head=bg_processes;
    int flag=0;
    



    while(l->next){
        // printf("Hi\n");
        
            
            kill(l->next->pid,SIGTSTP);
            kill(l->next->pid,SIGSTOP);
            struct background_struct* new=(struct background_struct*)malloc(sizeof(struct background_struct));
            new->name=(char*)malloc(sizeof(char)*100);
            strcpy(new->name,l->next->name);
            new->pid=l->next->pid;
            new->next=head->next;
            head->next=new;
        

        l->next=l->next->next;
        
        
    }
    
    

}

void sig_c(int sig){
    
    
    
    
    if(kill(fore,SIGINT)==-1){
        perrorf("Signal error");
        exit(1);
    }



}

void sig_d(int sig){
    
    if(sig==SIGQUIT){
        kill(0,SIGKILL);
        exit(1);
        }

}


void print_bg(struct background_struct* bg){
        struct background_struct* head=bg;

        while(head->next){
            int status;
            int r=waitpid(head->next->pid,&status,WNOHANG);
            if(r!=0){
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
        head->next=head->next->next;
        }
        else{
            head=head->next;
        }}}


void activities(struct processes* head){

    while(head){
        printf("%d : ",head->pid);
        printf("%s - ",head->name);
        int stat=kill(0,head->pid);

        if(stat==0){
            printf("Running\n");
        }
        else printf("Stopped\n");

        head=head->next;

    }

}

void activities_b(struct background_struct* head){

    while(head->next){
        printf("%d : ",head->next->pid);
        printf("%s - ",head->next->name);
        int status;
        int stat=waitpid(head->next->pid,&status,WNOHANG);

        

        if(stat==0){
            
            char* proc_path=(char*)malloc(sizeof(char)*50);
            snprintf(proc_path,50,"/proc/%d/stat",head->next->pid);
            // printf("%s\n",proc_path);
            FILE* file=fopen(proc_path,"r");
            char line[1000]; 
            int index = 0;  
            char thirdElements[100][50];
            while (fgets(line, sizeof(line), file)) {
               
                
                char *token = strtok(line, " ");

                int count = 0;
                while (token != NULL) {
                    if (count == 2) { 
                        strcpy(thirdElements[index], token); 
                        index++;
                        break; 
                    }
                    token = strtok(NULL, " ");
                    count++;
                }
            
}
    if(thirdElements[0][0]=='R' || thirdElements[0][0]=='S'){
        printf("Running\n");
    }
    else{
        printf("Stopped\n");
    }
}
        else{
            head->next=head->next->next;
        }

        head=head->next;

    }

}

int main()
{
    pid_t parent_pid = getpid();
    
        f=(struct file_buffer*)malloc(sizeof(struct file_buffer));
        f->end_index=0;
        f->count=0;
        f->start_index=0;
        for(int i=0;i<MAX_COMMANDS;i++){
            f->commands[i][0]='\0';
    }

    loadfile(f);
    signal(SIGINT,sig_c);
    signal(SIGQUIT,sig_d);
    signal(SIGTSTP,sighandler);

    int prompt_flag=0;
    char* fg_process=(char*)malloc(sizeof(char)*LEN);
    int fg_time;
    char copy_command[4096];
    directory=(char*)malloc(sizeof(char)*LEN);

    directory=getcwd(directory,LEN);
    prev_dir=(char*)malloc(sizeof(char)*LEN);
    strcpy(prev_dir,directory);
    char prev_input[4096];
    pastevents_flag=0;
    // char pastevents_command[4096];
    pastevents_dir=(char*)malloc(sizeof(char)*LEN);
    strcpy(pastevents_dir,directory);
    
    strcat(pastevents_dir,"/pastevents.txt");
    bg_processes=(struct background_struct*)malloc(sizeof(struct background_struct));
    bg_processes->next=NULL;
    list_proc=(struct processes*)malloc(sizeof(struct processes));
    list_proc->next=NULL;
    while (inter)
    {
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
        if(input_raw==NULL){
            
            break;
        }
        else if(input_raw[0]=='\0'){
            kill(0,SIGKILL);
            break;
        }
        else if(input_raw[0]=='\n'){
            continue;
        }
        else{
        input_raw[strcspn(input_raw,"\n")]='\0';
        

        
        if(input_raw[0]!='\n' && check_valid(f,input_raw) && strstr(input_raw,"pastevents")==NULL)
        insert(f,input_raw);
        print_bg(bg_processes);
        strcpy(copy_command,input_raw);
        char* input=strtok(input_raw,"\n");
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
        for(int i=0;i<index_of_array;i++){
            char* saveptr_two;
            int check_flag=0;
            int argument_flag=0;
            char* command_array_tokeniser=(char*)malloc(sizeof(char)*LEN);
            strcpy(command_array_tokeniser,command_array[i]);
            char* newtoken=strtok_r(command_array_tokeniser," ",&saveptr_two);

            if(strstr(command_array[i],"<")||strstr(command_array[i],">")||strstr(command_array[i],"|")){

                char* c_command=(char*)malloc(sizeof(char)*100);
                strcpy(c_command,command_array[i]);
                char* c_tok;
                c_tok=strtok(c_command,"|");
                char* prev_t=(char*)malloc(sizeof(char)*100);
                char** c_command_array=(char**)malloc(sizeof(char*)*MAX_COMMANDS);
                int c_comm_ind=0;
                for(int j=0;j<MAX_COMMANDS;j++){
                    c_command_array[j]=(char*)malloc(sizeof(char)*MAX_LEN);
                }

                while(c_tok){

                    
                    strcpy(c_command_array[c_comm_ind++],c_tok);

                    c_tok=strtok(NULL,"|");
                }
                for(int i=0;i<c_comm_ind;i++){
                    if(command_array[i][0]=='|' || command_array[i][strlen(command_array[i])-1]=='|'){
                        perrorf("Invalid use of Pipes!");
                        exit(1);
                    }
                }
                pipe_handler(c_command_array,c_comm_ind);

                

                

            }


            
            else{

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
                        FILE* read_file=fopen(pastevents_dir,"r");
                        if(read_file==NULL)perrorf("File couldn't be opened!");

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
            else if(strstr(command_array[i],"activities")){
                
                activities_b(bg_processes);
            }
            else if(strstr(command_array[i],"ping")){
                
                char** ping_array=(char**)malloc(sizeof(char*)*3);
                for(int j=0;j<3;j++){
                    ping_array[i]=(char*)malloc(sizeof(char)*50);
                    
                }
                int ping_ind=0;
            
                while(newtoken){
                    strcpy(ping_array[ping_ind++],newtoken);
                    printf("%s\n",newtoken);
                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }
                
                exec_ping(ping_array);
                

            }

            else if(strstr(command_array[i],"iMan")){

                if(strstr(command_array[i],"iMan")){
                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }
                char* man_path=(char*)malloc(sizeof(char)*100);
                strcpy(man_path,directory);
                strcat(man_path,"/man.txt");
                read_man(newtoken,man_path);


            }

            else if(strstr(command_array[i],"fg")){
                int check=0;
                char* pid=(char*)malloc(sizeof(char)*20);
                while(newtoken){
                    if(check==0)
                    if(strstr(newtoken,"fg"))check=1;

                    else{
                        strcpy(pid,newtoken);
                    }


                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }
                exec_fg(pid);
            } 

            else if(strstr(command_array[i],"bg")){
                int check=0;
                char* pid=(char*)malloc(sizeof(char)*20);
                while(newtoken){
                    if(check==0)
                    if(strstr(newtoken,"fg"))check=1;

                    else{
                        strcpy(pid,newtoken);
                    }


                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }
                exec_bg(pid);

            }

            else if(strstr(command_array[i],"neonate")){
                
                char** c_array=(char**)malloc(sizeof(char**)*3);
                for(int j=0;j<3;j++){
                    c_array[i]=(char*)malloc(sizeof(char)*100);

                }
                int ind=0;
                while(newtoken){
                    strcpy(c_array[ind++],newtoken);
                    newtoken=strtok_r(NULL," ",&saveptr_two);
                }
                int arg=atoi(c_array[2]);
                e_neonate(c_array[1][0],arg);
            }

            else{

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
                    if(strstr(prev_string,"&")){bg_flag=1;
                    // printf("Hi\n");}
                    }
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

                        if(pid<0)perrorf("Error spawning process");
                        else if(pid==0){
                           
                            
                            // signal(SIGINT,sighandler);
                            // signal(SIGTSTP,sig_z);
                            if (setpgid(0, 0) == -1) {
                                perrorf("setpgid");
                                exit(EXIT_FAILURE);
                            }
                            execvp(command_array_proc[0],command_array_proc);
                            proc_stat=1;
                            
                            perrorf("Not a valid command!");
                            exit(EXIT_FAILURE);
                            }
                        else if(pid>0){
                        // printf("%d\n",pid);
                        if(bg_flag==1){
                        struct background_struct* new=(struct background_struct*)malloc(sizeof(struct background_struct));
                        strcpy(new->name,command_array_proc[0]);
                        new->pid=pid;
                        new->next=bg_processes->next;
                        bg_processes->next=new;
                        

                        
                        printf("%d\n",pid);
                    
                        
                        }

                    
                    
                        
                        
                        else{

                            fore=pid;
                            struct processes* new_p=(struct processes*)malloc(sizeof(struct processes));
                            strcpy(new_p->name,command_array_proc[0]);
                            new_p->pid=pid;
                            new_p->next=list_proc->next;
                            list_proc->next=new_p;
                            int status;
                            
                            waitpid(pid,&status,WUNTRACED); // Wait for the child to finish
                            
                            gettimeofday(&end_time, NULL);

                            long long start_usec = start_time.tv_sec * 1000000LL + start_time.tv_usec;
                            long long end_usec = end_time.tv_sec * 1000000LL + end_time.tv_usec;
                            
                            double elapsed_time = (end_usec - start_usec) / 1000000.0;
                            if(elapsed_time>5){
                                prompt_flag=1;
                                strcpy(fg_process,command_array_proc[0]);
                                fg_time=elapsed_time;}
                            
                          
                        }
                        

                    }
                    strcpy(prev_string,save_In_one);
                    token_copy=strtok_r(NULL,"&",&save_In_one);
                    }
                    
          }}}
        }
        write_queue(f,pastevents_dir);
        
    }
}
