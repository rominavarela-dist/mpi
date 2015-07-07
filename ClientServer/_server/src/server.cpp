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
  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Info_set(info,"ip_port","1636");
  //MPI_Info_set(info,"ip_address","10.0.1.103");
  MPI_Open_port(info, port_name);
  std::cout << "Server up." << endl;
  std::cout << "Port name: " << port_name << endl;
  MPI_Publish_name("ocean", info, port_name);
  std::cout << "Service name: ocean" << endl;
  MPI_Comm_accept(port_name, info, 0, MPI_COMM_SELF,&client);
  std::cout << "Client connection acepted" << endl;

  //run
  run();

  //finalize
  MPI_Comm_disconnect(&client);
  std::cout << "Connection closed. Closing mpi." << endl;
  MPI_Close_port(port_name);
	MPI_Finalize();
	return 0;
}
