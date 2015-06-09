#include <mpi.h>
#define MASTER 0

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
    printf("\n[%d] HELLO FROM MASTER.\nThis is a barrier where we will distribut our arguments...", world_rank);
  MPI_Barrier(MPI_COMM_WORLD);
    init();

  //run
  MPI_Barrier(MPI_COMM_WORLD);
    run();


  //finalize
  if (world_rank == MASTER)
      printf("\n[%d] GOODBYE FROM MASTER.\nAt this points everybody must have finished to work.", world_rank);

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
    printf("\n[%d] Simulate you have N-M tasks to do", world_rank);
    printf("\n[%d] Give a #N to master:", world_rank);
		scanf("%d",&N);
    printf("\n[%d] Give a #M to master:", world_rank);
		scanf("%d",&M);

		buf[0]= N;
		buf[1]= M;

    printf("\n[%d] Let's distribute N-M tasks to slaves...", world_rank);
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
  int initIndex= N + world_rank;
  int endIndex= initIndex + (M/world_size);
  printf("\n[%d] Slave runs from index %d to %d", world_rank,initIndex,endIndex);
}
