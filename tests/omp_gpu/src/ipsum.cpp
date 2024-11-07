#include <ipsum.h>
#include <algorithm>
#include <iostream>

ipsum::ipsum(size_t sz) : sz(sz) {
    z = new int[sz];
}

void ipsum::target_enter(lorem &lor) const {
    #pragma omp target enter data map(to: lor)
    #pragma omp target enter data map(to: z[0:sz], lor.x[0:lor.sz]) \
                                  map(alloc: lor.y[0:lor.sz])
    // #pragma omp target enter data map(to: lor)
}

void ipsum::target_exit(lorem &lor) const {
    #pragma omp target exit data map(release: z[0:sz], lor.x[0:lor.sz], lor.y[0:lor.sz])
    #pragma omp target exit data map(release: lor)
}

void ipsum::target_update_to() const {
    #pragma omp target update to(z[0:sz])
}

void ipsum::target_update_from(lorem &lor) {
    #pragma omp target update from( \
        lor.x[0:lor.sz],            \
        lor.y[0:lor.sz]             \
    )
}

void ipsum::computation(lorem &lor) {
    static int* x = lor.x;
    static int* y = lor.y;
    unsigned long long a;
    unsigned long long b;
    #pragma omp target teams distribute parallel for simd map(from: a, b)
    for (size_t i = 0; i < sz; i++) {
        // lor.y[i] = lor.x[i] + z[i];
        // a = (unsigned long long)lor.y;
        // b = (unsigned long long)lor.x;
        y[i] = x[i] + z[i];
        a = (unsigned long long)y;
        b = (unsigned long long)x;
    }

    std::cout << "a: " << (int*)a << " lor.x: " << lor.x
              << "\nb: " << (int*)b << " lor.y: " << lor.y << "\n\n";

    std::swap<int*>(lor.x, lor.y);
    std::swap<int*>(x, y);
}

ipsum::~ipsum() {
    delete[] z;
}