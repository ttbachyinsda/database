#include "rawgroup.h"

RawGroup::RawGroup()
{
    this->num = 0;
}
void RawGroup::add(string input)
{
    if (input == "NULL__DATA")
        return;
    if (this->num == 0) {
        this->num = 1;
        this->maxn = input;
        this->minn = input;
        this->sumn = input;
    } else {
        this->num++;
        mpq_class temp(input);
        if (temp > this->maxn)
            this->maxn = temp;
        if (temp < this->minn)
            this->minn = temp;
        this->sumn += temp;
    }
}
string RawGroup::getaverage()
{
    mpq_class numn = num;
    mpq_class output = sumn / numn;
    return output.get_str();
}
string RawGroup::getsum()
{
    return sumn.get_str();
}
string RawGroup::getmax()
{
    return maxn.get_str();
}
string RawGroup::getmin()
{
    return minn.get_str();
}
int RawGroup::getnum()
{
    return num;
}

void RawGroup::clear() {

}
