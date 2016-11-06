#include "bplus_tree.h"

#include <stdlib.h>

#include <algorithm>
#include <list>
using std::swap;
using std::binary_search;
using std::lower_bound;
using std::upper_bound;

namespace bpt {

/* custom compare operator for STL algorithms */
bool operator<(const key_t& l, const index_t& r) {
    return keycmp(l, r.key) < 0;
}
bool operator<(const index_t& l, const key_t& r) {
    return keycmp(l.key, r) < 0;
}
bool operator==(const key_t& l, const index_t& r) {
    return keycmp(l, r.key) == 0;
}
bool operator==(const index_t& l, const key_t& r) {
    return keycmp(l.key, r) == 0;
}
bool operator<(const key_t& l, const record_t& r) {
    return keycmp(l, r.key) < 0;
}
bool operator<(const record_t& l, const key_t& r) {
    return keycmp(l.key, r) < 0;
}
bool operator==(const key_t& l, const record_t& r) {
    return keycmp(l, r.key) == 0;
}
bool operator==(const record_t& l, const key_t& r) {
    return keycmp(l.key, r) == 0;
}

/* helper iterating function */
template <class T>
inline typename T::child_t begin(T& node) {
    return node.children;
}
template <class T>
inline typename T::child_t end(T& node) {
    return node.children + node.n;
}

/* helper searching function */
inline index_t* find(internal_node_t& node, const key_t& key) {
    return upper_bound(begin(node), end(node) - 1, key);
}
inline record_t* find(leaf_node_t& node, const key_t& key) {
    return lower_bound(begin(node), end(node), key);
}

bplus_tree::bplus_tree(const char* p, bool force_empty /*false*/,
                       bool multi_value /*false*/)
    : fp(NULL), fp_level(0) {
    bzero(path, sizeof(path));
    strcpy(path, p);
    this->multi_value = multi_value;

    if (!force_empty)
        // read tree from file
        if (block_read(&head, OFFSET_META) != 0) force_empty = true;

    if (force_empty) {
        open_file("w+");  // truncate file

        // create empty tree if file doesn't exist
        init_from_empty();
        close_file();
    }
}

int bplus_tree::search(const key_t& key, value_t* value) const {
    leaf_node_t leaf;
    block_read(&leaf, search_leaf(key));

    // finding the record
    record_t* record = find(leaf, key);
    if (record != leaf.children + leaf.n) {
        // always return the lower bound
        *value = record->value;

        return keycmp(record->key, key);
    } else {
        return -1;
    }
}

int bplus_tree::search_range(const key_t& left, const key_t& right,
                             value_t* values, size_t max) const {
    if (keycmp(left, right) > 0) return -1;

    off_t off_left = search_leaf_l(left);
    off_t off_right = search_leaf(right);
    off_t off = off_left;
    size_t i = 0;
    record_t *b, *e;

    leaf_node_t leaf;
    while (off != off_right && off != 0 && i < max) {
        block_read(&leaf, off);

        // start point
        if (off_left == off)
            b = find(leaf, left);
        else
            b = begin(leaf);

        // copy
        e = leaf.children + leaf.n;
        for (; b != e && i < max; ++b, ++i) values[i] = b->value;

        off = leaf.next;
    }

    // the last leaf
    if (i < max) {
        block_read(&leaf, off_right);

        b = find(leaf, left);
        e = upper_bound(begin(leaf), end(leaf), right);
        for (; b != e && i < max; ++b, ++i)
            values[i] = b->value;
    }

    return (int)i;
}

int bplus_tree::remove(const key_t& key) {
    internal_node_t parent;
    leaf_node_t leaf;

    // find parent node
    off_t parent_off = search_index(key);
    block_read(&parent, parent_off);

    // find current node
    index_t* where = find(parent, key);
    off_t offset = where->child;
    block_read(&leaf, offset);

    // verify
    if (!binary_search(begin(leaf), end(leaf), key)) return -1;

    size_t min_n = head.leaf_node_num == 1 ? 0 : head.order / 2;
    assert(leaf.n >= min_n && leaf.n <= head.order);

    // delete the key
    record_t* to_delete = find(leaf, key);
    std::copy(to_delete + 1, end(leaf), to_delete);
    leaf.n--;

    // merge or borrow
    if (leaf.n < min_n) {
        // first borrow from left
        bool borrowed = false;
        if (leaf.prev != 0) borrowed = borrow_key(false, leaf);

        // then borrow from right
        if (!borrowed && leaf.next != 0) borrowed = borrow_key(true, leaf);

        // finally we merge
        if (!borrowed) {
            assert(leaf.next != 0 || leaf.prev != 0);

            key_t index_key;

            if (where == end(parent) - 1) {
                // if leaf is last element then merge | prev | leaf |
                assert(leaf.prev != 0);
                leaf_node_t prev;
                block_read(&prev, leaf.prev);
                index_key = begin(prev)->key;

                merge_leafs(&prev, &leaf);
                node_remove(&prev, &leaf);
                block_write(&prev, leaf.prev);
            } else {
                // else merge | leaf | next |
                assert(leaf.next != 0);
                leaf_node_t next;
                block_read(&next, leaf.next);
                index_key = begin(leaf)->key;

                merge_leafs(&leaf, &next);
                node_remove(&leaf, &next);
                block_write(&leaf, offset);
            }

            // remove parent's key
            remove_from_index(parent_off, parent, index_key);
        } else {
            block_write(&leaf, offset);
        }
    } else {
        block_write(&leaf, offset);
    }

    return 0;
}

int bplus_tree::insert(const key_t& key, value_t value) {
    off_t parent = search_index(key);
    off_t offset = search_leaf(parent, key);
    leaf_node_t leaf;
    block_read(&leaf, offset);

    // check if we have the same key
    bool search_result = binary_search(begin(leaf), end(leaf), key);
    if (search_result && !multi_value)
        return 1;

    if (leaf.n == head.order) {
        // split when full

        // new sibling leaf
        leaf_node_t new_leaf;
        node_create(offset, &leaf, &new_leaf);

        // find even split point
        size_t point = leaf.n / 2;
        bool place_right = keycmp(key, leaf.children[point].key) > 0;
        if (place_right) ++point;

        // split
        std::copy(leaf.children + point, leaf.children + leaf.n,
                  new_leaf.children);
        new_leaf.n = leaf.n - point;
        leaf.n = point;

        // which part do we put the key
        if (place_right)
            insert_record_no_split(&new_leaf, key, value);
        else
            insert_record_no_split(&leaf, key, value);

        // save leafs
        block_write(&leaf, offset);
        block_write(&new_leaf, leaf.next);

        // insert new index key
        insert_key_to_index(parent, new_leaf.children[0].key, offset,
                            leaf.next);
    } else {
        insert_record_no_split(&leaf, key, value);
        block_write(&leaf, offset);
    }

    return 0;
}

int bplus_tree::update(const key_t& key, value_t value) {
    off_t offset = search_leaf(key);
    leaf_node_t leaf;
    block_read(&leaf, offset);

    record_t* record = find(leaf, key);
    if (record != leaf.children + leaf.n)
        if (keycmp(key, record->key) == 0) {
            record->value = value;
            block_write(&leaf, offset);

            return 0;
        } else {
            return 1;
        }
    else
        return -1;
}

void bplus_tree::remove_from_index(off_t offset, internal_node_t& node,
                                   const key_t& key) {
    size_t min_n = head.root_offset == offset ? 1 : head.order / 2;
    assert(node.n >= min_n && node.n <= head.order);

    // remove key
    key_t index_key = begin(node)->key;
    index_t* to_delete = find(node, key);
    if (to_delete != end(node)) {
        (to_delete + 1)->child = to_delete->child;
        std::copy(to_delete + 1, end(node), to_delete);
    }
    node.n--;

    // remove to only one key
    if (node.n == 1 && head.root_offset == offset &&
        head.internal_node_num != 1) {
        unalloc(&node, head.root_offset);
        head.height--;
        head.root_offset = node.children[0].child;
        block_write(&head, OFFSET_META);
        return;
    }

    // merge or borrow
    if (node.n < min_n) {
        internal_node_t parent;
        block_read(&parent, node.parent);

        // first borrow from left
        bool borrowed = false;
        if (offset != begin(parent)->child)
            borrowed = borrow_key(false, node, offset);

        // then borrow from right
        if (!borrowed && offset != (end(parent) - 1)->child)
            borrowed = borrow_key(true, node, offset);

        // finally we merge
        if (!borrowed) {
            assert(node.next != 0 || node.prev != 0);

            if (offset == (end(parent) - 1)->child) {
                // if leaf is last element then merge | prev | leaf |
                assert(node.prev != 0);
                internal_node_t prev;
                block_read(&prev, node.prev);

                // merge
                index_t* where = find(parent, begin(prev)->key);
                reset_index_children_parent(begin(node), end(node), node.prev);
                merge_keys(where, prev, node);
                block_write(&prev, node.prev);
            } else {
                // else merge | leaf | next |
                assert(node.next != 0);
                internal_node_t next;
                block_read(&next, node.next);

                // merge
                index_t* where = find(parent, index_key);
                reset_index_children_parent(begin(next), end(next), offset);
                merge_keys(where, node, next);
                block_write(&node, offset);
            }

            // remove parent's key
            remove_from_index(node.parent, parent, index_key);
        } else {
            block_write(&node, offset);
        }
    } else {
        block_write(&node, offset);
    }
}

bool bplus_tree::borrow_key(bool from_right, internal_node_t& borrower,
                            off_t offset) {
    typedef typename internal_node_t::child_t child_t;

    off_t lender_off = from_right ? borrower.next : borrower.prev;
    internal_node_t lender;
    block_read(&lender, lender_off);

    assert(lender.n >= head.order / 2);
    if (lender.n != head.order / 2) {
        child_t where_to_lend, where_to_put;

        internal_node_t parent;

        // swap keys, draw on paper to see why
        if (from_right) {
            where_to_lend = begin(lender);
            where_to_put = end(borrower);

            block_read(&parent, borrower.parent);
            child_t where = lower_bound(begin(parent), end(parent) - 1,
                                        (end(borrower) - 1)->key);
            where->key = where_to_lend->key;
            block_write(&parent, borrower.parent);
        } else {
            where_to_lend = end(lender) - 1;
            where_to_put = begin(borrower);

            block_read(&parent, lender.parent);
            child_t where = find(parent, begin(lender)->key);
            where_to_put->key = where->key;
            where->key = (where_to_lend - 1)->key;
            block_write(&parent, lender.parent);
        }

        // store
        std::copy_backward(where_to_put, end(borrower), end(borrower) + 1);
        *where_to_put = *where_to_lend;
        borrower.n++;

        // erase
        reset_index_children_parent(where_to_lend, where_to_lend + 1, offset);
        std::copy(where_to_lend + 1, end(lender), where_to_lend);
        lender.n--;
        block_write(&lender, lender_off);
        return true;
    }

    return false;
}

bool bplus_tree::borrow_key(bool from_right, leaf_node_t& borrower) {
    off_t lender_off = from_right ? borrower.next : borrower.prev;
    leaf_node_t lender;
    block_read(&lender, lender_off);

    assert(lender.n >= head.order / 2);
    if (lender.n != head.order / 2) {
        typename leaf_node_t::child_t where_to_lend, where_to_put;

        // decide offset and update parent's index key
        if (from_right) {
            where_to_lend = begin(lender);
            where_to_put = end(borrower);
            change_parent_child(borrower.parent, begin(borrower)->key,
                                lender.children[1].key);
        } else {
            where_to_lend = end(lender) - 1;
            where_to_put = begin(borrower);
            change_parent_child(lender.parent, begin(lender)->key,
                                where_to_lend->key);
        }

        // store
        std::copy_backward(where_to_put, end(borrower), end(borrower) + 1);
        *where_to_put = *where_to_lend;
        borrower.n++;

        // erase
        std::copy(where_to_lend + 1, end(lender), where_to_lend);
        lender.n--;
        block_write(&lender, lender_off);
        return true;
    }

    return false;
}

void bplus_tree::change_parent_child(off_t parent, const key_t& o,
                                     const key_t& n) {
    internal_node_t node;
    block_read(&node, parent);

    index_t* w = find(node, o);
    assert(w != node.children + node.n);

    w->key = n;
    block_write(&node, parent);
    if (w == node.children + node.n - 1) {
        change_parent_child(node.parent, o, n);
    }
}

void bplus_tree::merge_leafs(leaf_node_t* left, leaf_node_t* right) {
    std::copy(begin(*right), end(*right), end(*left));
    left->n += right->n;
}

void bplus_tree::merge_keys(index_t* where, internal_node_t& node,
                            internal_node_t& next) {
    //(end(node) - 1)->key = where->key;
    // where->key = (end(next) - 1)->key;
    std::copy(begin(next), end(next), end(node));
    node.n += next.n;
    node_remove(&node, &next);
}

void bplus_tree::insert_record_no_split(leaf_node_t* leaf, const key_t& key,
                                        const value_t& value) {
    record_t* where = upper_bound(begin(*leaf), end(*leaf), key);
    std::copy_backward(where, end(*leaf), end(*leaf) + 1);

    where->key = key;
    where->value = value;
    leaf->n++;
}

void bplus_tree::insert_key_to_index(off_t offset, const key_t& key, off_t old,
                                     off_t after) {
    if (offset == 0) {
        // create new root node
        internal_node_t root;
        root.next = root.prev = root.parent = 0;
        head.root_offset = alloc(&root);
        head.height++;

        // insert `old` and `after`
        root.n = 2;
        root.children[0].key = key;
        root.children[0].child = old;
        root.children[1].child = after;

        block_write(&head, OFFSET_META);
        block_write(&root, head.root_offset);

        // update children's parent
        reset_index_children_parent(begin(root), end(root), head.root_offset);
        return;
    }

    internal_node_t node;
    block_read(&node, offset);
    assert(node.n <= head.order);

    if (node.n == head.order) {
        // split when full

        internal_node_t new_node;
        node_create(offset, &node, &new_node);

        // find even split point
        size_t point = (node.n - 1) / 2;
        bool place_right = keycmp(key, node.children[point].key) > 0;
        if (place_right) ++point;

        // prevent the `key` being the right `middle_key`
        // example: insert 48 into |42|45| 6|    |
        if (place_right && keycmp(key, node.children[point].key) < 0) point--;

        key_t middle_key = node.children[point].key;

        // split
        std::copy(begin(node) + point + 1, end(node), begin(new_node));
        new_node.n = node.n - point - 1;
        node.n = point + 1;

        // put the new key
        if (place_right)
            insert_key_to_index_no_split(new_node, key, after);
        else
            insert_key_to_index_no_split(node, key, after);

        block_write(&node, offset);
        block_write(&new_node, node.next);

        // update children's parent
        reset_index_children_parent(begin(new_node), end(new_node), node.next);

        // give the middle key to the parent
        // note: middle key's child is reserved
        insert_key_to_index(node.parent, middle_key, offset, node.next);
    } else {
        insert_key_to_index_no_split(node, key, after);
        block_write(&node, offset);
    }
}

void bplus_tree::insert_key_to_index_no_split(internal_node_t& node,
                                              const key_t& key, off_t value) {
    index_t* where = upper_bound(begin(node), end(node) - 1, key);

    // move later index forward
    std::copy_backward(where, end(node), end(node) + 1);

    // insert this key
    where->key = key;
    where->child = (where + 1)->child;
    (where + 1)->child = value;

    node.n++;
}

void bplus_tree::reset_index_children_parent(index_t* begin, index_t* end,
                                             off_t parent) {
    // this function can change both internal_node_t and leaf_node_t's parent
    // field, but we should ensure that:
    // 1. sizeof(internal_node_t) <= sizeof(leaf_node_t)
    // 2. parent field is placed in the beginning and have same size
    internal_node_t node;
    while (begin != end) {
        block_read(&node, begin->child);
        node.parent = parent;
        block_write(&node, begin->child, SIZE_NO_CHILDREN);
        ++begin;
    }
}

off_t bplus_tree::search_index(const key_t& key) const {
    off_t org = head.root_offset;
    int height = head.height;
    while (height > 1) {
        internal_node_t node;
        block_read(&node, org);

        index_t* i = upper_bound(begin(node), end(node) - 1, key);
        org = i->child;
        --height;
    }

    return org;
}

