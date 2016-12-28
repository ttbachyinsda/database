#include "bplus_tree.h"

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <list>
using std::cout;
using std::endl;
using std::swap;
using std::binary_search;
using std::lower_bound;
using std::upper_bound;

/* custom compare operator for STL algorithms */
bool operator<(const index_key& l, const index_t& r) {
    return keycmp(l, r.key) < 0;
}
bool operator<(const index_t& l, const index_key& r) {
    return keycmp(l.key, r) < 0;
}
bool operator==(const index_key& l, const index_t& r) {
    return keycmp(l, r.key) == 0;
}
bool operator==(const index_t& l, const index_key& r) {
    return keycmp(l.key, r) == 0;
}
bool operator<(const index_key& l, const record_t& r) {
    return keycmp(l, r.key) < 0;
}
bool operator<(const record_t& l, const index_key& r) {
    return keycmp(l.key, r) < 0;
}
bool operator==(const index_key& l, const record_t& r) {
    return keycmp(l, r.key) == 0;
}
bool operator==(const record_t& l, const index_key& r) {
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

int counter = 0;

/* helper searching function */
inline index_t* find(internal_node_t& node, const index_key& key) {
    index_t* temp = lower_bound(begin(node), end(node), key);
    if (temp - begin(node) >= node.n && node.n > 0)
        temp = end(node) - 1;
    if ( key < *temp && temp > begin(node))
        temp = temp - 1;
    return temp;
}
inline record_t* find(leaf_node_t& node, const index_key& key) {
    record_t* temp = lower_bound(begin(node), end(node), key);
    if (temp - begin(node) >= node.n && node.n > 0)
        temp = end(node) - 1;
    if ( key < *temp && temp > begin(node))
        temp = temp - 1;
    return temp;
}

bplus_tree::bplus_tree(const char* p, bool force_empty /*false*/,
                       bool multi_value /*false*/, int keySize /*20*/)
    : fp(NULL), fp_level(0) {
    memset(path,0, sizeof(path));
    strcpy(path, p);
    this->multi_value = multi_value;

    if (!force_empty) {
        // read tree from file
        open_file();
        if (block_read(&head, OFFSET_META) != 0) force_empty = true;
    }

    if (force_empty) {
        open_file("w+");  // truncate file

        // create empty tree if file doesn't exist
        init_from_empty(0);
//        close_file();
    }
}

int bplus_tree::search(const index_key& key, index_value* value) const {
    leaf_node_t leaf;
    block_read(&leaf, search_leaf(key));

    // finding the record
    record_t* record = find(leaf, key);
    if (record != leaf.children + leaf.n) {
        // always return the lower bound
        *value = record->value;
        int result = keycmp(record->key, key);
        if (result != 0)
            return -1;
        else return 0;
    } else {
        return -1;
    }
}

int bplus_tree::search_and_remove_multi(const index_key &key, int pagenum, int pageposition) {
    int off_left = search_leaf_l(key);
    int off_right = search_leaf(key);
    int off = off_left;
    record_t *b, *e;

    leaf_node_t leaf;
    while (off != off_right && off != 0) {
        block_read(&leaf, off);

        // start point
        if (off_left == off)
            b = find(leaf, key);
        else
            b = begin(leaf);

        if (keycmp(b->key, key) != 0)
            b++;

        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b) {
            if (b->value.pagenum == pagenum && b->value.pageposition == pageposition) {
                std::copy(b + 1, end(leaf), b);
                leaf.n--;

                // merge or borrow
                if (leaf.n == 0) {
                    leaf_node_t prev, next;
                    if (leaf.prev != 0) {
                        block_read(&prev, leaf.prev);
                        prev.next = leaf.next;
                        block_write(&prev, leaf.prev);
                    }

                    if (leaf.next != 0) {
                        block_read(&next, leaf.next);
                        next.prev = leaf.prev;
                        block_write(&next, leaf.next);
                    }
                    internal_node_t parent;
                    block_read(&parent, leaf.parent);
                    remove_from_index_multi(leaf.parent, off, parent, key);
                } else {
                    block_write(&leaf, off);
                    update_parent_node(leaf.parent, off, leaf.children[0].key);
                }
                return 0;
            }
        }

        off = leaf.next;
    }

    // the last leaf
    block_read(&leaf, off_right);

    b = find(leaf, key);
    if (keycmp(b->key, key) != 0)
        b++;
    e = upper_bound(begin(leaf), end(leaf), key);

    for (; b != e; ++b)
        if (b->value.pagenum == pagenum && b->value.pageposition == pageposition) {
            std::copy(b + 1, end(leaf), b);
            leaf.n--;

            // merge or borrow
            if (leaf.n == 0) {
                leaf_node_t prev, next;
                if (leaf.prev != 0) {
                    block_read(&prev, leaf.prev);
                    prev.next = leaf.next;
                    block_write(&prev, leaf.prev);
                }

                if (leaf.next != 0) {
                    block_read(&next, leaf.next);
                    next.prev = leaf.prev;
                    block_write(&next, leaf.next);
                }
                internal_node_t parent;
                block_read(&parent, leaf.parent);
                remove_from_index_multi(leaf.parent, off, parent, key);
            } else {
                block_write(&leaf, off);
                update_parent_node(leaf.parent, off, leaf.children[0].key);
            }
            return 0;
        }

    return -1;
}

