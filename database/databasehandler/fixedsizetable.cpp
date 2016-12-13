#include "fixedsizetable.h"

FixedSizeTable::FixedSizeTable()
{
    this->PageNum = 0;
    this->MaxRecordSize = 0;
    this->MaxRowNum = 0;
    this->RowSize = 0;
    this->RowNumInPage = NULL;
}
int FixedSizeTable::getPageNum() { return PageNum; }
int FixedSizeTable::getMaxRowNum() { return MaxRowNum; }
int FixedSizeTable::getRowSize(int rownum) { return RowSize; }

bool FixedSizeTable::Initialize()
{
    FM = new FileManager;
    bool canopen = FM->openFile(filename.data(), fileid);
    if (!canopen) {
        bool cancreate = FM->createFile(filename.data());
        if (cancreate) {
            canopen = FM->openFile(filename.data(), fileid);
            if (!canopen)
                return false;
        } else {
            return false;
        }
    }
    BPM = new BufPageManager(FM);
    int index;
    BufType b = BPM->allocPage(fileid, 0, index, true);
    /*
cout<<"Now begin "<<"testment"<<endl;
for (int i=0;i<PAGE_INT_NUM;i++)
{
    int k=b[i];
    cout<<"No."<<i<<" is: "<<k<<endl;
}
cout<<"Now end "<<"testment"<<endl;
*/
    char* temp = (char*)malloc(4);
    memcpy(temp, b, 4);
    string ob1 = "HEAD";
    if (!UIC::equal(temp, ob1.data(), 4) || havecreatetable) {
        PackageHeadFile(b);
        BPM->markDirty(index);
        Nullindex();
    } else {
        PackageFromHeadFile(b);
        BPM->access(index);
        readindex();
    }
    free(temp);
    haveinitialize = true;
    return true;
}

void FixedSizeTable::PackageFromHeadFile(BufType b)
{
    FileIterator position = 4;
    RowSize = UIC::readint(b, position);
    MaxRowNum = UIC::readint(b, position);
    int namelen = UIC::readint(b, position);
    name = UIC::readstring(b, position, namelen);
    PageNum = UIC::readint(b, position);
    majornum = UIC::readint(b,position);
    clearcolumn();
    columncount = UIC::readint(b, position);
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];
    for (int i = 0; i < this->columncount; i++) {
        int namelen = UIC::readint(b, position);
        columnname[i] = UIC::readstring(b, position, namelen);
        char* temptype = (char*)malloc(4);
        UIC::readchar(b, position, temptype, 4);
        int tempsize = UIC::readint(b, position);
        char* nullable = (char*)malloc(4);
        UIC::readchar(b, position, nullable, 4);
        bool cannull;
        if (nullable[0] == 'A')
            cannull = true;
        else
            cannull = false;
        char* canmulti = (char*)malloc(4);
        UIC::readchar(b, position, canmulti, 4);
        if (canmulti[0] == 'A')
            multivalue[i]=true;
        else
            multivalue[i]=false;
        int conditionsize=UIC::readint(b,position);
        DataBaseType* t = UIC::realreconvert(temptype, tempsize, cannull);
        t->readcondition(b + position,conditionsize, position);
        column[i] = t;
        free(temptype);
        free(nullable);
        free(canmulti);
    }
    MaxRecordSize = UIC::readint(b, position);
    if (RowNumInPage != NULL)
        delete[] RowNumInPage;
    RowNumInPage = new int[MaxRecordSize];
    for (int i = 0; i < MaxRecordSize; i++)
        RowNumInPage[i] = UIC::readint(b, position);
}
void FixedSizeTable::PackageHeadFile(BufType b)
{
    FileIterator position = 0;
    string temp = "HEAD";
    UIC::writechar(b, position, temp.data(), 4);
    UIC::writeint(b, position, RowSize);
    UIC::writeint(b, position, MaxRowNum);
    int namelen = name.length();
    UIC::writeint(b, position, namelen);
    UIC::writechar(b, position, name.data(), namelen);
    UIC::writeint(b, position, PageNum);
    UIC::writeint(b, position, majornum);
    UIC::writeint(b, position, columncount);
    for (int i = 0; i < columncount; i++) {
        int namelen = columnname[i].length();
        UIC::writeint(b, position, namelen);
        UIC::writechar(b, position, columnname[i].data(), namelen);
        char* temptype = (char*)malloc(4);
        char* nullable = (char*)malloc(4);
        char* canmulti = (char*)malloc(4);
        UIC::convert(column[i], temptype, nullable);
        UIC::convertmulti(multivalue[i],canmulti);
        UIC::writechar(b, position, temptype, 4);
        UIC::writeint(b, position, column[i]->getSize());
        UIC::writechar(b, position, nullable, 4);
        UIC::writechar(b, position, canmulti, 4);
        free(temptype);
        free(nullable);
        free(canmulti);
        UIC::writeint(b,position,column[i]->getconditionsize());
        column[i]->writecondition(b + position, position);
    }
    UIC::writeint(b, position, MaxRecordSize);
    for (int i = 0; i < MaxRecordSize; i++)
        UIC::writeint(b, position, RowNumInPage[i]);
}

