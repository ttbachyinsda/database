#ifndef FLEXIBLETABLE_H
#define FLEXIBLETABLE_H


#include "databasehandler/table.h"
#include "managementhandler/uic.h"
#include "recordhandler/record.h"
#include "recordhandler/flexiblerecord.h"
#include <sstream>

#define __position(x) (PAGE_SIZE-((x)+1)*4)
class FlexibleTable : public Table {
public:
    FlexibleTable();
    ~FlexibleTable();
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
    bool InsertAt(int pagenum, char* insertdata, int& rowposition);
    char* Packager(int totalsize);
    bool modifypd(int pagenum, int rownum, BufType& ct, int& newindex, int& pagenewnum);
    void Reconstruct(int pagenum, BufType b);
    char * getat(BufType b,int pageposition);
    void putat(BufType b,int pageposition,int rownum,char*data);
    int PageNum;
    int MaxRecordSize;
    int* reservedSizeInPage;
};
#endif // FLEXIBLETABLE_H
