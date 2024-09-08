#include "headers.h"


void exec_ping(char** ping_array){
    
    int process=atoi(ping_array[1]);
    int signal=atoi(ping_array[2]);
    signal=signal%32;
    if(kill(process,signal)==0){
        printf("Sent signal %d to process with pid %d\n",signal,process);

    }
    else{
        printf("No such process found\n");
    }

}

