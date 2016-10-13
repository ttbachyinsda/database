#include "uic.h"

UIC::UIC()
{

}
bool UIC::equal(char *s1, char *s2, int len)
{
    for (int i=0;i<len;i++)
        if (*(s1+i)!=*(s2+i))
            return false;
    return true;
}
bool UIC::equal(char *s1, const char *s2, int len)
{
    for (int i=0;i<len;i++)
        if (*(s1+i)!=*(s2+i))
            return false;
    return true;
}
bool UIC::equal(const char *s1, char *s2, int len)
{
    for (int i=0;i<len;i++)
        if (*(s1+i)!=*(s2+i))
            return false;
    return true;
}
void UIC::convert(type* t1,char* s1)
{
    string temp=t1->getType();
    if (temp[6]=='C')
    {
        *(s1)='C'; *(s1+1)='H'; *(s1+2)='A'; *(s1+3)='R';
    }
    if (temp[6]=='I')
    {
        *(s1)='I'; *(s1+1)='N'; *(s1+2)='T'; *(s1+3)='E';
    }
}
type* UIC::reconvert(char* s1,int size)
{
    if (*(s1)=='C')
    {
        type* temp = new DatabaseChar(size);
        return temp;
    }
    if (*(s1)=='I')
    {
        type* temp = new DatabaseInt(size);
        return temp;
    }
    return NULL;
}

