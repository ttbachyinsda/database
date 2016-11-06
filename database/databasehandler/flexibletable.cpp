#include "flexibletable.h"

FlexibleTable::FlexibleTable()
{
    this->PageNum = 0;
    this->MaxRecordSize = 0;
    this->reservedSizeInPage = NULL;
}
int FlexibleTable::getPageNum() { return PageNum; }
int FlexibleTable::getMaxRowNum() { return 0; }
int FlexibleTable::getRowSize() { return 0; }

bool FlexibleTable::Initialize()
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
    } else {
        PackageFromHeadFile(b);
        BPM->access(index);
    }
    free(temp);
    haveinitialize = true;
    return true;
}

void FlexibleTable::PackageFromHeadFile(BufType b)
{
    FileIterator position = 4;
    int namelen = UIC::readint(b, position);
    name = UIC::readstring(b, position, namelen);
    PageNum = UIC::readint(b, position);
    clearcolumn();
    columncount = UIC::readint(b, position);
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
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
        DataBaseType* t = UIC::realreconvert(temptype, tempsize, cannull);
        t->readcondition(b + position, position);
        column[i] = t;
        free(temptype);
        free(nullable);
    }

    MaxRecordSize = UIC::readint(b, position);
    if (reservedSizeInPage != NULL)
        delete[] reservedSizeInPage;
    reservedSizeInPage = new int[MaxRecordSize];
    for (int i = 0; i < MaxRecordSize; i++)
        reservedSizeInPage[i] = UIC::readint(b, position);
}
void FlexibleTable::PackageHeadFile(BufType b)
{
    FileIterator position = 0;
    string temp = "HEAD";
    UIC::writechar(b, position, temp.data(), 4);
    int namelen = name.length();
    UIC::writeint(b, position, namelen);
    UIC::writechar(b, position, name.data(), namelen);
    UIC::writeint(b, position, PageNum);
    UIC::writeint(b, position, columncount);
    for (int i = 0; i < columncount; i++) {
        int namelen = columnname[i].length();
        UIC::writeint(b, position, namelen);
        UIC::writechar(b, position, columnname[i].data(), namelen);
        char* temptype = (char*)malloc(4);
        char* nullable = (char*)malloc(4);
        UIC::convert(column[i], temptype, nullable);
        UIC::writechar(b, position, temptype, 4);
        UIC::writeint(b, position, column[i]->getMaxSize());
        UIC::writechar(b, position, nullable, 4);
        free(temptype);
        free(nullable);
        column[i]->writecondition(b + position, position);
    }
    UIC::writeint(b, position, MaxRecordSize);
    for (int i = 0; i < MaxRecordSize; i++)
        UIC::writeint(b, position, reservedSizeInPage[i]);
}

