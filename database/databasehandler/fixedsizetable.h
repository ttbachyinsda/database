#ifndef FIXEDSIZETABLE_H
#define FIXEDSIZETABLE_H

#include "databasehandler/table.h"
#include "managementhandler/uic.h"
#include <sstream>

class FixedSizeTable : public Table {
public:
    FixedSizeTable();
    ~FixedSizeTable();
    bool Initialize();
    void createTable(vector<string> clname, vector<string> cltype, vector<int> clsize);
    bool Insert();
    bool Modify(int pagenum, int rownum);
    bool DeleteAt(int pagenum, int rownum);
    bool FindAt(int pagenum, int rownum);
    int getPageRowNum(int pagenum);
    int getPageNum();
    int getRowSize();
    int getMaxRowNum();

private:
    void PackageFromHeadFile(BufType temp);
    void PackageHeadFile(BufType temp);
    bool InsertAt(int pagenum);
    char* Packager();
    bool modifypd(int pagenum, int rownum, BufType& ct, int& newindex, int& pagenewnum);
    void UnPackager(BufType b, int position);
    int PageNum;
    int RowSize;
    int MaxRowNum;
    int MaxRecordSize;
    int* RowNumInPage;
};

#endif // FIXEDSIZETABLE_H
