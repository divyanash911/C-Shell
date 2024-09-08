#include "headers.h"


void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}


void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void e_neonate(char ic,int n){
    
        setbuf(stdout, NULL);
        enableRawMode();
        int p=fork();


        if(p==0){
        while(1){
        
        FILE* f = fopen("/proc/sys/kernel/ns_last_pid","r"); 
        char pid[10];
        fgets(pid,10,f);


        printf("%s",pid);

        

        sleep(n);}
        }
        
        else if(p>0){
            char c;
             while (read(STDIN_FILENO, &c, 1) == 1 && c != ic) {
                continue;
             }

             kill(p,SIGKILL);

        }
        disableRawMode();

}


