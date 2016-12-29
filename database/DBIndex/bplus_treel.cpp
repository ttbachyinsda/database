#include "bplus_treel.h"

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <list>
using std::cout;
using std::endl;
using std::swap;
using std::binary_search;
using std::lower_bound;
using std::upper_bound;

CompareAlgo *bplus_treeL::global_cmp;

/* custom compare operator for STL algorithms */
bool operator<(const indexL_key& l, const indexL_t& r) {
    return keycmp(l, r.key, bplus_treeL::global_cmp) < 0;
}
bool operator<(const indexL_t& l, const indexL_key& r) {
    return keycmp(l.key, r, bplus_treeL::global_cmp) < 0;
}
bool operator==(const indexL_key& l, const indexL_t& r) {
    return keycmp(l, r.key, bplus_treeL::global_cmp) == 0;
}
bool operator==(const indexL_t& l, const indexL_key& r) {
    return keycmp(l.key, r, bplus_treeL::global_cmp) == 0;
}
bool operator<(const indexL_key& l, const recordL_t& r) {
    return keycmp(l, r.key, bplus_treeL::global_cmp) < 0;
}
bool operator<(const recordL_t& l, const indexL_key& r) {
    return keycmp(l.key, r, bplus_treeL::global_cmp) < 0;
}
bool operator==(const indexL_key& l, const recordL_t& r) {
    return keycmp(l, r.key, bplus_treeL::global_cmp) == 0;
}
bool operator==(const recordL_t& l, const indexL_key& r) {
    return keycmp(l.key, r, bplus_treeL::global_cmp) == 0;
}

/* helper iterating function */
template <class T>
inline typename T::childL_t beginL(T& node) {
    return node.children;
}
template <class T>
inline typename T::childL_t endL(T& node) {
    return node.children + node.n;
}

int counterL = 0;

/* helper searching function */
inline indexL_t* findL(internal_nodeL_t& node, const indexL_key& key) {
    indexL_t* temp = lower_bound(beginL(node), endL(node), key);
    if (temp - beginL(node) >= node.n && node.n > 0)
        temp = endL(node) - 1;
    if ( key < *temp && temp > beginL(node))
        temp = temp - 1;
    return temp;
}

inline recordL_t* findL(leaf_nodeL_t& node, const indexL_key& key) {
    using namespace std::placeholders;
    recordL_t* temp = lower_bound(beginL(node), endL(node), key);
    if (temp - beginL(node) >= node.n && node.n > 0)
        temp = endL(node) - 1;
    if ( key < *temp && temp > beginL(node))
        temp = temp - 1;
    return temp;
}

bplus_treeL::bplus_treeL(const char* p, bool force_empty /*false*/,
                       bool multi_value /*false*/, CompareAlgo *cmp, int keySize /*20*/)
