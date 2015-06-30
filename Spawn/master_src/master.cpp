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

void master_work()
{
  std::cout << "[" << rank << "]" << "HELLO FROM MASTER @ " << processor_name << endl;
  MPI_Recv(&n_children, 1, MPI_INT, 0, 0, children, MPI_STATUS_IGNORE);
  std::cout << "[" << rank << "]" << " Got " << n_children << " slaves..." << endl;
  std::cout << "[" << rank << "]" << "BYE BYE FROM MASTER" << endl;
}

/**
* @method main
**/
int main(int argc, char* argv[])
{
  //init
  MPI_Init(&argc, &argv);
  rank = MPI::COMM_WORLD.Get_rank();
  MPI_Get_processor_name(processor_name, &name_len);

  //add hosts and spawn
  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Info_set(info,"add-hostfile","host_file");
  MPI_Comm_spawn("./slave", MPI_ARGV_NULL, 4,
      info, 0, MPI_COMM_WORLD,
      &children, MPI_ERRCODES_IGNORE);

  //work
  master_work();
  sleep(3);

  //finialize
  MPI_Finalize();
  return 0;
}
