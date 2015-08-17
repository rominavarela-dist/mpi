#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

//mpi
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void rcv_client()
{
  //open port
  char portname[MPI_MAX_PORT_NAME];
  MPI_Open_port(MPI_INFO_NULL, portname);
  std::cout << "[SERVER] Portname:" << endl;
  std::cout << portname << endl;

  //connect
  MPI_Comm client;
  MPI_Comm_accept(portname, MPI_INFO_NULL, 0, MPI_COMM_SELF, &client);

  //send message
  int msg= 10;
  MPI_Send(&msg, 1, MPI_INT, 0, 0, client);

  //disconnect
  MPI_Comm_free(&client);

  //close port
  MPI_Close_port(portname);
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
  std::cout << "[SERVER] Hello @ " << processor_name << endl;
  //for(int i=0; i<10; i++)
      //std::cout << "[MASTER] Spawn#" << i << " Got " << spawn() << " slaves..." << endl;
  rcv_client();

  //finalize
  sleep(3);
  int MPI_Fin_err= MPI_Finalize();
  std::cout << "[SERVER] Init/Finalization code: " << MPI_Init_err << "/" << MPI_Fin_err << endl;
  return 0;
}
