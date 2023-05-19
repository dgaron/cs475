CC = gcc
EXEC = stencil_1D_SEQ stencil_2D_SEQ mat_vec_SEQ stencil_1D stencil_2D mat_vec
OBJS = timer.o
H_FILE = timer.h
MATHFLAG = -lm
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3 
FILES = makefile mat_vec.c stencil_1D.c stencil_2D.c report.pdf

all: $(EXEC)


stencil_1D_SEQ: stencil_1D.c $(OBJS) $(H_FILE)
	$(CC) $(SEQFLAGS) -o  $@ stencil_1D.c  $(OBJS)  $(MATHFLAG)

stencil_1D: stencil_1D.c $(OBJS) $(H_FILE)
	$(CC) $(FLAGS) $(MATHFLAG) -o $@ stencil_1D.c $(OBJS)


stencil_2D_SEQ: stencil_2D.c $(OBJS) $(H_FILE)
	$(CC) $(SEQFLAGS) -o  $@ stencil_2D.c  $(OBJS)  $(MATHFLAG)

stencil_2D: stencil_2D.c $(OBJS) $(H_FILE)
	$(CC) $(FLAGS) $(MATHFLAG) -o $@ stencil_2D.c $(OBJS)


mat_vec_SEQ: mat_vec.c $(OBJS) $(H_FILE)
	$(CC) $(SEQFLAGS) $(MATHFLAG) -o $@ mat_vec.c $(OBJS)

mat_vec: mat_vec.c $(OBJS) $(H_FILE)
	$(CC) $(FLAGS) $(MATHFLAG) -o $@ mat_vec.c $(OBJS)


timer.o: timer.c
	$(CC) $(SEQFLAGS) -o $@ -c timer.c

clean: 
	rm -f *.o $(OBJS) $(EXEC)

tar:
	tar -cf PA1.tar $(FILES)