    off_t bplus_tree::search_index_l(const key_t &key) const {
        off_t org = head.root_offset;
        int height = head.height;
        while (height > 1) {
            internal_node_t node;
            block_read(&node, org);

            index_t* i = lower_bound(begin(node), end(node) - 1, key);
            org = i->child;
            --height;
        }

        return org;
    }

off_t bplus_tree::search_leaf(off_t index, const key_t& key) const {
    internal_node_t node;
    block_read(&node, index);

    index_t* i = upper_bound(begin(node), end(node) - 1, key);
    return i->child;
}

    off_t bplus_tree::search_leaf_l(off_t index, const key_t& key) const {
        internal_node_t node;
        block_read(&node, index);

        index_t* i = lower_bound(begin(node), end(node) - 1, key);
        return i->child;
    }

template <class T>
void bplus_tree::node_create(off_t offset, T* node, T* next) {
    // new sibling node
    next->parent = node->parent;
    next->next = node->next;
    next->prev = offset;
    node->next = alloc(next);
    // update next node's prev
    if (next->next != 0) {
        T old_next;
        block_read(&old_next, next->next, SIZE_NO_CHILDREN);
        old_next.prev = node->next;
        block_write(&old_next, next->next, SIZE_NO_CHILDREN);
    }
    block_write(&head, OFFSET_META);
}

template <class T>
void bplus_tree::node_remove(T* prev, T* node) {
    unalloc(node, prev->next);
    prev->next = node->next;
    if (node->next != 0) {
        T next;
        block_read(&next, node->next, SIZE_NO_CHILDREN);
        next.prev = node->prev;
        block_write(&next, node->next, SIZE_NO_CHILDREN);
    }
    block_write(&head, OFFSET_META);
}

void bplus_tree::init_from_empty() {
    // init default head
    bzero(&head, sizeof(head_t));
    head.order = CHILDREN_NUM;
    head.value_size = sizeof(value_t);
    head.key_size = sizeof(key_t);
    head.height = 1;
    head.slot = OFFSET_BLOCK;

    // init root node
    internal_node_t root;
    root.next = root.prev = root.parent = 0;
    head.root_offset = alloc(&root);

    // init empty leaf
    leaf_node_t leaf;
    leaf.next = leaf.prev = 0;
    leaf.parent = head.root_offset;
    head.leaf_offset = root.children[0].child = alloc(&leaf);

    // save
    block_write(&head, OFFSET_META);
    block_write(&root, head.root_offset);
    block_write(&leaf, root.children[0].child);
}
}
