#include <iostream>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#define MASTER 0

using namespace std;

//nProcess, thisN, thisName
int world_size,world_rank,name_len;
char processor_name[MPI_MAX_PROCESSOR_NAME];
//server data
MPI_Comm server;
int server_size;
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

  //init client
  memset( port_name, '\0', MPI_MAX_PORT_NAME);
  strcpy( port_name, argv[1] );
  //MPI_Lookup_name("ocean",MPI_INFO_NULL,port_name);
  std::cout << "Initializing connection with server. Port name: " << port_name << endl;
  MPI_Comm_connect( port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &server );
  std::cout << "Server connection up" << endl;
  MPI_Comm_size(server, &server_size);
  std::cout << "Server size= " << server_size << endl;

  //run
  run();

  //finalize
  MPI_Comm_disconnect(&server);
  std::cout << "Connection closed. Closing mpi." << endl;
	MPI_Finalize();
	return 0;
}
