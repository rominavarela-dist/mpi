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

*OpenMPI linux installation (ubuntu)*

* Run:
 > sudo apt-get install libopenmpi-dev openmpi-bin libhdf5-openmpi-dev

* See:
 > http://selalib.gforge.inria.fr/install/ubuntu.html

*MPICH linux installation option 1 (ubuntu)*

* Run:
 > sudo apt-add-repository ppa:paulromano/staging

 > sudo apt-get update
 
 > sudo apt-get install mpich libmpich-dev

* See:
 > https://mit-crpg.github.io/openmc/usersguide/install.html
 
*MPICH linux installation option 2 (ubuntu)*

* Download http://www.mpich.org/downloads/

* Decompress and go to decompressed root directory

* Run:
 > sudo ./configure --disable-f77 --disable-fc –disable-fortran

 > make

 > sudo make install
 
 > sudo gedit ~/.bashrc
 
 > add: export MPICC=/usr/local/bin/mpicc
 
 > mpichversion

* See:

 > http://www.cse.cuhk.edu.hk/blogel/deploy.html

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

 > scp id_rsa.pub node@x.x.x.x:~/.ssh/id_rsa.pub

 > yes ... exit

*For each slave:*

 > cd ~/.ssh

 > cat id_rsa.pu >> authorized_keys

**See:**
 > https://www.youtube.com/watch?v=0jQrhBplCBY&index=3&list=PLbx-k3N9Yr99WQVwlIdbWdsVxi5ItGL14

Now you should be able to log from master to slave without restrictions.
