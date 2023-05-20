# Jacobi Stencil: MPI vs OpenMP

## Description:

The objective of this programming assignment is to write an MPI program and an OpenMP program for 
the one-D Jacobi problem similar to the stencil-1D code from PA1: where stencil-1D was a 5-point 
stencil, Jacobi is a 3 point stencil. In MPI you will use a blocked (halo) approach: each of the p 
MPI processes owns an n/p sized block of the array(s) and computes that block's result. To get data 
from neighboring blocks (in neighboring processes), the blocks have variable sized ghost element 
buffers, as described in Quinn Section 13.3.5. and the slides from that chapter. At the end, each 
block's result must be sent back to process 0 using "MPI_Gather" or "MPI_Gatherv" function calls. 
Timer should start after initialization of data and end after gather results from all the processes. 
You will write the MPI code, jacMPI.c, and analyse its performance on department machines, see 
these machines and grep 325. Then you will write the OpenMP version of the code, jacOMP.c, and 
compare the performance of the MPI and openMP versions of your code on one multi-core processor. 

## Objectives:

**One Processor / multicore comparison**  
  
Compare jacOMP and jacMPI on one CS department machine for 1 to 6 threads / processes, with data 
size n=120,000, number of iterations m=12,000, (for jacMPI) buffer size k=1. Report the results of 
your comparisons using tables and graphs. What is your conclusion? 

**Multi Processor / multi core comparison**  
  
For the multiprocessor jacMPI experiment, run a larger problem n=480,000, m=12,000 with 6 cores on one 
processor (-np = 6) and with 12 cores on 2 processors (-np 12). Experiment to find a good (near 
optimum) buffer size.

Report the results of your experiments using tables and graphs. What are your conclusions about 
speedup and buffer size?