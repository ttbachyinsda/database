#include "testbulbfile.h"

testbulbfile::testbulbfile()
{
}
void testbulbfile::begintest()
{
    BulbFile bf;
    bf.setfilename("bulbfile.txt", true);
    string a = "12345";
    vector<pair<int, int> > jl;
    for (int i = 0; i < 10; i++) {
        jl.push_back(make_pair(bf.put(a.c_str(), 5), 5));
    }
    for (int i = 0; i < 10; i++) {
        cout << i << ' ' << bf.get(jl[i].first, jl[i].second) << endl;
    }
}
