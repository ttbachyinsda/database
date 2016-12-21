#include "virtualtable.h"

VirtualTable::VirtualTable()
{

}
VirtualTable::~VirtualTable()
{

}
int VirtualTable::getPageNum() { return 0; }
int VirtualTable::getMaxRowNum() { return 2147483647; }
int VirtualTable::getRowSize(int rownum) { return realdatasize[rownum]; }

bool VirtualTable::Initialize()
{
    haveinitialize = true;
    // deleted in base class.
    this->DBindex = new db_index*[this->columncount];
    for (int i = 0; i < columncount; i++)
    {
        this->DBindex[i] = 0;
    }
    return true;
}

void VirtualTable::createTable(vector<string> clname, vector<DataBaseType*> cltype)
{
    this->columncount = clname.size();
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];
    for (int i = 0; i < columncount; i++) {
        columnname[i] = clname[i];
        column[i] = cltype[i];
        multivalue[i]=true;
    }
    havecreatetable = true;
}
bool VirtualTable::DeleteAt(int pagenum, int rownum)
{
    if (rownum >= realdata.size()) return false;
    if (realdatasize[rownum] == 0) return false;
    int tempsize = realdatasize[rownum];
    char* temp = (char*)malloc(tempsize);
    memcpy(temp,realdata[rownum].data(),tempsize);

    deleteall(temp,tempsize,0,rownum);

    realdatasize[rownum]=0;
    free(temp);
    return true;
}
int VirtualTable::getPageRowNum(int pagenum)
{
    return realdata.size();
}
bool VirtualTable::FastInsert(int& pagenum, int& rownum, Record* rec)
{
    int nowsize = rec->getSize();
    char* temp = (char*)malloc(nowsize);
    memcpy(temp,rec->getData(),nowsize);

    pagenum=1;
    rownum=realdata.size();
    insertall(temp,nowsize,0,rownum);

    string t(temp,nowsize);
    realdata.push_back(t);
    realdatasize.push_back(nowsize);
    free(temp);
    return true;
}
bool VirtualTable::FastAllInsert(int& pagenum, int& rownum, Record* rec)
{
    int nowsize = rec->getSize();
    char* temp = (char*)malloc(nowsize);
    memcpy(temp,rec->getData(),nowsize);

    pagenum=1;
    rownum=realdata.size();
    insertall(temp,nowsize,0,rownum);

    string t(temp,nowsize);
    realdata.push_back(t);
    realdatasize.push_back(nowsize);

    free(temp);
    return true;
}

bool VirtualTable::FastOutput(int pagenum, int rownum,Record* rec)
{
    if (rownum >= realdata.size())
    {
        return false;
    }
    char* temp = (char*)malloc(realdatasize[rownum]);
    memcpy(temp,realdata[rownum].data(),realdatasize[rownum]);
    rec->Input(temp);
    free(temp);
    return true;
}
void VirtualTable::FastOutput(int pagenum, int rownum, char * output, int& outputsize)
{
    if (rownum >= realdata.size())
    {
        output = NULL;
        outputsize = 0;
        return;
    }
    outputsize = realdatasize[rownum];
    memcpy(output,realdata[rownum].data(),outputsize);
}
void VirtualTable::modifyall(char *data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum)
{
    int index=4;
    for (int i=0;i<columncount;i++)
        if (DBindex != NULL && DBindex[i]!=NULL)
        {
            int nowdatasize=UIC::chartoint(data+index);
            index += 4;
            ModifyindexAt(i,data+index,nowdatasize-1,prepagenum,prerownum,newpagenum,newrownum);
            index += nowdatasize;
        }
}
void VirtualTable::deleteall(char *data, int datasize, int pagenum, int rownum)
{
    int index=4;

    for (int i=0;i<columncount;i++)
        if (DBindex != NULL && DBindex[i]!=NULL)
        {

            int nowdatasize=UIC::chartoint(data+index);
            index += 4;
            string t(data+index,nowdatasize-1);
            cout<<"delete at "<<t<<' '<<pagenum<<' '<<rownum<<endl;
            DeleteindexAt(i,data+index,nowdatasize-1,pagenum,rownum);
            index += nowdatasize;
        }
}
void VirtualTable::insertall(char *data, int datasize, int pagenum, int rownum)
{

    int index=4;
    for (int i=0;i<columncount;i++)
        if (DBindex != NULL && DBindex[i]!=NULL)
        {
            int nowdatasize=UIC::chartoint(data+index);
            index += 4;
            //string t(data+index,nowdatasize);
            //cout<<"insert"<<' '<<t<<' '<<nowdatasize<<' '<<pagenum<<' '<<rownum<<endl;
            InsertindexAt(i,data+index,nowdatasize-1,pagenum,rownum);
            index += nowdatasize;
        }
}
string VirtualTable::gettabletype()
{
    return "Virtual";
}
int VirtualTable::getinfo(int reqhashnum, int pagenum, int rownum, vector<int> *infovec)
{
    //Don't need to write that
    return 0;
}
