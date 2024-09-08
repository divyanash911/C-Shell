#include "headers.h"

void exec_fg(char* pid){

    int pid_r=atoi(pid);

    int status;
    int stat=waitpid(pid_r,&status,WNOHANG);
    if(stat!=0)perrorf("No process found");

    if(kill(pid_r,SIGCONT)==-1){
        perrorf("Signal error");
        exit(1);
    }

    // status;
    waitpid(pid_r,&status,WUNTRACED);

}

void exec_bg(char* pid){

    int pid_r=atoi(pid);

    int status;
    int stat=waitpid(pid_r,&status,WNOHANG);
    if(stat!=0)perrorf("No process found");

    if(kill(pid_r,SIGCONT)==-1){
        perrorf("Signal error");
        exit(1);
    }

    

}


