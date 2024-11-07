#include "ipsum.h"
#include <algorithm>

ipsum::ipsum(size_t sz) : sz(sz) {
    z = new int[sz];
}

void ipsum::target_enter(lorem &lor) const {
    #pragma omp target enter data map(to: z[0:sz], lor.x[0:lor.sz], lor) \
                                  map(alloc: lor.y[0:lor.sz])
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
    #pragma omp target teams distribute parallel for simd
    for (size_t i = 0; i < sz; i++) {
        lor.y[i] = lor.x[i] + z[i];
    }

    std::swap<int*>(lor.x, lor.y);
    #pragma omp target update to(lor)
}

ipsum::~ipsum() {
    delete[] z;
}