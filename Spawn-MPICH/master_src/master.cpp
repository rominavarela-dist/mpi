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
  MPI::Init(argc,argv);
  rank = MPI::COMM_WORLD.Get_rank();
  MPI_Get_processor_name(processor_name, &name_len);

  //add hosts and spawn
  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Info_set(info,"hostfile","./host_file");
  int spawn_callback = MPI_Comm_spawn(
	"./slave"/*name of program to be spawned*/,
	MPI_ARGV_NULL/*arguments to command*/,
	2/*max number of processes to start*/,
	info/*MPI_Info obj*/,
	0/*rank of process in which arguments are examined*/,
	MPI_COMM_WORLD/*MPI_Comm intracommunicator w/group of spawning proc*/,
	&children/*MPI_Comm intercommunicator between original group and new*/,
	MPI_ERRCODES_IGNORE/*array of err_codes*/);

  switch(spawn_callback)
  {
	case MPI_SUCCESS:
		std::cout << "spawn callback: MPI_SUCCESS" << endl;
		break;
	case MPI_ERR_COMM:
		std::cout << "spawn callback: MPI_ERR_COMM" << endl;
		break;
	case MPI_ERR_ARG:
		std::cout << "spawn callback: MPI_ERR_ARG" << endl;
		break;
	case MPI_ERR_INFO:
		std::cout << "spawn callback: MPI_ERR_INFO" << endl;
		break;
	case MPI_ERR_SPAWN:
		std::cout << "spawn callback: MPI_ERR_SPAWN" << endl;
		break;
  }

  //work
  master_work();
  sleep(3);

  //finialize
  MPI_Finalize();
  return 0;
}
