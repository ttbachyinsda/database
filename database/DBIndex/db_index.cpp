#include "db_index.h"
#include <iostream>
using namespace std;

db_index::db_index(char *path, bool forceNewIndex, bool multi_value, CompareAlgo *cmp, int keySize) {
    largeKey = false;
    if (keySize <= 20)
        b_tree = new bplus_tree(path, forceNewIndex, multi_value, cmp, keySize);
    else {
        b_treel = new bplus_treeL(path, forceNewIndex, multi_value, cmp, keySize);
        largeKey = true;
    }
    this->cmp = cmp;
    strcpy(this->path, path);
    this->multi_value = multi_value;
    this->keySize = keySize;
    insertTime = 0;
}

db_index::~db_index() {
    if (largeKey)
        delete b_treel;
    else
        delete b_tree;
}

bool db_index::isMulti_value() const { return multi_value; }

void db_index::setMulti_value(bool multi_value) {
    db_index::multi_value = multi_value;
    if (!largeKey)
        b_tree->set_MultiValue(multi_value);
    else
        b_treel->set_MultiValue(multi_value);
}

int db_index::search(const index_key &key, index_value *value,
                     vector<pair<int, int>> *result) const {
    if (!multi_value || result == NULL)
        return b_tree->search(key, value);
    else
        return b_tree->search_range(key, key, result);
}

int db_index::search_range(const index_key &left, const index_key &right,
                           vector<pair<int, int>> *result) const {
    return b_tree->search_range(left, right, result);
}

int db_index::remove(const index_key &key) {
    if (!multi_value)
        return b_tree->remove(key);
    else {
        index_value value;
        while (search(key, &value)) b_tree->remove(key);
        return 0;
    }
}

int db_index::insert(const index_key &key, index_value value) {
    insertTime++;
    return b_tree->insert(key, value);
}

int db_index::update(const index_key &key, index_value value) {
    if (!multi_value)
        return b_tree->update(key, value);
    else
        return -1;
}

int
db_index::update(char *insertData, int dataLen, int prepagenum, int prepageposition, int pagenum, int pageposition) {
    char key[255];
    memcpy(key, insertData, dataLen);
    if (!multi_value) {
        return update(index_key(key, dataLen), index_value(pagenum, pageposition));
    } else {
        if (b_tree->search_and_remove_multi(index_key(key, dataLen), prepagenum, prepageposition) == 0)
            return b_tree->insert(index_key(insertData, dataLen), index_value(pagenum, pageposition));
        else return -1;
    }
}

int db_index::remove(char *insertData, int dataLen, int pagenum, int pageposition) {
    char key[255];
    memcpy(key, insertData, dataLen);
    if (!multi_value) {
        if (!largeKey)
            return b_tree->remove(index_key(key, dataLen));
        else
            return b_treel->remove(indexL_key(key, dataLen));
    }
    else {
        if (!largeKey)
            return b_tree->search_and_remove_multi(index_key(key, dataLen), pagenum, pageposition);
        else
            return b_treel->search_and_remove_multi(indexL_key(key, dataLen), pagenum, pageposition);
    }
}

void db_index::findAll(SQLOperand operand, string key, int dataLen, vector<pair<int, int> > *result) {
    switch (operand) {
        case SQLOperand::GREATER: {
            if (!largeKey)
                b_tree->search_greater(index_key(key.c_str(), dataLen), result);
            else
                b_treel->search_greater(indexL_key(key.c_str(), dataLen), result);
            break;
        }
        case SQLOperand::GREATER_EQUAL: {
            if (!largeKey)
                b_tree->search_greater_equal(index_key(key.c_str(), dataLen), result);
            else
                b_treel->search_greater_equal(indexL_key(key.c_str(), dataLen), result);
            break;
        }
        case SQLOperand::LESS: {
            if (!largeKey)
                b_tree->search_less(index_key(key.c_str(), dataLen), result);
            else
                b_treel->search_less(indexL_key(key.c_str(), dataLen), result);
            break;
        }
        case SQLOperand::LESS_EQUAL: {
            if (!largeKey)
                b_tree->search_less_equal(index_key(key.c_str(), dataLen), result);
            else
                b_treel->search_less_equal(indexL_key(key.c_str(), dataLen), result);
            break;
        }
        case SQLOperand::EQUAL: {
            if (!largeKey)
                search_range(index_key(key.c_str(), dataLen), index_key(key.c_str(), dataLen), result);
            else
                b_treel->search_range(indexL_key(key.c_str(), dataLen), indexL_key(key.c_str(), dataLen), result);
            break;
        }
    }
}

int db_index::search_all(vector<pair<int, int> > *result) {
//    if (multi_value)
    return b_tree->search_all(result);
//    else return -1;
}

