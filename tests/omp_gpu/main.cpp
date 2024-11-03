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

struct obj {
public:
    int* _x;
    int* _y;
    size_t _sz;

    obj(size_t sz) {
        _sz = sz;
        _x = new int[sz];
        _y = new int[sz];

        #pragma omp target enter data map(alloc: _x[0:_sz], _y[0:_sz], _sz)
    }

    ~obj() {
        #pragma omp target exit data map(release: _x[0:_sz], _y[0:_sz], _sz)

        delete[] _x;
        delete[] _y;
    }

};

void computation(int *&x, int *&y, size_t &sz) {
    #pragma omp target teams distribute parallel for simd
    for (size_t i = 0; i < sz; i++) {
        y[i] = x[i] + 10;
    }

    std::swap<int*>(x, y);
}


int main() {
    obj test(SZ);
    for (size_t i = 0; i < SZ; i++) {
        test._x[i] = i;
    }
    
    #pragma omp target update to(test._x[0:SZ], test._sz)
    
    // #pragma omp target update to(test._x[0:SZ])
    computation(test._x, test._y, test._sz);
    // #pragma omp target update to(test._x[0:SZ])
    computation(test._x, test._y, test._sz);
    // #pragma omp target update to(test._x[0:SZ])
    computation(test._x, test._y, test._sz);
    // #pragma omp target update to(test._x[0:SZ])
    computation(test._x, test._y, test._sz);

    #pragma omp target update from(test._x[0:SZ], test._y[0:SZ])

    std::cout << "x: ";
    print_array(test._x, SZ);
    std::cout << "y: ";
    print_array(test._y, SZ);

    #ifdef _OPENMP
    std::cout << "num devices: " << omp_get_num_devices() << ", On device: " << omp_get_default_device() << "\n";
    #endif

    return 0;
}
