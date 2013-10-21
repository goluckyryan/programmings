CC=gfortran

all: fknockout  ppCheck ppGen Looppp

fknockout: knockout.f90
	$(CC) knockout.f90 -o fknockout
	
ppCheck: ppCheck.f90
	$(CC) ppCheck.f90 -o ppCheck

ppGen: ppGen.f90
	$(CC) ppGen.f90 -o ppGen
	
Looppp: Looppp.f90
	$(CC) Looppp.f90 -o Looppp

clean:
	rm -rf fknockout ppCheck ppGen Looppp