void FixedSizeTable::createTable(vector<string> clname, vector<DataBaseType*> cltype)
{
    remove(this->filename.c_str());
    int totalheadsize = 4 * 5 + 4 * 3 + name.length();
    this->clearcolumn();
    this->RowSize = 0;
    this->columncount = clname.size();
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];
    for (int i = 0; i < columncount; i++) {
        totalheadsize += clname[i].length() + 4 * 6 + cltype[i]->getconditionsize();
        columnname[i] = clname[i];
        column[i] = cltype[i];
        multivalue[i]=true;
        this->RowSize += cltype[i]->getSize();
    }
    this->MaxRowNum = (PAGE_SIZE - 8) / this->RowSize;
    this->PageNum = 0;
    this->MaxRecordSize = max((PAGE_SIZE - totalheadsize - 16) / 4, 0);
    if (this->RowNumInPage != NULL)
        delete[] RowNumInPage;
    RowNumInPage = new int[MaxRecordSize];
    for (int i = 0; i < this->MaxRecordSize; i++)
        this->RowNumInPage[i] = 0;
    havecreatetable = true;
}
char* FixedSizeTable::Packager()
{
    char* temp = (char*)malloc(this->RowSize);
    int nowsize = 0;
    for (int i = 0; i < columncount; i++) {
        memcpy(temp + nowsize, column[i]->getdata(), column[i]->getSize());
        nowsize += column[i]->getSize();
    }
    return temp;
}
bool FixedSizeTable::InsertAt(int pagenum, char* insertdata, int& rownum)
{
    if (pagenum == 0)
        return false;
    int nowindex = 0;
    BufType b = BPM->getPage(fileid, pagenum, nowindex);
    int position = 0;
    int pagerownum = 0;
    char* temp = (char*)malloc(4);
    string option1 = "PAGE";
    char* option2 = (char*)malloc(4);
    memset(option2, 0, 4);
    memcpy(temp, b + position, 4);
    if (UIC::equal(temp, option1.data(), 4)) {
        pagerownum = UIC::chartoint(b + position + 4);
    } else if (UIC::equal(temp, option2, 4)) {
        memcpy(b + position, option1.data(), 4);
        UIC::inttochar(0, b + position + 4);
        pagerownum = 0;
    } else {
        // cout<<"ERROR:: ????"<<endl;
        memcpy(b + position, option1.data(), 4);
        UIC::inttochar(0, b + position + 4);
        pagerownum = 0;
    }
    free(temp);
    free(option2);
    if (pagerownum == this->MaxRowNum)
        return false;
    position += 8 + this->RowSize * pagerownum;
    rownum = pagerownum;

    insertall(insertdata,this->RowSize,pagenum,rownum);

    memcpy(b + position, insertdata, this->RowSize);
    pagerownum++;
    UIC::inttochar(pagerownum, b + 4);
    if (pagenum < this->MaxRecordSize) {
        this->RowNumInPage[pagenum]++;
    }
    BPM->markDirty(nowindex);
    return true;
}
bool FixedSizeTable::modifypd(int pagenum, int rownum, BufType& ct,
    int& newindex, int& pagenewnum)
{
    if (pagenum > this->PageNum || pagenum == 0)
        return false;
    int nowindex = 0;
    BufType b = BPM->getPage(fileid, pagenum, nowindex);
    int position = 0;
    int pagerownum = 0;
    char* temp = (char*)malloc(4);
    string option1 = "PAGE";
    char* option2 = (char*)malloc(4);
    memset(option2, 0, 4);
    memcpy(temp, b + position, 4);
    if (UIC::equal(temp, option1.data(), 4)) {
        pagerownum = UIC::chartoint(b + position + 4);
    } else if (UIC::equal(temp, option2, 4)) {
        free(temp);
        free(option2);
        pagerownum = 0;
        return false;
    } else {
        cout << "ERROR:: ???" << endl;
        free(temp);
        free(option2);
        pagerownum = 0;
        return false;
    }
    free(temp);
    free(option2);
    if (rownum >= pagerownum)
        return false;
    ct = b;
    newindex = nowindex;
    pagenewnum = pagerownum;
    return true;
}

