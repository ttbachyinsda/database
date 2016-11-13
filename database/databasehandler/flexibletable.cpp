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

void FlexibleTable::PackageFromHeadFile(BufType b)
{
    FileIterator position = 4;
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
        DataBaseType* t = UIC::realreconvert(temptype, tempsize, cannull);
        int conditionsize=UIC::readint(b,position);
        t->readcondition(b + position,conditionsize, position);
        column[i] = t;
        free(temptype);
        free(nullable);
        free(canmulti);
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
    UIC::writeint(b,position,majornum);
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
        UIC::writeint(b, position, column[i]->getMaxSize());
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
        UIC::writeint(b, position, reservedSizeInPage[i]);
}

void FlexibleTable::createTable(vector<string> clname, vector<DataBaseType*> cltype)
{
    remove(this->filename.c_str());
    int totalheadsize = 4 * 3 + 4 * 3 + name.length();
    this->clearcolumn();
    this->columncount = clname.size();
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];
    for (int i = 0; i < columncount; i++) {
        totalheadsize += clname[i].length() + 4 * 6 + cltype[i]->getconditionsize();
        columnname[i] = clname[i];
        column[i] = cltype[i];
        multivalue[i]=true;
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
    cout<<"do a reconstruct"<<endl;
    int pagerownum = 0;
    int reservedsize = 0;
    int reservedpointer = 0;
    pagerownum = UIC::chartoint(b + 4);
    reservedsize = UIC::chartoint(b+8);
    reservedpointer = UIC::chartoint(b+12);
    char ** temprecord = new char*[pagerownum];
    int *preposition = new int[pagerownum];
    for (int i=0;i<pagerownum;i++)
    {
        preposition[i]=UIC::chartoint(b+__position(i));
        temprecord[i]=getat(b,preposition[i]);
    }
    reservedpointer=16;
    reservedsize = PAGE_SIZE-16;
    int nowrownum=0;
    for (int i=0;i<pagerownum;i++)
        if (temprecord[i]!=NULL)
        {
            int datalen=UIC::chartoint(temprecord[i]);
            modifyall(temprecord[i],datalen,pagenum,preposition[i],pagenum,reservedpointer);
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

bool FlexibleTable::InsertAt(int pagenum, char* insertdata, int& rownum)
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
    {
        //cout<<"error becaule datalen>reservedsize"<<' '<<datalen<<' '<<reservedsize<<endl;
        return false;
    }
    if (reservedsize>PAGE_SIZE-pagerownum*4-reservedpointer)
    {
        Reconstruct(pagenum,b);
        pagerownum = UIC::chartoint(b + 4);
        reservedsize = UIC::chartoint(b+8);
        reservedpointer = UIC::chartoint(b+12);
    }

    putat(b,reservedpointer,pagerownum,insertdata);
    rownum=pagerownum;

    insertall(insertdata,datalen,pagenum,rownum);

    //if (pagenum==1 && rownum<3)
    //cout<<rownum<<' '<<reservedpointer<<' '<<datalen<<endl;
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
    int position;
    position=UIC::chartoint(b+__position(rownum));
    if (position==0) return false;


    int newposition=0,currentsize;
    currentsize=UIC::chartoint(b+position);

    deleteall(b+position,currentsize,pagenum,rownum);

    UIC::inttochar(newposition,b+__position(rownum));

    int reservedsize = UIC::chartoint(b+8);
    reservedsize -= currentsize+4;
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
bool FlexibleTable::FastInsert(int& pagenum, int& rownum, Record* rec)
{
    bool can = InsertAt(pagenum, rec->getData(), rownum);
    if (!can)
        return false;
    return true;
}
bool FlexibleTable::FastAllInsert(int& pagenum, int& rownum, Record* rec)
{
    bool can = false;
    for (int i = min(this->MaxRecordSize-1,this->PageNum); i > 0; i--)
        if (this->reservedSizeInPage[i] >= rec->getSize()) {
            pagenum = i;
            can = FastInsert(pagenum, rownum, rec);
            if (!can) {
                cout << "ERROR:: ?????" <<' '<<i<<' '<<this->reservedSizeInPage[i]<<' '<<rec->getSize()<< endl;
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

bool FlexibleTable::FastOutput(int pagenum, int rownum, Record *rec)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    //cout<<"position at "<<__position(rownum)<<endl;
    int pageposition = UIC::chartoint(b+__position(rownum));
    rec->Input(b + pageposition);
    return true;
}
void FlexibleTable::FastOutput(int pagenum, int rownum, char* output, int& outputsize)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    int pageposition = UIC::chartoint(b+__position(rownum));
    outputsize = UIC::chartoint(b+pageposition);
    memcpy(output, b + pageposition, outputsize);
}
void FlexibleTable::modifyall(char *data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum)
{
    int index=4;
    for (int i=0;i<columncount;i++)
        if (DBindex[i]!=NULL)
        {
            int nowdatasize=UIC::chartoint(data+index);
            index += 4;
            ModifyindexAt(i,data+index,nowdatasize-1,prepagenum,prerownum,newpagenum,newrownum);
            index += nowdatasize;
        }
}
void FlexibleTable::deleteall(char *data, int datasize, int pagenum, int rownum)
{
    int index=4;

    for (int i=0;i<columncount;i++)
        if (DBindex[i]!=NULL)
        {

            int nowdatasize=UIC::chartoint(data+index);
            index += 4;
            string t(data+index,nowdatasize-1);
            cout<<"delete at "<<t<<' '<<pagenum<<' '<<rownum<<endl;
            DeleteindexAt(i,data+index,nowdatasize-1,pagenum,rownum);
            index += nowdatasize;
        }
}
void FlexibleTable::insertall(char *data, int datasize, int pagenum, int rownum)
{

    int index=4;
    for (int i=0;i<columncount;i++)
        if (DBindex[i]!=NULL)
        {
            int nowdatasize=UIC::chartoint(data+index);
            index += 4;
            //string t(data+index,nowdatasize);
            //cout<<"insert"<<' '<<t<<' '<<nowdatasize<<endl;
            InsertindexAt(i,data+index,nowdatasize-1,pagenum,rownum);
            index += nowdatasize;
        }
}

string FlexibleTable::gettabletype()
{
    return "Flexible";
}
