#ifndef LOREM_H
#define LOREM_H
#include <cstdlib>

class lorem {
public:
    size_t sz;
    int* x;
    int* y;
    lorem(size_t sz);

    ~lorem();
};

#endif