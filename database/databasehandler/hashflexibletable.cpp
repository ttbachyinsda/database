#include "hashflexibletable.h"

HashFlexibleTable::HashFlexibleTable()
{
    this->PageNum = 0;
    this->HBeginPageNum = new int[1024];
    this->HEndPageNum = new int[1024];
    memset(this->HBeginPageNum, 0, 4096);
    memset(this->HEndPageNum, 0, 4096);
    atemprecord = 0;
}
int HashFlexibleTable::getPageNum() { return PageNum; }
int HashFlexibleTable::getMaxRowNum() { return 0; }
int HashFlexibleTable::getRowSize(int rownum) { return 0; }

bool HashFlexibleTable::Initialize()
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
    BufType b = BPM->getPage(fileid, 0, index);

    char* temp = (char*)malloc(4);
    memcpy(temp, b, 4);
    string ob1 = "HEAD";
    if (!UIC::equal(temp, ob1.data(), 4) || havecreatetable) {
        PackageHeadFile(b);
        BPM->markDirty(index);
        b = BPM->getPage(fileid, 1, index);
        Packagebeginend(b);
        BPM->markDirty(index);
        Nullindex();
    } else {
        PackageFromHeadFile(b);
        BPM->access(index);
        b = BPM->getPage(fileid, 1, index);
        Packagefrombeginend(b);
        BPM->markDirty(index);
        readindex();
    }
    free(temp);
    haveinitialize = true;
    return true;
}
void HashFlexibleTable::Packagefrombeginend(BufType b)
{
    FileIterator position = 0;
    for (int i = 0; i < 1024; i++) {
        HBeginPageNum[i] = UIC::readint(b, position);
        HEndPageNum[i] = UIC::readint(b, position);
    }
}
void HashFlexibleTable::Packagebeginend(BufType b)
{
    FileIterator position = 0;
    for (int i = 0; i < 1024; i++) {
        UIC::writeint(b, position, HBeginPageNum[i]);
        UIC::writeint(b, position, HEndPageNum[i]);
    }
}

