#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>

void main(){
    srandom(time(NULL));
    char sendbuf[1024],recvbuf[1024];
    bzero(sendbuf,1024);
    bzero(recvbuf,1024);
    int clisoc=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(4950);
    connect(clisoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));

    recv(clisoc,recvbuf,1024,0);
    int n=atoi(recvbuf);
    bzero(recvbuf,1024);

    int count=1;
    while(1){
        recv(clisoc,recvbuf,1024,0);
        if(count==atoi(recvbuf)){
            sleep(1+(rand()%4));
            printf("\nReceived Frame %d",count);
            printf("\nSending Acknowledgement for Frame %d",count);
            sprintf(sendbuf,"%d",count++);
            send(clisoc,sendbuf,1024,0);
            bzero(sendbuf,1024);
            if(count==n+1)
                break;
        }
        bzero(recvbuf,1024);
    }
}
