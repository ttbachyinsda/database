#include "testflexible.h"

testflexible::testflexible()
{

}
string testflexible::RandomString()
{
    int aa = rand();
    stringstream ss;
    ss << aa;
    string s1 = ss.str();
    return s1;
}
string testflexible::InttoString(int num)
{
    int aa = num;
    stringstream ss;
    ss << aa;
    string s1 = ss.str();
    return s1;
}
void testflexible::testindex(Table* onetable)
{
    cout<<"test index begin"<<endl;
    string temp="0";
    char * tst=(char*)malloc(7);
    memset(tst,0,7);
    memcpy(tst,temp.c_str(),temp.length()+1);
    cout<<tst<<endl;
    index_key k(tst, 7);
    index_value v;
    cout<<onetable->getindexes()[0]->search(k,&v)<<endl;
    cout<<v.pagenum<<' '<<v.pageposition<<endl;
    cout<<"test index end"<<endl;
}

void testflexible::begintest()
{
    string filename = "oneflexibletable.tb";
    cout << "test iterator table begin..." << endl;
    Table* onetable = new FlexibleTable();
    onetable->setfilename(filename);
    onetable->setname("testiterator");
    vector<string> clname;
    vector<DataBaseType*> cltype;
    clname.push_back("userid");
    clname.push_back("password");
    clname.push_back("age");
    string t1 = "INTE";
    string t2 = "VARC";
    string t3 = "INTE";
    string *conditions = new string[3];
    conditions[0]="FRTO";
    conditions[1]="0";
    conditions[2]="500000";
    DataBaseType* type1 = UIC::reconvert(t1.data(), 6, true);
    type1->readcondition(conditions);
    DataBaseType* type2 = UIC::reconvert(t2.data(), 20, true);
    DataBaseType* type3 = UIC::reconvert(t3.data(), 2, true);
    cltype.push_back(type1);
    cltype.push_back(type2);
    cltype.push_back(type3);
    onetable->createTable(clname, cltype);
    onetable->Initialize();
    onetable->setmajornum(0);
    onetable->setmultivalue(0,false);
    onetable->createemptyindex(0);
    string* aaa = new string[3];
    int pagenum, pageposition;
    Record* t = RecordFactory::getrecord(onetable);
    QTime time;
    time.start();
    for (int i = 0; i < 200000; i++) {
        aaa[0] = InttoString(i);
        aaa[1] = "a"+InttoString(i);
        aaa[2] = "58";
        bool can = t->set(aaa);
        if (can && i%3)
        {
            can=t->setAt(1,"",true);
            t->update();
        }
        if (can)
            onetable->FastAllInsert(pagenum, pageposition, t);
        //if (i%1000==0) cout<<pagenum<<' '<<pageposition<<endl;
    }
    delete t;
    delete[] aaa;
    testindex(onetable);
    cout << onetable->getPageNum() << endl;
    cout << onetable->getPageRowNum(1030) << endl;
    int time_Diff = time.elapsed();
    float f = time_Diff / 1000.0;
    cout << "Time table: " << f << endl;

    cout << "test table end" << endl;
    cout << "test iterator begin" << endl;

    Iterator* iterator = IteratorFactory::getiterator(onetable);
    Record* record = RecordFactory::getrecord(onetable);
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }


    ++(*iterator);
    if (iterator->available()) {
       iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    iterator->access(300, 1);
    if (iterator->available()) {
       iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }

    iterator->access(300, 0);
    cout << "try to delete" << endl;
    iterator->deletedata();
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }

    delete iterator;
    delete record;
    delete onetable;

    cout << "Open again" << endl;
    onetable = new FlexibleTable();
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
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    ++(*iterator);
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    iterator->access(300, 1);
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    delete onetable;
    delete iterator;
    delete record;
    cout << onetable->getname() << endl;
    cout << "test table end" << endl;


}