void HashFlexibleTable::PackageFromHeadFile(BufType b)
{
    ifstream headfile(filename + ".tableinfo", ios::binary);
    int namelen;
    headfile.read((char*)&namelen, 4);
    char* namechar = (char*)malloc(namelen);
    headfile.read(namechar, namelen);
    string namestr(namechar, namelen);
    free(namechar);
    name = namestr;

    headfile.read((char*)&PageNum, 4);
    headfile.read((char*)&majornum, 4);

    clearcolumn();
    headfile.read((char*)&columncount, 4);

    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];
    for (int i = 0; i < this->columncount; i++) {

        int namelen;
        headfile.read((char*)&namelen, 4);
        char* namechar = (char*)malloc(namelen);
        headfile.read(namechar, namelen);
        string namestr(namechar, namelen);
        free(namechar);
        columnname[i] = namestr;

        char* temptype = (char*)malloc(4);
        headfile.read(temptype, 4);

        int tempsize;
        headfile.read((char*)&tempsize, 4);

        char* nullable = (char*)malloc(4);
        headfile.read(nullable, 4);

        bool cannull;
        if (nullable[0] == 'A')
            cannull = true;
        else
            cannull = false;
        char* canmulti = (char*)malloc(4);
        headfile.read(canmulti, 4);
        if (canmulti[0] == 'A')
            multivalue[i] = true;
        else
            multivalue[i] = false;
        DataBaseType* t = UIC::realreconvert(temptype, tempsize, cannull);

        int conditionsize;
        headfile.read((char*)&conditionsize, 4);

        char* tempcondition = (char*)malloc(conditionsize);
        headfile.read(tempcondition, conditionsize);

        int position = 0;
        t->readcondition(tempcondition, conditionsize, position);

        column[i] = t;
        free(temptype);
        free(nullable);
        free(canmulti);
        free(tempcondition);
    }

    tablecondition.clear();
    int vecsize, strsize, first, second;
    headfile.read((char*)&vecsize, 4);
    for (int i = 0; i < vecsize; i++) {
        headfile.read((char*)&first, 4);
        headfile.read((char*)&second, 4);
        headfile.read((char*)&strsize, 4);
        char* tmp = (char*)malloc(strsize);
        headfile.read(tmp, strsize);
        string third(tmp, strsize);
        tablecondition.push_back(make_triple(first, second, third));
        free(tmp);
    }

    headfile.read((char*)&vecsize, 4);
    for (int i = 0; i < vecsize; i++) {
        headfile.read((char*)&first, 4);
        headfile.read((char*)&second, 4);
        headfile.read((char*)&strsize, 4);
        char* tmp = (char*)malloc(strsize);
        headfile.read(tmp, strsize);
        string third(tmp, strsize);
        linkedcolumn.push_back(make_triple(first, third, second));
        free(tmp);
    }
    headfile.close();
}
void HashFlexibleTable::PackageHeadFile(BufType b)
{
    ofstream headfile(filename + ".tableinfo", ios::binary);

    string headstr = "HEAD";
    memcpy(b, headstr.data(), 4);

    int namelen = name.length();
    headfile.write((char*)&namelen, 4);
    headfile.write(name.data(), namelen);
    headfile.write((char*)&PageNum, 4);
    headfile.write((char*)&majornum, 4);
    headfile.write((char*)&columncount, 4);

    for (int i = 0; i < columncount; i++) {
        int namelen = columnname[i].length();

        headfile.write((char*)&namelen, 4);
        headfile.write(columnname[i].data(), namelen);

        char* temptype = (char*)malloc(4);
        char* nullable = (char*)malloc(4);
        char* canmulti = (char*)malloc(4);
        UIC::convert(column[i], temptype, nullable);
        UIC::convertmulti(multivalue[i], canmulti);

        headfile.write(temptype, 4);
        int tempsize = column[i]->getMaxSize();
        headfile.write((char*)&tempsize, 4);
        headfile.write(nullable, 4);
        headfile.write(canmulti, 4);

        free(temptype);
        free(nullable);
        free(canmulti);

        int conditionsize = column[i]->getconditionsize();
        headfile.write((char*)&conditionsize, 4);

        char* tempcondition = (char*)malloc(conditionsize);
        int position = 0;
        column[i]->writecondition(tempcondition, position);
        headfile.write(tempcondition, conditionsize);

        free(tempcondition);
    }
    int vecsize = this->tablecondition.size(), strsize;
    headfile.write((char*)&vecsize, 4);
    for (int i = 0; i < vecsize; i++) {
        int first = tablecondition[i].first;
        int second = tablecondition[i].second.first;
        string third = tablecondition[i].second.second;
        strsize = third.length();
        headfile.write((char*)&first, 4);
        headfile.write((char*)&second, 4);
        headfile.write((char*)&strsize, 4);
        headfile.write(third.data(), strsize);
    }
    vecsize = this->linkedcolumn.size();
    headfile.write((char*)&vecsize, 4);
    for (int i = 0; i < vecsize; i++) {
        int first = linkedcolumn[i].first;
        int second = linkedcolumn[i].second.second;
        string third = linkedcolumn[i].second.first;
        strsize = third.length();
        headfile.write((char*)&first, 4);
        headfile.write((char*)&second, 4);
        headfile.write((char*)&strsize, 4);
        headfile.write(third.data(), strsize);
    }
    headfile.close();
}

