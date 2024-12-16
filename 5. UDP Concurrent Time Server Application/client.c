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
    char recvbuf[1024],sendbuf[1024];
    for(int i=0;i<1024;i++){
        recvbuf[i]='\0';
        sendbuf[i]='\0';
    }
    time_t t;
    time(&t);
    strcpy(sendbuf,ctime(&t));
    struct sockaddr_in seraddr;
    int clisoc=socket(AF_INET,SOCK_DGRAM,0);
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t addrlen=sizeof(struct sockaddr_in);
    sendto(clisoc,sendbuf,1024,0,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    printf("\nClient time sent to server.\n");
    recvfrom(clisoc,recvbuf,1024,0,(struct sockaddr *)&seraddr,&addrlen);
    printf("\nServer Time: %s\n",recvbuf);
}
