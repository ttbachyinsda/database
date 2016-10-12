#include "type.h"

type::type()
{
    size=0;
    data=NULL;
}
char* type::getdata()
{
    return data;
}
void type::printdata(string testinfo)
{
    cout<<"Now begin "<<testinfo<<endl;
    for (int i=0;i<size;i++)
    {
        int k=data[i];
        cout<<"No."<<i<<" is: "<<k<<endl;
    }
    cout<<"Now end "<<testinfo<<endl;
}
type::~type()
{
    if (data!=NULL)
    {
        delete data;
        data=NULL;
    }
}
