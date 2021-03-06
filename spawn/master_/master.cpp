#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

//mpi
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

int spawn()
{
  int n_children;
  MPI_Comm children;
  int n_procs = 1;
  MPI_Status spawn_errs[n_procs];

  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Info_set(info,"hostfile","host_file");
  //MPI_Info_set(info,"wdir","/mirror/romina/workspace/demo/mpi/spawn");
  MPI_Comm_spawn("./slave", MPI_ARGV_NULL, n_procs,
      info, 0, MPI_COMM_WORLD,
      &children, MPI_ERRCODES_IGNORE);
  MPI_Recv(&n_children, 1, MPI_INT, 0, 0, children, spawn_errs);
  MPI_Comm_free(&children);

  for(int i=0; i<n_children; i++)
	std::cout << "[MASTER] Spawn#" << i << " Status:" << spawn_errs[i].MPI_ERROR << endl;
  return n_children;
}

/**
* @method main
**/
int main(int argc, char* argv[])
{
  //init
  int MPI_Init_err= MPI_Init(&argc, &argv);
  MPI_Get_processor_name(processor_name, &name_len);  

  //work
  std::cout << "[MASTER] Hello @ " << processor_name << endl;
  for(int i=0; i<10; i++)
	std::cout << "[MASTER] Spawn#" << i << " Got " << spawn() << " slaves..." << endl;

  //finalize
  sleep(3);
  int MPI_Fin_err= MPI_Finalize();
  std::cout << "[MASTER] Init/Finalization code: " << MPI_Init_err << "/" << MPI_Fin_err << endl;
  return 0;
}
