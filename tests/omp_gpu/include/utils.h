#ifndef UTILS_H
#define UTILS_H

namespace utils {
    template <typename T>
    T *get_dev_addr(T *host_addr) {
        unsigned long long dev_addr;
        #pragma omp target map(from: dev_addr)
        {
            dev_addr = (unsigned long long)host_addr;
        }

        return (T*)dev_addr;
    }
}

#endif