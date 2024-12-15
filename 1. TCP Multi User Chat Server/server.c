#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void recv_send( int i , fd_set *master , int fdmax , int sersoc ){
    char recvbuf[1024] , sendbuf[1024];
    for( int k=0 ; k<1024 ; k++ ){
        recvbuf[k] = '\0';
        sendbuf[k] = '\0';
    }
    int msglen = recv( i , recvbuf , 1024 , 0 ) ;
    if( msglen <= 0 ){
        close( i ) ;
        FD_CLR( i , master ) ;
        printf( "\nClient %d QUIT...\n" , ( i - 3 ) );
    }
    else{
        char display[] = "(Client  )" ;
        display[8] = (i-3) + '0' ;
        strcat( sendbuf , display ) ;
        strcat( sendbuf , recvbuf ) ;
        for ( int j=0 ; j <= fdmax ; j++ ){
            if( FD_ISSET( j , master ) ){
                if( ( j != i ) && ( j != sersoc ) ){
                    send( j , sendbuf , 1024 , 0 ) ;
                }
            }
        }
    }
}

void connection_accept( int sersoc , struct sockaddr_in *cliaddr , fd_set *master , int *fdmax ){
    socklen_t addrlen = sizeof( struct sockaddr_in ) ;
    int clisoc = accept( sersoc , ( struct sockaddr * ) cliaddr , &addrlen ) ;
    FD_SET( clisoc , master );
    if ( clisoc > *fdmax ){
        *fdmax = clisoc ;
    }
    printf("\nNew connection from %s on PORT %d\n",inet_ntoa(cliaddr->sin_addr),cliaddr->sin_port); //DONT FORGET THE \n OTHERWISE MSG WONT BE SHOWN IN TERMINAL
}

void construct ( int *sersoc , struct sockaddr_in *seraddr ){
    *sersoc = socket( AF_INET , SOCK_STREAM , 0 );
    seraddr -> sin_port = htons( 4950 ) ;
    seraddr -> sin_family = AF_INET ;
    bind( *sersoc , ( struct sockaddr * ) seraddr , sizeof( struct sockaddr_in ) );
    listen( *sersoc , 10 ) ;
    printf( "TCP server waiting for client at port %d\n\n" , ntohs( seraddr->sin_port ) );
}

void main(){
    fd_set master,temp;
    FD_ZERO(&master);
    FD_ZERO(&temp);
    struct sockaddr_in seraddr,cliaddr;
    int sersoc;
    construct(&sersoc,&seraddr);
    FD_SET(sersoc,&master);
    int fdmax=sersoc;
    while(1){
        temp=master;
        select(fdmax+1,&temp,NULL,NULL,NULL);
        for(int i=0;i<=fdmax;i++){
            if(FD_ISSET(i,&temp)){
                if(i==sersoc)
                    connection_accept(sersoc,&seraddr,&master,&fdmax);
                else
                    recv_send(i,&master,fdmax,sersoc);
            }
        }
    }
}
