#ifndef BPT_H
#define BPT_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
#include "bplus_node.h"
#include "predefined.h"

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

    head_t() {order = value_size = key_size = internal_node_num = leaf_node_num = height = slot =
               root_offset = leaf_offset = 0;}
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
    int search_range(const index_key &left, const index_key &right, index_value *values,
                     int max) const;
    int remove(const index_key &key);
    int insert(const index_key &key, index_value value);
    int update(const index_key &key, index_value value);

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

    /* borrow one key from other internal node */
    bool borrow_key(bool from_right, internal_node_t &borrower, int offset);

    /* borrow one record from other leaf */
    bool borrow_key(bool from_right, leaf_node_t &borrower);

    /* change one's parent key to another key */
    void change_parent_child(int parent, const index_key &o, const index_key &n);

    /* merge right leaf to left leaf */
    void merge_leafs(leaf_node_t *left, leaf_node_t *right);

    void merge_keys(index_t *where, internal_node_t &left,
                    internal_node_t &right);

    /* insert into leaf without split */
    void insert_record_no_split(leaf_node_t *leaf, const index_key &key,
                                const index_value &value);

    /* add key to the internal node */
    void insert_index_keyo_index(int offset, const index_key &key, int value,
                             int after);
    void insert_index_keyo_index_no_split(internal_node_t &node, const index_key &key,
                                      int value);

    /* change children's parent */
    void reset_index_children_parent(index_t *begin, index_t *end,
                                     int parent);

    template <class T>
    void node_create(int offset, T *node, T *next);

    template <class T>
    void node_remove(T *prev, T *node);

    /* multi-level file open/close */
    mutable FILE * fp = 0;
    mutable int fp_level;
    void open_file(const char *mode = "rb+") const {
        // `rb+` will make sure we can write everywhere without truncating
        // file
        if (fp_level == 0) fp = fopen(path, mode);

        ++fp_level;
    }

    void close_file() const {
        if (fp_level == 1) fclose(fp);

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
        fseek(fp, offset, SEEK_SET);
        int rd = fread(block, size, 1, fp);

        return rd - 1;
    }

    template <class T>
    int block_read(T *block, int offset) const {
        return block_read(block, offset, T::getSize());
    }

    /* write block to disk */
    int block_write(void *block, int offset, int size) const {
        fseek(fp, offset, SEEK_SET);
        int wd = fwrite(block, size, 1, fp);
        return wd - 1;
    }

    template <class T>
    int block_write(T *block, int offset) const {
        return block_write(block, offset, T::getSize());
    }
};

#endif /* end of BPT_H */
