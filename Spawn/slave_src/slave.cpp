#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

//mpi
int rank;
int n_children;
MPI_Comm parent;
MPI_Comm children;

void slave_work();

/**
* @method main
**/
int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
  rank = MPI::COMM_WORLD.Get_rank();
  parent = MPI::COMM_WORLD.Get_parent();

  slave_work();

  MPI_Finalize();

  return 0;
}

void slave_work()
{
  std::cout << "[" << rank << "]" << "HELLO FROM SLAVE" << endl;

  n_children = MPI::COMM_WORLD.Get_size();

  if (rank == MASTER)
    MPI_Send(&n_children, 1, MPI_INT, 0, 0, parent);

  std::cout << "[" << rank << "]" << "BYE BYE FROM SLAVE" << endl;
}
