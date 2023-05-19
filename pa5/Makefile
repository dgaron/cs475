OBJS = timer.o
H_FILE = timer.h

EXEC = jac jacOMP jacMPI diamondSEQ

all: $(EXEC)

jac: jac.c $(OBJS) $(H_FILE)
	gcc -O3 -o $@ $< $(OBJS) $(MATHFLAG)

jacOMP: jacOMP.c $(OBJS) $(H_FILE)
	gcc -O3 -o $@ $< $(OBJS) $(MATHFLAG) -fopenmp

jacMPI: jacMPI.c $(OBJS) $(H_FILE)
	mpicc -O3 -o $@ $< $(OBJS) $(MATHFLAG) 

clean:
	rm -f $(EXEC)

tar:
	tar cvf PA5.tar Makefile jacOMP.c jacMPI.c report.pdf
