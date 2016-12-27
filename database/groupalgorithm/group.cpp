#include "group.h"
Group::Group()
{
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
    mpq_class temp, maxn;
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
    cout << "getmax end" << ' ' << maxn << endl;
    return maxn.get_str();
}
string Group::getmin(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpq_class temp, minn;
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
    cout << "getmin end" << ' ' << minn << endl;
    return minn.get_str();
}
string Group::getsum(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpq_class temp, sum;
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
    cout << "getsum end" << ' ' << sum << endl;
    return sum.get_str();
}
string Group::getaverage(Table* onetable, int columnnum)
{
    auto t = RecordFactory::getrecord(onetable);
    int i = 0;
    mpq_class temp, sum;
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
    mpq_class num = i;
    mpq_class average;
    if (i)
       average = sum / num;
    else
       average = 0;

    cout << "getaverage end" << ' ' << average << endl;
    return average.get_str();
}