void FlexibleTable::createTable(vector<string> clname, vector<DataBaseType*> cltype)
{
    remove(this->filename.c_str());
    int totalheadsize = 4 * 2 + 4 * 3 + name.length();
    this->clearcolumn();
    this->columncount = clname.size();
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    for (int i = 0; i < columncount; i++) {
        totalheadsize += clname[i].length() + 4 * 4 + cltype[i]->getconditionsize();
        columnname[i] = clname[i];
        column[i] = cltype[i];
    }
    this->PageNum = 0;
    this->MaxRecordSize = max((PAGE_SIZE - totalheadsize - 16) / 4, 0);
    if (this->reservedSizeInPage != NULL)
        delete[] reservedSizeInPage;
    reservedSizeInPage = new int[MaxRecordSize];
    for (int i = 0; i < this->MaxRecordSize; i++)
        this->reservedSizeInPage[i] = PAGE_SIZE-16;
    havecreatetable = true;
}
char* FlexibleTable::Packager(int totalsize)
{
    char* temp = (char*)malloc(totalsize);
    UIC::inttochar(totalsize,temp);
    int nowsize = 4;
    for (int i = 0; i < columncount; i++) {
        int csize=column[i]->getSize();
        UIC::inttochar(csize,temp+nowsize);
        nowsize += 4;
        memcpy(temp + nowsize, column[i]->getdata(), csize);
        nowsize += csize;
    }
    return temp;
}
void FlexibleTable::Reconstruct(int pagenum, BufType b)
{
    int pagerownum = 0;
    int reservedsize = 0;
    int reservedpointer = 0;
    pagerownum = UIC::chartoint(b + 4);
    reservedsize = UIC::chartoint(b+8);
    reservedpointer = UIC::chartoint(b+12);
    char ** temprecord = new char*[pagerownum];
    for (int i=0;i<pagerownum;i++)
    {
        temprecord[i]=getat(b,UIC::chartoint(b+__position(i)));
    }
    reservedpointer=16;
    reservedsize = PAGE_SIZE-16;
    int nowrownum=0;
    for (int i=0;i<pagerownum;i++)
        if (temprecord[i]!=NULL)
        {
            int datalen=UIC::chartoint(temprecord[i]);
            putat(b,reservedpointer,nowrownum,temprecord[i]);
            reservedpointer += datalen;
            reservedsize -= datalen+4;
            nowrownum++;
        }
    UIC::inttochar(pagerownum, b + 4);
    UIC::inttochar(reservedsize,b+8);
    UIC::inttochar(reservedpointer,b+12);
    if (pagenum < this->MaxRecordSize) {
        this->reservedSizeInPage[pagenum] = reservedsize;
    }
    for (int i=0;i<pagerownum;i++)
        if (temprecord[i]!=NULL)
            free(temprecord[i]);
    delete[] temprecord;
}
char* FlexibleTable::getat(BufType b, int pageposition)
{
    if (pageposition==0) return NULL;
    int recordsize=UIC::chartoint(b+pageposition);
    char* temprecord = (char*)malloc(recordsize);
    memcpy(temprecord,b+pageposition,recordsize);
    return temprecord;
}
void FlexibleTable::putat(BufType b, int pageposition, int rownum, char *data)
{
    int datalen=UIC::chartoint(data);
    memcpy(b+pageposition,data,datalen);
    UIC::inttochar(pageposition,b+__position(rownum));
}

