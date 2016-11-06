#ifndef BPT_H
#define BPT_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "bplus_node.h"
#include "predefined.h"

/* offsets */
#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + sizeof(head_t)
#define SIZE_NO_CHILDREN sizeof(leaf_node_t) - CHILDREN_NUM * sizeof(record_t)

/* head information of B+ tree */
typedef struct {
    size_t order;             /* `order` of B+ tree */
    size_t value_size;        /* size of value */
    size_t key_size;          /* size of key */
    size_t internal_node_num; /* how many internal nodes */
    size_t leaf_node_num;     /* how many leafs */
    size_t height;            /* height of tree (exclude leafs) */
    off_t slot;               /* where to store new block */
    off_t root_offset;        /* where is the root of internal nodes */
    off_t leaf_offset;        /* where is the first leaf */
} head_t;

/* internal nodes' index segment */

/* the encapulated B+ tree */
class bplus_tree {
   public:
    bplus_tree(const char *path, bool force_empty = false,
               bool multi_value = false);

    ~bplus_tree() {
        fclose(fp);
    }

    /* abstract operations */
    int search(const index_key &key, index_value *value) const;
    int search_range(const index_key &left, const index_key &right, index_value *values,
                     size_t max) const;
    int remove(const index_key &key);
    int insert(const index_key &key, index_value value);
    int update(const index_key &key, index_value value);

    void set_MultiValue(bool multi_value) { this->multi_value = multi_value; };
    head_t get_head() const { return head; };

   private:
    char path[512];
    head_t head;
    bool multi_value;

    /* init empty tree */
    void init_from_empty();

    /* find index */
    off_t search_index(const index_key &key) const;
    off_t search_index_l(const index_key &key) const;

    /* find leaf */
    off_t search_leaf_l(off_t index, const index_key &key) const;
    off_t search_leaf_l(const index_key &key) const {
        return search_leaf_l(search_index_l(key), key);
    }
    off_t search_leaf(off_t index, const index_key &key) const;
    off_t search_leaf(const index_key &key) const {
        return search_leaf(search_index(key), key);
    }

    /* remove internal node */
    void remove_from_index(off_t offset, internal_node_t &node,
                           const index_key &key);

    /* borrow one key from other internal node */
    bool borrow_key(bool from_right, internal_node_t &borrower, off_t offset);

    /* borrow one record from other leaf */
    bool borrow_key(bool from_right, leaf_node_t &borrower);

    /* change one's parent key to another key */
    void change_parent_child(off_t parent, const index_key &o, const index_key &n);

    /* merge right leaf to left leaf */
    void merge_leafs(leaf_node_t *left, leaf_node_t *right);

    void merge_keys(index_t *where, internal_node_t &left,
                    internal_node_t &right);

    /* insert into leaf without split */
    void insert_record_no_split(leaf_node_t *leaf, const index_key &key,
                                const index_value &value);

    /* add key to the internal node */
    void insert_index_keyo_index(off_t offset, const index_key &key, off_t value,
                             off_t after);
    void insert_index_keyo_index_no_split(internal_node_t &node, const index_key &key,
                                      off_t value);

    /* change children's parent */
    void reset_index_children_parent(index_t *begin, index_t *end,
                                     off_t parent);

    template <class T>
    void node_create(off_t offset, T *node, T *next);

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
    off_t alloc(size_t size) {
        off_t slot = head.slot;
        head.slot += size;
        return slot;
    }

    off_t alloc(leaf_node_t *leaf) {
        leaf->n = 0;
        head.leaf_node_num++;
        return alloc(sizeof(leaf_node_t));
    }

    off_t alloc(internal_node_t *node) {
        node->n = 1;
        head.internal_node_num++;
        return alloc(sizeof(internal_node_t));
    }

    void unalloc(leaf_node_t *leaf, off_t offset) { --head.leaf_node_num; }

    void unalloc(internal_node_t *node, off_t offset) {
        --head.internal_node_num;
    }

    /* read block from disk */
    int block_read(void *block, off_t offset, size_t size) const {
        open_file();
        fseek(fp, offset, SEEK_SET);
        size_t rd = fread(block, size, 1, fp);
        close_file();

        return rd - 1;
    }

    template <class T>
    int block_read(T *block, off_t offset) const {
        return block_read(block, offset, sizeof(T));
    }

    /* write block to disk */
    int block_write(void *block, off_t offset, size_t size) const {
        open_file();
        fseek(fp, offset, SEEK_SET);
        size_t wd = fwrite(block, size, 1, fp);
        close_file();

        return wd - 1;
    }

    template <class T>
    int block_write(T *block, off_t offset) const {
        return block_write(block, offset, sizeof(T));
    }
};

#endif /* end of BPT_H */
