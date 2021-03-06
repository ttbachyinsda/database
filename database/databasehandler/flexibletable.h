#ifndef FLEXIBLETABLE_H
#define FLEXIBLETABLE_H

#include "../databasehandler/table.h"
#include "../managementhandler/uic.h"
#include "../recordhandler/flexiblerecord.h"
#include "../recordhandler/record.h"
#include <fstream>
#include <sstream>
using namespace std;

#define __position(x) (PAGE_SIZE - ((x) + 1) * 4)
class FlexibleTable : public Table {
public:
    FlexibleTable();
    ~FlexibleTable();
    bool Initialize();

    virtual unsigned long getTraverseCost() override;

    void createTable(vector<string> clname, vector<DataBaseType*> cltype);
    bool DeleteAt(int pagenum, int rownum);
    bool FastAllInsert(int& pagenum, int& rownum, Record* rec);
    bool FastOutput(int pagenum, int rownum, Record* rec);
    void FastOutput(int pagenum, int rownum, char* output, int& outputsize);
    string gettabletype();
    int getPageRowNum(int pagenum);
    int getPageNum();
    int getRowSize(int rownum);
    int getMaxRowNum();
    void createindex(vector<int> columnnum);
    int getinfo(int reqhashnum, int pagenum, int rownum, vector<int>* infovec);

private:
    void PackageFromHeadFile(BufType temp);
    void PackageHeadFile(BufType temp);
    bool FastInsert(int& pagenum, int& rownum, Record* rec);
    bool InsertAt(int pagenum, char* insertdata, int& rownum);
    char* Packager(int totalsize);
    bool modifypd(int pagenum, int rownum, BufType& ct, int& newindex, int& pagenewnum);
    void Reconstruct(int pagenum, BufType b);
    char* getat(BufType b, int pageposition);
    void putat(BufType b, int pageposition, int rownum, char* data);
    void modifyall(char* data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum);
    void insertall(char* data, int datasize, int pagenum, int rownum);
    void deleteall(char* data, int datasize, int pagenum, int rownum);
    int PageNum;
    int MaxRecordSize;
    int* reservedSizeInPage;
};
#endif // FLEXIBLETABLE_H
