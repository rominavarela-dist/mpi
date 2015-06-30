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

**Choose OpenMPI or MPICH**

**OpenMPI** *linux installation (ubuntu)*

* Run:
 > sudo apt-get install libopenmpi-dev openmpi-bin libhdf5-openmpi-dev

* See:
 > http://selalib.gforge.inria.fr/install/ubuntu.html

**MPICH** *linux installation (ubuntu)*

* Run:
 
 > sudo apt-get install mpich libmpich-dev
 
 > mpichversion

* SSH Extra configuration:

 - Add every neighborn to /etc/hosts
 
 - Add all nodes to ~/.ssh/config

Example config:

    Host romina1-VirtualBox
        Hostname 10.0.1.101
        User romina1

**SSH installation & configuration**

*(be sure you can ping among your nodes)*

*For every node:*

 > sudo apt-get install ssh

 > sudo apt-get install openssh-server

* For each node (except self):

 > ssh node@x.x.x.x

 > yes .. exit

*For master:*

 > ssh-keygen -t rsa

 > cd ~/.ssh

* For each node (including master it's self):

 > ssh-copy-id node@#.#.#.#

**See:**
 > https://www.digitalocean.com/community/tutorials/how-to-set-up-ssh-keys--2

Now you should be able to log from master to slave without restrictions.
