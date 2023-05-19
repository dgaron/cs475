///
/// matmultKernel00.cu
/// For CSU CS575 Spring 2011
/// Instructor: Wim Bohm
/// Based on code from the CUDA Programming Guide
/// Modified by Wim Bohm and David Newman
/// Created: 2011-01-27
/// Last Modified: 2011-02-23 DVN
///
/// Multiplies two matrices using CUDA: A x B = C
///
/// Copy this file and modify the MatMultKernel device function for
/// each of your experiments. 
///

#include "matmultKernel.h"

// Define a gpu kernel to perform matrix multiplication
// of A x B = C.
__global__ void MatMulKernel(Matrix A, Matrix B, Matrix C){

  // matrix blocks
  float *Asub, *Bsub, *Csub;
  // Putting these into registers speeds access.
  int thread_row = threadIdx.y;
  int thread_col = threadIdx.x;
  int block_row = blockIdx.y;
  int block_col = blockIdx.x;

  // Each THREAD BLOCK computes one sub matrix Csub of C
  // EACH THREAD creates its own matrix descriptor Csub
  Csub = &C.elements[C.stride * FOOTPRINT_SIZE * block_row + FOOTPRINT_SIZE * block_col];

  // Each thread computes one element of Csub in its copy of CValue
  float Cvalue00 = 0;
  float Cvalue01 = 0;
  float Cvalue10 = 0;
  float Cvalue11 = 0;
  
  // Loop over all sub matrices in block_row of A and block_col of B
  // required to compute Csub. Block multiply each pair of sub matrices
  // and accumulate results
  for (int m = 0;  m < (A.width / FOOTPRINT_SIZE); ++m){
    // Get Asub and Bsub descriptors
    Asub = &A.elements[A.stride * FOOTPRINT_SIZE * block_row + FOOTPRINT_SIZE * m];
    Bsub = &B.elements[B.stride * FOOTPRINT_SIZE * m + FOOTPRINT_SIZE * block_col];

    // Copy ELEMENTS OF  ASub and Bsub into shared memory
    // EACH THREAD loads four ELEMENTs of ASub and four of Bsub

    // Notice: every thread declares shared_A and shared_B in shared memory
    //         even though a thread block has only one shared_A and one shared_B
    __shared__ float shared_A[FOOTPRINT_SIZE][FOOTPRINT_SIZE];
    __shared__ float shared_B[FOOTPRINT_SIZE][FOOTPRINT_SIZE];

    // Each thread copies four elements of shared_A and one element of shared_B

/*
    shared_A[thread_row][thread_col] = Asub[thread_row * A.stride + thread_col];
    shared_A[thread_row + BLOCK_SIZE][thread_col] = Asub[(thread_row + BLOCK_SIZE) * A.stride + thread_col];
    shared_A[thread_row][thread_col + BLOCK_SIZE] = Asub[thread_row * A.stride + thread_col + BLOCK_SIZE];
    shared_A[thread_row + BLOCK_SIZE][thread_col + BLOCK_SIZE] = Asub[(thread_row + BLOCK_SIZE) * A.stride + thread_col + BLOCK_SIZE];

    shared_B[thread_row][thread_col] = Bsub[thread_row * B.stride + thread_col];
    shared_B[thread_row][thread_col + BLOCK_SIZE] = Bsub[thread_row * B.stride + thread_col + BLOCK_SIZE];
    shared_B[thread_row + BLOCK_SIZE][thread_col] = Bsub[(thread_row + BLOCK_SIZE) * B.stride + thread_col];
    shared_B[thread_row + BLOCK_SIZE][thread_col + BLOCK_SIZE] = Bsub[(thread_row + BLOCK_SIZE) * B.stride + thread_col + BLOCK_SIZE];
*/

    int rh = thread_row % 2 ? 1 : 0;
#pragma unroll
    for (int i = 0; i < 4; ++i) {
        shared_A[thread_row / 2 + i * 8][thread_col + rh * BLOCK_SIZE] = Asub[(thread_row / 2 + i * 8) * A.stride + thread_col + rh * BLOCK_SIZE];
        shared_B[thread_row / 2 + i * 8][thread_col + rh * BLOCK_SIZE] = Bsub[(thread_row / 2 + i * 8) * B.stride + thread_col + rh * BLOCK_SIZE];
    }

    // Synchronize to ensure all shared values have been stored
    __syncthreads();

    // Do an inproduct of one row of shared_A and one col of shared_B
    // computing one Cvalue by accumulation
#pragma unroll
    for(int e=0; e<FOOTPRINT_SIZE; ++e) {
       Cvalue00 += shared_A[thread_row][e] * shared_B[e][thread_col];
       Cvalue01 += shared_A[thread_row][e] * shared_B[e][thread_col + BLOCK_SIZE];
       Cvalue10 += shared_A[thread_row + BLOCK_SIZE][e] * shared_B[e][thread_col];
       Cvalue11 += shared_A[thread_row + BLOCK_SIZE][e] * shared_B[e][thread_col + BLOCK_SIZE];
    }

    // Synchronize to ensure all Cvalues have been incremented
    // before reading in the next shared_A AND shared_B BLOCKS
    __syncthreads();
  }

  // Write Csub to GLOBAL memory.
  // Each thread writes its own cell value.
  Csub[thread_row * C.stride + thread_col] = Cvalue00;
  Csub[thread_row * C.stride + thread_col + BLOCK_SIZE] = Cvalue01;
  Csub[(thread_row + BLOCK_SIZE) * C.stride + thread_col] = Cvalue10;
  Csub[(thread_row + BLOCK_SIZE) * C.stride + thread_col + BLOCK_SIZE] = Cvalue11;
}

