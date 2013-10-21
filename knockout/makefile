CC=g++
#CFLAG = -Wall -g

INCKUDEDIR = -I../CppLibrary

all: knockout.o knockoutExp.o knockoutPerl.o

knockout.o: knockout.cpp knockoutLibrary.h ../CppLibrary/nuclei_mass.h ../CppLibrary/mass03.txt
	$(CC) knockout.cpp -o knockout.o

knockoutExp.o: knockoutExp.cpp knockoutLibrary.h
	$(CC) knockoutExp.cpp -o knockoutExp.o 

knockoutPerl.o: knockoutPerl.cpp knockoutLibrary.h
	$(CC) knockoutPerl.cpp -o knockoutPerl.o 

clean:
	rm -rf knockout.o knockoutExp.o knockoutPerl.o
