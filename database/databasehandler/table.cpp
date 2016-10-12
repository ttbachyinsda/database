#include "table.h"

Table::Table()
{
    this->FM=NULL;
    this->BPM=NULL;
}
Table::Table(string name, string filename)
{
    this->name=name;
    this->filename=filename;
    if (this->FM!=NULL) delete this->FM;
    if (this->BPM!=NULL) delete this->BPM;
}

Table::~Table()
{
    for (unsigned int i=0;i<column.size();i++)
        if (column[i]!=NULL)
            delete column[i];
}
vector<string> Table::gettype()
{
    vector<string> temp;
    for (unsigned int i=0;i<column.size();i++)
        temp.push_back(column[i]->getType());
    return temp;
}
string Table::getname()
{
    return this->name;
}
string Table::getfilename()
{
    return this->filename;
}
void Table::setname(string name)
{
    this->name=name;
}
void Table::setfilename(string filename)
{
    this->filename=filename;
}
