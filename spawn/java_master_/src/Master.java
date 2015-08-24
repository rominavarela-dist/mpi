import mpi.*;

class Master {
	
	//configuration
	static int maxprocs= 4;
	static int loops= 10;
	static String hostfile = "/mirror/romina/workspace/demo/mpi/spawn/host_file";
	static String command = "/mirror/romina/workspace/demo/mpi/spawn/slave";

	//spawn
	static int spawn() throws MPIException {		
		Info info= new Info();
		int[] errcode = new int[maxprocs];
		info.set("hostfile", hostfile);
		Intercomm children= MPI.COMM_WORLD.spawn(command,new String[]{},maxprocs,info,0,errcode);

		int n_children[] = new int [1];
		children.recv(n_children, 1, MPI.INT, 0, 0);

		children.free();
		return n_children[0];
	}

	public static void main(String[] args) throws MPIException {
		//init
		MPI.Init(args);
		//int rank = MPI.COMM_WORLD.getRank();
		//int size = MPI.COMM_WORLD.getSize();
		String name = MPI.getProcessorName();

		//work
		System.out.println("[MASTER] Hello @ "+name);
		for(int i=0; i<loops; i++)
			try {
				System.out.println("[MASTER] Spawn Loop#" + i + " Got " + spawn() +" slaves...");
			    	Thread.sleep(1000);
			} catch(Exception ex) {
			    	System.out.println("Excpetion happened");
			}

		//finalize
		System.out.println("[MASTER] Good Bye");
		MPI.Finalize();
	}

}
