/*
* Author: Abdulrahman Abdulmoneim
* ID: 20110220
* Group: DS_CS_1
* Assignment-3 by send and recieve
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
	
	MPI_Status status;

	MPI_Init( &argc , &argv );

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	time_t start = time(NULL);
	
	if( my_rank != 0)
	{
	    
		int sz;
        int lb=0;
        int sum=0;
        	
		MPI_Recv(&sz, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		
		MPI_Recv(&lb, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		
		printf("process : %d\n",my_rank);
		//printf(" values of lb: %d and for sz  : %d\n",lb, sz+lb);
			
		for( i = lb; i < sz+lb ; i++)
		{
 	            if(isPrime(i))
 	                          sum++;
		}
		
		
		MPI_Send(&sum, 1, MPI_INT, source, tag, MPI_COMM_WORLD);	
			
	}else
	{
			
		int lb, ub;
		printf("Please enter lower bound and upper bound: ");
		scanf("%d%d",&lb,&ub);
		
		int sz = 10;
		int block_sz = (ub-lb) / (p - 1);
	    int it = lb;
	    int recv=0,total=0;
		
		for( des = 1; des < p ; des++)
		{   
		    if(des == p - 1)
			   //block_sz = block_sz + (sz % (p - 1));				
			
			printf("block size: %d", block_sz);
			MPI_Send(&block_sz, 1, MPI_INT, des, tag, MPI_COMM_WORLD);		
			MPI_Send(&it, 1, MPI_INT, des, tag, MPI_COMM_WORLD);
			
			it += block_sz;
		}
		
		for( des = 1; des < p ; des++)
		{
			MPI_Recv(&recv, 1, MPI_INT, des, tag, MPI_COMM_WORLD, &status );
		    
            total += recv;
		}
		
		printf("the total of primes in range is: %d\n",total);
		
		time_t end = time(NULL);
		printf("time elapsed: %.f seconds\n",difftime(end, start));
	}

	/* shutdown MPI */
	MPI_Finalize();
	
}
