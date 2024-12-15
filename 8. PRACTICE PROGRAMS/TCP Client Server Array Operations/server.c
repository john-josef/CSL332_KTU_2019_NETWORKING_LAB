

//   For compiling use the command      gcc server.c -lm 

/*   QUESTION

Create a TCP connection. Send an array of integers to server from client. 
In server side enter the perfect square numbers into one 
array and the cubes of the rest numbers into another array. 
Then send both the arrays back to client side and display these arrays.

*/   

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <math.h>


void main(){
    int portno,element;
    printf("\nEnter the PORT NUMBER: ");
    scanf("%d",&portno);
    char buffer[1024],temp[1024];
    bzero(temp,1024);
    bzero(buffer,1024);
    struct sockaddr_in seraddr,cliaddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port=htons(portno);
    int sersoc=socket(AF_INET,SOCK_STREAM,0);
    if(bind(sersoc,(struct sockaddr *)&seraddr,sizeof(struct sockaddr_in))!=0){
        printf("BINDING COULDNT BE DONE !!.. Please try another port number..\n");
        exit(0);
    }
    listen(sersoc,10);
    socklen_t addrlen=sizeof(struct sockaddr_in);
    printf("\nServer waiting for connections on port %d\n",ntohs(seraddr.sin_port));
    int clisoc=accept(sersoc,(struct sockaddr *)&cliaddr,&addrlen);
    printf("\nConnection established from Client %s on port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    recv(clisoc,buffer,1024,0);
    int n=atoi(buffer);
    printf("\nNumber %d received\n",n);
    bzero(buffer,1024);
    int array[n],arr1[n],arr2[n];
    int inx1=-1,inx2=-1;
    recv(clisoc,array,n*sizeof(int),0); 
    for(int i=0;i<n;i++){
        element=array[i];
        int temporary=(int)sqrt(element);   
        if(temporary*temporary==element) //CONDITION FOR PERFECT SQUARE
            arr1[++inx1]=element;
        else 
            arr2[++inx2]=element*element*element;
    }
    sprintf(temp,"%d",inx1);
    send(clisoc,temp,1024,0);
    bzero(temp,1024);
    sprintf(temp,"%d",inx2);
    send(clisoc,temp,1024,0);
    bzero(temp,1024);
    send(clisoc,arr1,n*sizeof(int),0);
    send(clisoc,arr2,n*sizeof(int),0);
}
