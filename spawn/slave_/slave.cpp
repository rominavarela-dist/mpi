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

char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void slave_work()
{
  std::cout << "[SLAVE-" << rank << "]" << "Hello @ " << processor_name << endl;

  n_children = MPI::COMM_WORLD.Get_size();

  if (rank == MASTER)
    {MPI_Send(&n_children, 1, MPI_INT, 0, 0, parent);
std::cout << "[SLAVE-" << rank << "]" << "Send OK" << endl;
}

  //std::cout << "[SLAVE-" << rank << "]" << "Bye bye" << endl;
}

/**
* @method main
**/
int main(int argc, char* argv[])
{
  //init
  int MPI_Init_err= MPI_Init(&argc, &argv);
  //std::cout << "SLAVE-" << rank << "] Initialization code: " << MPI_Init_err << endl;
  rank = MPI::COMM_WORLD.Get_rank();
  parent = MPI::COMM_WORLD.Get_parent();
  MPI_Get_processor_name(processor_name, &name_len);

  //work
  slave_work();

  //finialize
  int MPI_Fin_err= MPI_Finalize();
  std::cout << "[SLAVE-"<< rank <<"] Init/Finalization code: " << MPI_Init_err << "/" << MPI_Fin_err << endl;
  return 0;
}
