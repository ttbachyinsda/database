//
// Created by jameshuang on 16-12-10.
//

#include "ramtable.h"
#include <iostream>

RamTable::RamTable() {

}

RamTable::~RamTable() {
    for (char* datum : this->data)
        delete datum;
}

bool RamTable::Initialize() {
    // Init from RAM, always empty
    haveinitialize = true;
    return true;
}

void RamTable::createTable(vector<string> clname, vector<DataBaseType *> cltype) {
    this->clearcolumn();
    this->columncount = (int) clname.size();

    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];

    for (int i = 0; i < columncount; i++) {
        columnname[i] = clname[i];
        column[i] = cltype[i];
        multivalue[i] = true;
    }

    havecreatetable = true;
}

bool RamTable::DeleteAt(int pagenum, int rownum) {
    std::cerr << "Delete attempt on a ram table." << std::endl;
    assert(false);
    return false;
}

bool RamTable::FastInsert(int &pagenum, int &rownum, Record *rec) {
    pagenum = 0;
    rownum = 0;

    // TODO: Check newRecord header has an integer.
    char* newRecord = new char[rec->getSize()];
    memcpy(newRecord, rec->getData(), (size_t) rec->getSize());

    data.push_back(newRecord);
    sizes.push_back(rec->getSize());
    return true;
}

bool RamTable::FastAllInsert(int &pagenum, int &rownum, Record *rec) {
    return this->FastInsert(pagenum, rownum, rec);
}

bool RamTable::FastOutput(int pagenum, int rownum, Record *rec) {
    rec->Input(data[pagenum]);
    return true;
}

void RamTable::FastOutput(int pagenum, int rownum, char *output, int &outputsize) {
    memcpy(output, data[pagenum], (size_t) sizes[pagenum]);
}

string RamTable::gettabletype() {
    return "Ram";
}

int RamTable::getPageRowNum(int pagenum) {
    std::cerr << "getPageRowNum attempt on a ram table." << std::endl;
    assert(false);
    return 0;
}

int RamTable::getPageNum() {
    std::cerr << "getPageNum attempt on a ram table." << std::endl;
    assert(false);
    return 0;
}

int RamTable::getRowSize() {
    std::cerr << "getRowSize attempt on a ram table." << std::endl;
    assert(false);
    return 0;
}

int RamTable::getMaxRowNum() {
    std::cerr << "getMaxRowNum attempt on a ram table." << std::endl;
    assert(false);
    return 0;
}
