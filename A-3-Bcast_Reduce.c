/*
* Author: Abdulrahman Abdulmoneim
* ID: 20110220
* Group: DS_CS_1
* Assignment-3 by Bcast and Reduce
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mpi.h"

int isPrime(int n){
     int i;
     for (i=2; (i*i) <= n; i++) {
        if ((n % i) == 0) return 0;
        }
    return 1;
     }

main(int argc , char * argv[])
{
	int my_rank;
	int p;
	int source = 0;
	int des;
	int tag = 0;
	int i;
	int lb;
    int ub;
	int range;
	int mod;
	int sum;
	int total;
	
	MPI_Status status;

	MPI_Init( &argc , &argv );

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	time_t start = time(NULL);
	if( my_rank == 0)
	{
	    
		printf("Please enter lower bound and upper bound: ");
		scanf("%d%d",&lb,&ub);
		
		range = (ub-lb) / (p - 1);
		mod = (ub-lb) % (p - 1);
		
	}
	
	MPI_Bcast(&lb, 1, MPI_INT, tag, MPI_COMM_WORLD);
    MPI_Bcast(&range, 1, MPI_INT, tag, MPI_COMM_WORLD);
    MPI_Bcast(&mod, 1, MPI_INT, tag, MPI_COMM_WORLD);
    
	if( my_rank != 0)
	{
	    
		int sz;
        sum=0;
       	
       	int start, end;
       	
       	start = ((my_rank-1)*range)+1;
        end = my_rank*range;
        
        if(my_rank == p-1){
                   //printf("here : %d %d %d\n",my_rank, p-1, mod);
                   end += mod;
                   }
        
		printf("process : %d\n",my_rank);
		//printf("lb is: %d, and range is: %d \n",lb, range);
		printf("start is: %d, and end is: %d \n",start, end);
		
		for( i = start; i <= end ; i++)
		{
 	            if(isPrime(i))
 	                          sum++;
		}
		
	}
    
    MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM, tag, MPI_COMM_WORLD);
    
    if(my_rank == 0){
         time_t end = time(NULL);
         printf("the summation of primes in range is: %d\n",total);
         printf("time elapsed: %.f seconds\n",difftime(end, start));
         }
	/* shutdown MPI */
	MPI_Finalize();
	
}
