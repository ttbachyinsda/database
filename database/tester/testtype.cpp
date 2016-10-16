#include "testtype.h"

testtype::testtype()
{
}
void testtype::begintestchar()
{
    DataBaseType* a = new DatabaseChar(20);
    a->printdata("a");
    char* x = new char[20];
    memcpy(x, "acefg               ", 20);
    bool c = a->checkRightAndChange(x, 20);
    delete x;
    char* y = new char[53];
    memcpy(y, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 53);
    a->printdata("a");
    cout << a->output() << endl;
    c = a->checkRightAndChange(y, 53);
    delete y;
    a->printdata("a");
    cout << a->output() << 'E' << a->output().length() << endl;
    cout << a->getType() << endl;
    delete a;
    DataBaseType* b = new DatabaseInt(5);
    char* z = new char[5];
    memcpy(z, "12345", 5);
    b->printdata("b");
    cout << b->output() << 'E' << b->output().length() << endl;
    cout << b->checkRight("1aa") << endl;
    c = b->checkRightAndChange(z, 5);
    delete z;
    b->printdata("b");
    cout << b->output() << endl;
    delete b;
}
void testtype::beginteststring()
{
    DataBaseType* a = new DatabaseChar(20);
    a->printdata("a");
    a->checkRightAndChange("acefg");
    a->printdata("a");
    a->checkRightAndChange("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    a->printdata("a");
    cout << a->getType() << endl;
    delete a;
    DataBaseType* b = new DatabaseInt(5);
    b->printdata("b");
    cout << b->checkRight("1aa") << endl;
    b->checkRightAndChange("12345");
    b->printdata("b");
    delete b;
}

void testtype::begintest(bool timetest)
{
    cout << "test type begin" << endl;
    beginteststring();
    begintestchar();
    beginteststring();
    begintestchar();
    QTime time;
    time.start();
    if (timetest) {
        for (int i = 0; i < 100000000; i++) {
            DataBaseType* a = new DatabaseChar(20);
            a->checkRightAndChange("acefg");
            a->checkRightAndChange("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            delete a;
            DataBaseType* b = new DatabaseInt(5);
            b->checkRightAndChange("12345");
            delete b;
        }
        int time_Diff = time.elapsed();
        float f = time_Diff / 1000.0;
        cout << "Time string: " << f << endl;
        QTime time2;
        time2.start();
        for (int i = 0; i < 100000000; i++) {
            DataBaseType* a = new DatabaseChar(20);
            char* x = new char[20];
            memcpy(x, "acefg               ", 20);
            bool c = a->checkRightAndChange(x, 20);
            delete x;
            char* y = new char[53];
            memcpy(y, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 53);
            c = a->checkRightAndChange(y, 53);
            delete y;
            delete a;
            DataBaseType* b = new DatabaseInt(5);
            char* z = new char[5];
            memcpy(z, "12345", 5);
            c = b->checkRightAndChange(z, 5);
            delete z;
            delete b;
        }
        time_Diff = time2.elapsed();
        f = time_Diff / 1000.0;
        cout << "Time char: " << f << endl;
    }
    cout << "Type test complete." << endl;
}
