#include <iostream>
#include <mpi.h>
#define MASTER 0

using namespace std;

//nProcess, thisN, thisName
int world_size,world_rank,name_len;
char processor_name[MPI_MAX_PROCESSOR_NAME];
int N, M;

void init();
void run();

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
  if (world_rank == MASTER)
    std::cout << "[" << world_rank << "]" << "HELLO FROM MASTER" << endl;
  MPI_Barrier(MPI_COMM_WORLD);
    init();

  //run
  MPI_Barrier(MPI_COMM_WORLD);
    run();


  //finalize
  if (world_rank == MASTER)
    std::cout << "[" << world_rank << "]" << "GOODBYE FROM MASTER" << endl;

	MPI_Finalize();
  return 0;
}

/**
* @method init
**/
void init()
{
  int buf[2];

  if (world_rank == MASTER)
  {
    std::cout << "[" << world_rank << "]" << "Let's say you have N-M tasks to do" << endl;
    std::cout << "[" << world_rank << "]" << "Give #N:" << endl;
		scanf("%d",&N);
    std::cout << "[" << world_rank << "]" << "Give #M:" << endl;
		scanf("%d",&M);

		buf[0]= N;
		buf[1]= M;

    std::cout << "[" << world_rank << "]" << "Let's distribute N-M tasks to slaves..." << endl;
    int i;
    for (i = 0; i < world_size; i++)
      if (i != world_rank)
        MPI_Send(&buf, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
  }
  else
  {
    MPI_Recv(&buf, 2, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    N = buf[0];
    M = buf[1];
  }
}

/**
* @method run
**/
void run()
{
  int taskSize = (M/world_size);
  int initIndex= taskSize * world_rank;
  int endIndex= initIndex + taskSize;

  std::cout << "[" << world_rank << "]" << "Slave runs from index " << initIndex << " to " << endIndex << endl;
}
