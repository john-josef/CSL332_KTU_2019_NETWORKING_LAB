#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>

void main(){
	int portno;
	printf("Enter PORT NUMBER: ");
	scanf("%d",&portno);
	char sendbuf[1024],recvbuf[1024];
	bzero(sendbuf,1024);
	bzero(recvbuf,1024);
	struct timeval timeout;
	timeout.tv_sec=1;
	struct sockaddr_in seraddr,cliaddr;
	int sersoc=socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(portno);
	if (bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in))!=0){
		printf("\nBINDING ERROR..Please try another PORT\n");
		exit(0);
	}
	listen(sersoc,10);
	printf("\nServer waiting for connections...\n");
	socklen_t addrlen=sizeof(struct sockaddr_in);
	int clisoc=accept(sersoc,(struct sockaddr *)&cliaddr,&addrlen);
	setsockopt(clisoc,SOL_SOCKET,SO_RCVTIMEO,(struct timeval *)&timeout,sizeof(struct timeval));
	printf("\nConnection accepted from Client %s on port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
	printf("\nEnter the number of frames you would like to send: ");
	int n;
	scanf("%d",&n);
	sprintf(sendbuf,"%d",n);
	send(clisoc,sendbuf,1024,0);
	bzero(sendbuf,1024);
	int count=1,duplicate=0,initial=0;
	while(count<=n){
		sprintf(sendbuf,"%d",count);
		send(clisoc,sendbuf,1024,0);
		bzero(sendbuf,1024);
		if(duplicate==0)
			printf("\nFrame %d sent",count);
		else	
			printf("\nFrame %d sent (again)",count);
		if(recv(clisoc,recvbuf,1024,0)>0){
			printf("\nAcknowledgent for frame %d received",atoi(recvbuf));
			bzero(recvbuf,1024);
			duplicate=0;
			count++;
		}
		else{
			printf("\nAcknowledgement not received !!");
			duplicate=1;
		}
	}
	sprintf(sendbuf,"%d",count);
	send(clisoc,sendbuf,1024,0);
	bzero(sendbuf,1024);
}
