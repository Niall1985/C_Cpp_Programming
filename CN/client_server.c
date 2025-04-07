//server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 4771

int main(int argc, char *argv[]){
    //declare the variables and the buffer and the client-server socket struct
    char buffer[100];
    int sockfd, connfd, a, len, i=0;
    struct sockaddr_in serveraddr, cliaddr;

    //create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("Error in creating socket");
    }
    print("Server socket created successfully\n");

    //initialize the socket (server-side)
    bzero((struct sockaddr*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

     //bind the socket
    if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
        print("Error in bind function")
    }
    print("Server socket binded\n");

    //listen for incoming requests
    if((a = listen(sockfd, 5)) == -1){
        print("Error in listen function");
    }
    print("Server socket listened\n");

    //get the length of the clientadd
    len = sizeof(cliaddr);

    //setup the socket to listen for accepting messages from the client end
    if((conndf = accept(sockfd, (struct sockaddr*)&cliaddr, &len)) < 0){
        print("Error in accept\n");
    }

    //function to read and write data
    do{
        strcpy(buffer, "");
        read(conndf, buffer, 100);
        printf("From client: %s", buffer);
        if(strcmp(bufferm "bye\n") == 0){
            printf("From client: %s\n");
            goto stop;
        }
        printf("Server:");
        fgets(buffer, sizeof(buffer), stdin);
        wrtie(connfd, buffer, 100);
    } while(strcmp(buffer, "bye\n") != 0);
    stop:
        close(connfd);
        return 0;
}


// client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <apra/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 4771

int main(int argc, char *argv[]){
    //declare the variables and the buffer and the struct
    char buffer[100];
    int sockfd;
    struct sockaddr_in serveraddr;

    //create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("Errorin creating socket");
    }
    print("Server socket created successfully\n");

    // intitialize the socket
    bzero((struct sockaddr*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    //connect the client socket to the server
    if(connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
        perror("Error in connect");
        close(sockfd);
    }

    //send data to the serverside and read data from the server
    do{
        strcpy(buffer, "");
        print("Client:\n");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] == '\0';
        write(sockfd, buffer, sizeof(buffer));
        if(strcmp(buffer, "bye\n") == 0){
            printf("Client: %s\n");
            break;
        }
        strcpy(buffer, "");
        print("From Server: \n");
        read(sockfd, buffer, sizeof(buffer));
    } while(strcmp(buffer, "bye") != 0);
        close(sockfd);
}