void HashFlexibleTable::createTable(vector<string> clname, vector<DataBaseType*> cltype)
{
    remove(this->filename.c_str());
    string infoname = this->filename + ".tableinfo";
    remove(infoname.c_str());
    this->tablecondition.clear();
    this->clearcolumn();
    this->columncount = clname.size();
    columnname = new string[this->columncount];
    column = new DataBaseType*[this->columncount];
    multivalue = new bool[this->columncount];
    for (int i = 0; i < columncount; i++) {
        columnname[i] = clname[i];
        column[i] = cltype[i];
        multivalue[i] = true;
    }
    memset(this->HBeginPageNum, 0, 4096);
    memset(this->HEndPageNum, 0, 4096);
    PageNum = 1;
    havecreatetable = true;
}
char* HashFlexibleTable::Packager(int totalsize)
{
    char* temp = (char*)malloc(totalsize);
    UIC::inttochar(totalsize, temp);
    int nowsize = 4;
    for (int i = 0; i < columncount; i++) {
        int csize = column[i]->getSize();
        UIC::inttochar(csize, temp + nowsize);
        nowsize += 4;
        memcpy(temp + nowsize, column[i]->getdata(), csize);
        nowsize += csize;
    }
    return temp;
}
void HashFlexibleTable::Reconstruct(int pagenum, BufType b)
{
    cout << "do a reconstruct" << endl;
    int pagerownum = 0;
    int reservedsize = 0;
    int reservedpointer = 0;
    int jumppagenum = 0;
    pagerownum = UIC::chartoint(b + 4);
    reservedsize = UIC::chartoint(b + 8);
    reservedpointer = UIC::chartoint(b + 12);
    jumppagenum = UIC::chartoint(b + 16);
    char** temprecord = new char*[pagerownum];
    int* preposition = new int[pagerownum];
    for (int i = 0; i < pagerownum; i++) {
        preposition[i] = UIC::chartoint(b + __position(i));
        temprecord[i] = getat(b, preposition[i]);
    }
    reservedpointer = 20;
    reservedsize = PAGE_SIZE - 20;
    int nowrownum = 0;
    for (int i = 0; i < pagerownum; i++)
        if (temprecord[i] != NULL) {
            int datalen = UIC::chartoint(temprecord[i]);
            modifyall(temprecord[i], datalen, pagenum, preposition[i], pagenum, reservedpointer);
            putat(b, reservedpointer, nowrownum, temprecord[i]);
            reservedpointer += datalen;
            reservedsize -= datalen + 4;
            nowrownum++;
        }
    UIC::inttochar(pagerownum, b + 4);
    UIC::inttochar(reservedsize, b + 8);
    UIC::inttochar(reservedpointer, b + 12);
    UIC::inttochar(jumppagenum, b + 16);

    for (int i = 0; i < pagerownum; i++)
        if (temprecord[i] != NULL)
            free(temprecord[i]);
    delete[] temprecord;
}
char* HashFlexibleTable::getat(BufType b, int pageposition)
{
    if (pageposition == 0)
        return NULL;
    int recordsize = UIC::chartoint(b + pageposition);
    char* temprecord = (char*)malloc(recordsize);
    memcpy(temprecord, b + pageposition, recordsize);
    return temprecord;
}
void HashFlexibleTable::putat(BufType b, int pageposition, int rownum, char* data)
{
    int datalen = UIC::chartoint(data);
    memcpy(b + pageposition, data, datalen);
    UIC::inttochar(pageposition, b + __position(rownum));
}

