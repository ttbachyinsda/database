//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_RAMTABLE_H
#define DATABASE_RAMTABLE_H

#include "../databasehandler/table.h"

class RamTable : public Table {
public:
    RamTable();
    ~RamTable();
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
    std::vector<char*> data;
    std::vector<int> sizes;
};


#endif //DATABASE_RAMTABLE_H
