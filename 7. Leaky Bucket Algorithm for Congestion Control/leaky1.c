//LEAKY BUCKET ALGORITHM where if a packet is to be dropped, the packet can be split and accomodated in the bucket and the rest of the packet is dropped..

#include <stdio.h>
#include <string.h>

void main(){
    char buffer[1024],result[1024];
    bzero(buffer,1024);
    bzero(result,1024);
    int bucketsize,outrate,time=0,packetsize,bucket=0,sent,dropped,flag;
    printf("Enter the bucket size: ");
    scanf("%d",&bucketsize);
    printf("\nEnter the output rate: ");
    scanf("%d",&outrate);
    sprintf(buffer,"Time\tReceived\tSent\tDropped\tRemaining\n");
    strcpy(result,buffer);
    bzero(buffer,1024);
    do{
        printf("\nEnter the size of packet coming at sec %d: ",++time);
        scanf("%d",&packetsize);
        if(bucket+packetsize>bucketsize){
            dropped=bucket+packetsize-bucketsize;
            bucket=bucketsize;
        }
        else{
            dropped=0;
            bucket=bucket+packetsize;
        }
        if(bucket<=outrate)
            sent=bucket;
        else
            sent=outrate;
        bucket-=sent;
        sprintf(buffer,"\n%d\t\t%d\t\t%d\t\t%d\t\t%d",time,packetsize,sent,dropped,bucket);
        strcat(result,buffer);
        bzero(buffer,1024);
        printf("\nContinue(1)...Quit(0)  :  ");
        scanf("%d",&flag);
    }while(flag);
    printf("\n\n%s",result);
}

//INPUT-OUTPUT FORMAT

// Enter the bucket size: 100

// Enter the output rate: 30

// Enter the size of packet coming at sec 1: 30

// Continue(1)...Quit(0)  :  1

// Enter the size of packet coming at sec 2: 20

// Continue(1)...Quit(0)  :  1

// Enter the size of packet coming at sec 3: 100

// Continue(1)...Quit(0)  :  1

// Enter the size of packet coming at sec 4: 40

// Continue(1)...Quit(0)  :  1

// Enter the size of packet coming at sec 5: 110

// Continue(1)...Quit(0)  :  1

// Enter the size of packet coming at sec 6: 30

// Continue(1)...Quit(0)  :  1

// Enter the size of packet coming at sec 7: 20

// Continue(1)...Quit(0)  :  0


// Time    Received        Sent    Dropped Remaining

// 1               30              30              0               0
// 2               20              20              0               0
// 3               100             30              0               70
// 4               40              30              10              70
// 5               110             30              80              70
// 6               30              30              0               70
// 7               20              30              0               60
