#include "bplus_tree.h"

class db_index {
   public:
    db_index(char *path, bool forceNewIndex = false, bool multi_value = false);

    int search(const index_key &key, index_value *value,
               int max_num = 1000) const;
    int search_range(const index_key &left, const index_key &right,
                     index_value *values, size_t max = 1000) const;
    int remove(const index_key &key);
    int remove(char* insertData, int dataLen, int pagenum, int pageposition);
    int insert(const index_key &key, index_value value);
    int insert(char* insertData, int dataLen, int pagenum, int pageposition) {
        char key[255];
        memcpy(key, insertData, dataLen);
        return insert(index_key(key, dataLen), index_value(pagenum, pageposition));
    }
    int update(const index_key &key, index_value value);
    int update(char* insertData, int dataLen, int prepagenum, int prepageposition, int pagenum, int pageposition);

    bool isMulti_value() const;
    void setMulti_value(bool multi_value);

   private:
    bplus_tree b_tree;

    char path[512];
    bool multi_value;
    int insertTime;
};
