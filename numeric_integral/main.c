#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Trap(double a, double b, int n, double* global_result_p);

int main(int argc, char* argv[]) {
    double global_result = 0.0;
    double a, b;
    int n;
    int thread_count;
    thread_count = strtol(argv[1], NULL, 10);
    a = strtol(argv[2], NULL, 10);
    b = strtol(argv[3], NULL, 10);
    n = strtol(argv[4], NULL, 10);
    #pragma omp parallel num_threads(thread_count)
    Trap(a, b, n, &global_result);

    printf("With n = %d trapezoids, our estimate\n", n);
    

    return 0;
}