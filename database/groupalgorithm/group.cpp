#include "group.h"
Group::Group()
{
    mpreal::set_default_prec(mpfr::digits2bits(MAX_DIGITS));
}
bool Group::add(int x, int y)
{
    auto c = make_pair(x, y);
    if (data.count(c) == 0) {
        data[c] = 1;
        return true;
    } else {
        return false;
    }
}
string Group::getmax(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpreal temp, maxn;
    bool haveget = false;
    for (auto it = data.begin(); it != data.end(); it++) {
        i++;
        int pagenum = it->first.first, rownum = it->first.second;
        bool can = onetable->FastOutput(pagenum, rownum, t);
        if (!can) {
            i--;
            continue;
        }
        temp = t->getAt(columnnum);
        if (!haveget || temp > maxn) {
            haveget = true;
            maxn = temp;
        }
    }
    delete t;
    cout << "getmax end" << ' ' << getstr(maxn) << endl;
    return getstr(maxn);
}
string Group::getmin(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpreal temp, minn;
    bool haveget = false;
    for (auto it = data.begin(); it != data.end(); it++) {
        i++;
        int pagenum = it->first.first, rownum = it->first.second;
        bool can = onetable->FastOutput(pagenum, rownum, t);
        if (!can) {
            i--;
            continue;
        }
        temp = t->getAt(columnnum);
        if (!haveget || temp < minn) {
            haveget = true;
            minn = temp;
        }
    }
    delete t;
    cout << "getmin end" << ' ' << getstr(minn) << endl;
    return getstr(minn);
}
string Group::getsum(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpreal temp, sum;
    sum = 0;
    for (auto it = data.begin(); it != data.end(); it++) {
        i++;
        int pagenum = it->first.first, rownum = it->first.second;
        bool can = onetable->FastOutput(pagenum, rownum, t);
        if (!can) {
            i--;
            continue;
        }
        temp = t->getAt(columnnum);
        sum += temp;
    }
    delete t;
    cout << "getsum end" << ' ' << getstr(sum) << endl;
    return getstr(sum);
}
string Group::getaverage(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpreal temp, sum;
    sum = 0;
    for (auto it = data.begin(); it != data.end(); it++) {
        i++;
        int pagenum = it->first.first, rownum = it->first.second;
        bool can = onetable->FastOutput(pagenum, rownum, t);
        if (!can) {
            i--;
            continue;
        }
        temp = t->getAt(columnnum);
        sum += temp;
    }
    delete t;
    mpreal num = i;
    mpreal average;
    if (i)
       average = sum / num;
    else
       average = 0;

    cout << "getaverage end" << ' ' << getstr(average) << endl;
    return getstr(average);
}
string Group::getstr(mpreal num)
{
    stringstream sstream;
    sstream.precision(MAX_DIGITS);
    sstream<<num;
    return sstream.str();
}
