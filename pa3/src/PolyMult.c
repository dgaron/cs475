/*/////////////////////////////////////////////////////////////////////////////
//
// File name : PolyMult.c
// Author    : Sanjay Rajopdhye
// Date      : 2023/Feb/6
// Desc      : Finds the product of two polynomials of degree d
//
/////////////////////////////////////////////////////////////////////////////*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <omp.h>

#define max(x, y)   ((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))

void PolyMultGSQ(float *p, float *q, float *r, long d1, long d2, long stA, long stB, long stC, long tune1, long tune2, long tune3) {
    long i, j;
    long d = d1;

    if(d1 != d2){
        printf("The degrees of the two polynomials must be equal\n");
        exit(-1);
    }

#pragma omp parallel for private(j) 
    for(i=0; i <= d; i+=1){
        for(j=0; j <= i; j+=1) {
            r[i] = r[i] + p[i-j] * q[j];
        }
    }

#pragma omp parallel for private(j)
    for(i=d+1; i <= 2*d; i+=1){
        for(j=d; j >= i-d; j-=1) {
            r[i] = r[i] + p[i-j] * q[j];
        }
    }
}

void PolyMultINQ(float *p, float *q, float *r, long d1, long d2, long stA, long stB, long stC, long tune1, long tune2, long tune3) {
    //  Same as Grade School, but with j as the outer loop 
    long i, j;
    long r_size = d1 + d2 + 1;

#pragma omp parallel for reduction(+ : r[stC:r_size]) private(i, j)
    for (j = 0; j <= d2; ++j) {
        for (i = j; i <= d1 + j; ++i) {
            r[i + stC] += p[i - j + stA] * q[j + stB];
        }
    }
}

void PolyMultOPQ(float *p, float *q, float *r, long d1, long d2, long stA, long stB, long stC, long tune1, long tune2, long tune3) {
    // Grade school but with square iteration space
    long i, j;
    long r_size = d1 + d2 + 1;

#pragma omp parallel for reduction(+ : r[stC:r_size]) private(i, j)
    for (i = 0; i <= d1; ++i) {
        for (j = 0; j <= d2; ++j) {
            r[i + j + stC] += p[i + stA] * q[j + stB];
        }
    }
}

void PolyMultBLQ(float *p, float *q, float *r, long d1, long d2, long stA, long stB, long stC, long tune1, long tune2, long tune3) {
    //  Same as OPQ, but tiled/blocked for better locality
    //  Use tune1 as block size
    long i, j;
    long ii, jj, end_i, end_j;
    long r_size = d1 + d2 + 1;

    if (tune1 <= 0) {
        tune1 = 4096;
    }

    // Range of r indices accessed == 2 * tune1
    // Range of overlap == tune1

#pragma omp parallel for reduction(+ : r[stC:r_size]) private(ii, i, jj, j, end_i, end_j)
    for (ii = 0; ii <= d1; ii += tune1) {
        end_i = min(ii + tune1 - 1, d1);
        for (jj = 0; jj <= d2; jj += tune1) {
            end_j = min(jj + tune1 - 1, d2);
            for (i = ii; i <= end_i; ++i) {
                for (j = jj; j <= end_j; ++j) {
                    r[i + j + stC] += p[i + stA] * q[j + stB];
                }
            }
        }
    }
}

void PolyMultDCQ(float* p, float* q, float* r, long d1, long d2, long stA, long stB, long stC, long tune1, long tune2, long tune3) {
    // Uses divide and conquer algorithm from lecture
    // Use tune2 as leaf size 

    if (tune2 <= 0) {
        tune2 = 8192;
    }

    if (max(d1, d2) <= tune2 || d1 <= 0 || d2 <= 0) {
        PolyMultBLQ(p, q, r, d1, d2, stA, stB, stC, tune1, tune2, -1);
        return;
    } 

    long p_first = d1 / 2;
    long p_second = d1 - p_first - 1;    
    long start_p = d1 - p_first + ((d1 & 1) ^ 1) + stA;

    long q_first = d2 / 2;
    long q_second = d2 - q_first - 1;
    long start_q = d2 - q_first + ((d2 & 1) ^ 1) + stB;

#pragma omp parallel
    {
#pragma omp single
        {
        // These are the independent quadrants
#pragma omp task shared(p, q, r)
        PolyMultDCQ(p, q, r, p_first, q_first, stA, stB, stA + stB, tune1, tune2, tune3);
#pragma omp task shared(p, q, r)
        PolyMultDCQ(p, q, r, p_second, q_second, start_p, start_q, start_p + start_q, tune1, tune2, tune3);

#pragma omp task shared(p, q, r)
        PolyMultDCQ(p, q, r, p_first, q_second, stA, start_q, start_q + stA, tune1, tune2, tune3);

// Master thread
        PolyMultDCQ(p, q, r, p_second, q_first, start_p, stB, start_p + stB, tune1, tune2, tune3);
        }
#pragma omp taskwait
    }
} 

//void PolyMultDCK(float *p, float *q, float *r, long d1, long d2, long stA, long stB, long stC, long tune1, long tune2, long tune3) {
    // Karatsuba
    //
//}

