CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3 
MATHFLAGS = -lm
EXEC = sieve sieveP sieve1 sieve2 sieve3 sieve4 

all: $(EXEC)

# Original
sieve: sieve.c $(OBJS)
	$(CC) $(SEQFLAGS)  -o $@ $< $(OBJS) $(MATHFLAGS)

# Original Parallelized
sieveP: sieveP.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)

# Sequential + Upgrades
sieve1: sieve1.c $(OBJS)
	$(CC) $(SEQFLAGS)  -o $@ $< $(OBJS) $(MATHFLAGS)

# Parallelized + Upgrades
sieve2: sieve2.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)

# Sequential + Blocking
sieve3: sieve3.c $(OBJS)
	$(CC) $(SEQFLAGS)  -o $@ $< $(OBJS) $(MATHFLAGS)

# Parallelized + Blocking
sieve4: sieve4.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS) $(MATHFLAGS)

timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)

PA2.tar: sieve.c sieve1.c sieve2.c sieve3.c sieve4.c report.pdf makefile
	tar cvf PA2.tar sieve.c sieve1.c sieve2.c sieve3.c sieve4.c report.pdf makefile
