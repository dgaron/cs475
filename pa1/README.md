# Parallelizations in OpenMP

## Description:

The objective of this homework is to write three OpenMP programs, to debug and test them on a 
CS department machine, and to experimentally determine the gains you get when running it in 
parallel with up to 10 threads. The parallelizations are relatively simple, and the results should 
be interesting in terms of speedup. You should measure and plot the performance of your 
parallelization as a function of the number of threads, and analyze your observations.

## Objectives:

**Stencil 1D:**
* Parallelize the stencil_1D computation from the provided sequential code.

**Stencil 2D:**
* This is a 2D extension of the previous program; the data is updated using the values of eight 
neighboring row and column elements.

**Matrix-vector Product:**
* Parallelize the provided sequential program for the Matrix-vector product. 