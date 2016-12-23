#include "iterator.h"

Iterator::Iterator()
{
}

Iterator::~Iterator()
{
}
Iterator& Iterator::operator++()
{
    nextrow();
    return *this;
}
bool Iterator::find(string input, int columnnum)
{
    input = compile(input, columnnum);
    cout << input << endl;
    return false;
}
string Iterator::compile(string input, int columnnum)
{
    DataBaseType* temp = this->nowtable->getcolumn(columnnum);
    int tempsize = temp->getRealSize();
    int inputlen = input.length();
    if (tempsize < inputlen)
        inputlen = tempsize;
    string temptype = temp->getType();
    if (temptype[6] == 'I') {
        char* tempdata = (char*)malloc(tempsize);
        memset(tempdata, '0', tempsize);
        memcpy(tempdata + tempsize - inputlen, input.c_str(), inputlen);
        string t(tempdata, tempsize);
        free(tempdata);
        return t;
    } else {
        char* tempdata = (char*)malloc(tempsize);
        memset(tempdata, 0, tempsize);
        memcpy(tempdata, input.c_str(), inputlen);
        string t(tempdata, tempsize);
        free(tempdata);
        return t;
    }
}
