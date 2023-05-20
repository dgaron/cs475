# The Sieve of Eratosthenes

## Description:

The objective of this assignment is to step wise parallelize a Prime Sieve Program, and record the 
performance of your programs on a CS department machine, and to experimentally determine the gains 
you get with 1-8 threads. 

## Objectives:

**Sieve 1:** 
Your first task is to improve the sequential program provided, creating a program sieve1.c where you 
apply the sequential optimizations discussed in the lecture:

* Marking using a stride rather than testing every element for divisibility
* Starting the marking off at the square of the current prime
* Marking off multiples of only those primes that are no more than sqrt(n)
* Marking and storing only odds

Analyze the execution time of sieve1.c and compare it to the performance of sieve.c. Report 
performance for n = 100,000, n = 200,000, and 300,000. Analyse the order of magnitude improvement of 
your code.  

**Sieve 2:** Your next program sieve2.c should be a parallelization of sieve1. You should experiment 
with parallelizing one or more of the loops, and report how the speedup varies as a function of the 
number of threads (1, 2, 3, 4, 5, 6, 7, 8) on a Capital machine, for n=500,000,000, n=1,000,000,000, 
and n=1,500,000,000. If you do not get speedup, explain the reasons, as best as you can. Think about 
PA1. For which codes did you not get good speedup? Why was that there? Is there a relationship?

**Sieve 3:** Now return to your sequential program Sieve 1, and block the loop to improve locality 
as discussed in class. Make the blockSize a program parameter that can be passed as a command line 
argument. For this program, you should again analyze the performance gains achieved by blocking for 
the values of n given above. Play with blockSize and report which gives you good performance. What 
performance do you get when blockSize is 1,000,000?  

**Sieve 4:** is a parallelization of Sieve3. Report the speedup as a function of the number of 
threads. Ask yourself: which loop can be parallelized? 