#ifndef FIXEDSIZETABLE_H
#define FIXEDSIZETABLE_H

#include "databasehandler/table.h"
#include "managementhandler/uic.h"
#include "recordhandler/fixedsizerecord.h"
#include <sstream>

class FixedSizeTable : public Table {
public:
    FixedSizeTable();
    ~FixedSizeTable();
    bool Initialize();
    void createTable(vector<string> clname, vector<DataBaseType*> cltype);
    bool Modify(int pagenum, int rownum);
    bool DeleteAt(int pagenum, int rownum);
    bool FastModify(int pagenum, int pageposition, Record* rec);
    bool FastInsert(int& pagenum, int& pageposition, Record* rec);
    bool FastAllInsert(int& pagenum, int& pageposition, Record* rec);
    Record* FastOutput(int pagenum, int pageposition);
    void FastOutput(int pagenum, int pageposition, char* output, int& outputsize);
    string gettabletype();
    int getPageRowNum(int pagenum);
    int getPageNum();
    int getRowSize();
    int getMaxRowNum();

private:
    void PackageFromHeadFile(BufType temp);
    void PackageHeadFile(BufType temp);
    bool InsertAt(int pagenum, char* insertdata, int& rownum);
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
