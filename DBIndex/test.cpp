//
// Created by JerryJohn on 2016/10/17.
//

#include <iostream>
#include "db_index.h"
using namespace std;

int main() {
    db_index index("test.db", true);
    char value[32];
    index.insert("huangjiahui", "nan");
    index.search("huangjiahui", value);
    cout << value << endl;
    return 0;
}