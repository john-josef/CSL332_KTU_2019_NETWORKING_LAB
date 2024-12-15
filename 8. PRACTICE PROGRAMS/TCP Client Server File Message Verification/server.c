/*

Implement a TCP client server program for performing message verification operations. 
Client send a file containing text to server. Display the result returned by server. 
Server check if the text send by the client contains hate words.(Eg: I will kill you). 
If yes return the status "Rejected" else return "Approved". 
Send this message back to client and client must display the status message. 
Server may maintain a list of hate words in a buffer to identify 
if given input has hate word in it by matching with words in this buffer.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void main(){
    char hatewords[][15]={"kill","hate","murder","violence","abuse","attack","terror","assault","destroy",
    "slaughter","curse","revenge","bully","harm","ruin","annihilate","injure","explode","brutal","wrath"};
    int portno;
    printf("Enter PORT NUMBER: ");
    scanf("%d",&portno);
    int sersoc=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr,cliaddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    if(bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in))!=0){
        printf("\nCouldn't bind socket.. Please try another port\n");
        exit(0);
    }
    listen(sersoc,10);
    printf("\nServer waiting for incoming connections on port %d\n",ntohs(seraddr.sin_port));
    socklen_t addrlen=sizeof(struct sockaddr_in);
    int clisoc=accept(sersoc,(struct sockaddr *)&cliaddr,&addrlen);
    printf("\nConnection from client %s on port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    char buffer[1024],file[1024],temp[1024];
    bzero(temp,1024);
    bzero(file,1024);
    bzero(buffer,1024);
    recv(clisoc,file,1024,0);
    if(access(file,F_OK)!=0){
        printf("\nRequested File Not Found!!\n");
        exit(0);
    }
    FILE *fp=fopen(file,"r");
    int flag=1;
    while(fgets(buffer,1024,fp)){
        char *token=strtok(buffer," ");
        while(token!=NULL){
            for(int i=0;i<20;i++){
                if(strcmp(hatewords[i],token)==0){
                    flag=0;
                }
            }
            token=strtok(NULL," ");
        }
        bzero(buffer,1024);
    }
    if(flag==1)
        send(clisoc,"APPROVED",1024,0);
    else
        send(clisoc,"REJECTED",1024,0);
}
