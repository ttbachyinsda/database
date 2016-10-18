#include "testiterator.h"

testiterator::testiterator()
{
}
string testiterator::RandomString()
{
    int aa = rand();
    stringstream ss;
    ss << aa;
    string s1 = ss.str();
    return s1;
}
string testiterator::InttoString(int num)
{
    int aa = num;
    stringstream ss;
    ss << aa;
    string s1 = ss.str();
    return s1;
}

void testiterator::begintest()
{
    string filename = "onetable.tb";
    cout << "test iterator table begin..." << endl;
    Table* onetable = new FixedSizeTable();
    onetable->setfilename(filename);
    onetable->setname("testiterator");
    vector<string> clname;
    vector<string> cltype;
    vector<int> clsize;
    clname.push_back("userid");
    clname.push_back("password");
    clname.push_back("age");
    cltype.push_back("INT");
    cltype.push_back("CHAR");
    cltype.push_back("INT");
    clsize.push_back(20);
    clsize.push_back(20);
    clsize.push_back(2);
    onetable->createTable(clname, cltype, clsize);
    onetable->Initialize();
    string* aaa = new string[3];
    int pagenum, pageposition;
    Record* t = RecordFactory::getrecord(onetable);
    QTime time;
    time.start();
    for (int i = 0; i < 200000; i++) {
        aaa[0] = InttoString(i);
        aaa[1] = "12345678";
        aaa[2] = "58";
        t->set(aaa);
        onetable->FastAllInsert(pagenum, pageposition, t);
        //if (i%1000==0) cout<<pagenum<<' '<<pageposition<<endl;
    }
    delete t;
    delete[] aaa;
    cout << onetable->getPageNum() << endl;
    cout << onetable->getPageRowNum(1030) << endl;
    int time_Diff = time.elapsed();
    float f = time_Diff / 1000.0;
    cout << "Time table: " << f << endl;

    cout << "test table end" << endl;
    cout << "test iterator begin" << endl;

    Iterator* iterator = IteratorFactory::getiterator(onetable);
    Record* record = RecordFactory::getrecord(onetable);
    char* temp = new char[iterator->getcurrentsize()];
    if (iterator->available()) {
        int tempsize;
        iterator->getdata(temp, tempsize);
        record->Input(temp);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    ++(*iterator);
    if (iterator->available()) {
        int tempsize;
        iterator->getdata(temp, tempsize);
        record->Input(temp);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    iterator->access(1031, 179);
    if (iterator->available()) {
        int tempsize;
        iterator->getdata(temp, tempsize);
        record->Input(temp);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    iterator->access(1031, 0);
    cout << "try to delete" << endl;
    iterator->deletedata();
    if (iterator->available()) {
        int tempsize;
        iterator->getdata(temp, tempsize);
        record->Input(temp);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }
    delete onetable;
    delete iterator;
    delete record;
    delete[] temp;
}
