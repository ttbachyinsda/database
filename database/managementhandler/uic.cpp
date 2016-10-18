#include "uic.h"

UIC::UIC()
{
}
bool UIC::equal(char* s1, char* s2, int len)
{
    for (int i = 0; i < len; i++)
        if (*(s1 + i) != *(s2 + i))
            return false;
    return true;
}
bool UIC::equal(char* s1, const char* s2, int len)
{
    for (int i = 0; i < len; i++)
        if (*(s1 + i) != *(s2 + i))
            return false;
    return true;
}
bool UIC::equal(const char* s1, char* s2, int len)
{
    for (int i = 0; i < len; i++)
        if (*(s1 + i) != *(s2 + i))
            return false;
    return true;
}
void UIC::convert(DataBaseType* t1, char* s1)
{
    string temp = t1->getType();
    if (temp[6] == 'C') {
        *(s1) = 'C';
        *(s1 + 1) = 'H';
        *(s1 + 2) = 'A';
        *(s1 + 3) = 'R';
    }
    if (temp[6] == 'I') {
        *(s1) = 'I';
        *(s1 + 1) = 'N';
        *(s1 + 2) = 'T';
        *(s1 + 3) = 'E';
    }
}
DataBaseType* UIC::reconvert(char* s1, int size)
{
    if (*(s1) == 'C') {
        DataBaseType* temp = new DatabaseChar(size);
        return temp;
    }
    if (*(s1) == 'I') {
        DataBaseType* temp = new DatabaseInt(size);
        return temp;
    }
    return NULL;
}
DataBaseType* UIC::reconvert(string s1, int size)
{
    if (s1[0] == 'C') {
        DataBaseType* temp = new DatabaseChar(size);
        return temp;
    }
    if (s1[0] == 'I') {
        DataBaseType* temp = new DatabaseInt(size);
        return temp;
    }
    return NULL;
}
int UIC::chartoint(char* s1)
{
    int k = 0;
    memcpy(&k, s1, 4);
    return k;
}
void UIC::inttochar(int i1, char* s1)
{
    memcpy(s1, &i1, 4);
}
void UIC::readchar(BufType b, FileIterator& iterator, char* dest, int size_t)
{
    memcpy(dest, b + iterator, size_t);
    iterator += size_t;
}
int UIC::readint(BufType b, FileIterator& iterator)
{
    int temp = chartoint(b + iterator);
    iterator += 4;
    return temp;
}
void UIC::writechar(BufType b, FileIterator& iterator, char* source, int size_t)
{
    memcpy(b + iterator, source, size_t);
    iterator += size_t;
}
void UIC::writechar(BufType b, FileIterator& iterator, const char* source, int size_t)
{
    memcpy(b + iterator, source, size_t);
    iterator += size_t;
}
void UIC::writecharandjump(BufType b, FileIterator& iterator, char* source, int size_t, int jumpsize)
{
    memcpy(b + iterator, source, size_t);
    iterator += jumpsize;
}
void UIC::writecharandjump(BufType b, FileIterator& iterator, const char* source, int size_t, int jumpsize)
{
    memcpy(b + iterator, source, size_t);
    iterator += jumpsize;
}
void UIC::writeint(BufType b, FileIterator& iterator, int source)
{
    inttochar(source, b + iterator);
    iterator += 4;
}
string UIC::readstring(BufType b, FileIterator& iterator, int size_t)
{
    string temp(b + iterator, size_t);
    iterator += size_t;
    return temp;
}
string UIC::readstringandjump(BufType b, FileIterator& iterator, int size_t, int jumpsize)
{
    string temp(b + iterator, size_t);
    iterator += jumpsize;
    return temp;
}
DataBaseType** UIC::copytype(DataBaseType** input, int inputlen)
{
    DataBaseType** temp = new DataBaseType*[inputlen];
    for (int i=0;i<inputlen;i++)
    {
        char *s = (char*) malloc(4);
        int nowsize=input[i]->getSize();
        convert(input[i],s);
        temp[i]=reconvert(s,nowsize);
    }
    return temp;
}