void bplus_tree::remove_from_index_multi(int parent_off, int off, internal_node_t &parent, const index_key &key) {
    // remove key
    index_t* to_delete;
    for (int i = 0; i < parent.n; i++)
        if (parent.children[i].child == off) {
            to_delete = parent.children + i;
            break;
        }

    if (to_delete + 1 < parent.children + parent.n) {
        (to_delete + 1)->child = to_delete->child;
        std::copy(to_delete + 1, end(parent), to_delete);
    }
    parent.n--;

    // remove to only one key
    if (parent.n == 0 && head.root_offset == off &&
        head.internal_node_num != 1) {
        unalloc(&parent, head.root_offset);
        head.height--;
        head.root_offset = parent.children[0].child;
        block_write(&head, OFFSET_META);
        return;
    }

    // merge or borrow
    if (parent.n == 0) {
        internal_node_t pparent;
        block_read(&pparent, parent.parent);
        remove_from_index_multi(parent.parent, parent_off, pparent, key);
    } else {
        block_write(&parent, off);
        update_parent_node(parent.parent, off, parent.children[0].key);
    }

    return;
}

void bplus_tree::search_greater_equal(const index_key &key, vector<pair<int, int> > *result) {
    int off_left = search_leaf_l(key);

    int off = off_left;
    record_t *b, *e;

    leaf_node_t leaf;
    while (off != 0) {
        block_read(&leaf, off);

        // start point
        if (off_left == off)
            b = find(leaf, key);
        else
            b = begin(leaf);

        if (keycmp(b->key, key) < 0)
            b++;

        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));

        off = leaf.next;
    }

    return;
}

void bplus_tree::search_less_equal(const index_key &key, vector<pair<int, int> > *result) {
    int off_right = search_leaf(key);

    int off = off_right;
    record_t *b, *e;

    leaf_node_t leaf;
    while (off != 0) {
        block_read(&leaf, off);

        // start point
        b = begin(leaf);
        // copy
        if (off == off_right)
            e = upper_bound(begin(leaf), end(leaf), key);
        else
            e = leaf.children + leaf.n;

        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));

        off = leaf.prev;
    }

    return;
}

int bplus_tree::search_range(const index_key& left, const index_key& right,
                             vector<pair<int, int>> *result) const {
    if (keycmp(left, right) > 0) return -1;

    int off_left = search_leaf_l(left);
    int off_right = search_leaf(right);
    int off = off_left;
    record_t *b, *e;

    leaf_node_t leaf;
    while (off != off_right && off != 0) {
        block_read(&leaf, off);

        // start point
        if (off_left == off)
            b = find(leaf, left);
        else
            b = begin(leaf);

        if (keycmp(b->key, left) != 0)
            b++;

        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));

        off = leaf.next;
    }

    // the last leaf
    block_read(&leaf, off_right);

    b = find(leaf, left);
    if (keycmp(b->key, left) != 0)
        b++;
    if (b < leaf.children)
        b = leaf.children;
    e = upper_bound(begin(leaf), end(leaf), right);

    for (; b < e; ++b)
        result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));

    return result->size()==0?-1:0;
}

int bplus_tree::search_all(vector<pair<int, int> > *result) {
    int off_left = head.leaf_offset;
    int off = off_left;

    leaf_node_t leaf;
    while (off != 0) {
        block_read(&leaf, off);

        for(int i = 0; i < leaf.n; i++) {
            result->push_back(pair<int, int>(leaf.children[i].value.pagenum, leaf.children[i].value.pageposition));
        }

        off = leaf.next;
    }

    return result->size()==0?-1:0;
}

