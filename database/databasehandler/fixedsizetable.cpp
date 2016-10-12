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
    carrier temp(PAGE_SIZE);
    BPM->getPage(fileid,0,temp.getdata());
    temp.beginconvert();
    if (temp.GCR[0]!='1')
    {
        PackageHeadFile(temp);
    } else
    {
        PackageFromHeadFile(temp);
    }
    return true;
}
void FixedSizeTable::PackageFromHeadFile(carrier &temp)
{

}
void FixedSizeTable::PackageHeadFile(carrier &temp)
{

}
