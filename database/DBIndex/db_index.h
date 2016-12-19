#include "bplus_tree.h"
#include "../sqlengine/sqlstruct.h"
#include <vector>
#include <cstdlib>
#include <utility>

using std::pair;
using std::vector;

#include <string>
#include <vector>
#include "../sqlengine/sqlstruct.h"
using namespace std;

class db_index {
   public:
    db_index(char *path, bool forceNewIndex = false, bool multi_value = false, int keySize = 20);

    int search(const index_key &key, index_value *value,
               vector<pair<int, int>> *result = NULL) const;
    int search_range(const index_key &left, const index_key &right,
                     vector<pair<int, int>> *result) const;
    void findAll(SQLOperand operand, string key, int dataLen, vector<pair<int, int>> *result );
    int search_all(vector<pair<int, int>> *result);
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

    void findAll(SQLOperand operand, string targetValue, vector<pair<int,int>> *res) {}

   private:
    bplus_tree b_tree;

    char path[512];
    bool multi_value;
    int insertTime;
    int keySize;
};