int bplus_tree::remove(const index_key& key) {
    internal_node_t parent;
    leaf_node_t leaf;

    // find parent node
    int parent_off = search_index(key);
    block_read(&parent, parent_off);

    // find current node
    index_t* where = find(parent, key);
    int offset = where->child;
    block_read(&leaf, offset);

    // verify
    if (!binary_search(begin(leaf), end(leaf), key)) return -1;

    int min_n = head.leaf_node_num == 1 ? 0 : head.order / 2;

    // delete the key
    record_t* to_delete = find(leaf, key);
    std::copy(to_delete + 1, end(leaf), to_delete);
    leaf.n--;

    // merge or borrow
    if (leaf.n == 0) {
        leaf_node_t prev, next;
        if (leaf.prev != 0) {
            block_read(&prev, leaf.prev);
            prev.next = leaf.next;
            block_write(&prev, leaf.prev);
        } //else cout << 12331 << endl;

        if (leaf.next != 0) {
            block_read(&next, leaf.next);
            next.prev = leaf.prev;
            block_write(&next, leaf.next);
        } //else cout << 12331 << endl;
        remove_from_index(parent_off, parent, key);
    } else {
        block_write(&leaf, offset);
        update_parent_node(parent_off, offset, leaf.children[0].key);
    }

    return 0;
}

int bplus_tree::insert(const index_key& key, index_value value) {
//    if (key.k[0] == 244 && key.k[1] == 1) {
//        cout << counter++ << endl;
//        if (counter == 18)
//            int i = 0;
//    }

    int parent = search_index(key);
    int offset = search_leaf(parent, key);
    leaf_node_t leaf;
    block_read(&leaf, offset);

    // check if we have the same key
    bool search_result = binary_search(begin(leaf), end(leaf), key);
    if (search_result && !multi_value) return 1;

    if (leaf.n == head.order) {
        // split when full

        // new sibling leaf
        leaf_node_t new_leaf;
        node_create(offset, &leaf, &new_leaf);

        // find even split point
        int point = leaf.n / 2;
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
        insert_index_keyo_index(parent, new_leaf.children[0].key, offset,
                            leaf.next);
    } else {
        insert_record_no_split(&leaf, key, value);
        block_write(&leaf, offset);
        update_parent_node(parent, offset, leaf.children[0].key);
    }

    return 0;
}

void bplus_tree::update_parent_node(int parent, int offset, const index_key &key) {
    internal_node_t node;
    block_read(&node, parent);

    for (int i = 0; i < node.n; i++)
        if (node.children[i].child == offset) {
            node.children[i].key = key;
            break;
        }
    block_write(&node, parent);
    return;
}