: fp(NULL), fp_level(0) {
    memset(path,0, sizeof(path));
    strcpy(path, p);
    this->multi_value = multi_value;
    this->cmp = cmp;
    
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

int bplus_treeL::search(const indexL_key& key, indexL_value* value) const {
    global_cmp = cmp;
    leaf_nodeL_t leaf;
    block_read(&leaf, search_leaf(key));
    
    // findLing the recordL
    recordL_t* recordL = findL(leaf, key);
    if (recordL != leaf.children + leaf.n) {
        // always return the lower bound
        *value = recordL->value;
        int result = keycmp(recordL->key, key, cmp);
        if (result != 0)
            return -1;
        else return 0;
    } else {
        return -1;
    }
}

int bplus_treeL::search_and_remove_multi(const indexL_key &key, int pagenum, int pageposition) {
    int off_left = search_leaf_l(key);
    int off_right = search_leaf(key);
    int off = off_left;
    recordL_t *b, *e;
    
    leaf_nodeL_t leaf;
    while (off != off_right && off != 0) {
        block_read(&leaf, off);
        
        // start point
        if (off_left == off)
            b = findL(leaf, key);
        else
            b = beginL(leaf);
        
        if (keycmp(b->key, key, cmp) != 0)
            b++;
        
        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b) {
            if (b->value.pagenum == pagenum && b->value.pageposition == pageposition) {
                std::copy(b + 1, endL(leaf), b);
                leaf.n--;
                
                // merge or borrow
                if (leaf.n == 0) {
                    leaf_nodeL_t prev, next;
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
                    internal_nodeL_t parent;
                    block_read(&parent, leaf.parent);
                    remove_from_indexL_multi(leaf.parent, off, parent, key);
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
    
    b = findL(leaf, key);
    if (keycmp(b->key, key, cmp) != 0)
        b++;
    e = upper_bound(beginL(leaf), endL(leaf), key);
    
    for (; b != e; ++b)
        if (b->value.pagenum == pagenum && b->value.pageposition == pageposition) {
            std::copy(b + 1, endL(leaf), b);
            leaf.n--;
            
            // merge or borrow
            if (leaf.n == 0) {
                leaf_nodeL_t prev, next;
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
                internal_nodeL_t parent;
                block_read(&parent, leaf.parent);
                remove_from_indexL_multi(leaf.parent, off, parent, key);
            } else {
                block_write(&leaf, off);
                update_parent_node(leaf.parent, off, leaf.children[0].key);
            }
            return 0;
        }
    
    return -1;
}

void bplus_treeL::remove_from_indexL_multi(int parent_off, int off, internal_nodeL_t &parent, const indexL_key &key) {
    // remove key
    indexL_t* to_delete;
    for (int i = 0; i < parent.n; i++)
        if (parent.children[i].child == off)
            to_delete = parent.children + i;
    
    if (to_delete != endL(parent)) {
        (to_delete + 1)->child = to_delete->child;
        std::copy(to_delete + 1, endL(parent), to_delete);
    }
    parent.n--;
    
    // remove to only one key
    if (parent.n == 1 && head.root_offset == off &&
        head.internal_nodeL_num != 1) {
        unalloc(&parent, head.root_offset);
        head.height--;
        head.root_offset = parent.children[0].child;
        block_write(&head, OFFSET_META);
        return;
    }
    
    // merge or borrow
    if (parent.n == 0) {
        internal_nodeL_t pparent;
        block_read(&pparent, parent.parent);
        remove_from_indexL_multi(parent.parent, parent_off, pparent, key);
    } else {
        block_write(&parent, off);
        update_parent_node(parent.parent, off, parent.children[0].key);
    }
    
    return;
}

void bplus_treeL::search_greater(const indexL_key &key, vector<pair<int, int> > *result) {
    global_cmp = cmp;
    int off_left = search_leaf(key);
    
    int off = off_left;
    recordL_t *b, *e;
    
    leaf_nodeL_t leaf;
    while (off != 0) {
        block_read(&leaf, off);
        
        // start point
        if (off_left == off)
            b = upper_bound(beginL(leaf), endL(leaf), key);
        else
            b = beginL(leaf);
        
        if (keycmp(b->key, key, cmp) < 0)
            b++;
        
        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));
        
        off = leaf.next;
    }
    
    return;
}

void bplus_treeL::search_greater_equal(const indexL_key &key, vector<pair<int, int> > *result) {
    global_cmp = cmp;
    int off_left = search_leaf_l(key);
    
    int off = off_left;
    recordL_t *b, *e;
    
    leaf_nodeL_t leaf;
    while (off != 0) {
        block_read(&leaf, off);
        
        // start point
        if (off_left == off)
            b = findL(leaf, key);
        else
            b = beginL(leaf);
        
        if (keycmp(b->key, key, cmp) < 0)
            b++;
        
        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));
        
        off = leaf.next;
    }
    
    return;
}

void bplus_treeL::search_less(const indexL_key &key, vector<pair<int, int> > *result) {
    global_cmp = cmp;
    int off_right = search_leaf_l(key);
    
    int off = off_right;
    recordL_t *b, *e;
    
    leaf_nodeL_t leaf;
    while (off != 0) {
        block_read(&leaf, off);
        
        // start point
        b = beginL(leaf);
        // copy
        if (off == off_right)
            e = lower_bound(beginL(leaf), endL(leaf), key);
        else
            e = leaf.children + leaf.n;
        
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));
        
        off = leaf.prev;
    }
    
    return;
}

void bplus_treeL::search_less_equal(const indexL_key &key, vector<pair<int, int> > *result) {
    global_cmp = cmp;
    int off_right = search_leaf(key);
    
    int off = off_right;
    recordL_t *b, *e;
    
    leaf_nodeL_t leaf;
    while (off != 0) {
        block_read(&leaf, off);
        
        // start point
        b = beginL(leaf);
        // copy
        if (off == off_right)
            e = upper_bound(beginL(leaf), endL(leaf), key);
        else
            e = leaf.children + leaf.n;
        
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));
        
        off = leaf.prev;
    }
    
    return;
}

