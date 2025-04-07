/*
Workflow:
1. calculate end ip using start ip and cidr
2. calculate available number of hosts, using start and end ip
3. calculate subnet size
4. server program
5. take the inputs
6. find total required hosts using calculate subnets function
7. allocate subnets
*/ 




//server.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#define PORT 22000

unsigned int endip(unsigned int start_ip, int cidr){
    unsigned int mask = 0xFFFFFFFF << (32-cidr);
    retrun (start_ip & mask) | (~mask);
}
int available_hosts(unsigned int start_ip, unsigned int end_ip){
    return (end_ip - start_ip) - 1;
}

int subnet_size(int hosts_per_group[]){
    int size = 1;
    while(size < hosts_per_group+2){
        size *= 2;
    }
    return size;
}


int main(int argc, char *argv[]){
    int sockfd, connfd, len, a;
    int num_groups, cidr, subnet_size;
    unsigned int start_ip, end_ip; 
    struct sockaddr_in serveraddr, clitaddr;

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

    len = sizeof(cliaddr)
    if((connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len)) < 0){
        printf("Error in accepting\n");
        exit(0);
    }
    printf("No error in accepting\n");
    read(connfd, &start_ip, sizeof(start_ip));
    read(connfd, &cidr, sizeof(cidr));
    read(connfd, &num_groups, sizeof(num_groups));
    start_ip = ntohl(start_ip);
    cidr = ntohl(cidr);
    num_groups = ntohl(num_groups);

    end_ip = endip(start_ip, cidr);
    int available_hosts_no = available_hosts(start_ip, end_ip);

    int *hosts_per_group = (int*)malloc(num_groups*sizeof(int));
    for(int i = 0 ; i < num_groups ; i++){
        read(connfd, &hosts_per_group[i], sizeof(int));
        hosts_per_group[i] = ntohl(hosts_per_group[i]);
    }
    int total_required_ips = 0;
    for (int i = 0; i < num_groups; i++) {
        subnet_size = calculate_subnet_size(hosts_per_group[i]);
        total_required_ips += subnet_size;
    
        unsigned int network = start_ip;
    
        unsigned int first_address = network;
        unsigned int last_address = first_address + subnet_size - 1;

        printf("Group %d:\n", i + 1);
        printf("  First Address: %d.%d.%d.%d\n",
        (first_address >> 24) & 0xFF, (first_address >> 16) & 0xFF,
        (first_address >> 8) & 0xFF, first_address & 0xFF);

        printf("  Last Address: %d.%d.%d.%d\n",
        (last_address >> 24) & 0xFF, (last_address >> 16) & 0xFF,
        (last_address >> 8) & 0xFF, last_address & 0xFF);
        network += subnet_size;
    }
}



