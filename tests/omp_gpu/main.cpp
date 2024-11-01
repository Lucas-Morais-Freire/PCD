#include <iostream>
#include <omp.h>
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

void target_enter(int* arr, int sz) {
    #pragma omp target enter data map(to:arr[0:sz])
}

void target_get_data(int* arr, int sz) {
    #pragma omp target update from(arr[0:sz])
}

void target_set_data(int* arr, int sz) {
    #pragma omp target update to(arr[0:sz])
}

void target_release_data(int* arr, int sz) {
    #pragma omp target exit data map(release:arr[0:sz])
}

struct obj {
public:
    int* x;
    int* y;
    int* ax;
    int* ay;
    size_t sz;
    obj(size_t sz) {
        this->sz = sz;
        x = new int[sz];
        y = new int[sz];
    }
    ~obj() {
        delete[] x;
        delete[] y;
    }

    void computation() {
        #pragma omp target teams distribute parallel for simd default(none) shared(x, y, sz)
        for (size_t i = 0; i < sz; i++) {
            y[i] = x[i] + 2;
        }

        #pragma omp target
        {
            int* aux = x;
            x = y;
            y = aux;
        }
    }
};


int main() {
    obj test(SZ);
    for (size_t i = 0; i < SZ; i++) {
        test.x[i] = i;
    }
    
    #pragma omp target enter data map(to:test)
    #pragma omp target enter data map(to:test.x[0:SZ])
    #pragma omp target enter data map(to:test.y[0:SZ])

    test.computation();

    #pragma omp target exit data map(from:test.x[0:SZ])
    #pragma omp target exit data map(from:test.y[0:SZ])

    std::cout << "x: ";
    print_array(test.x, SZ);
    std::cout << "y: ";
    print_array(test.y, SZ);

    #ifdef _OPENMP
    std::cout << "num devices: " << omp_get_num_devices() << ", On device: " << omp_get_default_device() << "\n";
    #endif

    return 0;
}
