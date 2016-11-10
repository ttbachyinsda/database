#include "db_index.h"
#include <iostream>
using namespace std;

db_index::db_index(char *path, bool forceNewIndex, bool multi_value)
    : b_tree(path, forceNewIndex, multi_value) {
    strcpy(this->path, path);
    this->multi_value = multi_value;
    insertTime = 0;
}

bool db_index::isMulti_value() const { return multi_value; }

void db_index::setMulti_value(bool multi_value) {
    db_index::multi_value = multi_value;
    b_tree.set_MultiValue(multi_value);
}

int db_index::search(const index_key &key, index_value *value,
                     int max_num /*= 1000*/) const {
    if (!multi_value)
        return b_tree.search(key, value);
    else
        return b_tree.search_range(key, key, value, max_num);
}

int db_index::search_range(const index_key &left, const index_key &right,
                           index_value *values, size_t max /*= 1000*/) const {
    return b_tree.search_range(left, right, values, max);
}

int db_index::remove(const index_key &key) {
    if (!multi_value)
        return b_tree.remove(key);
    else {
        index_value value;
        while (search(key, &value, 1)) b_tree.remove(key);
        return 0;
    }
}

int db_index::insert(const index_key &key, index_value value) {
    if (!multi_value) {
        index_value *temp;
        if (search(key, temp) < 0) {
            cout << ++insertTime << endl;
            return b_tree.insert(key, value);
        }
        else
            return 0;
    }
    else
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
        return -1;
    }
}

int db_index::remove(char *insertData, int dataLen, int pagenum, int pageposition) {
    char key[255];
    memcpy(key, insertData, dataLen);
    if (!multi_value)
        return b_tree.remove(index_key(key, dataLen));
    else {
        return -1;
    }
}

