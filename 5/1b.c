#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])  
{
      int numtasks, rank, next, prev, buf[0] ,tag1=1, tag2=2;

      MPI_Request reqs[4];
      MPI_Status stats[4];

      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      prev = rank-1;
      next = rank+1;
      if (rank == 0)  
            prev = numtasks - 1;
      if (rank == (numtasks - 1))  
            next = 0;

      MPI_Send(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD);
      MPI_Send(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD );
      
      MPI_Recv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("Process %d received %d with tag %d from process %d\n", prev,buf[0],tag1,rank);
      MPI_Recv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("Process %d received %d with tag %d from process %d\n", next,buf[1], tag2,rank);


        
   

      MPI_Finalize();
}