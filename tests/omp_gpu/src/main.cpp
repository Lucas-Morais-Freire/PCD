#include <iostream>
#include <omp.h>

#include <lorem.h>
#include <ipsum.h>
#define SZ 10//0000000

template <typename T>
void print_array(T* arr, size_t sz) {
    if (sz == 0) {
        std::cout << "[]\n";
        return;
    }

    std::cout << '[' << arr[0];
    for (size_t i = 1; i < sz; i++) {
        std::cout << ", " << arr[i];
    }
    std::cout << "]\n";
}


int main(int argc, char** argv) {
    if (argc < 2 || argc > 2) {
        std::cout << "usage: ./main <n-computations>\n";
        return -1;
    }

    int n_comps = strtol(argv[1], nullptr, 10);

    lorem lor(SZ);
    ipsum ips(SZ);
    
    int* z = ips.get_z();
    for (size_t i = 0; i < SZ; i++) {
        z[i] = i;
        lor.x[i] = 1;
    }

    ips.target_enter(lor);

    for (int i = 0; i < n_comps; i++) {
        ips.computation(lor);
    }


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
