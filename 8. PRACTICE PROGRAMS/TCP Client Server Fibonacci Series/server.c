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
    char buffer[1024],temp[1024];
    bzero(temp,1024);
    bzero(buffer,1024);
    struct sockaddr_in seraddr,cliaddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port=htons(portno);
    int sersoc=socket(AF_INET,SOCK_STREAM,0);
    if(bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in))!=0){
        printf("BINDING COULDNT BE DONE !!.. Please try another port number..\n");
        exit(0);
    }
    listen(sersoc,10);
    socklen_t addrlen=sizeof(struct sockaddr_in);
    printf("\nServer waiting for connections on port %d\n",ntohs(seraddr.sin_port));
    int clisoc=accept(sersoc,(struct sockaddr *)&cliaddr,&addrlen);
    printf("\nConnection established from Client %s on port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    recv(clisoc,buffer,1024,0);
    int n=atoi(buffer);
    printf("\nNumber %d received\n",n);
    bzero(buffer,1024);
    strcpy(buffer,"\nFibonacci series upto ");
    sprintf(temp,"%d terms:  ",n);
    strcat(buffer,temp);
    bzero(temp,1024);
    int fibo[n];
    for(int j=0;j<n;j++){
        if(j<=1){
            fibo[j]=j;
            sprintf(temp,"%d ",fibo[j]);
            strcat(buffer,temp);
            bzero(temp,1024);
        }
        else{
            fibo[j]=fibo[j-1]+fibo[j-2];
            sprintf(temp,"%d ",fibo[j]);
            strcat(buffer,temp);
            bzero(temp,1024);
        }
    }
    strcat(buffer,"\n\n");
    send(clisoc,buffer,1024,0);
}
