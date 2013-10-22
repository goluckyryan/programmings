CC=g++
#CFlAGE =

all: nuclei_mass.o matlib.o

nuclei_mass.o: nuclei_mass.cpp nuclei_mass.h
	$(CC) nuclei_mass.cpp -o nuclei_mass.o
	
matlib.o: mathlib.cpp mathlib.h
	$(CC) mathlib.cpp -o mathlib.o
   
clean:
	rm -rvf *.o
