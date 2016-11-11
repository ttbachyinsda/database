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
    int len;
    char k[20];
    index_key(const char *str = "", int len = 0) {
        memcpy(k, str, len);
        this->len = len;
    }
};

inline int keycmp(const index_key &a, const index_key &b) {
    int x = a.len - b.len;
    if (x == 0) {
        for (int i = 0; i < a.len; i++) {
            if (a.k[i] > b.k[i])
                return 1;
            else if (b.k[i] > a.k[i])
                return -1;
        }
    }
    else return 0;
    return 0;
}

#endif /* end of PREDEFINED_H */
