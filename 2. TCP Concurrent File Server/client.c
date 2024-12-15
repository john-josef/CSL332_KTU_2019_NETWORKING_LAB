#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void writeFile(int clisoc){
    char buffer[1024];
    bzero(buffer,1024);
    FILE *fp=fopen("output.txt","w+");
    while(1){
        recv(clisoc,buffer,1024,0);
        if(strcmp(buffer,"exit")==0){
            printf("\nFILE TRANSFER SUCCESSFUL !!\n");
            break;
        }
        if(strcmp(buffer,"quit")==0){
            printf("\nREQUESTED FILE NOT FOUND !!\n");
            break;
        }
        printf("%s",buffer);
        fprintf(fp,"%s",buffer);
        bzero(buffer,1024);
    }
}

void main(){
    int portno;
    printf("Enter PORT NUMBER: ");
    scnaf("%d",&portno);
    char file[1024];
    bzero(file,1024);
    struct sockaddr_in seraddr;
    int clisoc=socket(AF_INET,SOCK_STREAM,0);
    printf("\n[+] Client socket created..\n");
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    connect(clisoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    printf("\n[+] Client Connected to server\n");
    printf("\nEnter the name of the file: ");
    scanf("%s",file);
    send(clisoc,file,1024,0);
    writeFile(clisoc);
}