int bplus_treeL::search_range(const indexL_key& left, const indexL_key& right,
                             vector<pair<int, int>> *result) const {
    global_cmp = cmp;
    if (keycmp(left, right, cmp) > 0) return -1;
    
    int off_left = search_leaf_l(left);
    int off_right = search_leaf(right);
    int off = off_left;
    recordL_t *b, *e;
    
    leaf_nodeL_t leaf;
    while (off != off_right && off != 0) {
        block_read(&leaf, off);
        
        // start point
        if (off_left == off)
            b = findL(leaf, left);
        else
            b = beginL(leaf);
        
        if (keycmp(b->key, left, cmp) != 0)
            b++;
        
        // copy
        e = leaf.children + leaf.n;
        for (; b != e; ++b)
            result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));
        
        off = leaf.next;
    }
    
    // the last leaf
    block_read(&leaf, off_right);
    
    b = findL(leaf, left);
    if (keycmp(b->key, left, cmp) != 0)
        b++;
    if (b < leaf.children)
        b = leaf.children;
    e = upper_bound(beginL(leaf), endL(leaf), right);
    
    for (; b < e; ++b)
        result->push_back(pair<int, int>(b->value.pagenum, b->value.pageposition));
    
    return result->size()==0?-1:0;
}

int bplus_treeL::search_all(vector<pair<int, int> > *result) {
    global_cmp = cmp;
    int off_left = head.leaf_offset;
    int off = off_left;
    
    leaf_nodeL_t leaf;
    while (off != 0) {
        block_read(&leaf, off);
        
        for(int i = 0; i < leaf.n; i++) {
            result->push_back(pair<int, int>(leaf.children[i].value.pagenum, leaf.children[i].value.pageposition));
        }
        
        off = leaf.next;
    }
    
    return result->size()==0?-1:0;
}

int bplus_treeL::remove(const indexL_key& key) {
    global_cmp = cmp;
    internal_nodeL_t parent;
    leaf_nodeL_t leaf;
    
    // findL parent node
    int parent_off = search_indexL(key);
    block_read(&parent, parent_off);
    
    // findL current node
    indexL_t* where = findL(parent, key);
    int offset = where->child;
    block_read(&leaf, offset);
    
    // verify
    if (!binary_search(beginL(leaf), endL(leaf), key)) return -1;
    
    int min_n = head.leaf_nodeL_num == 1 ? 0 : head.order / 2;
    
    // delete the key
    recordL_t* to_delete = findL(leaf, key);
    std::copy(to_delete + 1, endL(leaf), to_delete);
    leaf.n--;
    
    // merge or borrow
    if (leaf.n == 0) {
        leaf_nodeL_t prev, next;
        if (leaf.prev != 0) {
            block_read(&prev, leaf.prev);
            prev.next = leaf.next;
            block_write(&prev, leaf.prev);
        } //else cout << 12331 << endLl;
        
        if (leaf.next != 0) {
            block_read(&next, leaf.next);
            next.prev = leaf.prev;
            block_write(&next, leaf.next);
        } //else cout << 12331 << endLl;
        remove_from_indexL(parent_off, parent, key);
    } else {
        block_write(&leaf, offset);
        update_parent_node(parent_off, offset, leaf.children[0].key);
    }
    
    return 0;
}

int bplus_treeL::insert(const indexL_key& key, indexL_value value) {
    global_cmp = cmp;
    //    if (key.k[0] == 244 && key.k[1] == 1) {
    //        cout << counterL++ << endLl;
    //        if (counterL == 18)
    //            int i = 0;
    //    }
    
    int parent = search_indexL(key);
    int offset = search_leaf(parent, key);
    leaf_nodeL_t leaf;
    block_read(&leaf, offset);
    
    // check if we have the same key
    bool search_result = binary_search(beginL(leaf), endL(leaf), key);
    if (search_result && !multi_value) return 1;
    
    if (leaf.n == head.order) {
        // split when full
        
        // new sibling leaf
        leaf_nodeL_t new_leaf;
        node_create(offset, &leaf, &new_leaf);
        
        // findL even split point
        int point = leaf.n / 2;
        bool place_right = keycmp(key, leaf.children[point].key, cmp) > 0;
        if (place_right) ++point;
        
        // split
        std::copy(leaf.children + point, leaf.children + leaf.n,
                  new_leaf.children);
        new_leaf.n = leaf.n - point;
        leaf.n = point;
        
        // which part do we put the key
        if (place_right)
            insert_recordL_no_split(&new_leaf, key, value);
        else
            insert_recordL_no_split(&leaf, key, value);
        
        // save leafs
        block_write(&leaf, offset);
        block_write(&new_leaf, leaf.next);
        
        // insert new indexL key
        insert_indexL_keyo_indexL(parent, new_leaf.children[0].key, offset,
                                leaf.next);
    } else {
        insert_recordL_no_split(&leaf, key, value);
        block_write(&leaf, offset);
        update_parent_node(parent, offset, leaf.children[0].key);
    }
    
    return 0;
}

