#ifndef FIXEDSIZETABLE_H
#define FIXEDSIZETABLE_H

#include "databasehandler/table.h"

class FixedSizeTable : public Table
{
public:
    FixedSizeTable();
    bool Initialize();
private:
    void PackageFromHeadFile(carrier &temp);
    void PackageHeadFile(carrier &temp);
    int PageNum;
    int MaxRowNum;
    int MaxRecordSize;
    int headindex;
    vector<int> PageIndex;
    vector<int> RowNumInPage;
};

#endif // FIXEDSIZETABLE_H
