#include "testtable.h"

testtable::testtable()
{

}
string testtable::RandomString()
{
    int aa = rand();
    stringstream ss;
    ss<<aa;
    string s1 = ss.str();
    return s1;
}
string testtable::InttoString(int num)
{
    int aa = num;
    stringstream ss;
    ss<<aa;
    string s1 = ss.str();
    return s1;
}

void testtable::begintest()
{
    string filename="onetable.db";
    cout<<"test table begin..."<<endl;
    Table* onetable = new FixedSizeTable();
    onetable->setfilename(filename);
    onetable->setname("testtable");
    vector<string> clname; vector<string> cltype; vector<int> clsize;
    clname.push_back("userid"); clname.push_back("password"); clname.push_back("age");
    cltype.push_back("INT"); cltype.push_back("CHAR"); cltype.push_back("INT");
    clsize.push_back(20); clsize.push_back(20); clsize.push_back(2);
    onetable->createTable(clname,cltype,clsize);
    onetable->Initialize();
    vector<string> aaa;
    QTime time;
    time.start();
    for (int i=0;i<200000;i++)
    {
    aaa.push_back(InttoString(i)); aaa.push_back("12345678"); aaa.push_back("58");
    onetable->checkInsert(aaa);
    onetable->Insert();
    aaa.clear();
    }
    int time_Diff = time.elapsed();
    float f = time_Diff/1000.0;
    cout<<"Time table: "<<f<<endl;
    bool yes=onetable->FindAt(1,0);
    aaa.clear();
    if (yes)
    {
        aaa=onetable->checkOutput();
        for (unsigned int i=0;i<aaa.size();i++)
        {
            cout<<"yes: "<<clname[i]<<" &&&"<<aaa[i]<<"&&& "<<endl;
        }
    }
    yes=onetable->FindAt(1,1);
    aaa.clear();
    if (yes)
    {
        aaa=onetable->checkOutput();
        for (unsigned int i=0;i<aaa.size();i++)
        {
            cout<<"yes: "<<clname[i]<<" &&&"<<aaa[i]<<"&&& "<<endl;
        }
    }
    delete onetable;

    //Open Again:
    cout<<"Open again"<<endl;
    onetable = new FixedSizeTable();
        onetable->setfilename("onetable.db");
        onetable->Initialize();
        yes=onetable->FindAt(1,0);
        aaa.clear();
        if (yes)
        {
            aaa=onetable->checkOutput();
            for (unsigned int i=0;i<aaa.size();i++)
            {
                cout<<"yes: "<<clname[i]<<" &&&"<<aaa[i]<<"&&& "<<endl;
            }
        }
        yes=onetable->FindAt(1,1);
        aaa.clear();
        if (yes)
        {
            aaa=onetable->checkOutput();
            for (unsigned int i=0;i<aaa.size();i++)
            {
                cout<<"yes: "<<clname[i]<<" &&&"<<aaa[i]<<"&&& "<<endl;
            }
        }
        delete onetable;
    cout<<onetable->getname()<<endl;
    cout<<"test table end"<<endl;
}
