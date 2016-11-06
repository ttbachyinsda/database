#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <string.h>

/* predefined B+ info */
#define CHILDREN_NUM 20

/* key/value type */
struct index_value {
    int pagenum;
    int pageposition;

    index_value(int pagenum = 0, int pageposition = 0) {
        this->pagenum = pagenum;
        this->pageposition = pageposition;
    }
};
struct index_key {
    char k[256];

    index_key(const char *str = "") {
        bzero(k, sizeof(k));
        strcpy(k, str);
    }
};

inline int keycmp(const index_key &a, const index_key &b) {
    int x = strlen(a.k) - strlen(b.k);
    return x == 0 ? strcmp(a.k, b.k) : x;
}

#endif /* end of PREDEFINED_H */
