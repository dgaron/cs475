# Polynomial Multiplication

## Description:

The objective of this assignment is to explore implementations of Polynomial Multiplication. Record 
the performance of your programs on a CS department machine, and experimentally determine the gains 
you get with 1-8 threads. 

The following two sequential programs have been implemented for you.

**PolyMultGSQ:** (Grade School Quadratic) This is the naive implementation of polynomial 
multiplication.
**PolyMultGold:** This (sequential) implementation includes all of the optimizations up to 
PolyMultBLQ. It is only provided as a binary. Use it as a benchmark to compare your programs against. 

## Objectives:

**PolyMultINQ** (Inverted Quadratic)
* Invert the inner and outer loops of both computational loops from the PolyMultGSQ implementation
  * Hint: once the loops have been inverted you can condense the computation into a single double 
  for loop.
* Explore loop parallelism. Report the optimal strategy and number of threads. 

**PolyMultOPQ** (Outer Product Quadratic)
* Rewrite PolyMultGSQ to use a square iteration space (as shown in lecture).
* Explore loop parallelism. Report the optimal strategy and number of threads. 

**PolyMultBLQ** (Blocked Quadratic)
* Block both the inner and outer loops from PolyMultOPQ.
* Use the same parameter (tune1) to set the block size for each loop.
* Explore loop parallelism. Report the optimal strategy, number of threads, and block size. 

**PolyMultDCQ** (Divide and Conquer Quadratic)
* Rewrite polyMultOPQ to use the divide and conquer strategy presented in lecture.
* Use tune2 to set the minimum leaf size.
* Explore task parallelism and test the use of different non recursive algorithms in the leafs (e.g. 
PolyMult{INQ,OPQ,BLQ}). Determine and report which configuration gives you the best performance. 

