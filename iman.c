#include "headers.h"

int read_man(char* token,char* path){
    const char *host = "man.he.net"; 
    char* page=(char*)malloc(sizeof(char)*100);
    strcpy(page,"http://man.he.net/?topic="); 
    strcat(page,token);
    strcat(page,"&section=all");

   
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perrorf("Socket creation error");
        return 1;
    }

    
    struct hostent *server = gethostbyname(host);
    if (server == NULL) {
        perrorf("Host resolution error");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);

    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection error");
        return 1;
    }
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", page, host);
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Request sending error");
        return 1;
    }
    char response[MAX_BUFFER_SIZE];
    char content[MAX_BUFFER_SIZE];
    ssize_t bytes_received;
    FILE* f=fopen(path,"w");
    while ((bytes_received = recv(sockfd, response, sizeof(response), 0)) > 0) {
        fwrite(response, 1, bytes_received, f);
    }
    // printf("%s\n",content);
    if (bytes_received < 0) {
        perrorf("Response receiving error");
        return 1;
    }
    close(sockfd);


    char line[1000];
    fclose(f);
    FILE* f_r=fopen(path,"r");
    
    int flag=0;
    int c=0;
    while(fgets(line,1000,f_r)){
        if(line[0]=='N'){
            flag=1;
        }
        if(line[0]=='G'){
            flag=0;
        }
        if(flag==1){
            printf("%s\n",line);
            c=1;
        }
        

    }
    fclose(f_r);
    if(c==0){
        perrorf("Invalid command\n");
    }


}

