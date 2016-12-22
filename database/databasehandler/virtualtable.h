#ifndef VIRTUALTABLE_H
#define VIRTUALTABLE_H
#include "table.h"

//Virtual Table is a memory table

class VirtualTable : public Table {
public:
    VirtualTable();
    ~VirtualTable();
    int getNowRowSize(int rownum);
    bool Initialize();
    void createTable(vector<string> clname, vector<DataBaseType*> cltype);
    bool DeleteAt(int pagenum, int rownum);
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

private:
    void modifyall(char* data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum);
    void insertall(char* data, int datasize, int pagenum, int rownum);
    void deleteall(char* data, int datasize, int pagenum, int rownum);
    vector<string> realdata;
    vector<int> realdatasize;
};

#endif // VIRTUALTABLE_H
