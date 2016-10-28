//
// Created by JerryJohn on 2016/10/17.
//

#include <iostream>
#include "db_index.h"
using namespace std;

int main() {
    db_index index("test.db", false, true);
    bpt::value_t value[250];
//    index.remove("huangjiahui");
//    index.insert("huangjiahui", "nan");
    int num = index.search("huangjiahui", value, 10);
    for (int i = 0; i < num; i++)
        cout << value[i].v << endl;
    return 0;
}