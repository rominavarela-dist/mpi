# MPI
Message Passing Interface for distributed systems

**Compile**

 > make

**Run**

* number-of processes:
 > mpirun -np # demo

* connected machines:

 > mpirun -hostfile host_file demo

 > mpirun --mca btl_tcp_if_include x.x.x.0/24 -hostfile host_file demo

*see: http://stackoverflow.com/questions/8230027/mpi-barrier-doesnt-function-properly*

---

###Be Ready

**1. Choose OpenMPI or MPICH**

 * OpenMPI

     * Follow: https://github.com/rominavarela-demo/ub-scripts/blob/master/mpi/openmpi.md

 * MPICH

     * Follow: https://github.com/rominavarela-demo/ub-scripts/blob/master/mpi/mpich.md

**2. Install and configure SSH**

 * Virtual Machines first follow: https://github.com/rominavarela-demo/ub-scripts/blob/master/ssh/vbox-network.md

 * Follow: https://github.com/rominavarela-demo/ub-scripts/blob/master/ssh/ssh.md
