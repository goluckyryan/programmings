CC=gfortran
CFLAGS = -I$FFTW3_dir/include -lfftw3 -lm

all: FFTW.o FFTW_batch.o

FFTW.o: FFTW.cpp FFTWLibrary.h
	$(CC) FFTW.cpp -o FFTW.o $(CFLAGS)

FFTW_batch.o: FFTW_batch.cpp FFTWLibrary.h
	$(CC) FFTW_batch.cpp -o FFTW_batch.o $(CFLAGS)

clean:
	rm -rf FFTW.o FFTW_batch.o
