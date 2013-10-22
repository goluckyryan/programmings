CC=g++

all: 3DeeGen.o 3knockGen.o make_infile.o read_outfile.o

3DeeGen.o: 3DeeGen.cpp
	$(CC) 3DeeGen.cpp -o 3DeeGen.o

3knockGen.o: 3knockGen.cpp
	$(CC) 3knockGen.cpp -o 3knockGen.o
	
make_infile.o: make_infile.cpp
	$(CC) make_infile.cpp -o make_infile.o
	
read_outfile.o: read_outfile.cpp
	$(CC) read_outfile.cpp -o read_outfile.o

clean:
	rm -rfv *.o 
