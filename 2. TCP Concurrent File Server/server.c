#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void readFile(char file[],int clisoc){
    FILE *fp = fopen(file,"r");
    char buffer[1024];
    bzero(buffer,1024);
    while((fgets(buffer,1024,fp))!=NULL){
        send(clisoc,buffer,1024,0);
        bzero(buffer,1024);
    }
}

void main(){
    int portno;
    printf("Enter PORT NUMBER: ");
    scanf("%d",&portno);
    int clisoc,count=0;
    char file[1024],buffer[1024];
    bzero(file,1024);
    bzero(buffer,1024);
    socklen_t addrlen;
    pid_t child;
    struct sockaddr_in seraddr,cliaddr;
    int sersoc=socket(AF_INET,SOCK_STREAM,0);
    printf("[+] Server socket created\n");
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    if (bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in)) != 0){
        printf("Error in binding.. Try another PORT");
        exit(0);
    }
    printf("[+] Server socket bound\n");
    listen(sersoc,10);
    printf("[+] Server socket waiting for incoming connections....\n");
    while(1){
        clisoc=accept(sersoc,(struct sockaddr *)&cliaddr,&addrlen);
        printf("\n[+] Connection accepted from client %s on port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
        printf("\n[+] Total number of clients connected : %d\n",++count);
        if((child=fork())==0){
            recv(clisoc,file,1024,0);
            strcpy(buffer,"\nServer PROCESS ID: ");
            char serverpid[1024];
            sprintf(serverpid,"%d",getpid());
            strcat(buffer,serverpid);
            strcat(buffer,"\n");
            send(clisoc,buffer,1024,0);
            if(access(file,F_OK)==0){
                printf("\n[+] Requested File Found\n");
                readFile(file,clisoc);
                printf("\n[+] Requested file sent to client successfully\n");
                send(clisoc,"exit",1024,0);
            }
            else{
                printf("\n[+] Requested File NOT FOUND !!!\n");
                send(clisoc,"quit",1024,0);
            }
            exit(0);
        }
    }
}
