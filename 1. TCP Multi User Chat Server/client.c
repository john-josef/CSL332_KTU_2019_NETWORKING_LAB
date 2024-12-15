#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void recv_send( int fd , int clisoc ){
    char recvbuf[1024],sendbuf[1024];
    for(int i = 0 ; i < 1024 ; i++ ){
        recvbuf[i] = '\0';
        sendbuf[i] = '\0';
    }
    if ( fd == 0 ){
        fgets( sendbuf , 1024 , stdin );
        if( strcmp( sendbuf , "quit\n" ) == 0 )
            exit(0);
        else{
            printf("\n");
            send( clisoc , sendbuf , 1024 , 0 );
        }
    }
    else{
        int msglen = recv( clisoc , recvbuf , 1024 , 0 ) ;
        printf("%s\n",recvbuf);
    }

}

void construct( int *clisoc , struct sockaddr_in *seraddr ){
    *clisoc = socket( AF_INET , SOCK_STREAM , 0 ) ;
    seraddr -> sin_port = htons(4950) ;
    seraddr -> sin_family = AF_INET ;
    connect( *clisoc , (struct sockaddr *) seraddr , sizeof( struct sockaddr_in ) ) ;
}

void main(){
    fd_set master,temp;
    FD_ZERO(&master);
    FD_ZERO(&temp);
    struct sockaddr_in seraddr;
    int clisoc;
    construct(&clisoc,&seraddr);
    FD_SET(clisoc,&master);
    FD_SET(0,&master);
    while(1){
        temp=master;
        select(clisoc+1,&temp,NULL,NULL,NULL);
        if(FD_ISSET(0,&temp))
            recv_send(0,clisoc);
        else if(FD_ISSET(clisoc,&temp))
            recv_send(clisoc,clisoc);
    }
}
