#ifndef FIXEDSIZETABLE_H
#define FIXEDSIZETABLE_H

#include "../databasehandler/table.h"
#include "../managementhandler/uic.h"
#include "../recordhandler/fixedsizerecord.h"
#include <sstream>
#define __FIXPOSITION(x) (8+(x)*this->RowSize)
class FixedSizeTable : public Table {
public:
    FixedSizeTable();
    ~FixedSizeTable();
    bool Initialize();
    void createTable(vector<string> clname, vector<DataBaseType*> cltype);
    bool DeleteAt(int pagenum, int rownum);
    bool FastInsert(int& pagenum, int& rownum, Record* rec);
    bool FastAllInsert(int& pagenum, int& rownum, Record* rec);
    bool FastOutput(int pagenum, int rownum, Record *rec);
    void FastOutput(int pagenum, int rownum, char* output, int& outputsize);
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
    void modifyall(char* data,int datasize,int prepagenum,int prerownum,int newpagenum,int newrownum);
    void insertall(char* data,int datasize,int pagenum,int rownum);
    void deleteall(char* data,int datasize,int pagenum,int rownum);
    int PageNum;
    int RowSize;
    int MaxRowNum;
    int MaxRecordSize;
    int* RowNumInPage;
};

#endif // FIXEDSIZETABLE_H
