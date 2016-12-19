#include "flexibleiterator.h"

FlexibleIterator::FlexibleIterator(Table* table)
{
    this->nowtable = table;
    BPM = this->nowtable->getBPM();
    fileid = this->nowtable->getfileid();
    getbegin();
    this->nowrowsize = getThisRowSize();
}
int FlexibleIterator::getThisRowSize()
{
    if (!available()) return 0;
    int index = 0;
    BufType b = BPM->getPage(fileid, this->nowpagenum, index);
    BPM->access(index);
    return UIC::chartoint(b + __position(this->nowrownum));
}
bool FlexibleIterator::access(int pagenum, int rownum)
{
    if (pagenum<1) return false;
    this->nowpagenum = pagenum;
    this->nowrownum = rownum;
    if (this->nowpagenum > this->nowtable->getPageNum())
    {
        return false;
    }
    int index=0;
    BufType b= BPM->getPage(fileid,this->nowpagenum,index);
    BPM->access(index);
    int pagerownum = UIC::chartoint(b + 4);
    this->nowpagerownum = pagerownum;
    if (rownum >= nowpagerownum) {
        return false;
    }
    return true;
}
bool FlexibleIterator::available()
{
    if (this->nowpagenum > this->nowtable->getPageNum()) return false;
    int maxpagenum=this->nowtable->getPageNum();
    if (this->nowpagenum>maxpagenum) return false;
    int index=0;
    BufType b= BPM->getPage(fileid,this->nowpagenum,index);
    BPM->access(index);
    int rownum = this->nowrownum;
    int pagerownum = UIC::chartoint(b + 4);
    if (rownum>=pagerownum) return false;
    this->nowpagerownum = pagerownum;

    int pageposition = UIC::chartoint(b + __position(rownum));
    //cout<<"pageposition at "<<this->nowpagenum<<' '<<this->nowrownum<<' '<<__position(rownum)<<' '<<pageposition<<endl;
    if (pageposition!=0) return true; else return false;
}
bool FlexibleIterator::nextrow()
{
    int maxpagenum=this->nowtable->getPageNum();
    this->nowrownum++;
    bool can=available();
    if (!can)
    while (this->nowpagenum<=maxpagenum)
    {
        this->nowpagenum++;
        int index=0;
        BufType b= BPM->getPage(fileid,this->nowpagenum,index);
        int pagerownum = UIC::chartoint(b+4);
        for (int i=0;i<pagerownum;i++)
        {
            this->nowrownum=i;
            int pageposition = UIC::chartoint(b + __position(i));
            if (pageposition!=0)
            {
                can=true;
                break;
            }
        }
        if (can) break;
    }
    if (this->nowpagenum>maxpagenum) return false;
     return true;
}

bool FlexibleIterator::getdata(char* output, int& outputsize)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum, output, outputsize);
    return true;
}
bool FlexibleIterator::getdata(Record* rec)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum,rec);
    return true;
}
bool FlexibleIterator::insertdata(Record* rec)
{
    int temppagenum, temprownum;
    bool can = this->nowtable->FastAllInsert(temppagenum, temprownum, rec);
    if (can) {
        this->nowpagenum=temppagenum;
        this->nowrownum=temprownum;
        return true;
    } else
        return false;
}
bool FlexibleIterator::deletedata()
{
    if (!available())
        return false;
    this->nowtable->DeleteAt(this->nowpagenum, this->nowrownum);
    return true;
}
void FlexibleIterator::getbegin()
{
    this->nowrownum=0;
    this->nowpagenum=1;
    if (!available())
        nextrow();
}
int FlexibleIterator::getcurrentsize()
{
    return getThisRowSize();
}
void FlexibleIterator::updaterownum()
{
    int index=0;
    BufType b= BPM->getPage(fileid,this->nowpagenum,index);
    BPM->access(index);
    int pagerownum = UIC::chartoint(b + 4);
    this->nowpagerownum = pagerownum;
}
