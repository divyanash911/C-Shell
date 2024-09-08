#include "headers.h"

void exec_bash(char* command,int ip,int op,char* ipfile,char* opfile,int append){

    char* copy_command=(char*)malloc(sizeof(char)*4096);
    strcpy(copy_command,command);

    char* token;
    token=strtok(copy_command," ");
    char** arr=(char**)malloc(sizeof(char*)*10);
    for(int i=0;i<10;i++){
        arr[i]=(char*)malloc(sizeof(char)*100);
    }
    int ind=0;
    while(token){

        
        strcpy(arr[ind++],token);
        token=strtok(NULL," ");

    }



    arr[ind]=NULL;
    int fd_o,fd_i;
    if(ip==1){
        fd_i=open(ipfile,O_RDONLY);
        // printf("%s\n",ipfile);
        if(fd_i==-1){
            
            perrorf("File error");
            exit(1);
        }
    }

    if(op==1){

        if(append==0){
        fd_o=open(opfile,O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // printf("%s\n",opfile);
        if(fd_o==-1){
            
            perrorf("File error %s\n");
            exit(1);
        }}
        else{
            

           fd_o=open(opfile,O_WRONLY | O_APPEND, 0644);
        // printf("%s\n",opfile);
        if(fd_o==-1){
            
            perrorf("File error %s\n");
            exit(1); }

        }
    }
    if(strstr(command,"warp") || strstr(command,"peek") || strstr(command,"pastevents") || strstr(command,"seek") || strstr(command,"activities") || strstr(command,"ping") ||strstr(command,"proclore") || strstr(command,"iMan")){
        // printf("hi\n");
    int pid=fork();

    if(pid==0){
      if(ip==1){

            if(dup2(fd_i,STDIN_FILENO)==-1){
                perrorf("Dup error");
                exit(1);
            }
            close(fd_i);


        }

    if(op==1){

            if(dup2(fd_o,STDOUT_FILENO)==-1){
                perrorf("Dup error");
                exit(1);
            }
            close(fd_o);

    }
    if(strstr(command,"warp")){
        char* newtoken;
        char* c_command=(char*)malloc(sizeof(char)*100);
        newtoken=strtok(command," ");
        int check_flag=0;
        int argument_flag=0;
        char* current_directory=(char*)malloc(sizeof(char)*LEN);
        current_directory=getcwd(current_directory,LEN);
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
                newtoken=strtok(NULL," ");

        }
        exit(1);
        }
    else if(strstr(command,"peek")){
        // printf("%s\n",command);
                char* newtoken;
                char* c_command=(char*)malloc(sizeof(char)*100);
                newtoken=strtok(command," ");
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
                newtoken=strtok(NULL," ");
                
                
            }
    exit(1);

    }
    else if(strstr(command,"pastevents")){

        char* newtoken;
        char* c_command=(char*)malloc(sizeof(char)*100);
        newtoken=strtok(command," ");

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
                    
                    newtoken=strtok(NULL," ");
                }
                if(check_flag==1&&argument_flag==0){
                    print_queue(f);
                }

        exit(1);
    }
    else if(strstr(command,"seek")){

        return;

    }
    else if(strstr(command,"activities")){
        activities_b(bg_processes);
        exit(1);
    }
    else if(strstr(command,"ping")){
        
        char* newtoken;
        newtoken=strtok(command," ");
        char** ping_array=(char**)malloc(sizeof(char*)*3);
        for(int j=0;j<3;j++){
                    ping_array[j]=(char*)malloc(sizeof(char)*50);
                    
        }
                int ping_ind=0;
            
                while(newtoken){
                    strcpy(ping_array[ping_ind++],newtoken);
                    printf("%s\n",newtoken);
                    newtoken=strtok(NULL," ");
                }
                
                exec_ping(ping_array);
        exit(1);

    }
    else if(strstr(command,"proclore")){

        char* newtoken=strtok(command," ");
        int check_flag=0;
                int argument_flag=0;
                
                while(newtoken){
                    exec_proclore(newtoken,&check_flag,&argument_flag);
                    newtoken=strtok(NULL," ");}
                if(check_flag==1&&argument_flag==0){
                    pid_t pid_shell = getpid();
                    char string_pid[5];
                    sprintf(string_pid,"%d",pid_shell);
                    exec_shell_proclore(string_pid);
                }
                exit(1);
    }

    else if(strstr(command,"iMan")){
        char* c_comm=(char*)malloc(sizeof(char)*100);
        strcpy(c_comm,command);
        char* newtoken=strtok(c_comm," ");
        if(strstr(command,"iMan")){
                    newtoken=strtok(NULL," ");
                }
                char* man_path=(char*)malloc(sizeof(char)*100);
                strcpy(man_path,directory);
                strcat(man_path,"/man.txt");
                read_man(newtoken,man_path);
    exit(1);
    }
    
    }
    else if(pid>0){
        int status;
        waitpid(pid,&status,WUNTRACED);
    }


    }
    else{
    int pid=fork();

    if(pid==0){

        if(ip==1){

            if(dup2(fd_i,STDIN_FILENO)==-1){
                perrorf("Dup error");
                exit(1);
            }
            close(fd_i);


        }

        if(op==1){

            

            if(dup2(fd_o,STDOUT_FILENO)==-1){
                perrorf("Dup error");
                exit(1);
            }
            close(fd_o);

        }

        

        execvp(arr[0],arr);
        exit(1);
    }
    else if(pid>0){
        int status;
        waitpid(pid,&status,WUNTRACED);

    }
    }

}

