#include "rawgroup.h"

RawGroup::RawGroup()
{
    mpreal::set_default_prec(mpfr::digits2bits(MAX_DIGITS));
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
        mpreal temp(input);
        if (temp > this->maxn)
            this->maxn = temp;
        if (temp < this->minn)
            this->minn = temp;
        this->sumn += temp;
    }
}
string RawGroup::getaverage()
{
    if (num == 0)
    {
        return "0";
    }
    mpreal numn = num;
    mpreal output = sumn / numn;
    return getstr(output);
}
string RawGroup::getsum()
{
    return getstr(sumn);
}
string RawGroup::getmax()
{
    return getstr(maxn);
}
string RawGroup::getmin()
{
    return getstr(minn);
}
int RawGroup::getnum()
{
    return num;
}
string RawGroup::getstr(mpreal num)
{
    stringstream sstream;
    sstream.precision(MAX_DIGITS);
    sstream<<num;
    return sstream.str();
}

void RawGroup::clear() {

}
