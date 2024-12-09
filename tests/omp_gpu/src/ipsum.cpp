#include <algorithm>
#include <iostream>
#include <omp.h>

#include <ipsum.h>
#include <utils.h>

ipsum::ipsum(size_t sz) : sz(sz) {
    z = new int[sz];
}

void ipsum::target_enter(lorem &lor) {
    #pragma omp target enter data map(alloc: lor.y[:lor.sz])   \
                                  map(to: lor.x[:lor.sz], z[:sz])
}

void ipsum::target_exit(lorem &lor) const {
    #pragma omp target exit data map(release: z[:sz], lor.x[:lor.sz], lor.y[:lor.sz])
}

void ipsum::target_update_to() const {
    #pragma omp target update to(z[0:sz])
}

void ipsum::target_update_from(lorem &lor) {
    #pragma omp target update from( \
        lor.x[:lor.sz],             \
        lor.y[:lor.sz]              \
    )
}

void ipsum::computation(lorem &lor) {
    int *lx = lor.x;
    int *ly = lor.y;
    static int *lz = z;
    // unsigned long long _x, _y, _z;
    static size_t _sz = sz;
    #pragma omp target teams distribute parallel for simd 
    for (size_t i = 0; i < _sz; i++) {
        ly[i] = lx[i] + lz[i];

        lz[i] = lz[i];
    }

    // std::cout << (int*)_x << ' ' << (int*)_y << ' ' << (int*)_z <<'\n';
    // std::cout << lastx << " " << lasty << " " << lastz << " " << utils::get_dev_addr(lor.x) << " " << utils::get_dev_addr(lor.y) << '\n';

    std::swap<int*>(lor.x, lor.y);
}

ipsum::~ipsum() {
    delete[] z;
}