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
    printf("\nEnter the PORT NUMBER: ");
    scanf("%d",&portno);
    char buffer[1024];
    bzero(buffer,1024);
    int clisoc=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    connect(clisoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    printf("\nEnter the number of terms required in the fibonacci series to be displayed: ");
    int n;
    scanf("%d",&n);
    sprintf(buffer,"%d",n);
    send(clisoc,buffer,1024,0);
    bzero(buffer,1024);
    recv(clisoc,buffer,1024,0);
    printf("\n%s",buffer);
}
