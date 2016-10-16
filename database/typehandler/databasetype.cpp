#include "databasetype.h"

DataBaseType::DataBaseType()
{
    size = 0;
    data = NULL;
}
char* DataBaseType::getdata()
{
    return data;
}
void DataBaseType::printdata(string testinfo)
{
    cout << "Now begin " << testinfo << endl;
    for (int i = 0; i < size; i++) {
        int k = data[i];
        cout << "No." << i << " is: " << k << endl;
    }
    cout << "Now end " << testinfo << endl;
}
DataBaseType::~DataBaseType()
{
    if (data != NULL) {
        free(data);
        data = NULL;
    }
}
