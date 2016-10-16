#include "databaseint.h"
/*We should know that the max size of type(Int) is 255, if you set the size larger than 255
 * the size will force to be 255, whatever your input is.
 * */
DatabaseInt::DatabaseInt(int size)
{
    if (size > MAX_INT_SIZE)
        size = MAX_INT_SIZE;
    this->size = size;
    data = (char*)malloc(size);
    memset(data, 0, size);
}
/* Remember that if you input a string more than 255 characters or illegal, data will be
 * empty.
 * */
DatabaseInt::DatabaseInt(string input)
{
    this->size = MAX_INT_SIZE;
    bool can = checkRight(input);
    if (can) {
        this->size = input.length();
        data = (char*)malloc(this->size);
        memcpy(data, input.data(), this->size);
    } else {
        int size = input.length();
        if (size > MAX_INT_SIZE)
            size = MAX_INT_SIZE;
        this->size = size;
        data = (char*)malloc(size);
        memset(data, 0, size);
    }
}
DatabaseInt::DatabaseInt(char* input, int size)
{
    this->size = MAX_INT_SIZE;
    bool can = checkRight(input, size);
    if (can) {
        this->size = size;
        data = (char*)malloc(size);
        memcpy(data, input, size);
    } else {
        if (size > MAX_INT_SIZE)
            size = MAX_INT_SIZE;
        this->size = size;
        this->data = (char*)malloc(size);
        memset(data, 0, size);
    }
}

//Return length of type(Int)
int DatabaseInt::getSize()
{
    return this->size;
}

/* Don't try to use it in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseInt::change(string input)
{
    int size = input.length();
    memset(data, 0, this->size);
    memcpy(data, input.data(), size);
}
void DatabaseInt::change(char* input, int size)
{
    memset(data, 0, this->size);
    memcpy(data, input, size);
}

/* Really commend to use these two methods
 * */
bool DatabaseInt::checkRight(string input)
{
    int lengthofinput = input.length();
    if (lengthofinput > this->size)
        return false;
    for (int i = 0; i < lengthofinput; i++)
        if (input[i] < '0' || input[i] > '9')
            return false;
    return true;
}
bool DatabaseInt::checkRightAndChange(string input)
{
    bool can = checkRight(input);
    if (can) {
        change(input);
        return true;
    }
    return false;
}
/* Be careful to use these two methods. If you want to use that, don't delete char*input,
 * because databasechar will not copy the content.
 * */
bool DatabaseInt::checkRight(char* input, int size)
{
    if (size > this->size)
        return false;
    for (int i = 0; i < size; i++)
        if (*(input + i) < '0' || *(input + i) > '9')
            if (*(input + i) != 0)
                return false;
    return true;
}
bool DatabaseInt::checkRightAndChange(char* input, int size)
{
    bool can = checkRight(input, size);
    if (can) {
        change(input, size);
        return true;
    }
    return false;
}
/* Return the type and the maxlength of Type(char)
 * */
string DatabaseInt::getType()
{
    char str[25];
    sprintf(str, "%d", size);
    string temp(str);
    return "Type: Int(" + temp + ")";
}
string DatabaseInt::output()
{
    char* tmp = new char[size];
    memcpy(tmp, data, size);
    for (int i = 0; i < size; i++)
        if (*(tmp + i) == 0 || *(tmp + i) == 32)
            *(tmp + i) = '0';
    string s(tmp, size);
    return s;
}

/* Don't delete that
 * */
DatabaseInt::~DatabaseInt()
{
}
