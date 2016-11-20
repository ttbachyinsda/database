//
// Created by JerryJohn on 2016/10/28.
//

#ifndef DBINDEX_BPLUS_NODE_H
#define DBINDEX_BPLUS_NODE_H

#include <stddef.h>
#include <stdio.h>
#include "predefined.h"

//struct bplus_node {
//    int parent; /* parent node offset */
//    int next;
//    int prev;
//    int n; /* num of children */
//};

struct index_t {
    index_key key;
    int child; /* child's offset */

    static int getSize() {return index_key::getSize() + sizeof(int);}
};

struct record_t {
    index_key key;

    index_value value;
    static int getSize() {return index_key::getSize() + index_value::getSize();}
};

struct internal_node_t {
    typedef index_t *child_t;

    internal_node_t() {
        parent = next = prev = n = 0;
    }

    int parent; /* parent node offset */
    int next;
    int prev;
    int n; /* num of children */

    index_t children[CHILDREN_NUM];

    static int getSize() {return 4 * sizeof(int) + CHILDREN_NUM*sizeof(index_t);}
};

struct leaf_node_t {
    typedef record_t *child_t;

    leaf_node_t() {
        parent = next = prev = n = 0;
    }

    int parent; /* parent node offset */
    int next;
    int prev;
    int n; /* num of children */

    record_t children[CHILDREN_NUM];

    static int getSize() {return 4 * sizeof(int) + CHILDREN_NUM*sizeof(record_t);}
};

#endif  // DBINDEX_BPLUS_NODE_H