void bplus_treeL::update_parent_node(int parent, int offset, const indexL_key &key) {
    internal_nodeL_t node;
    block_read(&node, parent);
    
    for (int i = 0; i < node.n; i++)
        if (node.children[i].child == offset) {
            node.children[i].key = key;
            break;
        }
    block_write(&node, parent);
    return;
}

int bplus_treeL::update(const indexL_key& key, indexL_value value) {
    global_cmp = cmp;
    int offset = search_leaf(key);
    leaf_nodeL_t leaf;
    block_read(&leaf, offset);
    
    recordL_t* recordL = findL(leaf, key);
    if (recordL != leaf.children + leaf.n)
        if (keycmp(key, recordL->key, cmp) == 0) {
            recordL->value = value;
            block_write(&leaf, offset);
            
            return 0;
        } else {
            return 1;
        }
        else
            return -1;
}

void bplus_treeL::remove_from_indexL(int offset, internal_nodeL_t& node,
                                   const indexL_key& key) {
    // remove key
    indexL_key indexL_key = beginL(node)->key;
    indexL_t* to_delete = findL(node, key);
    if (to_delete != endL(node)) {
        (to_delete + 1)->child = to_delete->child;
        std::copy(to_delete + 1, endL(node), to_delete);
    }
    node.n--;
    
    // remove to only one key
    if (node.n == 1 && head.root_offset == offset &&
        head.internal_nodeL_num != 1) {
        unalloc(&node, head.root_offset);
        head.height--;
        head.root_offset = node.children[0].child;
        block_write(&head, OFFSET_META);
        return;
    }
    
    // merge or borrow
    if (node.n == 0) {
        internal_nodeL_t parent;
        block_read(&parent, node.parent);
        remove_from_indexL(node.parent, parent, indexL_key);
    } else {
        block_write(&node, offset);
        update_parent_node(node.parent, offset, node.children[0].key);
    }
}

void bplus_treeL::insert_recordL_no_split(leaf_nodeL_t* leaf, const indexL_key& key,
                                        const indexL_value& value) {
    recordL_t* where = upper_bound(beginL(*leaf), endL(*leaf), key);
    std::copy_backward(where, endL(*leaf), endL(*leaf) + 1);
    
    where->key = key;
    where->value = value;
    leaf->n++;
}

void bplus_treeL::insert_indexL_keyo_indexL(int offset, const indexL_key& key, int old,
                                         int after) {
    internal_nodeL_t node;
    block_read(&node, offset);
    assert(node.n <= head.order);
    
    if (node.n == head.order) {
        // split when full
        
        internal_nodeL_t new_node;
        node_create(offset, &node, &new_node);
        
        // findL even split point
        int point = (node.n - 1) / 2;
        bool place_right = keycmp(key, node.children[point].key, cmp) > 0;
        if (place_right) ++point;
        
        // prevent the `key` being the right `middle_key`
        // example: insert 48 into |42|45| 6|    |
        if (place_right && keycmp(key, node.children[point].key, cmp) < 0) point--;
        
        // split
        std::copy(beginL(node) + point + 1, endL(node), beginL(new_node));
        new_node.n = node.n - point - 1;
        node.n = point + 1;
        
        // put the new key
        if (place_right)
            insert_indexL_keyo_indexL_no_split(new_node, key, after, old);
        else
            insert_indexL_keyo_indexL_no_split(node, key, after, old);
        
        indexL_key middle_key = new_node.children[0].key;
        block_write(&node, offset);
        block_write(&new_node, node.next);
        
        // update children's parent
        reset_indexL_children_parent(beginL(new_node), endL(new_node), node.next);
        
        if (offset == head.root_offset) {
            // create new root node
            internal_nodeL_t root;
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
            reset_indexL_children_parent(beginL(root), endL(root), head.root_offset);
            return;
        }
        
        // give the middle key to the parent
        // note: middle key's child is reserved
        insert_indexL_keyo_indexL(node.parent, middle_key, offset, node.next);
    } else {
        insert_indexL_keyo_indexL_no_split(node, key, after, old);
        block_write(&node, offset);
    }
}

