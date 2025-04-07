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
    int sockfd, connfd, len, a, thresh, timeout;
    struct sockaddr_in serveraddr, cliaddr;

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

    
    read(connfd, &thresh, sizeof(thresh));
    read(connfd, &timeout, sizeof(timeout));

    thresh = ntohl(thresh);
    timeout = ntohl(timeout);

    printf("Updated threshhold: %d\n", timeout/2);
    printf("cwnd before timeout: \n");
    int a = 1;
    while(1){
        printf("cwnd: %d\n", a);
        a *= 2;
        if(a > timeout || a > thresh){
            break;
        }
    }

    printf("cwnd after timeout: \n");
    a = 1;
    int cwnd = timeout/2;
    int flag = 0;
    while(1){
        if(flag == 0){
            printf("cwnd: %d\n",a);
            a *= 2;
        }
        else{
            printf("cwnd: %d\n", a);
            a++;
        }
        if(a==cwnd){ 
            flag=1; 
           } 
           if(a>thresh){ 
            break; 
           } 
         
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

int main(int argc, char *argv[]){
    int sockfd, len;
    int timeout, thresh;
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
    thresh = htonl(thresh);
    timeout = htonl(timeout);
    write(sockfd, &thresh, sizeof(thresh));
    write(sockfd, &timeout, sizeof(timeout));
}