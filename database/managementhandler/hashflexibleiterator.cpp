#include "hashflexibleiterator.h"

HashFlexibleIterator::HashFlexibleIterator(Table* table)
{
    this->nowtable = table;
    getbegin();
}
bool HashFlexibleIterator::access(int pagenum, int rownum)
{
    if (pagenum<2)
    {
        cout<<"You are trying to access dangerous page and luckily program found it."<<endl;
        return false;
    }
    this->nowpagenum = pagenum;
    this->nowrownum = rownum;
    return available();
}
bool HashFlexibleIterator::available()
{
    if (this->nowhashnum == -1)
    {
        this->nowhashnum = 0;
        this->nowpagenum = this->nowtable->getinfo(0,0,0,0);
        this->nowrownum = 0;
    }
    vector<int> infovec;
    bool yes = this->nowtable->getinfo(-1,this->nowpagenum,this->nowrownum,&infovec);
    if (!yes)
    {
        if (infovec.size() == 1)
        {
            return false;
        } else if (infovec.size() == 3)
        {
            this->nowpagerownum = infovec[0];
            this->jumppagenum = infovec[1];
            return false;
        } else
        {
            cout<<"ERROR: ERROR element num"<<endl;
            return false;
        }
    } else
    {
        assert(infovec.size() == 4);
        this->nowpagerownum = infovec[0];
        this->jumppagenum = infovec[1];
        this->nowrowsize = infovec[2];
        this->nowhashnum = infovec[3];
        return true;
    }
}
bool HashFlexibleIterator::nextrow()
{
    if (this->nowhashnum == -1)
    {
        this->nowhashnum = 0;
        this->nowpagenum = this->nowtable->getinfo(0,0,0,0);
        this->nowrownum = 0;
    }
    this->nowrownum++;
    bool can=available();
    if (!can)
    {
    vector<int> infovec;
    while (true)
    {
        infovec.clear();
        bool yes = this->nowtable->getinfo(-1,this->nowpagenum,this->nowrownum,&infovec);
        if (!yes)
        {
            if (infovec.size() == 1)
            {
                this->nowpagenum = 0;
                this->nowrownum = 0;
                while (true)
                {
                    this->nowhashnum++;
                    if (this->nowhashnum == 1024) break;
                    this->nowpagenum = this->nowtable->getinfo(this->nowhashnum,0,0,0);
                    if (this->nowpagenum >=2) break;
                }
                if (this->nowhashnum == 1024) return false;

                continue;
            } else if (infovec.size() == 3)
            {
                this->nowpagerownum = infovec[0];
                this->jumppagenum = infovec[1];
                if (this->jumppagenum != 0)
                {
                    this->nowpagenum = this->jumppagenum;
                    this->nowrownum = 0;
                } else
                {
                    this->nowpagenum = 0;
                    this->nowrownum = 0;
                    while (true)
                    {
                        this->nowhashnum++;
                        if (this->nowhashnum == 1024) break;
                        this->nowpagenum = this->nowtable->getinfo(this->nowhashnum,0,0,0);
                        if (this->nowpagenum >=2) break;
                    }
                    if (this->nowhashnum == 1024) return false;
                }
                continue;
            } else
            {
                cout<<"ERROR: ERROR element num"<<endl;
                return false;
            }
        } else
        {
            assert(infovec.size() == 4);
            this->nowpagerownum = infovec[0];
            this->jumppagenum = infovec[1];
            this->nowrowsize = infovec[2];
            this->nowhashnum = infovec[3];
            return true;
        }
    }
    }
    return false;
}

bool HashFlexibleIterator::getdata(char* output, int& outputsize)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum, output, outputsize);
    return true;
}
bool HashFlexibleIterator::getdata(Record* rec)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum,rec);
    return true;
}
bool HashFlexibleIterator::insertdata(Record* rec)
{
    int temppagenum, temprownum;
    bool can = this->nowtable->FastAllInsert(temppagenum, temprownum, rec);
    if (can) {
        this->nowpagenum=temppagenum;
        this->nowrownum=temprownum;
        available();
        return true;
    } else
        return false;
}
bool HashFlexibleIterator::deletedata()
{
    if (!available())
        return false;
    this->nowtable->DeleteAt(this->nowpagenum, this->nowrownum);
    return true;
}
void HashFlexibleIterator::getbegin()
{
    this->nowrownum=0;
    this->nowpagenum=0;
    this->nowhashnum=-1;
    if (!available())
        nextrow();
}
int HashFlexibleIterator::getcurrentsize()
{
    return this->nowrowsize;
}
int HashFlexibleIterator::gethashnum()
{
    return this->nowhashnum;
}
