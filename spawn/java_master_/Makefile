CLASS_NAME = Master

SRC_DIR = ./src/
DST_DIR = ./bin/
SRC = $(SRC_DIR)$(CLASS_NAME).java

MPI_CLASS_PATH = /mirror/romina/openmpi/openmpi-1.8.8/install/lib/mpi.jar

all:
	mkdir -p $(DST_DIR)
	javac -classpath $(MPI_CLASS_PATH) $(SRC) -d $(DST_DIR)

run:
	mpirun java -classpath $(DST_DIR):$(MPI_CLASS_PATH) $(CLASS_NAME)
