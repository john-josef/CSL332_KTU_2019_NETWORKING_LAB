#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void main(){
    int portno,n;
    char buffer[1024],temp[1024];
    bzero(buffer,1024);
    bzero(temp,1024);
    printf("Enter PORT NUMBER: ");
    scanf("%d",&portno);
    int clisoc=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\nEnter a number in the range 0-10 : ");
    scanf("%d",&n);
    sprintf(temp,"%d",n);
    strcpy(buffer,temp);
    sendto(clisoc,buffer,1024,0,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    bzero(buffer,1024);
    socklen_t addrlen=sizeof(struct sockaddr_in);
    recvfrom(clisoc,buffer,1024,0,(struct sockaddr *)&seraddr,&addrlen);
    printf("\n\n\t\t\t%s\n\n",buffer);
}