bool FixedSizeTable::DeleteAt(int pagenum, int rownum)
{
    BufType b;
    int nowindex, pagerownum;
    if (!modifypd(pagenum, rownum, b, nowindex, pagerownum))
        return false;
    int position1 = 8 + this->RowSize * (pagerownum - 1);
    int position2 = 8 + this->RowSize * rownum;
    char* temp = (char*)malloc(this->RowSize);

    deleteall(b+position2,this->RowSize,pagenum,rownum);

    if (position1!=position2)
        modifyall(b+position1,this->RowSize,pagenum,position1,pagenum,position2);

    memcpy(temp, b + position1, this->RowSize);
    memcpy(b + position2, temp, this->RowSize);

    pagerownum--;
    UIC::inttochar(pagerownum, b + 4);
    if (pagenum < this->MaxRecordSize) {
        this->RowNumInPage[pagenum]--;
    }
    BPM->markDirty(nowindex);
    free(temp);
    return true;
}
void FixedSizeTable::UnPackager(BufType b, int position)
{
    // cout<<"unpack position="<<position<<endl;
    char* temp = (char*)malloc(this->RowSize);
    memcpy(temp, b + position, this->RowSize);
    int totalsize = 0;
    for (int i = 0; i < columncount; i++) {
        // cout<<"unpacker at:"<<totalsize<<endl;
        column[i]->read(temp + totalsize,column[i]->getSize(),totalsize);
    }
    free(temp);
}
FixedSizeTable::~FixedSizeTable()
{
    int index = 0;
    BufType b = BPM->getPage(fileid, 0, index);
    PackageHeadFile(b);
    BPM->markDirty(index);
    if (RowNumInPage != NULL)
        delete[] RowNumInPage;
}
int FixedSizeTable::getPageRowNum(int pagenum)
{
    //cout << "maxrecordsize=" << this->MaxRecordSize << endl;
    if (pagenum > this->PageNum)
        return 0;
    if (pagenum < this->MaxRecordSize)
        return RowNumInPage[pagenum];
    int index = 0;
    BufType b = BPM->getPage(fileid, pagenum, index);
    int nowrownum = UIC::chartoint(b + 4);
    return nowrownum;
}
bool FixedSizeTable::FastInsert(int& pagenum, int& rownum, Record* rec)
{
    bool can = InsertAt(pagenum, rec->getData(), rownum);
    if (!can)
        return false;
    return true;
}
bool FixedSizeTable::FastAllInsert(int& pagenum, int& rownum, Record* rec)
{
    bool can = false;
    for (int i = min(this->MaxRecordSize-1,this->PageNum); i > 0; i--)
        if (this->RowNumInPage[i] < this->MaxRowNum) {
            pagenum = i;
            can = FastInsert(pagenum, rownum, rec);
            if (!can) {
                cout << "ERROR:: ?????" << endl;
            }
            if (can) {
                if (this->PageNum < i)
                    this->PageNum = i;
                return true;
            }
        }
    for (int i = this->MaxRecordSize; i <= this->PageNum; i++) {
        pagenum = i;
        can = FastInsert(pagenum, rownum, rec);
        if (can)
            return true;
    }
    this->PageNum++;
    pagenum = this->PageNum;
    can = FastInsert(pagenum, rownum, rec);
    return can;
}

bool FixedSizeTable::FastOutput(int pagenum, int rownum,Record* rec)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    rec->Input(b + __FIXPOSITION(rownum));
    return true;
}
void FixedSizeTable::FastOutput(int pagenum, int rownum, char* output, int& outputsize)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    outputsize = this->RowSize;
    memcpy(output, b + __FIXPOSITION(rownum), outputsize);
}
void FixedSizeTable::modifyall(char *data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum)
{
    int index=0;
    for (int i=0;i<columncount;i++)
        if (DBindex != NULL && DBindex[i]!=NULL)
        {
            int nowdatasize=column[i]->getSize();
            ModifyindexAt(i,data+index,nowdatasize-1,prepagenum,prerownum,newpagenum,newrownum);
            index += nowdatasize;
        }
}
void FixedSizeTable::deleteall(char *data, int datasize, int pagenum, int rownum)
{
    int index=0;
    for (int i=0;i<columncount;i++)
        if (DBindex != NULL && DBindex[i]!=NULL)
        {
            int nowdatasize=column[i]->getSize();
            string t(data+index,nowdatasize-1);
            cout<<"delete data at "<<t<<' '<<pagenum<<' '<<rownum<<endl;
            DeleteindexAt(i,data+index,nowdatasize-1,pagenum,rownum);
            index += nowdatasize;
        }
}
void FixedSizeTable::insertall(char *data, int datasize, int pagenum, int rownum)
{
    int index=0;
    for (int i=0;i<columncount;i++)
        if (DBindex != NULL && DBindex[i]!=NULL)
        {
            int nowdatasize=column[i]->getSize();
            //string t(data+index,nowdatasize-1);
            //cout<<"insert at "<<t<<' '<<pagenum<<' '<<rownum<<endl;
            InsertindexAt(i,data+index,nowdatasize-1,pagenum,rownum);
            index += nowdatasize;
        }
}
string FixedSizeTable::gettabletype()
{
    return "Fixed";
}