bool HashFlexibleTable::InsertAt(int datahash, int pagenum, char* insertdata, int& rownum)
{
    if (pagenum == 0)
        return false;
    int nowindex = 0;
    BufType b = BPM->getPage(fileid, pagenum, nowindex);
    int pagerownum = 0;
    int reservedsize = 0;
    int reservedpointer = 0;
    int jumppagenum = 0;
    char* temp = (char*)malloc(4);
    string option1 = "PAGE";
    char* option2 = (char*)malloc(4);
    memset(option2, 0, 4);
    memcpy(temp, b, 4);
    if (UIC::equal(temp, option1.data(), 4)) {
        pagerownum = UIC::chartoint(b + 4);
        reservedsize = UIC::chartoint(b + 8);
        reservedpointer = UIC::chartoint(b + 12);
        jumppagenum = UIC::chartoint(b + 16);
    } else if (UIC::equal(temp, option2, 4)) {
        memcpy(b, option1.data(), 4);
        pagerownum = 0;
        reservedsize = PAGE_SIZE - 20;
        reservedpointer = 20;
        UIC::inttochar(pagerownum, b + 4);
        UIC::inttochar(reservedsize, b + 8);
        UIC::inttochar(reservedpointer, b + 12);
        UIC::inttochar(jumppagenum, b + 16);

    } else {
        // cout<<"ERROR:: ????"<<endl;
        memcpy(b, option1.data(), 4);
        pagerownum = 0;
        reservedsize = PAGE_SIZE - 20;
        reservedpointer = 20;
        UIC::inttochar(pagerownum, b + 4);
        UIC::inttochar(reservedsize, b + 8);
        UIC::inttochar(reservedpointer, b + 12);
        UIC::inttochar(jumppagenum, b + 16);
    }
    free(temp);
    free(option2);
    int datalen = UIC::chartoint(insertdata);
    if (datalen + 4 > reservedsize) {
        //cout<<"error becaule datalen>reservedsize"<<' '<<datalen<<' '<<reservedsize<<endl;
        return false;
    }
    if (reservedsize > PAGE_SIZE - pagerownum * 4 - reservedpointer) {
        Reconstruct(pagenum, b);
        pagerownum = UIC::chartoint(b + 4);
        reservedsize = UIC::chartoint(b + 8);
        reservedpointer = UIC::chartoint(b + 12);
        jumppagenum = UIC::chartoint(b + 16);
    }

    putat(b, reservedpointer, pagerownum, insertdata);
    rownum = pagerownum;

    insertall(insertdata, datalen, pagenum, rownum);

    //if (pagenum==1 && rownum<3)
    //cout<<rownum<<' '<<reservedpointer<<' '<<datalen<<endl;
    datalen = UIC::chartoint(b + reservedpointer);
    pagerownum++;
    reservedsize -= datalen + 4;
    reservedpointer += datalen;
    UIC::inttochar(pagerownum, b + 4);
    UIC::inttochar(reservedsize, b + 8);
    UIC::inttochar(reservedpointer, b + 12);
    UIC::inttochar(jumppagenum, b + 16);

    BPM->markDirty(nowindex);
    return true;
}
bool HashFlexibleTable::modifypd(int pagenum, int rownum, BufType& ct,
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

bool HashFlexibleTable::DeleteAt(int pagenum, int rownum)
{
    BufType b;
    int nowindex, pagerownum;
    if (!modifypd(pagenum, rownum, b, nowindex, pagerownum))
        return false;
    int position;
    position = UIC::chartoint(b + __position(rownum));
    if (position == 0)
        return false;

    int newposition = 0, currentsize;
    currentsize = UIC::chartoint(b + position);

    deleteall(b + position, currentsize, pagenum, rownum);

    UIC::inttochar(newposition, b + __position(rownum));

    int reservedsize = UIC::chartoint(b + 8);
    reservedsize -= currentsize + 4;
    UIC::inttochar(reservedsize, b + 8);

    BPM->markDirty(nowindex);
    return true;
}
HashFlexibleTable::~HashFlexibleTable()
{
    int index = 0;
    BufType b = BPM->getPage(fileid, 0, index);
    PackageHeadFile(b);
    BPM->markDirty(index);
    b = BPM->getPage(fileid, 1, index);
    Packagebeginend(b);
    BPM->markDirty(index);
    delete[] HBeginPageNum;
    delete[] HEndPageNum;
    if (atemprecord != 0)
        delete atemprecord;
}
int HashFlexibleTable::getPageRowNum(int pagenum)
{
    //cout << "maxrecordsize=" << this->MaxRecordSize << endl;
    if (pagenum > this->PageNum || pagenum < 2)
        return 0;
    int index = 0;
    BufType b = BPM->getPage(fileid, pagenum, index);
    int nowrownum = UIC::chartoint(b + 4);
    return nowrownum;
}
bool HashFlexibleTable::FastInsert(int& pagenum, int& rownum, Record* rec)
{
    //cannot insert at every page
    return false;
}
bool HashFlexibleTable::FastAllInsert(int& pagenum, int& rownum, Record* rec)
{
    int snum = (majornum == -1 ? 0 : majornum);

    int hashnum = getHashNum(rec->getAt(snum));

    if (HBeginPageNum[hashnum] == 0) {
        this->PageNum++;
        HBeginPageNum[hashnum] = this->PageNum;
        HEndPageNum[hashnum] = this->PageNum;
        pagenum = this->PageNum;
        InsertAt(hashnum, pagenum, rec->getData(), rownum);

    } else {
        pagenum = HEndPageNum[hashnum];
        int i = 0;
        int index = 0;
        BufType b;
        while (!InsertAt(hashnum, pagenum, rec->getData(), rownum)) {
            i++;
            this->PageNum++;

            b = BPM->getPage(fileid, HEndPageNum[hashnum], index);
            UIC::inttochar(this->PageNum, b + 16);

            HEndPageNum[hashnum] = this->PageNum;
            pagenum = HEndPageNum[hashnum];
        }
        assert(i <= 1);
    }
    return true;
}

bool HashFlexibleTable::FastOutput(int pagenum, int rownum, Record* rec)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    //cout<<"position at "<<__position(rownum)<<endl;
    int pageposition = UIC::chartoint(b + __position(rownum));
    if (pageposition == 0)
        return false;
    rec->Input(b + pageposition);
    return true;
}
void HashFlexibleTable::FastOutput(int pagenum, int rownum, char* output, int& outputsize)
{
    int index;
    BufType b = BPM->getPage(fileid, pagenum, index);
    int pageposition = UIC::chartoint(b + __position(rownum));
    if (pageposition == 0) {
        output = NULL;
        outputsize = 0;
    }
    outputsize = UIC::chartoint(b + pageposition);
    memcpy(output, b + pageposition, outputsize);
}
void HashFlexibleTable::modifyall(char* data, int datasize, int prepagenum, int prerownum, int newpagenum, int newrownum)
{
    int index = 4;
    for (int i = 0; i < columncount; i++)
    {
        int nowdatasize = UIC::chartoint(data + index);
        index += 4;
        if (DBindex != NULL && DBindex[i] != NULL) {

            ModifyindexAt(i, data + index, nowdatasize - 1, prepagenum, prerownum, newpagenum, newrownum);

        }
        index += nowdatasize;
    }
}
void HashFlexibleTable::deleteall(char* data, int datasize, int pagenum, int rownum)
{
    int index = 4;

    for (int i = 0; i < columncount; i++)
    {
        int nowdatasize = UIC::chartoint(data + index);
        index += 4;
        if (DBindex != NULL && DBindex[i] != NULL) { 
            //string t(data + index, nowdatasize - 1);
            //cout << "delete at " << t << ' ' << pagenum << ' ' << rownum << endl;
            DeleteindexAt(i, data + index, nowdatasize - 1, pagenum, rownum);

        }
        index += nowdatasize;
    }
}
void HashFlexibleTable::insertall(char* data, int datasize, int pagenum, int rownum)
{

    int index = 4;
    for (int i = 0; i < columncount; i++)
    {
        int nowdatasize = UIC::chartoint(data + index);
        index += 4;
        if (DBindex != NULL && DBindex[i] != NULL) {

            //string t(data+index,nowdatasize);
            //cout<<"insert"<<' '<<t<<' '<<nowdatasize<<endl;
            InsertindexAt(i, data + index, nowdatasize - 1, pagenum, rownum);
        }
        index += nowdatasize;
    }
}
void HashFlexibleTable::createindex(vector<int> columnnum)
{
    bool* v = new bool[columncount];
    memset(v, 0, columncount);
    for (int bj : columnnum) {
        v[bj] = 1;
        createemptyindex(bj);
    }
    for (int pg = 2; pg <= PageNum; pg++) {
        int pageindex = 0;
        BufType b = BPM->getPage(fileid, pg, pageindex);
        int pagerownum = UIC::chartoint(b + 4);
        for (int i = 0; i < pagerownum; i++) {
            int pageposition = UIC::chartoint(b + __position(i));
            if (pageposition != 0) {
                int index = 4;
                for (int j = 0; j < this->columncount; j++) {
                    int nowdatasize = UIC::chartoint(b + pageposition + index);
                    index += 4;
                    //string t(data+index,nowdatasize);
                    //cout<<"insert"<<' '<<t<<' '<<nowdatasize<<endl;
                    if (v[j])
                        InsertindexAt(j, b + pageposition + index, nowdatasize - 1, pg, i);
                    index += nowdatasize;
                }
            }
        }
    }
    delete[] v;
}
string HashFlexibleTable::gettabletype()
{
    return "HashFlexible";
}

