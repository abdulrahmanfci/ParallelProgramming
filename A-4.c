/*
* Author: Abdulrahman Abdulmoneim
* ID: 20110220
* Group: DS_CS_1
* Assignment-4
*
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

int convertInt(char* str){
    int result=0;
    while ((*str >= '0') && (*str <= '9'))
    {
      result = (result * 10) + ((*str) - '0');
      str++;
    }
    
    return result;
    }
     
main(int argc, char* argv[]){
         int p;
         int my_rank;
         int n;
         int range;
         int source=0;
         int mainSum=0;
         int sum=0;
         int i,j;
         int* a;
         int* b;
         int tag=0;
         int start, end;
         
         double avg=0.0;
         double total=0.0;
         
         int array_size=1000;
         int arr[array_size];
         
         FILE *f;
         char* name = "/shared/num.txt";
        
         int c;
         size_t sz=0;
         char buffer[512];
         
         MPI_Status status;
         
         MPI_Init(&argc, &argv);
         MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
         MPI_Comm_size(MPI_COMM_WORLD, &p);
         
         if(my_rank == 0){
                    f = fopen(name,"w+");
       
                    if(f == NULL){
                        printf("Error!\n");
                        exit(1);
                        }
                   
                    int i;     
                    for(i=1;i<=array_size;i++)
                                   fprintf(f, "%d\n",i);
                    fclose(f);
                    
                    f = fopen(name, "r");
                    
                    if(f == NULL){
                         printf("Error!!\n");
                         perror("fopen");
                         exit(1);
                         }
                    
                    
                    i=0;
                    while ((c = getc(f)) != EOF){
                          if((char)c != '\n'){
                                           buffer[sz] = (char)c;
                                           sz++;
                                           }
                          else{
                               buffer[sz]='\0';
                               //printf("%d\n",convertInt(buffer));
                               arr[i] = convertInt(buffer);
                               mainSum += arr[i];
                               //printf("%d\n",arr[i]);
                               i++;
                               memset(buffer, 0, sizeof(buffer));
                               sz=0;
                               }       
                    }
                    fclose(f);
                    
                    if(array_size%p != 0){
                        int remain = array_size%p;
                        int size = (array_size/p)*p;
                        
                        MPI_Send(&remain, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
                        MPI_Send(&arr[size], remain, MPI_INT, p-1, tag, MPI_COMM_WORLD);
                        }
         }
         int part = array_size/p;
         b = malloc(part*sizeof(int));
         MPI_Scatter(arr, part, MPI_INT, b, part, MPI_INT, 0, MPI_COMM_WORLD);
                    
         
         printf("hello rank: %d, ",my_rank);
         int size;
         int* rem;
         
         if(my_rank == p-1 && array_size%p != 0 ){
                    
                    MPI_Recv(&size, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
                    rem = malloc(size*sizeof(int));
                    MPI_Recv(rem, size, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
                    
                    printf(" ");
                    for(i=0;i<size;i++){
                        //printf("%d ",rem[i]); 
                        sum += rem[i];
                        }
                    }
                               
         part = array_size/p;
         for(i=0;i<part;i++){
                         //printf("%d ",b[i]);
                         sum += b[i];
                         }
         /*                
         if(my_rank == p-1)
                    part += array_size%p;
         */
         
         avg = (double)sum/part; 
         printf("sum here is: %d || & avg: %.3f",sum,avg);
         printf("\n");
         
         MPI_Reduce(&avg, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            
         if(my_rank == 0){
                    total = (double)total/(p+(array_size%p?1:0 ));
                    printf("total of averages is: %.3f \n",total); 
                    printf("and main average is: %.3f \n",(double)mainSum/array_size);
                    }
         
         MPI_Bcast(&total, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
         
         printf("hello rank: %d, ",my_rank);
         part = array_size/p;
         if(my_rank == p-1 && array_size%p != 0){
                    if(array_size%p != 0){
                       for(i=0;i<size;i++){
                                           rem[i] = rem[i] - total;
                                           //printf("%d  hhh ",rem[i]);
                                           }
                        
                        MPI_Send(&size, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                        MPI_Send(rem, size, MPI_INT, 0, tag, MPI_COMM_WORLD);
                        }
                    }
         
         for(i=0;i<part;i++){
                         b[i] = b[i] - total;     
                         //printf("%d ",b[i]);
                         }  
                         
         printf("\n");
         
         part = array_size/p;
         MPI_Gather(b, part, MPI_INT, arr, part, MPI_INT, 0, MPI_COMM_WORLD);
         
         if(my_rank == 0){
                    //printf("Here %d\n",arr[3]);
                    
                    if(array_size%p != 0){
                        MPI_Recv(&size, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD, &status );
                        rem = malloc(size*sizeof(int));
                        MPI_Recv(rem, size, MPI_INT, p-1, tag, MPI_COMM_WORLD, &status );
                        
                    
                        for(i=array_size-size,j=0;i<array_size,j<size;i++,j++){
                                                             //printf("arr[i]: %d",arr[i]);                
                                                             arr[i] = rem[j];
                                                             }
                    }
                    
                   name = "/shared/num2.txt";
                   
                   f = fopen(name,"w+");
                   
                   if(f == NULL){
                        printf("Error!\n");
                        exit(1);
                        }
                       
                   for(i=0;i<array_size;i++)
                                   fprintf(f, "%d \n",arr[i]);
                   fclose(f);
                   
                    } 
         
                 
         MPI_Finalize();
         //getchar();
         }
