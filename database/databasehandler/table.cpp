#include "table.h"

Table::Table()
{
    this->havecreatetable = false;
    this->haveinitialize = false;
    this->majornum=0;
    this->columncount = 0;
    this->column = NULL;
    this->columnname = NULL;
    this->fileid = 0;
    this->FM = NULL;
    this->BPM = NULL;
    this->DBindex=NULL;
    this->multivalue=NULL;
}
Table::Table(string name, string filename)
{
    this->havecreatetable = false;
    this->haveinitialize = false;
    this->majornum=0;
    this->columncount = 0;
    this->column = NULL;
    this->columnname = NULL;
    this->DBindex=NULL;
    this->fileid = 0;
    this->name = name;
    this->multivalue = NULL;
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
    clearindex();
    if (BPM != NULL) {
        BPM->close();
    }
    if (FM != NULL) {
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
    if (column==NULL) return;
    for (int i = 0; i < columncount; i++)
        if (column[i] != NULL)
            delete column[i];
    if (column != NULL)
        delete[] column;
    if (columnname != NULL)
        delete[] columnname;
    column = NULL;
    columnname = NULL;
    if (multivalue != NULL)
        delete[] multivalue;
    multivalue=NULL;
}
void Table::clearindex()
{
    if (DBindex==NULL) return;
    for (int i = 0; i < columncount; i++)
        if (DBindex[i] != NULL)
            delete DBindex[i];
    if (DBindex != NULL)
        delete[] DBindex;
    DBindex=NULL;
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
int Table::getmajornum()
{
    return this->majornum;
}
void Table::setmajornum(int nownum)
{
    this->majornum=nownum;
}
db_index** Table::getindexes()
{
    return this->DBindex;
}

void Table::readindex()
{
    clearindex();
    this->DBindex=new db_index*[this->columncount];
    for (int i=0;i<columncount;i++)
    {
        string t=UIC::inttostring(i);
        string temp=filename+t;
        char* tst=(char*)malloc(temp.length()+1);
        memcpy(tst,temp.data(),temp.length());
        tst[temp.length()]='\0';
        int can=access(temp.c_str(),0);
        if (can!=-1)
        {
            this->DBindex[i]=new db_index(tst,false,multivalue[i]);
        } else
            this->DBindex[i]=NULL;
        free(tst);
    }
}
void Table::createemptyindex(int i)
{
    string t=UIC::inttostring(i);
    string temp=filename+t;
    char* tst=(char*)malloc(temp.length()+1);
    memcpy(tst,temp.data(),temp.length());
    tst[temp.length()]='\0';
    if (this->DBindex==NULL) readindex();
    this->DBindex[i]=new db_index(tst,true,multivalue[i]);
    free(tst);
}

int Table::getColumnIndexByName(const string &name)
{
    for (int i = 0; i < columncount; ++ i) {
        if (columnname[i] == name)
            return i;
    }
    return -1;
}

void Table::setmultivalue(int i,bool istrue)
{
    multivalue[i]=istrue;
}
bool Table::getmultivalue(int i)
{
    return multivalue[i];
}
void Table::Nullindex()
{
    clearindex();
    this->DBindex=new db_index*[this->columncount];
    for (int i=0;i<columncount;i++)
    {
        this->DBindex[i]=NULL;
    }
}
void Table::InsertindexAt(int num, char *insertdata, int datalen, int pagenum, int pageposition)
{
    this->DBindex[num]->insert(insertdata,datalen,pagenum,pageposition);
}
void Table::ModifyindexAt(int num, char *modifydata, int datalen, int prepagenum, int prepageposition, int newpagenum, int newpageposition)
{
    this->DBindex[num]->update(modifydata,datalen,prepagenum,prepageposition,newpagenum,newpageposition);
}
void Table::DeleteindexAt(int num, char *deletedata, int datalen, int pagenum, int pageposition)
{
    this->DBindex[num]->remove(deletedata,datalen,pagenum,pageposition);
}
