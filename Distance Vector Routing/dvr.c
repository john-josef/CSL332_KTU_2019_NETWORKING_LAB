//INPUTS are provided as comments below the program
#include <stdio.h>
#include <stdlib.h>

void printing(int i,int j,int n,int nexthop[n][n]){
    if(i!=j){
        printf("%c-",i+65);
        printing(nexthop[i][j],j,n,nexthop);
    }
    else
        printf("%c",i+65);
}

void main(){
    int n,change;
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    int dmat[n][n];
    int distance[n][n];
    int nexthop[n][n];
    printf("\nEnter the cost matrix.. enter -1 if there is no path between two given vertices...\n");
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d",&dmat[i][j]);
            if(dmat[i][j]==-1)
                dmat[i][j]=1000;
            dmat[i][i]=0;
            distance[i][j]=dmat[i][j];
            nexthop[i][j]=j;
        }
    }
    do{
        change=0;
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                for (int k=0;k<n;k++){
                    if (distance[i][j]>dmat[i][k]+distance[k][j]){
                        distance[i][j]=dmat[i][k]+distance[k][j];
                        nexthop[i][j]=k;
                        change=1;
                    }
                }
            }
        }
    }while(change==1);
    printf("------------------------------------------------------\n");
    for (int i=0;i<n;i++){
        printf("For router %c\t\n",i+65);
        printf("\t\nDest  Nexthop  Distance          Path\n\n");
        for (int j=0;j<n;j++){
            if(distance[i][j]!=1000)
                printf("%c\t%c\t%d",j+65,nexthop[i][j]+65,distance[i][j]);
            else
                printf("%c\t%c\tNO PATH",j+65,nexthop[i][j]+65);
            printf("\t\t");
            printing(i,j,n,nexthop);
            printf("\n");
        }
        printf("------------------------------------------------------\n");
    }
}

//   INPUT-OUTPUT 1
// Enter the number of nodes: 7

// Enter the cost matrix.. enter -1 if there is no path between two given vertices...
// 0 3 2 -1 -1 -1 -1
// 3 0 2 1 4 -1 -1
// 2 2 0 3 -1 6 5
// -1 1 3 0 -1 2 -1
// -1 4 -1 -1 0 1 -1
// -1 -1 6 2 1 0 2
// -1 -1 5 -1 -1 2 0
// ------------------------------------------------------
// For router A

// Dest  Nexthop  Distance          Path

// A       A       0               A
// B       B       3               A-B
// C       C       2               A-C
// D       B       4               A-B-D
// E       B       7               A-B-E
// F       B       6               A-B-D-F
// G       C       7               A-C-G
// ------------------------------------------------------
// For router B

// Dest  Nexthop  Distance          Path

// A       A       3               B-A
// B       B       0               B
// C       C       2               B-C
// D       D       1               B-D
// E       E       4               B-E
// F       D       3               B-D-F
// G       D       5               B-D-F-G
// ------------------------------------------------------
// For router C

// Dest  Nexthop  Distance          Path

// A       A       2               C-A
// B       B       2               C-B
// C       C       0               C
// D       D       3               C-D
// E       B       6               C-B-E
// F       B       5               C-B-D-F
// G       G       5               C-G
// ------------------------------------------------------
// For router D

// Dest  Nexthop  Distance          Path

// A       B       4               D-B-A
// B       B       1               D-B
// C       C       3               D-C
// D       D       0               D
// E       F       3               D-F-E
// F       F       2               D-F
// G       F       4               D-F-G
// ------------------------------------------------------
// For router E

// Dest  Nexthop  Distance          Path

// A       B       7               E-B-A
// B       B       4               E-B
// C       B       6               E-B-C
// D       F       3               E-F-D
// E       E       0               E
// F       F       1               E-F
// G       F       3               E-F-G
// ------------------------------------------------------
// For router F

// Dest  Nexthop  Distance          Path

// A       D       6               F-D-B-A
// B       D       3               F-D-B
// C       D       5               F-D-C
// D       D       2               F-D
// E       E       1               F-E
// F       F       0               F
// G       G       2               F-G
// ------------------------------------------------------
// For router G

