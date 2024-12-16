#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void main(){
    int portno;
    printf("Enter PORT NUMBER: ");
    scanf("%d",&portno);
    char recvbuf[1024],sendbuf[1024],temp[1024];
    bzero(recvbuf,1024);
    bzero(sendbuf,1024);
    bzero(temp,1024);
    int n;
    printf("\nEnter a number: ");
    scanf("%d",&n);
    sprintf(temp,"%d",n);
    strcpy(sendbuf,temp);
    struct sockaddr_in seraddr;
    int clisoc=socket(AF_INET,SOCK_DGRAM,0);
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    socklen_t addrlen=sizeof(struct sockaddr_in);
    sendto(clisoc,sendbuf,1024,0,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    recvfrom(clisoc,recvbuf,1024,0,(struct sockaddr *)&seraddr,&addrlen);
    printf("\n%s\n",recvbuf);
}