bool FlexibleTable::InsertAt(int pagenum, char* insertdata, int& rowposition)
{
    if (pagenum == 0)
        return false;
    int nowindex = 0;
    BufType b = BPM->getPage(fileid, pagenum, nowindex);
    int pagerownum = 0;
    int reservedsize = 0;
    int reservedpointer = 0;
    char* temp = (char*)malloc(4);
    string option1 = "PAGE";
    char* option2 = (char*)malloc(4);
    memset(option2, 0, 4);
    memcpy(temp, b, 4);
    if (UIC::equal(temp, option1.data(), 4)) {
        pagerownum = UIC::chartoint(b + 4);
        reservedsize = UIC::chartoint(b+8);
        reservedpointer = UIC::chartoint(b+12);
    } else if (UIC::equal(temp, option2, 4)) {
        memcpy(b, option1.data(), 4);
        pagerownum = 0;
        reservedsize = PAGE_SIZE-16;
        reservedpointer = 16;
        UIC::inttochar(pagerownum, b + 4);
        UIC::inttochar(reservedsize,b+8);
        UIC::inttochar(reservedpointer,b+12);

    } else {
        // cout<<"ERROR:: ????"<<endl;
        memcpy(b , option1.data(), 4);
        pagerownum = 0;
        reservedsize = PAGE_SIZE-16;
        reservedpointer = 16;
        UIC::inttochar(pagerownum, b  + 4);
        UIC::inttochar(reservedsize,b+8);
        UIC::inttochar(reservedpointer,b+12);
    }
    free(temp);
    free(option2);
    int datalen=UIC::chartoint(insertdata);
    if (datalen>reservedsize)
        return false;
    if (reservedsize>PAGE_SIZE-pagerownum*4-reservedpointer)
    {
        Reconstruct(pagenum,b);
        pagerownum = UIC::chartoint(b + 4);
        reservedsize = UIC::chartoint(b+8);
        reservedpointer = UIC::chartoint(b+12);
    }
    putat(b,reservedpointer,pagerownum,insertdata);
    datalen=UIC::chartoint(b+reservedpointer);
    pagerownum++;
    reservedsize -= datalen+4;
    reservedpointer += datalen;
    UIC::inttochar(pagerownum, b + 4);
    UIC::inttochar(reservedsize,b+8);
    UIC::inttochar(reservedpointer,b+12);
    if (pagenum < this->MaxRecordSize) {
        this->reservedSizeInPage[pagenum] = reservedsize;
    }
    rowposition=reservedpointer;
    BPM->markDirty(nowindex);
    return true;
}
bool FlexibleTable::modifypd(int pagenum, int rownum, BufType& ct,
    int& newindex, int& pagenewnum)
{
    if (pagenum > this->PageNum || pagenum == 0)
        return false;
    int nowindex = 0;
    BufType b = BPM->getPage(fileid, pagenum, nowindex);
    int pagerownum = 0;
    char* temp = (char*)malloc(4);
    string option1 = "PAGE";
    char* option2 = (char*)malloc(4);
    memset(option2, 0, 4);
    memcpy(temp, b, 4);
    if (UIC::equal(temp, option1.data(), 4)) {
        pagerownum = UIC::chartoint(b + 4);
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

bool FlexibleTable::DeleteAt(int pagenum, int rownum)
{
    BufType b;
    int nowindex, pagerownum;
    if (!modifypd(pagenum, rownum, b, nowindex, pagerownum))
        return false;
    int realnum=-1,position;
    int i;
    for (i=0;i<pagerownum;i++)
    {
        position=UIC::chartoint(b+__position(i));
        if (position!=0)
        {
            realnum++;
            if (realnum==rownum) break;
        }
    }
    if (realnum!=rownum) return false;
    int newposition=0,currentsize;
    UIC::inttochar(newposition,b+__position(i));
    currentsize=UIC::chartoint(b+position);
    int reservedsize = UIC::chartoint(b+8);
    reservedsize -= currentsize+4;
    pagerownum--;
    UIC::inttochar(pagerownum, b + 4);
    UIC::inttochar(reservedsize,b+8);
    if (pagenum < this->MaxRecordSize) {
        this->reservedSizeInPage[pagenum]=reservedsize;
    }
    BPM->markDirty(nowindex);
    return true;
}
FlexibleTable::~FlexibleTable()
{
    int index = 0;
    BufType b = BPM->getPage(fileid, 0, index);
    PackageHeadFile(b);
    BPM->markDirty(index);
    if (reservedSizeInPage != NULL)
        delete[] reservedSizeInPage;
}
bool FlexibleTable::Modify(int pagenum, int rownum)
{
    return false;
}
int FlexibleTable::getPageRowNum(int pagenum)
{
    //cout << "maxrecordsize=" << this->MaxRecordSize << endl;
    if (pagenum > this->PageNum)
        return 0;
    int index=0;
    BufType b = BPM->getPage(fileid, pagenum, index);
    int nowrownum = UIC::chartoint(b + 4);
    return nowrownum;
}
bool FlexibleTable::FastModify(int pagenum, int pageposition, Record* rec)
{
    return false;
}
bool FlexibleTable::FastInsert(int& pagenum, int& pageposition, Record* rec)
{
    int rowposition;
    bool can = InsertAt(pagenum, rec->getData(), rowposition);
    if (!can)
        return false;
    pageposition = rowposition;
    return true;
}
bool FlexibleTable::FastAllInsert(int& pagenum, int& pageposition, Record* rec)
{
    bool can = false;
    for (int i = 1; i < this->MaxRecordSize; i++)
        if (this->reservedSizeInPage[i] >= rec->getSize()) {
            pagenum = i;
            can = FastInsert(pagenum, pageposition, rec);
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
        can = FastInsert(pagenum, pageposition, rec);
        if (can)
            return true;
    }
    this->PageNum++;
    pagenum = this->PageNum;
    can = FastInsert(pagenum, pageposition, rec);
    return can;
}

Record* FlexibleTable::FastOutput(int pagenum, int pageposition)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    Record* temp = new FlexibleRecord();
    DataBaseType** t = UIC::copytype(this->column, columncount);
    temp->Initialize(t, columncount);
    temp->Input(b + pageposition);
    return temp;
}
void FlexibleTable::FastOutput(int pagenum, int pageposition, char* output, int& outputsize)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    outputsize = UIC::chartoint(b+pageposition);
    memcpy(output, b + pageposition, outputsize);
}
string FlexibleTable::gettabletype()
{
    return "Flexible";
}
