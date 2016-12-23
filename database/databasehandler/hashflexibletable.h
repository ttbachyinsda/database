#ifndef HASHFLEXIBLETABLE_H
#define HASHFLEXIBLETABLE_H

#include "../databasehandler/table.h"
#include "../managementhandler/md5.h"
#include "../managementhandler/uic.h"
#include "../recordhandler/flexiblerecord.h"
#include "../recordhandler/record.h"
#include <fstream>
#include <gmp.h>
#include <gmpxx.h>
#include <sstream>

#define __position(x) (PAGE_SIZE - ((x) + 1) * 4)
class HashFlexibleTable : public Table {
public:
    HashFlexibleTable();
    ~HashFlexibleTable();
    bool Initialize();
    void createTable(vector<string> clname, vector<DataBaseType*> cltype);
    bool DeleteAt(int pagenum, int rownum);

    virtual unsigned long getTraverseCost() override;

    bool FastInsert(int& pagenum, int& rownum, Record* rec);
    bool FastAllInsert(int& pagenum, int& rownum, Record* rec);
    bool FastOutput(int pagenum, int rownum, Record* rec);
    void FastOutput(int pagenum, int rownum, char* output, int& outputsize);
    string gettabletype();
    int getPageRowNum(int pagenum);
    int getPageNum();
    int getRowSize(int rownum);
    int getMaxRowNum();
    int getinfo(int reqhashnum, int pagenum, int rownum, vector<int>* infovec);
    bool FastFind(Record* rec);
    void createindex(vector<int> columnnum);

private:
    void PackageFromHeadFile(BufType b);
    void PackageHeadFile(BufType b);
    void Packagebeginend(BufType b);
    void Packagefrombeginend(BufType b);
    bool InsertAt(int datahash, int pagenum, char* insertdata, int& rownum);
    char* Packager(int totalsize);
    bool modifypd(int pagenum, int rownum, BufType& ct, int& newindex, int& pagenewnum);
    void Reconstruct(int pagenum, BufType b);
    char* getat(BufType b, int pageposition);
    void putat(BufType b, int pageposition, int rownum, char* data);
    void modifyall(char* data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum);
    void insertall(char* data, int datasize, int pagenum, int rownum);
    void deleteall(char* data, int datasize, int pagenum, int rownum);
    int PageNum;
    int* HBeginPageNum;
    int* HEndPageNum;

    //Hash Method
    int getHashNumc(char* data, int datasize);
    int getHashNum(string data);
    int getHashNumIn(char* data, int reqcolumn);
    void updateHashpagenum(int hashnum, int beginpagenum, int endpagenum);
    void getHashpagenum(int hashnum, int& beginpagenum, int& endpagenum);
    Record* atemprecord;
};

#endif // HASHFLEXIBLETABLE_H
