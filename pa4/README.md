# CUDA First Steps

## Description:

The purpose of this exercise is for you to learn how to write programs using the CUDA programming 
interface, how to run such programs using an NVIDIA graphics processor (GP GPU general purpose 
Graphics Processing Unit), and how to think about the factors that govern the performance of 
programs running within the CUDA environment. 

## Objectives:

**Vector MAX: coalescing memory accesses**  
  
The provided kernel is part of a program that performs vector MAX reduction. Notice that the MAX 
operator is commutative and associative. This means that you can execute MAXs in any order, so you 
can apply the coalescing thread transformation you experimented with in Lab 5. In the provided 
kernel each thread computes one maximum of a contiguous partition of the input array and writes it 
to global memory. The host mem copies the result back, and computes the max of all maxes.

Given a 1D grid of 80 threadblocks and a 1D threadblock of 128 threads, and a problem size 
n = 1,280,000,000, each thread computes the maximum of 125,000 elements. The input array is of size 
n, whereas the result array is of size n / 125,000, in this case 80 * 128= 10,240.

In your modified kernel each thread will read, in a coalescing fashion, n / (80 * 128) interleaved 
global array elements. In the case of n=1,280,000,000, each thread reads again 125,000 elements. 
Leave the grid and threadblock dims the same. Again, each thread computes one maximum, of a now 
interleaved partition. The intermediate maxes computed by the GPU threads will be different from the 
ones computed by the original kernel. However, the max of maxes computed by the host will be the 
same as the original max of maxes.

Measure and report the difference in performance of the two codes.  
  
**Shared CUDA Matrix Multiply**  
  
The first exercise made you aware of coalescing and its performance enhancement. The main exercise 
performs matrix multiplication.

Running make produces a binary called matmult00 and it is invoked like this,

        $ ./matmult00 X
  
where X controls the problem size (i.e., the matrices are NxN matrices of size N=X*FOOTPRINT_SIZE). 
FOOTPRINT_SIZE is defined in matmultKernel.h. This is done to avoid nasty padding issues. If you run 
it with X=100 for example, then you see this:

        $ ./matmult00 100
        Data dimensions: 1600x1600
        Grid Dimensions: 100x100
        Block Dimensions: 16x16
        Footprint Dimensions: 16x16
        Time: 0.017199 (sec), nFlops: 8192000000, GFlopsS: 476.305669

The "Grid Dimensions" represent the number of CUDA thread blocks being used and matches the value 
passed as X. The "Block Dimensions" represent the size of each CUDA thread block (i.e., the number 
of threads per block). This is controlled by the compile time constant BLOCK_SIZE in 
matmultKernel.h. The "Footprint dimensions" represent the size of the patch of C computed by each 
CUDA block. This is controlled by FOOTPRINT_SIZE. In the provided matmult00 implementation, the 
FOOTPRINT_SIZE and BLOCK_SIZE are the same which means that each thread updates a single element of 
C.

Your task is to modify the kernel, (copy matmultKernel00.cu into matmultKernel01.cu), and produce a 
new binary matmult01 where each thread updates more than one element of C, based on the values of 
FOOTPRINT_SIZE and BLOCK_SIZE. For example, in order to have each thread update 4 elements of its 
block's patch, then you would set FOOTPRINT_SIZE to twice that of BLOCK_SIZE. Your submitted code 
should have each thread compute 4 values in the resulting C matrix.

Here is an example of running the solution code's matmult01:

        $ ./matmult01 100
        Data dimensions: 3200x3200 
        Grid Dimensions: 100x100 
        Block Dimensions: 16x16 
        Footprint Dimensions: 32x32 
        Time: 0.108151 (sec), nFlops: 65536000000, GFlopsS: 605.967812

Notice that parameter 100 now creates a 100*32 = 3200 square matrix problem, because the footprint 
has become 32x32.

Investigate how each of the following factors influences performance of matrix multiplication in 
CUDA:

* The size of matrices to be multiplied
* The size of the block computed by each thread block 

You should time the initial code provided and your modifed version using square matrices of each of 
the following sizes: 1600, 3200, 6400. The easiest way to update the footprint size for matmult01 is 
to add the flag -DFOOTPRINT_SIZE=32 to the lines in your makefile where you compile matmult01. 