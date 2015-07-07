#include <iostream>
#include <mpi.h>
#include <unistd.h>
#define MASTER 0

using namespace std;

//nProcess, thisN, thisName
int world_size,world_rank,name_len;
char processor_name[MPI_MAX_PROCESSOR_NAME];
//server data
MPI_Comm client;
char port_name[MPI_MAX_PORT_NAME];

void run()
{
  sleep(3);
}

/**
* @method main
**/
int main(int argc, char* argv[])
{
  //init mpi
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Get_processor_name(processor_name, &name_len);
	std::cout << "rank:" << world_rank << " , host: " << processor_name << " > Hello World!" << endl;

  //init server
  MPI_Open_port(MPI_INFO_NULL, port_name);
  std::cout << "Server up. Port name: (" << port_name << ")" << endl;
  MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF,&client);
  std::cout << "Client connection acepted" << endl;

  //run
  run();

  //finalize
  MPI_Comm_disconnect(&client);
  std::cout << "Connection closed. Closing mpi." << endl;
	MPI_Finalize();
	return 0;
}
