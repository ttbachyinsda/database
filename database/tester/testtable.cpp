#include "testtable.h"

testtable::testtable()
{

}
void testtable::begintest()
{
    cout<<"test table begin..."<<endl;
    Table* onetable = new FixedSizeTable();
    onetable->setfilename("/home/ttbachyinsda/onetable.db");
    onetable->setname("testtable");
    vector<string> clname; vector<string> cltype; vector<int> clsize;
    clname.push_back("userid"); clname.push_back("password"); clname.push_back("age");
    cltype.push_back("INT"); cltype.push_back("CHAR"); cltype.push_back("INT");
    clsize.push_back(20); clsize.push_back(20); clsize.push_back(2);
    onetable->createTable(clname,cltype,clsize);
    onetable->Initialize();
    vector<string> aaa;
    aaa.push_back("1234567"); aaa.push_back("12345678"); aaa.push_back("58");
    onetable->checkInsert(aaa);
    onetable->Insert();
    aaa.clear();
    aaa.push_back("234567"); aaa.push_back("2345678"); aaa.push_back("08");
    onetable->checkInsert(aaa);
    onetable->Insert();
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
    cout<<"test table end"<<endl;
}
