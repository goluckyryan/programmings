CC=g++
#CFLAG = -Wall -g

all: knockout4V.o Exp4V.o

	
knockout4V.o: knockout4V.cpp knockoutLibrary4V.h ../CppLibrary/nuclei_mass.h ../CppLibrary/fourVector.h ../CppLibrary/lorentzian.h 
	$(CC) knockout4V.cpp -o knockout4V.o 

Exp4V.o: Exp4V.cpp knockoutLibrary4V.h ../CppLibrary/nuclei_mass.h ../CppLibrary/fourVector.h ../CppLibrary/lorentzian.h 
	$(CC) Exp4V.cpp -o Exp4V.o 


clean:
	rm -rf  knockout4V.o Exp4V.o
