#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>

void main(){
    struct timeval timeout;
    timeout.tv_sec=2;
    char sendbuf[1024],recvbuf[1024];
    bzero(sendbuf,1024);
    bzero(recvbuf,1024);
    int sersoc=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr,cliaddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(4950);
    bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    listen(sersoc,10);
    socklen_t addrlen=sizeof(struct sockaddr_in);
    int clisoc=accept(sersoc,(struct sockaddr *)&cliaddr,&addrlen);
    setsockopt(clisoc,SOL_SOCKET,SO_RCVTIMEO,(struct timeval *)&timeout,sizeof(struct timeval));
    printf("\nConnection established from Client %s on port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

    int n,window,count=1;
    printf("Enter the number of frames to be sent to the client: ");
    scanf("%d",&n);
    printf("\nEnter the size of the window: ");
    scanf("%d",&window);

    sprintf(sendbuf,"%d",n);
    send(clisoc,sendbuf,1024,0);
    bzero(sendbuf,1024);

    for(int i=0;i<window;i++){
        printf("\nSending Frame %d",count);
        sprintf(sendbuf,"%d",count++);
        send(clisoc,sendbuf,1024,0);
        bzero(sendbuf,1024);
    }

    while(1){
        if(recv(clisoc,recvbuf,1024,0)>0){
            printf("\nAcknowledgement for Frame %d received",atoi(recvbuf));
            if(atoi(recvbuf)==n)
                break;
            if(count<=n){
                printf("\nSending Frame %d",count);
                sprintf(sendbuf,"%d",count++);
                send(clisoc,sendbuf,1024,0);
                bzero(sendbuf,1024);
            }
            else{
                count++;
            }
        }
        else{
            count-=window;
            printf("\nAcknowledgement for Frame %d NOT received\n",count);
            for(int k=0;k<window;k++){
                if(count<=n){
                    printf("\nSending Frame %d (again)",count);
                    sprintf(sendbuf,"%d",count++);
                    send(clisoc,sendbuf,1024,0);
                    bzero(sendbuf,1024);
                }
            }
        }
        bzero(recvbuf,1024);
    }
}
