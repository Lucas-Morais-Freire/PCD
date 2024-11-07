#ifndef IPSUM_H
#define IPSUM_H
#include <cstdlib>
#include <lorem.h>

class ipsum {
    int* z;
    size_t sz;
public:
    ipsum(size_t sz);

    int* get_z() { return z; }

    void target_enter(lorem& lor) const;

    void target_exit(lorem& lor) const;

    void target_update_to() const;
    
    void target_update_from(lorem& lor);

    void computation(lorem& lor);

    ~ipsum();
};

#endif