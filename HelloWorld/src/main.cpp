#include <iostream>
#include <mpi.h>
#define MASTER 0

using namespace std;

//nProcess, thisN, thisName
int world_size,world_rank,name_len;
char processor_name[MPI_MAX_PROCESSOR_NAME];

/**
* @method main
**/
int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Get_processor_name(processor_name, &name_len);

  //init
  MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "[" << world_rank << "]" << "Hello World!" << endl;

  MPI_Finalize();
  return 0;
}
