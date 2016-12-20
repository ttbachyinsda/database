#ifndef BPT_H
#define BPT_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
using std::vector;
using std::pair;
using std::cout;
using std::endl;
#include "bplus_node.h"
#include "predefined.h"
#include <fcntl.h>
#ifdef __linux
#define PARA O_RDWR
#elif __APPLE__
#define PARA O_RDWR
#else
#define PARA O_RDWR|O_BINARY
#endif

/* offsets */
#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + head_t::getSize()
#define SIZE_NO_CHILDREN leaf_node_t::getSize() - CHILDREN_NUM * sizeof(record_t)

/* head information of B+ tree */
struct head_t{
    int order;             /* `order` of B+ tree */
    int value_size;        /* size of value */
    int key_size;          /* size of key */
    int internal_node_num; /* how many internal nodes */
    int leaf_node_num;     /* how many leafs */
    int height;            /* height of tree (exclude leafs) */
    int slot;               /* where to store new block */
    int root_offset;        /* where is the root of internal nodes */
    int leaf_offset;        /* where is the first leaf */
    int last_leaf_offset;

    head_t() {order = value_size = key_size = internal_node_num = leaf_node_num = height = slot =
               root_offset = leaf_offset = last_leaf_offset = 0;}
    static int getSize() {return sizeof(head_t);}
};

/* internal nodes' index segment */

/* the encapulated B+ tree */
class bplus_tree {
   public:
    bplus_tree(const char *path, bool force_empty = false,
               bool multi_value = false, int keySize = 20);

    ~bplus_tree() {
        close_file();
    }

    /* abstract operations */
    int search(const index_key &key, index_value *value) const;
    int search_range(const index_key &left, const index_key &right, vector<pair<int, int>> *result) const;
    void search_greater_equal(const index_key &key, vector<pair<int, int>> *result);
    void search_less_equal(const index_key &key, vector<pair<int, int>> *result);
    int search_and_remove_multi(const index_key &key, int pagenum, int pageposition);
    int remove(const index_key &key);
    int insert(const index_key &key, index_value value);
    int update(const index_key &key, index_value value);
    int search_all(vector<pair<int, int>> *result);

    void set_MultiValue(bool multi_value) { this->multi_value = multi_value; }
    head_t get_head() const { return head; }

   private:
    char path[512];
    head_t head;
    bool multi_value;

    /* init empty tree */
    void init_from_empty(int keySize);

    /* find index */
    int search_index(const index_key &key) const;
    int search_index_l(const index_key &key) const;

    /* find leaf */
    int search_leaf_l(int index, const index_key &key) const;
    int search_leaf_l(const index_key &key) const {
        return search_leaf_l(search_index_l(key), key);
    }
    int search_leaf(int index, const index_key &key) const;
    int search_leaf(const index_key &key) const {
        return search_leaf(search_index(key), key);
    }

    /* remove internal node */
    void remove_from_index(int offset, internal_node_t &node,
                           const index_key &key);

    void remove_from_index_multi(int parent_off, int off, internal_node_t &parent, const index_key &key);

    /* insert into leaf without split */
    void insert_record_no_split(leaf_node_t *leaf, const index_key &key,
                                const index_value &value);

    /* add key to the internal node */
    void insert_index_keyo_index(int offset, const index_key &key, int value,
                             int after);
    void insert_index_keyo_index_no_split(internal_node_t &node, const index_key &key,
                                      int value, int prev_off);
    void update_parent_node(int parent, int offset, const index_key &key);

    /* change children's parent */
    void reset_index_children_parent(index_t *begin, index_t *end,
                                     int parent);

    template <class T>
    void node_create(int offset, T *node, T *next);

    template <class T>
    void node_remove(T *prev, T *node);

    /* multi-level file open/close */
    mutable FILE * fp = 0;
    mutable int fp_desc;
    mutable int fp_level;
    void open_file(const char *mode = "rb+") const {
        // `rb+` will make sure we can write everywhere without truncating
        // file
        if (fp_level == 0) {
            fp = fopen(path, mode);
            fclose(fp);
        }
        fp_desc = open(path, PARA);
        ++fp_level;
    }

    void close_file() const {
//        if (fp_level == 1) fclose(fp);
        close(fp_desc);
        --fp_level;
    }

    /* alloc from disk */
    int alloc(int size) {
        int slot = head.slot;
        head.slot += size;
        return slot;
    }

    int alloc(leaf_node_t *leaf) {
        leaf->n = 0;
        head.leaf_node_num++;
        head.last_leaf_offset = head.slot;
        return alloc(leaf_node_t::getSize());
    }

    int alloc(internal_node_t *node) {
        node->n = 1;
        head.internal_node_num++;
        return alloc(internal_node_t::getSize());
    }

    void unalloc(leaf_node_t *leaf, int offset) { --head.leaf_node_num; }

    void unalloc(internal_node_t *node, int offset) {
        --head.internal_node_num;
    }

    /* read block from disk */
    int block_read(void *block, int offset, int size) const {
        lseek(fp_desc, offset, SEEK_SET);
        read(fp_desc, block, size);

        return 0;
    }

    template <class T>
    int block_read(T *block, int offset) const {
        return block_read(block, offset, T::getSize());
    }

    /* write block to disk */
    int block_write(void *block, int offset, int size) const {
        lseek(fp_desc, offset, SEEK_SET);
        write(fp_desc, block, size);
        return 0;
    }

    template <class T>
    int block_write(T *block, int offset) const {
        return block_write(block, offset, T::getSize());
    }
};

#endif /* end of BPT_H */
