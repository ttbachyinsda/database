//
// Created by JerryJohn on 2016/10/28.
//

#ifndef DBINDEX_BPLUS_NODE_H
#define DBINDEX_BPLUS_NODE_H

#include <stddef.h>
#include <stdio.h>
#include "predefined.h"

struct bplus_node {
    off_t parent; /* parent node offset */
    off_t next;
    off_t prev;
    size_t n; /* num of children */
};

struct index_t {
    index_key key;
    off_t child; /* child's offset */
};

struct record_t {
    index_key key;

    index_value value;
};

struct internal_node_t : public bplus_node {
    typedef index_t *child_t;

    index_t children[CHILDREN_NUM];
};

struct leaf_node_t : public bplus_node {
    typedef record_t *child_t;

    record_t children[CHILDREN_NUM];
};

#endif  // DBINDEX_BPLUS_NODE_H
