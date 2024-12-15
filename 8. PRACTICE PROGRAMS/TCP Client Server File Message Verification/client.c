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
    int clisoc=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    connect(clisoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    char file[1024],buffer[1024];
    bzero(buffer,1024);
    bzero(file,1024);
    printf("\nEnter the name of the file: ");
    scanf("%s",file);
    send(clisoc,file,1024,0);
    recv(clisoc,buffer,1024,0);
    printf("\n\n\t\t\t%s\n\n",buffer);
}
