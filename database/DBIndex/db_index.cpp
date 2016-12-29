#include "db_index.h"
#include <iostream>
using namespace std;

db_index::db_index(char *path, bool forceNewIndex, bool multi_value, int keySize)
    : b_tree(path, forceNewIndex, multi_value, keySize) {
    strcpy(this->path, path);
    this->multi_value = multi_value;
    this->keySize = keySize;
    insertTime = 0;
}

bool db_index::isMulti_value() const { return multi_value; }

void db_index::setMulti_value(bool multi_value) {
    db_index::multi_value = multi_value;
    b_tree.set_MultiValue(multi_value);
}

int db_index::search(const index_key &key, index_value *value,
                     vector<pair<int, int>> *result) const {
    if (!multi_value || result == NULL)
        return b_tree.search(key, value);
    else
        return b_tree.search_range(key, key, result);
}

int db_index::search_range(const index_key &left, const index_key &right,
                           vector<pair<int, int>> *result) const {
    return b_tree.search_range(left, right, result);
}

int db_index::remove(const index_key &key) {
    if (!multi_value)
        return b_tree.remove(key);
    else {
        index_value value;
        while (search(key, &value)) b_tree.remove(key);
        return 0;
    }
}

int db_index::insert(const index_key &key, index_value value) {
    insertTime++;
    return b_tree.insert(key, value);
}

int db_index::update(const index_key &key, index_value value) {
    if (!multi_value)
        return b_tree.update(key, value);
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
        if (b_tree.search_and_remove_multi(index_key(key, dataLen), prepagenum, prepageposition) == 0)
            return b_tree.insert(index_key(insertData, dataLen), index_value(pagenum, pageposition));
        else return -1;
    }
}

int db_index::remove(char *insertData, int dataLen, int pagenum, int pageposition) {
    char key[255];
    memcpy(key, insertData, dataLen);
    if (!multi_value)
        return b_tree.remove(index_key(key, dataLen));
    else {
        return b_tree.search_and_remove_multi(index_key(key, dataLen), pagenum, pageposition);
    }
}

void db_index::findAll(SQLOperand operand, string key, int dataLen, vector<pair<int, int> > *result) {
    index_key temp_key(key.c_str(), dataLen);
    switch (operand) {
        case SQLOperand::GREATER: {
            b_tree.search_greater(temp_key, result);
            break;
        }
        case SQLOperand::GREATER_EQUAL: {
            b_tree.search_greater_equal(temp_key, result);
            break;
        }
        case SQLOperand::LESS: {
            b_tree.search_less(temp_key, result);
            break;
        }
        case SQLOperand::LESS_EQUAL: {
            b_tree.search_less_equal(temp_key, result);
            break;
        }
        case SQLOperand::EQUAL: {
            search_range(temp_key, temp_key, result);
            break;
        }
    }
}

int db_index::search_all(vector<pair<int, int> > *result) {
//    if (multi_value)
    return b_tree.search_all(result);
//    else return -1;
}

