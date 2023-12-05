#include "headers.h"

void print_in_color(char* string,char* print_string){

    struct stat file_stat;
    int code=0;

    // Use the stat function to get file information
    if (stat(string, &file_stat) == 0) {
        if (S_ISDIR(file_stat.st_mode)) {
            code=2;
        } 
        if ((file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH) && code!=2) {
            
            code=3;
        }
        }
    if(code==0){printf("%s",print_string);}
    else if(code==2){
        printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET,print_string);
    }
    else if(code==3){
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET,print_string);
    }


}

void print_permissions(mode_t mode) {
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}