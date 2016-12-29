#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <string.h>
#include "comparealgo.h"

/* predefined B+ info */
#define CHILDREN_NUM 200

/* key/value type */
struct index_value {
    int pagenum;
    int pageposition;

    static int getSize() {return 2 * sizeof(int);}

    index_value(int pagenum = 0, int pageposition = 0) {
        this->pagenum = pagenum;
        this->pageposition = pageposition;
    }
};
struct index_key {
    int len;
    char k[20];

    static int getSize() {return sizeof(index_key);}

    index_key(const char *str = "", int len = 0) {
        memset(k, 0, 20);
        memcpy(k, str, len);
        this->len = len;
    }
};

inline int keycmp(const index_key &a, const index_key &b, CompareAlgo *cmp) {
    return cmp->strcmp(a.k, a.len, b.k, b.len);
}

#endif /* end of PREDEFINED_H */
