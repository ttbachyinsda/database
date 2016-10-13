#include "databasechar.h"
/*We should know that the max size of type(Char) is 255, if you set the size larger than 255
 * the size will force to be 255, whatever your input is.
 * */
DatabaseChar::DatabaseChar(int size)
{
    if (size>MAX_CHAR_SIZE) size=MAX_CHAR_SIZE;
    this->size=size;
    data=new char[size];
    memset(data,0,size);
}
/* Remember that if you input a string more than 255 characters or illegal, data will be
 * empty.
 * */
DatabaseChar::DatabaseChar(string input)
{
    this->size=MAX_CHAR_SIZE;
    bool can=checkRight(input);
    if (can)
    {
        this->size=input.length();
        data=new char[this->size];
        memcpy(data,input.data(),this->size);
    } else
    {
        int size=input.length();
        if (size>MAX_CHAR_SIZE) size=MAX_CHAR_SIZE;
        this->size=size;
        data=new char[size];
        memset(data,0,size);
    }
}
DatabaseChar::DatabaseChar(char *input, int size)
{
    if (size<=MAX_CHAR_SIZE)
    {
        this->size=size;
        data=new char[size];
        memcpy(data,input,size);
    } else
    {
        this->size=MAX_CHAR_SIZE;
        this->data=new char[MAX_CHAR_SIZE];
        memset(data,0,size);
    }
}

//Return length of type(Char)
int DatabaseChar::getSize()
{
    return this->size;
}

/* Don't try to use them in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseChar::change(string input)
{
    int size=input.length();
    memset(data,0,this->size);
    memcpy(data,input.data(),size);
}
void DatabaseChar::change(char *input, int size)
{
    memset(data,0,this->size);
    memcpy(data,input,size);
}

/* Really commend to use these two methods
 * */
bool DatabaseChar::checkRight(string input)
{
    int lengthofinput=input.length();
    if (lengthofinput>this->size) return false;
    return true;
}
bool DatabaseChar::checkRightAndChange(string input)
{
    bool can=checkRight(input);
    if (can)
    {
        change(input);
        return true;
    }
    return false;
}
/* Be careful to use these two methods. If you want to use that, don't delete char*input,
 * because databasechar will not copy the content.
 * */
bool DatabaseChar::checkRight(char* input,int size)
{
    if (size>this->size) return false;
    return true;
}
bool DatabaseChar::checkRightAndChange(char* input,int size)
{
    if (size<=this->size)
    {
        change(input,size);
        return true;
    }
    return false;
}
/* Return the type and the maxlength of Type(char)
 * */
string DatabaseChar::getType()
{
    char str[25];
    sprintf(str, "%d" , size);
    string temp(str);
    return "Type: Char("+temp+")";
}
string DatabaseChar::output()
{
    string s(data,size);
    return s;
}

/* Don't delete that
 * */
DatabaseChar::~DatabaseChar()
{

}
