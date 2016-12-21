#include "testhashflexible.h"

testhashflexible::testhashflexible()
{

}
string testhashflexible::RandomString()
{
    int aa = rand();
    stringstream ss;
    ss << aa;
    string s1 = ss.str();
    return s1;
}
string testhashflexible::InttoString(int num)
{
    int aa = num;
    stringstream ss;
    ss << aa;
    string s1 = ss.str();
    return s1;
}
string testhashflexible::signedlongtostring(long long num)
{
    char s[8];
    memcpy(s,&num,8);
    string t(s,8);
    return t;
}
string testhashflexible::doubletostring(double num)
{
    char s[8];
    memcpy(s,&num,8);
    string t(s,8);
    return t;
}

void testhashflexible::testindex(Table* onetable,string input)
{
    if (onetable->getindexes() == NULL)
    {
        cout<<"MERROR"<<endl;
        return;
    }
    if (onetable->getindexes()[0]==NULL)
    {
        cout<<"no error"<<endl;
        return;
    }
    cout<<"test hashflexible index begin"<<endl;
    Iterator* it = IteratorFactory::getiterator(onetable);
    string temp=it->compile(input,0);
    cout<<"try to search "<<temp<<endl;
    index_key k(temp.c_str(),temp.length());
    index_value v;
    int answer=onetable->getindexes()[0]->search(k,&v);
    if (answer==0)
    {
        cout<<"has found"<<endl;
        cout<<v.pagenum<<' '<<v.pageposition<<endl;
    } else
        cout<<"has not found"<<endl;
    cout<<"test index end"<<endl;
    delete it;
}

void testhashflexible::begintest()
{
    string filename = "onehashflexibletable.tb";
    cout << "test hash flexible table begin..." << endl;
    Table* onetable = new HashFlexibleTable();
    onetable->setfilename(filename);
    onetable->setname("hashflexible");
    vector<string> clname;
    vector<DataBaseType*> cltype;
    clname.push_back("userid");
    clname.push_back("password");
    clname.push_back("age");
    clname.push_back("lucky");
    clname.push_back("primary");
    string t1 = "INTE";
    string t2 = "VARC";
    string t3 = "INTE";
    string t4 = "LINT";
    string t5 = "REAL";
    auto *conditions = new string[5];
    conditions[0]="FRTO";
    conditions[1]="0";
    conditions[2]="20000000";
    auto type1 = UIC::reconvert(t1, 10, true);
    type1->readcondition(conditions);
    auto type2 = UIC::reconvert(t2, 20, true);
    auto type3 = UIC::reconvert(t3, 2, true);
    auto type4 = UIC::reconvert(t4, 8, true);
    auto type5 = UIC::reconvert(t5, 8, true);
    cltype.push_back(type1);
    cltype.push_back(type2);
    cltype.push_back(type3);
    cltype.push_back(type4);
    cltype.push_back(type5);
    onetable->createTable(clname, cltype);
    onetable->Initialize();
    delete[] conditions;

    onetable->setmajornum(0);

    onetable->setmultivalue(0,false);
    //onetable->createemptyindex(0);
    auto aaa = new string[5];
    int pagenum, rownum;
    auto t = RecordFactory::getrecord(onetable);
    QTime time;
    time.start();
    Group group;
    for (int i = 0; i < 200000; i++) {
        aaa[0] = InttoString(i);
        aaa[1] = "a"+InttoString(i);
        aaa[2] = "58";
        aaa[3] = signedlongtostring(i);
        aaa[4] = doubletostring(i);
        bool can = t->set(aaa);
        if (can && i%3)
        {
            can=t->setAt(1,"",true);
            t->update();
        }
        if (can)
            onetable->FastAllInsert(pagenum, rownum, t);
        if (i%3==0)
            group.add(pagenum,rownum);
        //cout<<pagenum<<' '<<rownum<<endl;
        //assert(pagenum <= onetable->getPageNum());
        //cout<<e<<endl;
    }
    delete t;
    delete[] aaa;

    vector<int> colnum; colnum.push_back(0);
    onetable->createindex(colnum);


    cout<<"group begin"<<endl;
    group.getmax(onetable,0);
    group.getmin(onetable,0);
    group.getsum(onetable,0);
    group.getaverage(onetable,0);
    group.getmax(onetable,3);
    group.getmin(onetable,3);
    group.getsum(onetable,3);
    group.getaverage(onetable,3);
    group.getmax(onetable,4);
    group.getmin(onetable,4);
    group.getsum(onetable,4);
    group.getaverage(onetable,4);
    cout<<"group end"<<endl;

    int time_Diff = time.elapsed();
    float f = time_Diff / 1000.0;
    cout << "Time table: " << f << endl;

    cout << "test table end" << endl;
    cout << "test iterator begin" << endl;

    testindex(onetable,"5");
    cout << onetable->getPageNum() << endl;
    cout << onetable->getPageRowNum(1030) << endl;


    auto iterator = IteratorFactory::getiterator(onetable);
    auto record = RecordFactory::getrecord(onetable);

//    int js=0;
//    while (iterator->available())
//    {
//        js++;
//        int k = iterator->gethashnum();
//        if (k<1024)
//        cout<<iterator->gethashnum()<<endl;
//        iterator->getdata(record);

//        for (int i = 0; i < cltype.size(); i++) {
//            cout << i << ' ' << record->getAt(i) << ' ';
//        }
//        cout<<endl;
//        ++(*iterator);
//    }

//    iterator->getbegin();

    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }


    ++(*iterator);
    if (iterator->available()) {
       iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    iterator->access(300, 1);
    if (iterator->available()) {
       iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }

    iterator->access(2, 0);
    cout << "try to delete" << endl;
    iterator->deletedata();
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    testindex(onetable,"0");
    testindex(onetable,"1");
    testindex(onetable,"19");
    delete iterator;
    delete record;
    delete onetable;

    cout << "Open again" << endl;
    onetable = new HashFlexibleTable();
    onetable->setfilename(filename);
    onetable->Initialize();

    for (int i=0;i<onetable->getcolumncount();i++)
    {
        cout<<"MULTIPLY: "<<onetable->getmultivalue(i)<<endl;
    }
    iterator = IteratorFactory::getiterator(onetable);
    record = RecordFactory::getrecord(onetable);
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    ++(*iterator);
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    iterator->access(300, 1);
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < cltype.size(); i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    cout<<"group begin"<<endl;
    group.getmax(onetable,0);
    group.getmin(onetable,0);
    group.getsum(onetable,0);
    group.getaverage(onetable,0);
    group.getmax(onetable,3);
    group.getmin(onetable,3);
    group.getsum(onetable,3);
    group.getaverage(onetable,3);
    group.getmax(onetable,4);
    group.getmin(onetable,4);
    group.getsum(onetable,4);
    group.getaverage(onetable,4);
    cout<<"group end"<<endl;
    delete onetable;
    delete iterator;
    delete record;
    cout << onetable->getname() << endl;
    cout<<"test hash flexible table end"<<endl;

}
