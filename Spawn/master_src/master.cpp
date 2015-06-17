#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

//mpi
int rank;
int n_children;
MPI_Comm children;

char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void master_work();

/**
* @method main
**/
int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
  rank = MPI::COMM_WORLD.Get_rank();
  MPI_Get_processor_name(processor_name, &name_len);

  MPI_Comm_spawn("slave", argv, 4,
      MPI_INFO_NULL, 0, MPI_COMM_WORLD,
      &children, MPI_ERRCODES_IGNORE);

  master_work();

  sleep(3);

  MPI_Finalize();

  return 0;
}

void master_work()
{
  std::cout << "[" << rank << "]" << "HELLO FROM MASTER @ " << processor_name << endl;

  MPI_Recv(&n_children, 1, MPI_INT, 0, 0, children, MPI_STATUS_IGNORE);

  std::cout << "[" << rank << "]" << " Got " << n_children << " slaves..." << endl;

  std::cout << "[" << rank << "]" << "BYE BYE FROM MASTER" << endl;
}