void io_redirect(char* command){

    int ip=0,op=0;
    int append=0;

    if(strstr(command,"<"))ip=1;
    if(strstr(command,">"))op=1;

    

    if(ip==0&&op==0){
        exec_bash(command,0,0,NULL,NULL,0);

    }

    else if(ip==1&&op==0){
        char* token;
        char* copy_command=(char*)malloc(sizeof(char)*100);
        strcpy(copy_command,command);
        token=strtok(copy_command," ");
        char* command_e=(char*)malloc(sizeof(char)*100);
        char* file_i=(char*)malloc(sizeof(char)*100);
        // printf("%s",copy_command);
        int count=0;
        while(token){
            
            if(count==0){
                strcpy(command_e,token);
            }
            
            else if(count==2){
                strcpy(file_i,token);
            }   
            else if(count!=1){
                perrorf("Invalid redirection");
                exit(1);
            }
            count++;
            token=strtok(NULL," ");

        }

        
        // printf("%s\n",command_e);
        // printf("%s\n",file_i);
        exec_bash(command_e,ip,0,file_i,NULL,append);

        
    }

    else if(ip==0&&op==1){

        char* token;
        char* copy_command=(char*)malloc(sizeof(char)*100);
        strcpy(copy_command,command);
        token=strtok(copy_command," ");
        char* command_e=(char*)malloc(sizeof(char)*100);
        char* file_i=(char*)malloc(sizeof(char)*100);
        // printf("%s",copy_command);
        char* prev=(char*)malloc(sizeof(char)*100);
        int count=0;
        while(token){
        if(count==0&&strstr(token,">")==NULL){
        count++;
        strcpy(prev,token);
        }
         else if(strstr(token,">")==NULL)
         {
                strcat(prev," ");
                strcat(prev,token);}
                
            
            // printf("%s\n",prev);
            token=strtok(NULL," ");
            if(token&&(strstr(token,">"))){
                if(strstr(token,">>")){
                    append=1;
                }
                strcpy(command_e,prev);
                count=0;
            }
            else if(!token){
                strcpy(file_i,prev);
            } 
        
            
        }
        

        // printf("%s\n",file_i);
        
        exec_bash(command_e,0,1,NULL,file_i,append);

    

        
    }

    
    else{

        char* token;
        char* copy_command=(char*)malloc(sizeof(char)*100);
        strcpy(copy_command,command);
        token=strtok(copy_command," ");
        char* command_e=(char*)malloc(sizeof(char)*100);
        char* file_i=(char*)malloc(sizeof(char)*100);
        char* file_o=(char*)malloc(sizeof(char)*100);
        // printf("%s",copy_command);
        char* prev=(char*)malloc(sizeof(char)*100);
        int count=0;
        while(token){
        // printf("%s\n",token);
        if(strstr(token,"<")==NULL && strstr(token,">")==NULL){
            if(count==0){
                strcpy(prev,token);
                count++;
                

            }
            else{
                strcat(prev," ");
                strcat(prev,token);
            }}

        else{

            if(strstr(token,"<")){
                // printf("%s\n",prev);
                strcpy(command_e,prev);
                count=0;
            }
            else if(strstr(token,">")){
                if(strstr(token,">>"))append=1;
                // printf("%s\n",prev);
                strcpy(file_i,prev);
                count=0;
            }

        }


            token=strtok(NULL," ");



        }
        
        strcpy(file_o,prev);
        // printf("%s\n",comma
        exec_bash(command_e,1,1,file_i,file_o,append);

    }


}

void pipe_handler(char** command_array,int n){
    
    if(n==1){
        // printf("hi\n");
        io_redirect(command_array[0]);
    }

else{

    int inp=dup(STDOUT_FILENO);
    int op=dup(STDIN_FILENO);

    int piped[2],pipe_p[2];

    if(pipe(piped)<0){
        perror("Piping error\n");
        return;
    }

    if(dup2(piped[1],STDOUT_FILENO)==-1){
        perror("Dup error!");
        return;
    }

    close(piped[1]);


    io_redirect(command_array[0]);


    pipe_p[0]=piped[0];
    pipe_p[1]=piped[1];

    for(int i=1;i<n-1;i++){

        if(pipe(piped)<0){
        perror("Piping error\n");
        return;}

        if(dup2(pipe_p[0],STDIN_FILENO)==-1){
            perror("Dup error!");
            return;
        }
        if(dup2(piped[1],STDOUT_FILENO)==-1){
            perror("Dup error!");
            return;
        }

        //exec
        io_redirect(command_array[i]);



        close(pipe_p[0]);
        close(piped[1]);

        pipe_p[0]=piped[0];
        pipe_p[1]=piped[1];
    }

    

    dup2(piped[0],STDIN_FILENO);
    close(piped[0]);
    dup2(op,STDOUT_FILENO);

    io_redirect(command_array[n-1]);
    

    dup2(inp,STDIN_FILENO);

}

}