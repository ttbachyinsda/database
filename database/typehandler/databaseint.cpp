#include "databaseint.h"
/*We should know that the max size of type(Int) is 255, if you set the size larger than 255
 * the size will force to be 255, whatever your input is.
 * */
DatabaseInt::DatabaseInt(int size)
{
    if (size>MAX_INT_SIZE) size=MAX_INT_SIZE;
    this->size=size;
    data=new char[size];
}
/* Remember that if you input a string more than 255 characters or illegal, data will be
 * empty.
 * */
DatabaseInt::DatabaseInt(string input)
{
    bool can=checkRight(input);
    if (can)
    {
        change(input);
    } else
    {
        int size=input.length();
        if (size>MAX_INT_SIZE) size=MAX_INT_SIZE;
        this->size=size;
        data=new char[size];
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
    if (data!=NULL) delete data;
    int size=input.length();
    this->size=size;
    data=new char[size];
    for (int i=0;i<size;i++)
    {
        data[i]=input[i];
    }
}
/* Really commend to use these two methods
 * */
bool DatabaseInt::checkRight(string input)
{
    int lengthofinput=input.length();
    if (lengthofinput>this->size) return false;
    for (int i=0;i<lengthofinput;i++)
        if (input[i]<'0' || input[i]>'9')
            return false;
    return true;
}
bool DatabaseInt::checkRightAndChange(string input)
{
    bool can=checkRight(input);
    if (can)
    {
        change(input);
        return true;
    }
    return false;
}
string DatabaseInt::getType()
{
    char str[25];
    sprintf(str, "%d" , size);
    string temp(str);
    return "Type: Int("+temp+")";
}
