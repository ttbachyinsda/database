#include "table.h"

Table::Table()
{
    this->havecreatetable = false;
    this->haveinitialize = false;
    this->columncount = 0;
    this->column = NULL;
    this->columnname = NULL;
    this->order = NULL;
    this->fileid = 0;
    this->FM = NULL;
    this->BPM = NULL;
}
Table::Table(string name, string filename)
{
    this->havecreatetable = false;
    this->haveinitialize = false;
    this->columncount = 0;
    this->column = NULL;
    this->columnname = NULL;
    this->order = NULL;
    this->fileid = 0;
    this->name = name;
    this->filename = filename;
    if (BPM != NULL) {
        BPM->close();
    }
    if (this->FM != NULL)
        delete this->FM;
    if (this->BPM != NULL)
        delete this->BPM;
}

Table::~Table()
{
    clearcolumn();
    if (BPM != NULL) {
        BPM->close();
    }
    if (FM != NULL){
        FM->closeFile(fileid);
    }
    if (BPM != NULL)
        delete BPM;
    if (FM != NULL)
        delete FM;
}
vector<string> Table::gettype()
{
    vector<string> temp;
    for (int i = 0; i < columncount; i++)
        temp.push_back(column[i]->getType());
    return temp;
}
string Table::getname() { return this->name; }
string Table::getfilename() { return this->filename; }
bool Table::setname(string name)
{
    if (name.length() <= MAX_NAME_SIZE) {
        this->name = name;
        return true;
    }
    return false;
}
void Table::setfilename(string filename) { this->filename = filename; }
void Table::clearcolumn()
{
    for (int i = 0; i < columncount; i++)
        if (column[i] != NULL)
            delete column[i];
    columncount = 0;
    if (column != NULL)
        delete[] column;
    if (columnname != NULL)
        delete[] columnname;
    column = NULL;
    columnname = NULL;
    if (order != NULL)
        delete[] order;
    order = NULL;
}
DataBaseType* Table::getcolumn(int i) { return column[i]; }
string Table::getcolumnname(int i) { return columnname[i]; }
bool Table::checkInsert(vector<string> data)
{
    if ((int)data.size() != columncount)
        return false;
    for (int i = 0; i < columncount; i++) {
        bool can = column[i]->checkRight(data[i]);
        if (!can)
            return false;
    }
    for (int i = 0; i < columncount; i++)
        column[i]->checkRightAndChange(data[i]);
    return true;
}
vector<string> Table::checkOutput()
{
    vector<string> temp;
    for (int i = 0; i < columncount; i++)
        temp.push_back(column[i]->output());
    return temp;
}
BufPageManager* Table::getBPM()
{
    return this->BPM;
}
int Table::getfileid()
{
    return this->fileid;
}
DataBaseType** Table::getcolumns()
{
    return this->column;
}
int Table::getcolumncount()
{
    return this->columncount;
}
