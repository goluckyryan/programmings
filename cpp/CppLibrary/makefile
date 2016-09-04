CC=g++
#CFlAGE =

all: nuclei_mass.o matlib.o test.o nuclei_data_gen.o matrix.o

nuclei_mass.o: nuclei_mass.cpp nuclei_mass.h constant.h
	$(CC) nuclei_mass.cpp -o nuclei_mass.o

matlib.o: mathlib.cpp mathlib.h constant.h
	$(CC) mathlib.cpp -o mathlib.o

nuclei_data_gen.o: nuclei_data_gen.cpp constant.h nuclei_mass.h
	$(CC) nuclei_data_gen.cpp -o nuclei_data_gen.o

test.o: test.cpp matrix4D.h vector4D.h fourVector.h constant.h
	$(CC) test.cpp -o test.o
	
matrix.o: matrix.cpp matrix.h constant.h
	$(CC) matrix.cpp -o matrix.o

clean:
	rm -rvf *.o *.exe
