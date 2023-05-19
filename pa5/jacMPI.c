/*
 * jacobi.c
 * WimBo
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "mpi.h"

#define max(x, y)   ((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))

int main(int argc, char **argv) {

    int n;
    int t;
    int m = 2000;
    double  *prev, *cur;

    // MPI variables
    int my_id, next_id, prev_id;
    int p;       // Num processes
    int k = 1;   // Buffer size
    int start, end, segment_size;
    MPI_Status status;

    // On your marks
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    next_id = (my_id + 1);
    prev_id = (my_id - 1);       

    // Get set
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Timer
    double time;

    // temporary variables
    int i,j;
    int v = 0; //verbose
    double  *temp;

    // Check commandline args.
    if ( argc > 1 ) {
        n = atoi(argv[1]);
    } else {
        printf("Usage : %s [N]\n", argv[0]);
        exit(1);
    }
    if ( argc > 2 ) {
        m = atoi(argv[2]);
    }
    if ( argc > 3 ) {
        k = atoi(argv[3]);
    }
    if ( argc > 4 ) {
        v = 1;
    }

    segment_size = n / p;
    start = my_id * segment_size;
    end = start + segment_size;

    // Memory allocation for data array.
    prev  = (double *) malloc( sizeof(double) * n);
    cur   = (double *) malloc( sizeof(double) * n);
    if ( prev == NULL || cur == NULL ) {
        printf("[ERROR] : Fail to allocate memory.\n");
        exit(1);
    }

    // Initialization
    for (i = 0; i < n; ++i) {
        prev[i] = i;
    }
    cur[0] = 0;
    cur[n - 1] = n - 1;

    // Go
    if (my_id == 0) {
        initialize_timer();
        start_timer();
    }

    // Computation
    t = 0;
    // Controls the narrowing segment bounds
    int k_counter = k - 1;

    while (t < m) {
        for (i = max(start - k_counter, 1); i < min(end + k_counter, n - 1); ++i) {
            cur[i] = (prev[i - 1] + prev[i] + prev[i + 1]) / 3;
        }
        if (k_counter == 0) {
            if (my_id != 0) {
                // Send first element, receive neighbor's last element
                MPI_Send(&cur[start], k, MPI_DOUBLE, prev_id, 0, MPI_COMM_WORLD);
                MPI_Recv(&cur[start - k], k, MPI_DOUBLE, prev_id, 0, MPI_COMM_WORLD, &status);
            }
            if (my_id != p - 1) {
                // Send last element, receive neighbor's first element
                MPI_Send(&cur[end - k], k, MPI_DOUBLE, next_id, 0, MPI_COMM_WORLD);
                MPI_Recv(&cur[end], k, MPI_DOUBLE, next_id, 0, MPI_COMM_WORLD, &status);
            }
            k_counter = k - 1;
        } else {
            --k_counter;
        }
        temp = prev;
        prev = cur;
        cur  = temp;
        ++t;
    }

    temp = NULL;
    if (my_id == 0) {
        temp = prev;
    }

    MPI_Gather(&prev[start], segment_size, MPI_DOUBLE, temp, segment_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (my_id == 0) {
        stop_timer();
        time = elapsed_time();
        if(v){
            for(i=0;i<n;i++) {
                printf("%f ",prev[i]);
                fflush(stdout);
            }
            printf("\n");
        } else {
            printf("first, mid, last: %f %f %f\n",prev[0], prev[n/2-1], prev[n-1]);
            fflush(stdout);
        }
        printf("Data size : %d  , #iterations : %d , time : %lf sec\n", n, t, time);
        fflush(stdout);
    }

    free(cur);
    free(prev);

    MPI_Finalize();

    return 0;
}



