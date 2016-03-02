#include <stdio.h>
//===================================================//
/* Assignment-1 (operations on matrices)
 * Author: Abdulrahman Abdulmoneim
 * ID: 20110220
 * Group: DS_CS
 */
//===================================================//
void fill(int **m, int r, int c){
     int i=0,j=0;
     for(i=0; i<r; i++)
              for(j=0; j<c; j++)
                       scanf("%d",&m[i][j]);
     
     return ;
     }
//===================================================//
void print(int **m, int r, int c){
     int i=0,j=0;
     for(i=0; i<r; i++){
              for(j=0; j<c; j++)
                       printf("%d \t",m[i][j]);
              
              printf("\n");
              }
              
     printf("\n");
     return ;
     }
//===================================================//
int ** multiply(int **m1, int **m2, int r1, int c1, int r2, int c2){
    
    int **m3 = (int **) malloc(sizeof(int *)*r1);
    int i=0,j=0,k=0,s=0;
    for(i=0; i<r1; i++)
             m3[i] = (int *) malloc(sizeof(int)*c2);
             
    i=0,j=0,k=0;
   
    for(i=0;i<r1;i++)
      for(j=0;j<c2;j++){
        for(k=0;k<r2;k++)
                         s += m1[i][k]*m2[k][j];
        
        m3[i][j] = s;
        s=0;
        }
    
    return m3;
    }
//===================================================//
int ** add(int **m1, int **m2, int r1, int c1, int r2, int c2){
   int **m3 = (int **) malloc(sizeof(int *)*r1);
   int i=0,j=0;
   for(i=0; i<r1; i++)
            m3[i] = (int *) malloc(sizeof(int)*c1);
    
   i=0,j=0;
   for(i=0; i<r1; i++)
      for(j=0; j<c1; j++)
               m3[i][j] = m1[i][j]+m2[i][j];
   
   return m3;
    }
//===================================================//
int ** subtract(int **m1, int **m2, int r1, int c1, int r2, int c2){
   int **m3 = (int **) malloc(sizeof(int *)*r1);
   int i=0,j=0;
   for(i=0; i<r1; i++)
            m3[i] = (int *) malloc(sizeof(int)*c1);
    
   i=0,j=0;
   for(i=0; i<r1; i++)
      for(j=0; j<c1; j++)
               m3[i][j] = m1[i][j]-m2[i][j];
   
   return m3;
    }
//===================================================//
//===================================================//
int main(){
    int row1, col1, row2, col2;
    printf("Please enter dim of the first matrix\n");
    scanf("%d%d",&row1,&col1);
    
    printf("Please enter dim of the second matrix\n");
    scanf("%d%d",&row2,&col2);
    
    int **m1 = (int **) malloc(sizeof(int *)*row1);
    int i=0;
    for(i=0; i<row1; i++)
            m1[i] = (int *) malloc(sizeof(int)*col1);
            
    int **m2 = (int **) malloc(sizeof(int *)*row2);
    i=0;
    for(i=0; i<row2; i++)
            m2[i] = (int *) malloc(sizeof(int)*col2);
            
    printf("Please enter the first matrix\n");
    fill(m1,row1,col1);
    
    printf("Please enter the second matrix\n");
    fill(m2,row2,col2);
    
    //==================================//
    //==================================//
    printf("\nFirst matrix is:\n***********************************\n");
    print(m1,row1,col1);
    printf("Second matrix is:\n***********************************\n");
    print(m2,row2,col2);
    
    printf("\n\n");
    //==================================//
    //==================================//
    int ** m3;
    
    if(col1 == row2){
            printf("the result of multiplication is:\n***********************************\n");
            m3 = multiply(m1,m2,row1,col1,row2,col2);
            print(m3,row1,col2);
         }
    else{
        printf("These matrices can't be multiplied\n\n");
        }
    //==================================//
    if(row1 == row2 && col1 == col2){
            printf("the result of addition is:\n***********************************\n");
            m3 = add(m1,m2,row1,col1,row2,col2);
            print(m3,row1,col1);
            
            printf("the result of subtraction is:\n***********************************\n");
            m3 = subtract(m1,m2,row1,col1,row2,col2);
            print(m3,row1,col1);
    }
    else{
         printf("These matrices can't be added\n\n");
         printf("These matrices can't be subtracted\n\n");
         }
               
    getch();
    return 0;
    }