int bplus_tree::update(const index_key& key, index_value value) {
    int offset = search_leaf(key);
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

void bplus_tree::remove_from_index(int offset, internal_node_t& node,
                                   const index_key& key) {
    // remove key
    index_key index_key = begin(node)->key;
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
    if (node.n == 0) {
        internal_node_t parent;
        block_read(&parent, node.parent);
        remove_from_index(node.parent, parent, index_key);
    } else {
        block_write(&node, offset);
        update_parent_node(node.parent, offset, node.children[0].key);
    }
}

void bplus_tree::insert_record_no_split(leaf_node_t* leaf, const index_key& key,
                                        const index_value& value) {
    record_t* where = upper_bound(begin(*leaf), end(*leaf), key);
    std::copy_backward(where, end(*leaf), end(*leaf) + 1);

    where->key = key;
    where->value = value;
    leaf->n++;
}

void bplus_tree::insert_index_keyo_index(int offset, const index_key& key, int old,
                                     int after) {
    internal_node_t node;
    block_read(&node, offset);
    assert(node.n <= head.order);

    if (node.n == head.order) {
        // split when full

        internal_node_t new_node;
        node_create(offset, &node, &new_node);

        // find even split point
        int point = (node.n - 1) / 2;
        bool place_right = keycmp(key, node.children[point].key) > 0;
        if (place_right) ++point;

        // prevent the `key` being the right `middle_key`
        // example: insert 48 into |42|45| 6|    |
        if (place_right && keycmp(key, node.children[point].key) < 0) point--;

        // split
        std::copy(begin(node) + point + 1, end(node), begin(new_node));
        new_node.n = node.n - point - 1;
        node.n = point + 1;

        // put the new key
        if (place_right)
            insert_index_keyo_index_no_split(new_node, key, after, old);
        else
            insert_index_keyo_index_no_split(node, key, after, old);

        index_key middle_key = new_node.children[0].key;
        block_write(&node, offset);
        block_write(&new_node, node.next);

        // update children's parent
        reset_index_children_parent(begin(new_node), end(new_node), node.next);

        if (offset == head.root_offset) {
            // create new root node
            internal_node_t root;
            root.next = root.prev = root.parent = 0;
            head.root_offset = alloc(&root);
            head.height++;

            // insert `old` and `after`
            root.n = 2;
            root.children[0].key = node.children[0].key;
            root.children[0].child = offset;
            root.children[1].child = node.next;
            root.children[1].key = new_node.children[0].key;

            block_write(&head, OFFSET_META);
            block_write(&root, head.root_offset);

            // update children's parent
            reset_index_children_parent(begin(root), end(root), head.root_offset);
            return;
        }

        // give the middle key to the parent
        // note: middle key's child is reserved
        insert_index_keyo_index(node.parent, middle_key, offset, node.next);
    } else {
        insert_index_keyo_index_no_split(node, key, after, old);
        block_write(&node, offset);
    }
}

void bplus_tree::insert_index_keyo_index_no_split(internal_node_t& node,
                                              const index_key& key, int value, int prev_off) {
    index_t* where = node.children;

    for (int i = 0; i < node.n; i++)
        if (node.children[i].child == prev_off)
            where = node.children+i+1;

    // move later index forward
    std::copy_backward(where, end(node), end(node) + 1);

    // insert this key
    where->key = key;
    where->child = value;

    node.n++;
}

void bplus_tree::reset_index_children_parent(index_t* begin, index_t* end,
                                             int parent) {
    // this function can change both internal_node_t and leaf_node_t's parent
    // field, but we should ensure that:
    // 1. sizeof(internal_node_t) <= sizeof(leaf_node_t)
    // 2. parent field is placed in the beginning and have same size
    internal_node_t node;
    while (begin != end) {
        block_read(&node, begin->child);
        node.parent = parent;
        block_write(&node, begin->child);
        ++begin;
    }
}

int bplus_tree::search_index(const index_key& key) const {
    int org = head.root_offset;
    int height = head.height;
    while (height > 1) {
        internal_node_t node;
        block_read(&node, org);

        index_t* i = upper_bound(begin(node), end(node), key);
        if (i - begin(node) >= node.n)
            i = end(node) - 1;
        if ( key < *i && i > begin(node))
            i = i - 1;
        org = i->child;
        --height;
    }

    return org;
}

int bplus_tree::search_index_l(const index_key& key) const {
    int org = head.root_offset;
    int height = head.height;
    while (height > 1) {
        internal_node_t node;
        block_read(&node, org);

        index_t* i = lower_bound(begin(node), end(node), key);
        if (i - begin(node) >= node.n)
            i = end(node) - 1;
        if ( (key < *i || key == *i) && i > begin(node))
            i = i - 1;
        org = i->child;
        --height;
    }

    return org;
}

int bplus_tree::search_leaf(int index, const index_key& key) const {
    internal_node_t node;
    block_read(&node, index);
    index_t* i = upper_bound(begin(node), end(node), key);
    if (i - begin(node) >= node.n)
        i = end(node) - 1;
    if ( key < *i && i > begin(node) )
        i--;
    return i->child;
}

int bplus_tree::search_leaf_l(int index, const index_key& key) const {
    internal_node_t node;
    block_read(&node, index);
    index_t* i = lower_bound(begin(node), end(node), key);
    if (i - begin(node) >= node.n)
        i = end(node) - 1;
    if ( (key < *i || key == *i) && i > begin(node) )
        i--;
    return i->child;
}

template <class T>
void bplus_tree::node_create(int offset, T* node, T* next) {
    // new sibling node
    next->parent = node->parent;
    next->next = node->next;
    next->prev = offset;
    node->next = alloc(next);
    // update next node's prev
    if (next->next != 0) {
        T old_next;
        block_read(&old_next, next->next);
        old_next.prev = node->next;
        block_write(&old_next, next->next);
    }
    block_write(&head, OFFSET_META);
}

template <class T>
void bplus_tree::node_remove(T* prev, T* node) {
    unalloc(node, prev->next);
    prev->next = node->next;
    if (node->next != 0) {
        T next;
        block_read(&next, node->next);
        next.prev = node->prev;
        block_write(&next, node->next);
    }
    block_write(&head, OFFSET_META);
}

void bplus_tree::init_from_empty(int keySize) {
    // init default head
    memset(&head,0, head_t::getSize());
    head.order = CHILDREN_NUM;
    head.value_size = index_value::getSize();
    head.key_size = keySize;
    head.height = 1;
    head.slot = OFFSET_BLOCK;

    // init root node
    internal_node_t root;
    root.next = root.prev = root.parent = 0;
    head.root_offset = alloc(&root);
//    cout << root.n << endl;

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
