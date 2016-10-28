#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <string.h>

namespace bpt {

/* predefined B+ info */
#define CHILDREN_NUM 20

/* key/value type */
struct value_t {
  char v[32];

  value_t(const char *str = "") {
    bzero(v, sizeof(v));
    strcpy(v, str);
  }
};
struct key_t {
  char k[32];

  key_t(const char *str = "") {
    bzero(k, sizeof(k));
    strcpy(k, str);
  }
};

inline int keycmp(const key_t &a, const key_t &b) {
  int x = strlen(a.k) - strlen(b.k);
  return x == 0 ? strcmp(a.k, b.k) : x;
}

//#define OPERATOR_KEYCMP(type)                                                  \
//  bool operator<(const key_t &l, const type &r) {                              \
//    return keycmp(l, r.key) < 0;                                               \
//  }                                                                            \
//  bool operator<(const type &l, const key_t &r) {                              \
//    return keycmp(l.key, r) < 0;                                               \
//  }                                                                            \
//  bool operator==(const key_t &l, const type &r) {                             \
//    return keycmp(l, r.key) == 0;                                              \
//  }                                                                            \
//  bool operator==(const type &l, const key_t &r) {                             \
//    return keycmp(l.key, r) == 0;                                              \
//  }
}

#endif /* end of PREDEFINED_H */
