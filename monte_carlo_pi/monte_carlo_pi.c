#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

double rand_from(double min, double max)  {
    return min + rand()*(max - min)/RAND_MAX;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    if (argc != 2) {
        printf("numero de argumentos (%d) invalido", argc - 1);
        return -1;
    }

    double r = 1.0;
    r *= r;
    double l = 2.0;
    l /= 2;

    int n = strtol(argv[1], NULL, 10);
    int hits = 0;
    double x, y;
    for (int i = 0; i < n; i++) {
        x = rand_from(0, 2*l);
        y = rand_from(0, 2*l);

        if ((x - l)*(x - l) + (y - l)*(y - l) <= r) {
            hits++;
        }
    }

    printf("pi = %f", ((double)hits)/n);

    return 0;
}