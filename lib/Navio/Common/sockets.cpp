/** @file gps.cpp
 * 
 * @brief Socket library implementation of
 * sockets.h
 *
 * @author Santiago Torres Borda       
 * 
 * @version 1.0
 *
 */ 
#ifndef SOCKETS_H
#include"sockets.h"
#endif

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int create(){
    int sockfd;
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            printf("socket creation failed\n");
            exit(EXIT_FAILURE);
    }
    return sockfd;
}

void send_float(int sock, float msg, int port, char* addr){
    char buffer[MAXLINE];
    char message[MAXLINE];
    sprintf(&message[0],"%f",msg);
    struct sockaddr_in       servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(addr);
    unsigned int n, len;

    sendto(sock, (const char *)message, strlen(message),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Hello message sent.\n");
}