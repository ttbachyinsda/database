#include "databasetext.h"

DatabaseText::DatabaseText()
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
DatabaseText::DatabaseText(bool cannull)
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

int DatabaseText::getSize()
{
    return this->size + 1;
}
int DatabaseText::getRealSize()
{
    return this->size;
}
int DatabaseText::getMaxSize()
{
    return this->size + 1;
}
/* Don't try to use them in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseText::change(string input)
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
void DatabaseText::change(char* input, int size)
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
void DatabaseText::changetoNull()
{
    isNull = true;
    data[this->size] = IS_NULL;
}

/* Really commend to use these two methods
 * */
bool DatabaseText::checkRight(string input)
{
    return true;
}
bool DatabaseText::checkRight(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    return true;
}
bool DatabaseText::checkRightAndChange(string input)
{
    change(input);
    return true;
}
bool DatabaseText::checkRightAndChange(string input, bool inputisnull)
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
bool DatabaseText::checkRightc(char* input, int size)
{
    return true;
}
bool DatabaseText::checkRightc(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    return true;
}
bool DatabaseText::checkRightAndChangec(char* input, int size)
{
    change(input, size);
    return true;
}
bool DatabaseText::checkRightAndChangec(char* input, int size, bool inputisnull)
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
string DatabaseText::getType()
{
    return "Type: Text";
}
string DatabaseText::output()
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
DatabaseText::~DatabaseText()
{
}
bool DatabaseText::read(char* input, int inputlen, int& position)
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
bool DatabaseText::write(char* input, int& position)
{
    memcpy(input, data, this->size + 1);
    position += this->size + 1;
    return true;
}
bool DatabaseText::analysis(string input)
{
    return true;
}
bool DatabaseText::analysisc(char* input, int inputsize)
{
    return true;
}
