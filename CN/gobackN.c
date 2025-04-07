//server.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 22000

int power(int updated_n){
    int res = 1;
    for(int i = 0 ; i < updated_n ; i++){
        res *= 2;
    }

    int final_res = res-1;
    return final_res;
}
int main(int argc, char *argv[]){
    int sockfd, connfd, len, a;
    struct sockaddr_in serveraddr, cliaddr;
    int received_data[5];

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

    read(connfd, received_data, sizeof(received_data));
    int unpacked_n = ntohl(received_data[0]);
    int unpacked_sf = ntohl(received_data[1]);
    // printf("SF: %d\n", unpacked_sf);
    int unpacked_sn = ntohl(received_data[2]);
    int unpacked_ack = ntohl(received_data[3]);
    int unpacked_new_frames = ntohl(received_data[4]);
    int window_size = power(unpacked_n);
    printf("Window size: %d\n", window_size);
    int new_sf = unpacked_sf + 1;
    printf("New sf: %d\n", new_sf);
    int new_sn = unpacked_sn + unpacked_new_frames;
    printf("New Sn: %d\n", new_sn);
    int updated_range_val = (unpacked_sf + window_size) % (window_size+1);
    printf("Updated range: %d to %d\n", unpacked_sf, updated_range_val-1);    
}

//client.c

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
    int n, sf, sn, ack, new_frames;
    struct sockaddr_in serveraddr;
    printf("Enter timeout and threshhold values:\n");
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
    printf("Enter your data -> n, sf, sn, ack, new_frames:\n");
    scanf("%d %d %d %d %d", &n, &sf, &sn, &ack, &new_frames);
    int packed_Data[5];
    packed_Data[0] = htonl(n);
    packed_Data[1] = htonl(sf);
    packed_Data[2] = htonl(sn);
    packed_Data[3] = htonl(ack);
    packed_Data[4] = htonl(new_frames);
    write(sockfd, &packed_Data, sizeof(packed_Data));
}
