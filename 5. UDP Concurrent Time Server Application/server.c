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
    struct sockaddr_in seraddr,cliaddr;
    int sersoc=socket(AF_INET,SOCK_DGRAM,0);
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    if(bind(sersoc, (struct sockaddr *)&seraddr , sizeof(struct sockaddr_in))!=0){
        printf("\nBINDING ERROR..Try a different PORT\n");
        exit(0);
    }
    socklen_t addrlen=sizeof(struct sockaddr_in);
    recvfrom(sersoc,recvbuf,1024,0,(struct sockaddr *)&cliaddr,&addrlen);
    printf("\nClient Time: %s\n",recvbuf);
    sendto(sersoc,sendbuf,1024,0,(struct sockaddr *)&cliaddr,sizeof(struct sockaddr_in));
    printf("\nServer time sent to client.\n");
}
