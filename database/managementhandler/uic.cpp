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
void UIC::convert(DataBaseType* t1, char* s1, char* s2)
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
    if (temp[6] == 'V') {
        *(s1) = 'V';
        *(s1 + 1) = 'A';
        *(s1 + 2) = 'R';
        *(s1 + 3) = 'C';
    }
    if (temp[6] == 'R') {
        *(s1) = 'R';
        *(s1 + 1) = 'E';
        *(s1 + 2) = 'A';
        *(s1 + 3) = 'L';
    }
    if (temp[6] == 'L') {
        *(s1) = 'L';
        *(s1 + 1) = 'I';
        *(s1 + 2) = 'N';
        *(s1 + 3) = 'T';
    }
    if (temp[6] == 'D') {
        *(s1) = 'D';
        *(s1 + 1) = 'A';
        *(s1 + 2) = 'T';
        *(s1 + 3) = 'E';
    }
    if (temp[6] == 'B') {
        *(s1) = 'B';
        *(s1 + 1) = 'U';
        *(s1 + 2) = 'L';
        *(s1 + 3) = 'B';
    }
    if (temp[6] == 'T') {
        *(s1) = 'T';
        *(s1 + 1) = 'E';
        *(s1 + 2) = 'X';
        *(s1 + 3) = 'T';
    }
    if (t1->getNullable() == true) {
        *(s2) = 'A';
        *(s2 + 1) = 'B';
        *(s2 + 2) = 'L';
        *(s2 + 3) = 'E';
    } else {
        *(s2) = 'U';
        *(s2 + 1) = 'N';
        *(s2 + 2) = 'A';
        *(s2 + 3) = 'B';
    }
}
DataBaseType* UIC::reconvertc(char* s1, int size, bool cannull)
{
    if (*(s1) == 'C') {
        DataBaseType* temp = new DatabaseChar(size, cannull);
        return temp;
    }
    if (*(s1) == 'I') {
        DataBaseType* temp = new DatabaseInt(size, cannull);
        return temp;
    }
    if (*(s1) == 'V') {
        DataBaseType* temp = new DatabaseVarchar(size, cannull);
        return temp;
    }
    if (*(s1) == 'R') {
        DataBaseType* temp = new DatabaseReal(cannull);
        return temp;
    }
    if (*(s1) == 'L') {
        DataBaseType* temp = new DatabaseLint(cannull);
        return temp;
    }
    if (*(s1) == 'D') {
        DataBaseType* temp = new DatabaseDate(cannull);
        return temp;
    }
    if (*(s1) == 'B') {
        DataBaseType* temp = new DatabaseBulb(cannull);
        return temp;
    }
    if (*(s1) == 'T') {
        DataBaseType* temp = new DatabaseText(cannull);
        return temp;
    }
    return NULL;
}
DataBaseType* UIC::reconvert(string s1, int size, bool cannull)
{
    if (s1[0] == 'C') {
        DataBaseType* temp = new DatabaseChar(size, cannull);
        return temp;
    }
    if (s1[0] == 'I') {
        DataBaseType* temp = new DatabaseInt(size, cannull);
        return temp;
    }
    if (s1[0] == 'V') {
        DataBaseType* temp = new DatabaseVarchar(size, cannull);
        return temp;
    }
    if (s1[0] == 'R') {
        DataBaseType* temp = new DatabaseReal(cannull);
        return temp;
    }
    if (s1[0] == 'L') {
        DataBaseType* temp = new DatabaseLint(cannull);
        return temp;
    }
    if (s1[0] == 'D') {
        DataBaseType* temp = new DatabaseDate(cannull);
        return temp;
    }
    if (s1[0] == 'B') {
        DataBaseType* temp = new DatabaseBulb(cannull);
        return temp;
    }
    if (s1[0] == 'T') {
        DataBaseType* temp = new DatabaseText(cannull);
        return temp;
    }
    return NULL;
}
DataBaseType* UIC::realreconvertc(char* s1, int size, bool cannull)
{
    if (*(s1) == 'C') {
        DataBaseType* temp = new DatabaseChar(size - 1, cannull);
        return temp;
    }
    if (*(s1) == 'I') {
        DataBaseType* temp = new DatabaseInt(size - 1, cannull);
        return temp;
    }
    if (*(s1) == 'V') {
        DataBaseType* temp = new DatabaseVarchar(size - 1, cannull);
        return temp;
    }
    if (*(s1) == 'R') {
        DataBaseType* temp = new DatabaseReal(cannull);
        return temp;
    }
    if (*(s1) == 'L') {
        DataBaseType* temp = new DatabaseLint(cannull);
        return temp;
    }
    if (*(s1) == 'D') {
        DataBaseType* temp = new DatabaseDate(cannull);
        return temp;
    }
    if (*(s1) == 'B') {
        DataBaseType* temp = new DatabaseBulb(cannull);
        return temp;
    }
    if (*(s1) == 'T') {
        DataBaseType* temp = new DatabaseText(cannull);
        return temp;
    }
    return NULL;
}
DataBaseType* UIC::realreconvert(string s1, int size, bool cannull)
{
    if (s1[0] == 'C') {
        DataBaseType* temp = new DatabaseChar(size - 1, cannull);
        return temp;
    }
    if (s1[0] == 'I') {
        DataBaseType* temp = new DatabaseInt(size - 1, cannull);
        return temp;
    }
    if (s1[0] == 'V') {
        DataBaseType* temp = new DatabaseVarchar(size - 1, cannull);
        return temp;
    }
    if (s1[0] == 'R') {
        DataBaseType* temp = new DatabaseReal(cannull);
        return temp;
    }
    if (s1[0] == 'L') {
        DataBaseType* temp = new DatabaseLint(cannull);
        return temp;
    }
    if (s1[0] == 'D') {
        DataBaseType* temp = new DatabaseDate(cannull);
        return temp;
    }
    if (s1[0] == 'B') {
        DataBaseType* temp = new DatabaseBulb(cannull);
        return temp;
    }
    if (s1[0] == 'T') {
        DataBaseType* temp = new DatabaseText(cannull);
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
    for (int i = 0; i < inputlen; i++) {
        string temptype = input[i]->getType();
        if (temptype[6] == 'I') {
            temp[i] = new DatabaseInt(0);
        } else if (temptype[6] == 'C') {
            temp[i] = new DatabaseChar(0);
        } else if (temptype[6] == 'V') {
            temp[i] = new DatabaseVarchar(input[i]->getMaxSize() - 1);
        } else if (temptype[6] == 'R') {
            temp[i] = new DatabaseReal();
        } else if (temptype[6] == 'L') {
            temp[i] = new DatabaseLint();
        } else if (temptype[6] == 'D') {
            temp[i] = new DatabaseDate();
        } else if (temptype[6] == 'B') {
            temp[i] = new DatabaseBulb();
        } else if (temptype[6] == 'T') {
            temp[i] = new DatabaseText();
        } else {
            cout << "eeeeeRR" << endl;
        }
        temp[i]->initialize(input[i]);
    }
    return temp;
}
int UIC::stringtoint(string text)
{
    std::stringstream ss;
    int number;
    ss << text;
    ss >> number;
    return number;
}
string UIC::inttostring(int text)
{
    std::stringstream ss;
    string number;
    ss << text;
    number = ss.str();
    return number;
}
void UIC::convertmulti(bool can, char* s1)
{
    if (can) {
        *(s1) = 'A';
        *(s1 + 1) = 'B';
        *(s1 + 2) = 'L';
        *(s1 + 3) = 'E';
    } else {
        *(s1) = 'U';
        *(s1 + 1) = 'N';
        *(s1 + 2) = 'A';
        *(s1 + 3) = 'B';
    }
}

DataBaseType *UIC::copyType(DataBaseType *oriType) {
    string type = oriType->getType().substr(6);
    int size = oriType->getSize();
    bool canNull = oriType->getNullable();
    return UIC::reconvert(type, size, canNull);
}

std::vector<std::string> UIC::stringSplit(const std::string &s,
                      const std::string &delim) {
    std::vector<std::string> ret;
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    while (index != std::string::npos) {
        ret.push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    if (index - last > 0) {
        ret.push_back(s.substr(last, index - last));
    }
    return ret;
}
