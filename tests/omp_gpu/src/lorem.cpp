#include <lorem.h>
#include <ctype.h>

lorem::lorem(size_t sz) : sz(sz) {
    x = new int[sz];
    y = new int[sz];
}

lorem::~lorem() {
    delete[] x;
    delete[] y;
}