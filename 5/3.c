#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
    int prod_arr[6] = {1,2,4,5,6,7};
    MPI_Init(NULL, NULL);
    int size_world, my_rank;
    size_t n = sizeof(prod_arr)/sizeof(prod_arr[0]);

    //initilaizing product
    int product = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size_world);

   
int partial_prod = 1;
    if (my_rank==0){
       
        for (int i = 0;i<(my_rank+(n/size_world));i++){
            partial_prod *=prod_arr[i];
        }
    }
    else{
       
        for (int i = 3 ;i<n;i++){
            partial_prod *=prod_arr[i];
        }
    }

    
    MPI_Reduce(&partial_prod, &product, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

     if (my_rank == 0)
 {
 	printf("Product  of array is : %d\n", product); 
 } 

    MPI_Finalize();

    return 0;
}