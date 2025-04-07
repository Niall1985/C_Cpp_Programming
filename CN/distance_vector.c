// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 22000
#define INF 100
#define MAX_NODES 10

int costmatrix[MAX_NODES][MAX_NODES];
int distanceTable[MAX_NODES][MAX_NODES];
int nextHop[MAX_NODES][MAX_NODES];
int nodes;

void distanceVectorRouting() {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            distanceTable[i][j] = costmatrix[i][j];
            if (costmatrix[i][j] != INF && i != j) {
                nextHop[i][j] = j;
            } else {
                nextHop[i][j] = -1;
            }
        }
    }

    int updated;
    do {
        updated = 0;
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                for (int k = 0; k < nodes; k++) {
                    if (distanceTable[i][k] + distanceTable[k][j] < distanceTable[i][j]) {
                        distanceTable[i][j] = distanceTable[i][k] + distanceTable[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

void printRoutingTables() {
    printf("\nFinal Routing Tables:\n");
    for (int i = 0; i < nodes; i++) {
        printf("\nRouter %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < nodes; j++) {
            printf("%d\t\t%d\t\t%d\n", j, nextHop[i][j], distanceTable[i][j]);
        }
    }
}

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in serveraddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket created successfully\n");

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }
    printf("Socket bound successfully\n");

    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        close(sockfd);
        exit(1);
    }
    printf("Server listening on port %d\n", PORT);

    len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (connfd < 0) {
        perror("Accept failed");
        close(sockfd);
        exit(1);
    }
    printf("Connection accepted\n");

    int net_nodes;
    read(connfd, &net_nodes, sizeof(net_nodes));
    nodes = ntohl(net_nodes);

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            int val;
            read(connfd, &val, sizeof(val));
            costmatrix[i][j] = ntohl(val);
        }
    }

    distanceVectorRouting();
    printRoutingTables();

    close(connfd);
    close(sockfd);
    return 0; 
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <Server IP>\n", argv[0]);
        return 1;
    }

    int sockfd, nodes;
    int costmatrix[10][10];
    struct sockaddr_in serveraddr;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter cost matrix (%d x %d):\n", nodes, nodes);
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &costmatrix[i][j]);
        }
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(1);
    }

    int net_nodes = htonl(nodes);
    write(sockfd, &net_nodes, sizeof(net_nodes));

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            int val = htonl(costmatrix[i][j]);
            write(sockfd, &val, sizeof(val));
        }
    }

    close(sockfd);
    return 0;
}
