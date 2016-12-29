#include "databasebulb.h"

DatabaseBulb::DatabaseBulb()
{
    NullCondition();
    this->size = 8;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    data[size] = IS_NOT_NULL;

    this->nowoffset = -1;
    memcpy(data, &this->nowoffset, 4);

    this->Nullable = true;
    this->isNull = false;
}
DatabaseBulb::DatabaseBulb(bool cannull)
{
    NullCondition();
    this->size = 8;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    data[size] = IS_NOT_NULL;

    this->nowoffset = -1;
    memcpy(data, &this->nowoffset, 4);

    this->Nullable = cannull;
    this->isNull = false;
}

int DatabaseBulb::getSize()
{
    return this->size + 1;
}
int DatabaseBulb::getRealSize()
{
    return this->size;
}
int DatabaseBulb::getMaxSize()
{
    return this->size + 1;
}
/* Don't try to use them in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseBulb::change(string input)
{
    isNull = false;
    memcpy(data,input.data(),8);
//    this->nowoffset = BulbFile::put(input.data(), input.length());

//    memcpy(data, &this->nowoffset, 4);
//    int strsize = input.length();
//    memcpy(data + 4, &strsize, 4);

    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseBulb::change(char* input, int size)
{
    isNull = false;
    memcpy(data,input,8);
//    this->nowoffset = BulbFile::put(input, size);

//    memcpy(data, &this->nowoffset, 4);
//    int strsize = size;
//    memcpy(data + 4, &strsize, 4);

    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseBulb::changetoNull()
{
    isNull = true;
    data[this->size] = IS_NULL;
}

/* Really commend to use these two methods
 * */
bool DatabaseBulb::checkRight(string input)
{
    return true;
}
bool DatabaseBulb::checkRight(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    return true;
}
bool DatabaseBulb::checkRightAndChange(string input)
{
    change(input);
    return true;
}
bool DatabaseBulb::checkRightAndChange(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull) {
        changetoNull();
        return true;
    }
    change(input);
    return true;
}
/* Don't Be careful to use these two methods. If you want to use that,
 * you can delete char*input,
 * because databasechar will copy the content.
 * */
bool DatabaseBulb::checkRightc(char* input, int size)
{
    return true;
}
bool DatabaseBulb::checkRightc(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    return true;
}
bool DatabaseBulb::checkRightAndChangec(char* input, int size)
{
    change(input, size);
    return true;
}
bool DatabaseBulb::checkRightAndChangec(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull) {
        changetoNull();
        return true;
    }
    change(input, size);
    return true;
}
/* Return the type and the maxlength of Type(char)
 * */
string DatabaseBulb::getType()
{
    return "Type: BULB";
}
string DatabaseBulb::output()
{
    if (isNull)
        return "NULL__DATA";
    string temp(data,8);
    return temp;
//    if (this->nowoffset == -1)
//        return "";
//    int strsize;
//    memcpy(&strsize, data + 4, 4);
//    return BulbFile::get(this->nowoffset, strsize);
}

/* Don't delete that
 * */
DatabaseBulb::~DatabaseBulb()
{
}
bool DatabaseBulb::read(char* input, int inputlen, int& position)
{
    memcpy(data, input, this->size + 1);
    position += this->size + 1;
    if (data[this->size] == IS_NULL)
        this->isNull = true;
    else
        this->isNull = false;
    memcpy(&this->nowoffset, data, 4);

    return true;
}
bool DatabaseBulb::write(char* input, int& position)
{
    memcpy(input, data, this->size + 1);
    position += this->size + 1;
    return true;
}
bool DatabaseBulb::analysis(string input)
{
    return true;
}
bool DatabaseBulb::analysisc(char* input, int inputsize)
{
    return true;
}
