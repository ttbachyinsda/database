#include "bplus_tree.h"

class db_index {
   public:
    db_index(char *path, bool forceNewIndex = false, bool multi_value = false);

    int search(const bpt::key_t &key, bpt::value_t *value, int max_num) const;
    int search_range(const bpt::key_t &left, const bpt::key_t &right,
                     bpt::value_t *values, size_t max) const;
    int remove(const bpt::key_t &key);
    int insert(const bpt::key_t &key, bpt::value_t value);
    int update(const bpt::key_t &key, bpt::value_t value);

    bool isMulti_value() const;
    void setMulti_value(bool multi_value);

   private:
    bpt::bplus_tree b_tree;

    char path[512];
    bool multi_value;
};
