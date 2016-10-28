//
// Created by JerryJohn on 2016/10/28.
//

#ifndef DBINDEX_BPLUS_NODE_H
#define DBINDEX_BPLUS_NODE_H

#include <stddef.h>
#include <stdio.h>
#include "predefined.h"

namespace bpt {

//struct bplus_node {
//   public:
//    off_t parent; /* parent node offset */
//    off_t next;
//    off_t prev;
//    size_t n; /* how many children */
//};

struct index_t {
    key_t key;
    off_t child; /* child's offset */
};

struct record_t {
    key_t key;

    value_t value;
};

struct internal_node_t {
    typedef index_t *child_t;

    off_t parent; /* parent node offset */
    off_t next;
    off_t prev;
    size_t n; /* how many children */
    index_t children[CHILDREN_NUM];
};

struct leaf_node_t {
    typedef record_t *child_t;

    off_t parent; /* parent node offset */
    off_t next;
    off_t prev;
    size_t n; /* how many children */
    record_t children[CHILDREN_NUM];
};
}

#endif  // DBINDEX_BPLUS_NODE_H
