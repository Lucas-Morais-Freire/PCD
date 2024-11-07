#include <iostream>
#include <omp.h>

#include "lorem.h"
#include "ipsum.h"
#define SZ 10

template <typename T>
void print_array(T* arr, int sz) {
    if (sz == 0) {
        std::cout << "[]\n";
        return;
    }

    std::cout << '[' << arr[0];
    for (int i = 1; i < sz; i++) {
        std::cout << ", " << arr[i];
    }
    std::cout << "]\n";
}

void computation(int *&x, int *&y, size_t &sz) {
    #pragma omp target teams distribute parallel for simd
    for (size_t i = 0; i < sz; i++) {
        y[i] = x[i] + 10;
    }

    std::swap<int*>(x, y);
}


int main() {
    lorem lor(SZ);
    ipsum ips(SZ);

    
    int* z = ips.get_z();
    for (size_t i = 0; i < SZ; i++) {
        z[i] = i;
        lor.x[i] = 1;
    }

    ips.target_enter(lor);

    ips.computation(lor);
    // ips.target_update_from(lor);
    ips.computation(lor);

    ips.target_update_from(lor);

    std::cout << "x: ";
    print_array(lor.x, SZ);
    std::cout << "y: ";
    print_array(lor.y, SZ);

    ips.target_exit(lor);

    #ifdef _OPENMP
    std::cout << "num devices: " << omp_get_num_devices() << ", On device: " << omp_get_default_device() << "\n";
    #endif

    return 0;
}
