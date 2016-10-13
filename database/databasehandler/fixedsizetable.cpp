#include "fixedsizetable.h"

FixedSizeTable::FixedSizeTable()
{

}
bool FixedSizeTable::Initialize()
{

    FM = new FileManager;
    bool canopen=FM->openFile(filename.c_str(),fileid);
    if (!canopen)
    {
        bool cancreate=FM->createFile(filename.c_str());
        if (cancreate)
        {
            canopen=FM->openFile(filename.c_str(),fileid);
            if (!canopen) return false;
        } else
        {
            return false;
        }
    }
    BPM = new BufPageManager(FM);
    int index;
    BufType b = BPM->allocPage(fileid, 0, index, false);
    if (b[0]!=11111)
    {
        PackageHeadFile(b);
        BPM->markDirty(index);
    } else
    {
        PackageFromHeadFile(b);
        BPM->access(index);
    }

    return true;
}

void FixedSizeTable::PackageFromHeadFile(BufType b)
{
    int position=0;
    int namelen;
    position += 4;
    namelen=b[position>>2];
    char *tmp = new char[namelen];
    position += 4;
    memcpy(tmp,(char*)(b)+position,namelen);
    name=tmp;
    delete tmp;
    position += MAX_NAME_SIZE;
    this->PageNum = b[position>>2];
    clearcolumn();
    position += 4;
    this->columncount = b[position>>2];
    for (int i=0;i<this->columncount;i++)
    {
        int namelen;
        position += 4;
        namelen=b[position>>2];
        char *tmp = new char[namelen];
        position += 4;
        memcpy(tmp,(char*)(b)+position,namelen);
        string c=tmp;
        columnname.push_back(c);
        delete tmp;
        position += MAX_NAME_SIZE;
        char temptype[4];
        memcpy(temptype,(char*)(b)+position,4);
        position += 4;
        int tempsize=b[position>>2];
        type* t = UIC::reconvert(temptype,tempsize);
        this->column.push_back(t);
        position += 4;
        int temporder=b[position>>2];
        this->order.push_back(temporder);
    }
    position += 4;
    this->RowSize = b[position>>2];
    position += 4;
    this->MaxRowNum = b[position>>2];
    position += 4;
    this->MaxRecordSize = b[position>>2];
    this->RowNumInPage.clear();
    for (int i=0;i<MaxRecordSize;i++)
    {
        position += 4;
        this->RowNumInPage.push_back(b[position>>2]);
    }

}
void FixedSizeTable::PackageHeadFile(BufType b)
{
    int position=0;
    string temp="HEAD";
    memcpy((char*)b,temp.c_str(),4);
    int namelen=name.length();
    position += 4;
    b[position>>2] = namelen;
    position += 4;
    memcpy((char*)(b)+position,name.c_str(),namelen);
    position += MAX_NAME_SIZE;
    b[position>>2] = this->PageNum;
    position += 4;
    b[position>>2] = this->columncount;
    for (int i=0;i<this->columncount;i++)
    {
        int namelen=columnname[i].length();
        position += 4;
        b[position>>2] = namelen;
        position += 4;
        memcpy((char*)(b)+position,columnname[i].c_str(),namelen);
        position += MAX_NAME_SIZE;
        char temptype[4];
        UIC::convert(column[i],temptype);
        memcpy((char*)(b)+position,temptype,4);
        position += 4;
        b[position>>2] = column[i]->getSize();
        position += 4;
        b[position>>2] = order[i];
    }
    position += 4;
    b[position>>2] = this->RowSize;
    position += 4;
    b[position>>2] = this->MaxRowNum;
    position += 4;
    b[position>>2] = this->MaxRecordSize;
    for (int i=0;i<MaxRecordSize;i++)
    {
        position += 4;
        b[position>>2] = this->RowNumInPage[i];
    }
    cout<<"total size= "<<position+4<<endl;
}