void bplus_treeL::insert_indexL_keyo_indexL_no_split(internal_nodeL_t& node,
                                                  const indexL_key& key, int value, int prev_off) {
    indexL_t* where = node.children;
    
    for (int i = 0; i < node.n; i++)
        if (node.children[i].child == prev_off)
            where = node.children+i+1;
    
    // move later indexL forward
    std::copy_backward(where, endL(node), endL(node) + 1);
    
    // insert this key
    where->key = key;
    where->child = value;
    
    node.n++;
}

void bplus_treeL::reset_indexL_children_parent(indexL_t* beginL, indexL_t* endL,
                                             int parent) {
    // this function can change both internal_nodeL_t and leaf_nodeL_t's parent
    // field, but we should ensure that:
    // 1. sizeof(internal_nodeL_t) <= sizeof(leaf_nodeL_t)
    // 2. parent field is placed in the beginLning and have same size
    internal_nodeL_t node;
    while (beginL != endL) {
        block_read(&node, beginL->child);
        node.parent = parent;
        block_write(&node, beginL->child);
        ++beginL;
    }
}

int bplus_treeL::search_indexL(const indexL_key& key) const {
    int org = head.root_offset;
    int height = head.height;
    while (height > 1) {
        internal_nodeL_t node;
        block_read(&node, org);
        
        indexL_t* i = upper_bound(beginL(node), endL(node), key);
        if (i - beginL(node) >= node.n)
            i = endL(node) - 1;
        if ( key < *i && i > beginL(node))
            i = i - 1;
        org = i->child;
        --height;
    }
    
    return org;
}

int bplus_treeL::search_indexL_l(const indexL_key& key) const {
    int org = head.root_offset;
    int height = head.height;
    while (height > 1) {
        internal_nodeL_t node;
        block_read(&node, org);
        
        indexL_t* i = lower_bound(beginL(node), endL(node), key);
        if (i - beginL(node) >= node.n)
            i = endL(node) - 1;
        if ( (key < *i || key == *i) && i > beginL(node))
            i = i - 1;
        org = i->child;
        --height;
    }
    
    return org;
}

int bplus_treeL::search_leaf(int indexL, const indexL_key& key) const {
    internal_nodeL_t node;
    block_read(&node, indexL);
    indexL_t* i = upper_bound(beginL(node), endL(node), key);
    if (i - beginL(node) >= node.n)
        i = endL(node) - 1;
    if ( key < *i && i > beginL(node) )
        i--;
    return i->child;
}

int bplus_treeL::search_leaf_l(int indexL, const indexL_key& key) const {
    internal_nodeL_t node;
    block_read(&node, indexL);
    indexL_t* i = lower_bound(beginL(node), endL(node), key);
    if (i - beginL(node) >= node.n)
        i = endL(node) - 1;
    if ( (key < *i || key == *i) && i > beginL(node) )
        i--;
    return i->child;
}

template <class T>
void bplus_treeL::node_create(int offset, T* node, T* next) {
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
void bplus_treeL::node_remove(T* prev, T* node) {
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

void bplus_treeL::init_from_empty(int keySize) {
    // init default head
    memset(&head,0, headL_t::getSize());
    head.order = CHILDREN_NUM;
    head.value_size = indexL_value::getSize();
    head.key_size = keySize;
    head.height = 1;
    head.slot = OFFSET_BLOCK;
    
    // init root node
    internal_nodeL_t root;
    root.next = root.prev = root.parent = 0;
    head.root_offset = alloc(&root);
    //    cout << root.n << endLl;
    
    // init empty leaf
    leaf_nodeL_t leaf;
    leaf.next = leaf.prev = 0;
    leaf.parent = head.root_offset;
    head.leaf_offset = root.children[0].child = alloc(&leaf);
    
    // save
    block_write(&head, OFFSET_META);
    block_write(&root, head.root_offset);
    block_write(&leaf, root.children[0].child);
}
