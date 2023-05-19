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

int main(int argc, char **argv) {

    long N  = 100;

    char *mark;

    long size;
    long current_num;
    long current_index;
    long i, j;
    long count;

    long num_index;

    /* Time */

    double time;

    if (argc > 1) N  = atol(argv[1]);

    /* Start Timer */

    initialize_timer ();
    start_timer();

    size = ceil(N / 2.0); 
    mark = (char *)malloc(size * sizeof(char));

    for (i = 0; i <= size; ++i) {
        mark[i] = 0;
    }

    current_num = 3;       /*first prime after 2*/
    current_index = 1;
    while (current_num * current_num <= N) {
        for (i = current_num * current_num; i <= N; i += 2 * current_num) {
            num_index = (i - 1) >> 1;
            mark[num_index] = 1;
        }
        while (mark[++current_index]) ; /* do nothing */
        current_num = current_index * 2 + 1;
    /* now index has the first unmarked number, so ... */
    }

    /* stop timer */
    stop_timer();
    time=elapsed_time ();

    /*number of primes*/
    count = 1;
    for(i = 1; i < size; ++i){
        if(mark[i] == 0) {
         	//printf("\t prime %ld  \n",i );
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
    return 0;
}


