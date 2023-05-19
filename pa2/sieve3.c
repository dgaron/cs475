/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve.c
// Author    : Nissa Osheim
// Date      : 2010/19/10
// Desc      : Finds the primes up to N
//
// updated Wim Bohm
/////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

long min(long a, long b) {
   return a < b ? a : b;
}

long fmib(long start, long prime) {
    // This is the first multiple before block, plus one times prime if even, two if odd
    return prime * ((start / prime) + ((start / prime) & 1) + 1);
}

int main(int argc, char **argv) {

    long N  = 100;
    long block_size = 96000;

    char *mark;
    long *primes;

    long size;
    long size_primes;
    long root_N; 
    long last_prime;
    long count;

    long current_num;
    long current_index;
    long i, j, ii;
    long first_odd_mult;
    long loop_end;
    long num_index;
    long prime_sq;

    /* Time */

    double time;

    if (argc > 1) N  = atol(argv[1]);
    if (argc > 2) block_size = atol(argv[2]);

    /* Start Timer */

    initialize_timer ();
    start_timer();
    
    size = ceil(N / 2.0);
    mark = (char *)malloc(size * sizeof(char));

    root_N = floor(sqrt(N));
    size_primes = ceil(root_N / 2.0);
    primes = (long *)malloc(root_N * sizeof(long));

    for (ii = 0; ii < size; ii += block_size) {
        loop_end = min(ii + block_size, size);
        for (i = ii; i < loop_end; ++i) {
            mark[i] = 0;
        }
    }

    /* Preamble: Find primes up to sqrt(N) */
    current_num = 3;       /*first prime after 2*/
    current_index = 1;
    last_prime = -1;  
    while (current_num * current_num <= N) {
        primes[++last_prime] = current_num;
        for (i = current_num * current_num; i <= root_N; i += 2 * current_num) {
            num_index = (i - 1) >> 1;
            mark[num_index] = 1;
        }
        while (mark[++current_index]) ; /* do nothing */
        current_num = current_index * 2 + 1;
    }

    for (ii = root_N; ii < N; ii += block_size) {
        for (j = 0; j <= last_prime; ++j) {
            prime_sq = primes[j] * primes[j];
            // If prime_sq is within the block, we start there
            first_odd_mult = prime_sq;
            if (prime_sq > ii + block_size) {
                // No need to mark if prime squared is past the block end
                break;
            } else if (prime_sq < ii) {
                // Probably the most common case
                first_odd_mult = fmib(ii, primes[j]);
            }
            loop_end = min(ii + block_size, N);
            for (i = first_odd_mult; i <= loop_end; i += 2 * primes[j]) {
                num_index = (i - 1) >> 1;
                mark[num_index] = 1;
            }
        }
    }

    /* stop timer */
    stop_timer();
    time=elapsed_time ();

    /*number of primes*/
    count = 1;
    for(i = 1; i < size; ++i){
        if(mark[i] == 0) {
            //current_num = i * 2 + 1;
            //printf("\t prime %ld  \n", current_num);
            ++count;
         }
    }
    printf("There are %ld primes less than or equal to %ld\n", count, N);

    /* print results */
    printf("First three primes:");
    j = 1;
    printf("%d ", 2);
    for ( i=1 ; i < size && j < 3; ++i ) {
       if (mark[i] == 0){
             current_num = i * 2 + 1;
             printf("%ld ", current_num);
             ++j;
       }
    }
    printf("\n");

    printf("Last three primes:");
    j = 0;
    for (i = size - 1; i > 0 && j < 3; --i) {
        if (mark[i] == 0) {
            current_num = i * 2 + 1;
            printf("%ld ", current_num);
            j++;
        }
    }
    printf("\n");

    printf("elapsed time = %lf (sec)\n", time);

    free(mark);
    free(primes);
    return 0;
}


