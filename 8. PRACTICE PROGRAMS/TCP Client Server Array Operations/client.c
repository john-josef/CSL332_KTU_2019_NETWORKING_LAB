#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void main(){
    int portno,n;
    printf("\nEnter the PORT NUMBER: ");
    scanf("%d",&portno);
    char buffer[1024],temp[1024];
    bzero(buffer,1024);
    bzero(temp,1024);
    int clisoc=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(portno);
    connect(clisoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in));
    printf("\nEnter the number of terms in the array: ");
    scanf("%d",&n);
    sprintf(buffer,"%d",n);
    send(clisoc,buffer,1024,0);
    bzero(buffer,1024);
    int array[n],arr1[n],arr2[n];
    printf("\nEnter the numbers: ");
    for(int i=0;i<n;i++)
        scanf("%d",&array[i]);
    send(clisoc,array,n*sizeof(int),0);   
    recv(clisoc,temp,1024,0);             
    int inx1=atoi(temp);
    bzero(temp,1024);
    recv(clisoc,temp,1024,0);
    int inx2=atoi(temp);
    bzero(temp,1024);
    recv(clisoc,arr1,n*sizeof(int),0);
    recv(clisoc,arr2,n*sizeof(int),0);
    printf("\nThe array of Perfect squares: ");
    for(int i=0;i<=inx1;i++)
        printf("%d ",arr1[i]);
    printf("\n\nThe array of Cubes of other numbers: ");
    for(int i=0;i<=inx2;i++)
        printf("%d ",arr2[i]);
}