//Hash Method
int HashFlexibleTable::getHashNum(string data)
{
    return MD5::BKDRHash(data.c_str());
}
int HashFlexibleTable::getHashNumc(char* data, int datasize)
{
    string ss(data, datasize);
    return MD5::BKDRHash(ss.c_str());
}
void HashFlexibleTable::updateHashpagenum(int hashnum, int beginpagenum, int endpagenum)
{
    HBeginPageNum[hashnum] = beginpagenum;
    HEndPageNum[hashnum] = endpagenum;
}
void HashFlexibleTable::getHashpagenum(int hashnum, int& beginpagenum, int& endpagenum)
{
    beginpagenum = HBeginPageNum[hashnum];
    endpagenum = HEndPageNum[hashnum];
}
int HashFlexibleTable::getinfo(int reqhashnum, int pagenum, int rownum, vector<int>* infovec)
{
    bool can = true;
    if (reqhashnum == -1) {
        if (pagenum > this->PageNum || pagenum < 2) {
            infovec->push_back(-1);
            can = false;
        } else {
            int index;
            BufType b = BPM->getPage(fileid, pagenum, index);
            int pagerownum = UIC::chartoint(b + 4);
            infovec->push_back(pagerownum);
            int jumppagenum = UIC::chartoint(b + 16);
            infovec->push_back(jumppagenum);

            int pageposition = UIC::chartoint(b + __position(rownum));

            if (pageposition == 0 || rownum >= pagerownum) {
                can = false;
                infovec->push_back(0);
            } else {
                infovec->push_back(UIC::chartoint(b + pageposition)); //rowsize
                infovec->push_back(getHashNumIn(b + pageposition, (majornum == -1) ? 0 : majornum));
            }
        }
        if (can)
            return 1;
        else
            return 0;
    } else {
        assert(reqhashnum >= 0);
        assert(reqhashnum <= 1023);
        return HBeginPageNum[reqhashnum];
    }
}
int HashFlexibleTable::getHashNumIn(char* data, int reqcolumn)
{
    assert(reqcolumn < columncount);
    assert(reqcolumn >= 0);
    if (atemprecord == 0) {
        atemprecord = new FlexibleRecord();
        DataBaseType** col = UIC::copytype(getcolumns(), getcolumncount());
        atemprecord->Initialize(col, getcolumncount());
    }
    atemprecord->Input(data);
    return getHashNum(atemprecord->getAt(reqcolumn));
}
bool HashFlexibleTable::FastFind(Record* rec)
{
    bool can = false;
    int snum = (majornum == -1 ? 0 : majornum);
    int hashnum = getHashNum(rec->getAt(snum));
    int nowpagenum = HBeginPageNum[hashnum];
    if (atemprecord == 0) {
        atemprecord = new FlexibleRecord();
        DataBaseType** col = UIC::copytype(getcolumns(), getcolumncount());
        atemprecord->Initialize(col, getcolumncount());
    }
    string temp = rec->getAt(snum);
    while (nowpagenum >= 2) {
        int index;
        BufType b = BPM->getPage(fileid, nowpagenum, index);
        int pagerownum = UIC::chartoint(b + 4);
        int jumppagenum = UIC::chartoint(b + 16);
        for (int i = 0; i < pagerownum; i++) {
            int position = UIC::chartoint(b + __position(i));
            if (position) {
                atemprecord->Input(b + position);
                if (atemprecord->getAt(snum) == temp) {
                    can = true;
                    return true;
                }
            }
        }
        nowpagenum = jumppagenum;
    }
    return can;
}
