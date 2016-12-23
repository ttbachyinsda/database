#include "testregex.h"

testregex::testregex()
{
}
void testregex::begintest()
{
//    string pattern = "狂三...我...老婆";
//    cout<<pattern.length()<<endl;
//    regex r(pattern);
//    string temp = "狂三是我的老婆";
//    cout<<temp.length()<<endl;
//    bool can=regex_match(temp,r);
//    cout<<(can?"Yes":"No")<<endl;
    string pattern;
    string temp;
    bool can;
    pattern = "C%[AB]%%123";

    unsigned int pos;
    while ((pos = pattern.find("%")) < pattern.size()) {
        pattern = pattern.replace(pos, 1, ".*");
    }

}