void FixedSizeTable::createTable(vector<string> clname, vector<string> cltype,vector<int> clsize)
{
    int totalheadsize=4*4+4*3+MAX_NAME_SIZE;
    this->clearcolumn();
    this->order.clear();
    this->RowSize=0;
    this->columncount=clname.size();
    for (int i=0;i<columncount;i++)
    {
        totalheadsize += MAX_NAME_SIZE+4*4;
        columnname.push_back(clname[i]);
        if (cltype[i]=="CHAR")
        {
            type* temp=new DatabaseChar(clsize[i]);
            column.push_back(temp);
        }
        if (cltype[i]=="INT")
        {
            type* temp=new DatabaseInt(clsize[i]);
            column.push_back(temp);
        }
        this->order.push_back(i);
        this->RowSize += clsize[i];
    }
    this->MaxRowNum=(PAGE_SIZE-8)/this->RowSize;
    this->PageNum=0;
    this->MaxRecordSize=max((PAGE_SIZE-totalheadsize-16)/4,0);
    this->RowNumInPage.clear();
    for (int i=0;i<this->MaxRecordSize;i++)
        this->RowNumInPage.push_back(0);
}
char* FixedSizeTable::Packager()
{
    char* temp = new char[this->RowSize];
    int nowsize=0;
    for (int i=0;i<columncount;i++)
    {
        cout<<"packer at:"<<nowsize<<' '<<column[i]->output()<<endl;
        memcpy(temp+nowsize,column[i]->getdata(),column[i]->getSize());
        nowsize += column[i]->getSize();
    }
    return temp;
}
bool FixedSizeTable::InsertAt(int pagenum)
{
    if (pagenum==0) return false;
    int nowindex=0;
    BufType b=BPM->getPage(fileid,pagenum,nowindex);
    int position=0; int pagerownum=0;
    char* temp = new char[4];
    string option1="PAGE";
    char* option2 = new char[4];
    memset(option2,0,4);
    memcpy(temp,(char*)(b)+position,4);
    if (UIC::equal(temp,option1.c_str(),4))
    {
        pagerownum=b[1];
    } else if (UIC::equal(temp,option2,4))
    {
        memcpy((char*)(b)+position,option1.c_str(),4);
        b[1]=0;
    } else
    {
        cout<<"ERROR:: ????"<<endl;
        memcpy((char*)(b)+position,option1.c_str(),4);
        b[1]=0;
    }
    delete temp;
    delete option2;
    if (pagerownum==this->MaxRowNum) return false;
    char* insertdata=Packager();
    position += 8+this->RowSize*pagerownum;
    cout<<"packager wz="<<position<<endl;
    memcpy((char*)(b)+position,insertdata,this->RowSize);
    b[1]++;
    if (pagenum<this->MaxRecordSize)
    {
        this->RowNumInPage[pagenum]++;
    }
    BPM->markDirty(nowindex);
    return true;
}
bool FixedSizeTable::Insert()
{
    bool can=false;
    for (int i=1;i<this->MaxRecordSize;i++)
        if (this->RowNumInPage[i]<this->MaxRowNum)
        {
            can=InsertAt(i);
            if (!can)
            {
                cout<<"ERROR:: ?????"<<endl;
            }
            if (can)
            {
                if (this->PageNum<i) this->PageNum=i;
                return true;
            }
        }
    for (int i=this->MaxRecordSize;i<=this->PageNum;i++)
    {
        can=InsertAt(i);
        if (can) return true;
    }
    this->PageNum++;
    can=InsertAt(this->PageNum);
    return can;
}
bool FixedSizeTable::DeleteAt(int pagenum, int rownum)
{
    if (pagenum>this->PageNum || pagenum==0) return false;
    int nowindex=0;
    BufType b=BPM->getPage(fileid,pagenum,nowindex);
    int position=0; int pagerownum=0;
    char* temp = new char[4];
    string option1="PAGE";
    char* option2 = new char[4];
    memset(option2,0,4);
    memcpy(temp,(char*)(b)+position,4);
    if (UIC::equal(temp,option1.c_str(),4))
    {
        pagerownum=b[1];
    } else if (UIC::equal(temp,option2,4))
    {
        delete temp;
        delete option2;
        return false;
    } else
    {
        cout<<"ERROR:: ???"<<endl;
        delete temp;
        delete option2;
        return false;
    }
    delete temp;
    delete option2;
    if (rownum>=pagerownum) return false;
    int position1=8+this->RowSize*(pagerownum-1);
    int position2=8+this->RowSize*rownum;
    temp = new char[this->RowSize];
    memcpy(temp,(char*)(b)+position1,this->RowSize);
    memcpy((char*)(b)+position2,temp,this->RowSize);
    b[1]--;
    if (pagenum<this->MaxRecordSize)
    {
        this->RowNumInPage[pagenum]--;
    }
    BPM->markDirty(nowindex);
    return true;
}
bool FixedSizeTable::FindAt(int pagenum, int rownum)
{
    if (pagenum>this->PageNum) return false;
    int nowindex=0;
    BufType b=BPM->getPage(fileid,pagenum,nowindex);
    int position=0; int pagerownum=0;
    char* temp = new char[4];
    string option1="PAGE";
    char* option2 = new char[4];
    memset(option2,0,4);
    memcpy(temp,(char*)(b)+position,4);
    if (UIC::equal(temp,option1.c_str(),4))
    {
        pagerownum=b[1];
    } else if (UIC::equal(temp,option2,4))
    {
        delete temp;
        delete option2;
        return false;
    } else
    {
        cout<<"ERROR:: ???"<<endl;
        delete temp;
        delete option2;
        return false;
    }
    delete temp;
    delete option2;
    if (rownum>=pagerownum) return false;
    UnPackager(b,8+this->RowSize*rownum);
    BPM->access(nowindex);
    return true;
}
void FixedSizeTable::UnPackager(BufType b, int position)
{
    cout<<"unpack position="<<position<<endl;
    char* temp = new char[this->RowSize];
    memcpy(temp,(char*)(b)+position,this->RowSize);
    int totalsize=0;
    for (int i=0;i<columncount;i++)
    {
        cout<<"unpacker at:"<<totalsize<<endl;
        int size=column[i]->getSize();
        column[i]->checkRightAndChange(temp+totalsize,size);
        totalsize += size;
    }
}
FixedSizeTable::~FixedSizeTable()
{
    int index=0;
    BufType b = BPM->allocPage(fileid, 0, index, false);
    PackageHeadFile(b);
    BPM->markDirty(index);
}
