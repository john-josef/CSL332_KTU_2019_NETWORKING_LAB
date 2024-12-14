#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>

void main(){
	char recvbuf[1024],sendbuf[1024];
	bzero(recvbuf,1024);
	bzero(sendbuf,1024);
	srandom(time(NULL));
	struct sockaddr_in seraddr;
	int clisoc=socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(4950);
	connect(clisoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
	printf("\nClient waiting to receive...\n");
	recv(clisoc,recvbuf,1024,0);
	int n=recvbuf[0]-'0';
	bzero(recvbuf,1024);
	int count=1,flag=0;
	while(1){
		recv(clisoc,recvbuf,1024,0);
		if((recvbuf[0]-'0')==count){
			if(flag==1){
				printf("\nFrame %d received\nAcknowledgement for frame %d sent\n",count-1,count-1);
				if(count==n+1)
					break;
			}
			sleep(1+(rand()%4));
			sprintf(sendbuf,"%d",count);
			send(clisoc,sendbuf,1024,0);
			bzero(sendbuf,1024);
			flag=1;
			count++;
		}
		else{
			printf("\nDELAYED\n");
		}
		bzero(recvbuf,1024);
	}
}