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
    char buffer[1024];
    bzero(buffer,1024);
    printf("Enter PORT NUMBER: ");
    scanf("%d",&portno);
    int sersoc=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in seraddr,cliaddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    seraddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in)) != 0){
        printf("\nBINDING ERROR...Please try a different PORT\n");
        exit(0);
    }
    socklen_t addrlen=sizeof(struct sockaddr_in);
    recvfrom(sersoc,buffer,1024,0,(struct sockaddr *)&cliaddr,&addrlen);
    int n=atoi(buffer);
    printf("\n%d received\n",n);
    bzero(buffer,1024);

    switch(n){
        case 0:
            strcpy(buffer,"ZERO");
            break;
        case 1:
            strcpy(buffer,"ONE");
            break;
        case 2:
            strcpy(buffer,"TWO");
            break;
        case 3:
            strcpy(buffer,"THREE");
            break;
        case 4:
            strcpy(buffer,"FOUR");
            break;
        case 5:
            strcpy(buffer,"FIVE");
            break;
        case 6:
            strcpy(buffer,"SIX");
            break;
        case 7:
            strcpy(buffer,"SEVEN");
            break;
        case 8:
            strcpy(buffer,"EIGHT");
            break;
        case 9:
            strcpy(buffer,"NINE");
            break;
        case 10:
            strcpy(buffer,"TEN");
            break;
    }
    sendto(sersoc,buffer,1024,0,(struct sockaddr *)&cliaddr,sizeof(struct sockaddr_in));
}
