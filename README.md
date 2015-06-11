# mpi
Message Passing Interface for distributed systems

##OpenMPIDemo
###OpenMPI linux installation (ubuntu)
* Run:
 > sudo apt-get install libopenmpi-dev openmpi-bin libhdf5-openmpi-dev

* See:
 > http://selalib.gforge.inria.fr/install/ubuntu.html

###Execution
* Compile:
 > make

* Run (# processes):
 > mpirun -np # demo

* Run (# machines):
 > mpirun -hostfile host_file demo
