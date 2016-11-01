#include "db_index.h"

db_index::db_index(char *path, bool forceNewIndex, bool multi_value)
    : b_tree(path, forceNewIndex, multi_value) {
    strcpy(this->path, path);
    this->multi_value = multi_value;
}

bool db_index::isMulti_value() const { return multi_value; }

void db_index::setMulti_value(bool multi_value) {
    db_index::multi_value = multi_value;
    b_tree.set_MultiValue(multi_value);
}

int db_index::search(const bpt::key_t &key, bpt::value_t *value, int max_num) const {
    if (!multi_value)
        return b_tree.search(key, value);
    else
        return b_tree.search_range(key, key, value, max_num);
}

int db_index::search_range(const bpt::key_t &left, const bpt::key_t &right,
                           bpt::value_t *values, size_t max) const {
    return b_tree.search_range(left, right, values, max);
}

int db_index::remove(const bpt::key_t &key) {
    if (!multi_value)
        return b_tree.remove(key);
    else {
        bpt::value_t value;
        while (search(key, &value, 1))
            b_tree.remove(key);
    }
}

int db_index::insert(const bpt::key_t &key, bpt::value_t value) {
    return b_tree.insert(key, value);
}

int db_index::update(const bpt::key_t &key, bpt::value_t value) {
    return b_tree.update(key, value);
}
