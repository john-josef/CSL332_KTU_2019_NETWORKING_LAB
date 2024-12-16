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
    bzero(recvbuf,1024);
    bzero(sendbuf,1024);
    struct sockaddr_in seraddr,cliaddr;
    int sersoc=socket(AF_INET,SOCK_DGRAM,0);
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    seraddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sersoc, (struct sockaddr *)&seraddr , sizeof(struct sockaddr_in))!=0){
        printf("\nBINDING ERROR..Try a different PORT\n");
        exit(0);
    }
    socklen_t addrlen=sizeof(struct sockaddr_in);
    recvfrom(sersoc,recvbuf,1024,0,(struct sockaddr *)&cliaddr,&addrlen);

    int n=atoi(recvbuf);
    printf("\nNumber %d received\n",n);
    strcpy(sendbuf,recvbuf);
    if(n<=1)
        strcat(sendbuf," is Neither Prime Nor Composite");
    else{
        int flag=1;
        for(int k=2;k<n;k++){
            if(n%k==0){
                flag=0;
                strcat(sendbuf," is Composite");
                break;
            }
        }
        if(flag==1)
            strcat(sendbuf," is Prime");
    }

    sendto(sersoc,sendbuf,1024,0,(struct sockaddr *)&cliaddr,sizeof(struct sockaddr_in));
}
