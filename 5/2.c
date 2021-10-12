#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv)
{
	int my_rank, nprocs;
	MPI_Request request;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int data = 100;

	if (my_rank!=0){
		
		MPI_Isend(&data, 1, MPI_INT, my_rank-1, 1, MPI_COMM_WORLD,&request);
		printf("Process %d sent data %d to  process %d\n", my_rank,data, my_rank-1);
		MPI_Wait(&request, &status);

	}
	if (my_rank!=nprocs){
		
		MPI_Irecv(&data, 1, MPI_INT, (my_rank+1)%nprocs , 0, MPI_COMM_WORLD, &request);
		printf("Process %d received data %d from process %d\n",my_rank,data,(my_rank+1)%nprocs);
		
	}



		MPI_Finalize();
 }