#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

//mpi
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

/**
* @method main
**/
int main(int argc, char* argv[])
{
  //init
  int MPI_Init_err= MPI_Init(&argc, &argv);
  MPI_Get_processor_name(processor_name, &name_len);

  std::cout << "[CLIENT] Hello @ " << processor_name << endl;

  if (argc >= 2){
      //connect
      MPI_Comm server;
      char portname[MPI_MAX_PORT_NAME];
      std::cout << "[CLIENT] Connecting to " << argv[1] << endl;
      strcpy(portname, argv[1]);
      MPI_Comm_connect(portname, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &server);

      //get server message
      int server_msg;
      MPI_Recv(&server_msg, 1, MPI_INT, 0, 0, server, MPI_STATUS_IGNORE);
      std::cout << "[CLIENT] Server message: " << server_msg << endl;

      //disconnect
      MPI_Comm_disconnect(&server);
   }

  //finalize
  sleep(3);
  int MPI_Fin_err= MPI_Finalize();
  std::cout << "[CLIENT] Init/Finalization code: " << MPI_Init_err << "/" << MPI_Fin_err << endl;
  return 0;
}