// Dest  Nexthop  Distance          Path

// A       C       7               G-C-A
// B       F       5               G-F-D-B
// C       C       5               G-C
// D       F       4               G-F-D
// E       F       3               G-F-E
// F       F       2               G-F
// G       G       0               G
// ------------------------------------------------------











// INPUT-OUTPUT 2
// Enter the number of nodes: 6

// Enter the cost matrix.. enter -1 if there is no path between two given vertices...
// 0 2 4 -1 -1 -1
// -1 0 1 7 -1 -1
// -1 -1 0 -1 3 -1
// -1 -1 -1 0 -1 1
// -1 -1 -1 2 0 5
// -1 -1 -1 -1 -1 0
// ------------------------------------------------------
// For router A

// Dest  Nexthop  Distance          Path

// A       A       0               A
// B       B       2               A-B
// C       B       3               A-B-C
// D       B       8               A-B-C-E-D
// E       B       6               A-B-C-E
// F       B       9               A-B-C-E-D-F
// ------------------------------------------------------
// For router B

// Dest  Nexthop  Distance          Path

// A       A       NO PATH         B-A
// B       B       0               B
// C       C       1               B-C
// D       C       6               B-C-E-D
// E       C       4               B-C-E
// F       C       7               B-C-E-D-F
// ------------------------------------------------------
// For router C

// Dest  Nexthop  Distance          Path

// A       A       NO PATH         C-A
// B       B       NO PATH         C-B
// C       C       0               C
// D       E       5               C-E-D
// E       E       3               C-E
// F       E       6               C-E-D-F
// ------------------------------------------------------
// For router D

// Dest  Nexthop  Distance          Path

// A       A       NO PATH         D-A
// B       B       NO PATH         D-B
// C       C       NO PATH         D-C
// D       D       0               D
// E       E       NO PATH         D-E
// F       F       1               D-F
// ------------------------------------------------------
// For router E

// Dest  Nexthop  Distance          Path

// A       A       NO PATH         E-A
// B       B       NO PATH         E-B
// C       C       NO PATH         E-C
// D       D       2               E-D
// E       E       0               E
// F       D       3               E-D-F
// ------------------------------------------------------
// For router F

// Dest  Nexthop  Distance          Path

// A       A       NO PATH         F-A
// B       B       NO PATH         F-B
// C       C       NO PATH         F-C
// D       D       NO PATH         F-D
// E       E       NO PATH         F-E
// F       F       0               F
// ------------------------------------------------------













//INPUT-OUTPUT 3
// Enter the number of nodes: 5

// Enter the cost matrix.. enter -1 if there is no path between two given vertices...
// 0 5 2 3 -1
// 5 0 4 -1 3
// 2 4 0 -1 4
// 3 -1 -1 0 -1
// -1 3 4 -1 0
// ------------------------------------------------------
// For router A

// Dest  Nexthop  Distance          Path

// A       A       0               A
// B       B       5               A-B
// C       C       2               A-C
// D       D       3               A-D
// E       C       6               A-C-E
// ------------------------------------------------------
// For router B

// Dest  Nexthop  Distance          Path

// A       A       5               B-A
// B       B       0               B
// C       C       4               B-C
// D       A       8               B-A-D
// E       E       3               B-E
// ------------------------------------------------------
// For router C

// Dest  Nexthop  Distance          Path

// A       A       2               C-A
// B       B       4               C-B
// C       C       0               C
// D       A       5               C-A-D
// E       E       4               C-E
// ------------------------------------------------------
// For router D

// Dest  Nexthop  Distance          Path

// A       A       3               D-A
// B       A       8               D-A-B
// C       A       5               D-A-C
// D       D       0               D
// E       A       9               D-A-C-E
// ------------------------------------------------------
// For router E

// Dest  Nexthop  Distance          Path

// A       C       6               E-C-A
// B       B       3               E-B
// C       C       4               E-C
// D       C       9               E-C-A-D
// E       E       0               E
// ------------------------------------------------------
