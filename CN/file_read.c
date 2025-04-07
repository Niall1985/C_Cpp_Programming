//server.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 22000

int main(int argc, char *argv[]){
    int sockfd, connfd, len, a;
    struct sockaddr_in serveraddr, cliaddr;
    char ch;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1){
        printf("Error in creating the socket\n");
        exit(0);
    }

    bzero((struct sockaddr*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
        printf("Error in binding socket\n");
        exit(0);
    }
    printf("Socket has been bound successfully\n");

    if((a = listen(sockfd, 5)) == -1){
        printf("Error in Listening\n");
        exit(0);
    }
    printf("No error in Listening\n");

    len = sizeof(cliaddr);
    if((connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len)) < 0){
        printf("Error in accepting\n");
        exit(0);
    }
    printf("No error in accepting\n");
    int count = 0;
    while(read(connfd, &ch, sizeof(ch)) > 0 ){
        if(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' ||ch == 'u'){
            count++;
        }
        printf("Count of vowels: %d\n", count);
    }
    
    
}



// client.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 22000
File *file;
char ch;

int main(int argc, char *argv[]){
    int sockfd, len;
    struct sockaddr_in serveraddr;
    printf("Enter timeout and threshhold values:\n");
    scanf("%d %d", &timeout, &thresh);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("Failed to create the socket\n");
        exit(0);
    }
    printf("Socket created successfully\n");

    bzero((struct sockaddr*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
        printf("Failed to bind the socket\n");
        exit(0);
    }
    printf("Socket binded successfylly\n");
    file = fopen("sample.txt", "r");
    if (file == NULL){
        printf("No file found\n");
        exit(0);
    }
    while((ch = fgetc(file)) != EOF){
        write(sockfd, &ch, sizeof(ch));
    }

}