#include "headers.h"

void searchFile(char *dirPath, char *filename,int d_flag,int e_flag,int f_flag,char** files,int* index) {
    DIR *dir;
    struct dirent *file_path_struct;
    struct stat fileStat;
    
    dir = opendir(dirPath);
    if (dir) {
        while ((file_path_struct = readdir(dir)) != NULL) {
            if (strcmp(file_path_struct->d_name, ".") == 0 || strcmp(file_path_struct->d_name, "..") == 0) {
                continue; 
            }

            char filePath[PATH_MAX];
            snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, file_path_struct->d_name);

            if (stat(filePath, &fileStat) == 0) {
                // printf("%s\n",file_path_struct->d_name);
                if ( strcmp(file_path_struct->d_name,filename)!=0) {
                    // Recursively search in subdirectories
                    if(S_ISDIR(fileStat.st_mode)){
                    searchFile(filePath, filename,d_flag,e_flag,f_flag,files,index);}
                } else if (strcmp(file_path_struct->d_name, filename) == 0)
                
                 {
                
                    strcpy(files[(*index)++],filePath);

                }
            }
        }
        closedir(dir);
    }
}