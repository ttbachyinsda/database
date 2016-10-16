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
int FixedSizeTable::getRowSize() { return RowSize; }

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
    } else {
        PackageFromHeadFile(b);
        BPM->access(index);
    }
    free(temp);
    haveinitialize = true;
    return true;
}

void FixedSizeTable::PackageFromHeadFile(BufType b)
{
    int position = 0;
    int namelen;
    position += 4;
    namelen = UIC::chartoint(b + position);
    char* tmp = (char*)malloc(namelen);
    position += 4;
    memcpy(tmp, b + position, namelen);
    string tempname(tmp, namelen);
    name = tempname;
    free(tmp);
    position += MAX_NAME_SIZE;
    this->PageNum = UIC::chartoint(b + position);
    clearcolumn();
    position += 4;
    this->columncount = UIC::chartoint(b + position);
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    order = new int[this->columncount];
    for (int i = 0; i < this->columncount; i++) {
        int namelen;
        position += 4;
        namelen = UIC::chartoint(b + position);
        char* tmp = (char*)malloc(namelen);
        position += 4;
        memcpy(tmp, b + position, namelen);
        string c = tmp;
        columnname[i] = c;
        free(tmp);
        position += MAX_NAME_SIZE;
        char* temptype = (char*)malloc(4);
        memcpy(temptype, b + position, 4);
        position += 4;
        int tempsize = UIC::chartoint(b + position);
        DataBaseType* t = UIC::reconvert(temptype, tempsize);
        column[i] = t;
        free(temptype);
        position += 4;
        int temporder = UIC::chartoint(b + position);
        order[i] = temporder;
    }
    position += 4;
    this->RowSize = UIC::chartoint(b + position);
    position += 4;
    this->MaxRowNum = UIC::chartoint(b + position);
    position += 4;
    this->MaxRecordSize = UIC::chartoint(b + position);
    if (this->RowNumInPage != NULL)
        delete[] RowNumInPage;
    RowNumInPage = new int[MaxRecordSize];
    for (int i = 0; i < MaxRecordSize; i++) {
        position += 4;
        this->RowNumInPage[i] = UIC::chartoint(b + position);
    }
}
void FixedSizeTable::PackageHeadFile(BufType b)
{
    int position = 0;
    string temp = "HEAD";
    memcpy(b, temp.data(), 4);
    int namelen = name.length();
    position += 4;
    UIC::inttochar(namelen, b + position);
    position += 4;
    memcpy(b + position, name.data(), namelen);
    position += MAX_NAME_SIZE;
    UIC::inttochar(this->PageNum, b + position);
    position += 4;
    UIC::inttochar(this->columncount, b + position);
    for (int i = 0; i < this->columncount; i++) {
        int namelen = columnname[i].length();
        position += 4;
        UIC::inttochar(namelen, b + position);
        position += 4;
        memcpy(b + position, columnname[i].data(), namelen);
        position += MAX_NAME_SIZE;
        char* temptype = (char*)malloc(4);
        UIC::convert(column[i], temptype);
        memcpy(b + position, temptype, 4);
        free(temptype);
        position += 4;
        UIC::inttochar(column[i]->getSize(), b + position);
        position += 4;
        UIC::inttochar(order[i], b + position);
    }
    position += 4;
    UIC::inttochar(this->RowSize, b + position);
    position += 4;
    UIC::inttochar(this->MaxRowNum, b + position);
    position += 4;
    UIC::inttochar(this->MaxRecordSize, b + position);
    for (int i = 0; i < MaxRecordSize; i++) {
        position += 4;
        UIC::inttochar(this->RowNumInPage[i], b + position);
    }
    // cout<<"total size= "<<position+4<<endl;
}

void FixedSizeTable::createTable(vector<string> clname, vector<string> cltype,
    vector<int> clsize)
{
    remove(this->filename.c_str());
    int totalheadsize = 4 * 4 + 4 * 3 + MAX_NAME_SIZE;
    this->clearcolumn();
    this->RowSize = 0;
    this->columncount = clname.size();
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    order = new int[this->columncount];
    for (int i = 0; i < columncount; i++) {
        totalheadsize += MAX_NAME_SIZE + 4 * 4;
        columnname[i] = clname[i];
        if (cltype[i] == "CHAR") {
            DataBaseType* temp = new DatabaseChar(clsize[i]);
            column[i] = temp;
        }
        if (cltype[i] == "INT") {
            DataBaseType* temp = new DatabaseInt(clsize[i]);
            column[i] = temp;
        }
        order[i] = i;
        this->RowSize += clsize[i];
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
        // cout<<"packer at:"<<nowsize<<' '<<column[i]->output()<<endl;
        memcpy(temp + nowsize, column[i]->getdata(), column[i]->getSize());
        nowsize += column[i]->getSize();
    }
    return temp;
}
bool FixedSizeTable::InsertAt(int pagenum)
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
    char* insertdata = Packager();
    position += 8 + this->RowSize * pagerownum;
    // cout<<"packager wz="<<position<<endl;
    memcpy(b + position, insertdata, this->RowSize);
    pagerownum++;
    UIC::inttochar(pagerownum, b + 4);
    if (pagenum < this->MaxRecordSize) {
        this->RowNumInPage[pagenum]++;
    }
    BPM->markDirty(nowindex);
    // cout<<pagenum<<endl;
    return true;
}
bool FixedSizeTable::Insert()
{
    bool can = false;
    for (int i = 1; i < this->MaxRecordSize; i++)
        if (this->RowNumInPage[i] < this->MaxRowNum) {
            can = InsertAt(i);
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
        can = InsertAt(i);
        if (can)
            return true;
    }
    this->PageNum++;
    can = InsertAt(this->PageNum);
    return can;
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
bool FixedSizeTable::FindAt(int pagenum, int rownum)
{
    BufType b;
    int nowindex, pagerownum;
    if (!modifypd(pagenum, rownum, b, nowindex, pagerownum))
        return false;
    UnPackager(b, 8 + this->RowSize * rownum);
    BPM->access(nowindex);
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
        int size = column[i]->getSize();
        column[i]->checkRightAndChange(temp + totalsize, size);
        totalsize += size;
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
bool FixedSizeTable::Modify(int pagenum, int rownum)
{
    BufType b;
    int nowindex, pagerownum;
    if (!modifypd(pagenum, rownum, b, nowindex, pagerownum))
        return false;
    char* temp = Packager();
    int position2 = 8 + this->RowSize * rownum;
    memcpy(b + position2, temp, this->RowSize);
    return true;
}
int FixedSizeTable::getPageRowNum(int pagenum)
{
    cout << "maxrecordsize=" << this->MaxRecordSize << endl;
    if (pagenum > this->PageNum)
        return 0;
    if (pagenum < this->MaxRecordSize)
        return RowNumInPage[pagenum];
    int index = 0;
    BufType b = BPM->getPage(fileid, pagenum, index);
    int nowrownum = UIC::chartoint(b + 4);
    return nowrownum;
}
