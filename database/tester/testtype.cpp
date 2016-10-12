#include "testtype.h"

testtype::testtype()
{

}
void testtype::begintestchar()
{
    type *a = new DatabaseChar(20);
    a->printdata("a");
    char *x= new char[20];
    strncpy(x,"acefg               ",20);
    bool c=a->checkRightAndChange(x,20);
    if (!c) delete x;
    char *y= new char[53];
    strncpy(y,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",53);
    a->printdata("a");
    cout<<a->output()<<endl;
    c=a->checkRightAndChange(y,53);
    if (!c) delete y;
    a->printdata("a");
    cout<<a->output()<<endl;
    cout<<a->getType()<<endl;
    delete a;
    type *b = new DatabaseInt(5);
    char *z= new char[5];
    strncpy(z,"12345",5);
    b->printdata("b");
    cout<<b->output()<<endl;
    cout<<b->checkRight("1aa")<<endl;
    c=b->checkRightAndChange(z,5);
    if (!c) delete z;
    b->printdata("b");
    cout<<b->output()<<endl;
    delete b;
}
void testtype::beginteststring()
{
    type *a = new DatabaseChar(20);
    a->printdata("a");
    a->checkRightAndChange("acefg");
    a->printdata("a");
    a->checkRightAndChange("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    a->printdata("a");
    cout<<a->getType()<<endl;
    delete a;
    type *b = new DatabaseInt(5);
    b->printdata("b");
    cout<<b->checkRight("1aa")<<endl;
    b->checkRightAndChange("12345");
    b->printdata("b");
    delete b;
}

void testtype::begintest(bool timetest)
{
    cout<<"test type begin"<<endl;
    beginteststring();
    begintestchar();
    beginteststring();
    begintestchar();
    QTime time;
    time.start();
    if (timetest)
    {
    for (int i=0;i<100000000;i++)
    {
        type *a = new DatabaseChar(20);
        a->checkRightAndChange("acefg");
        a->checkRightAndChange("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        delete a;
        type *b = new DatabaseInt(5);
        b->checkRightAndChange("12345");
        delete b;
    }
    int time_Diff = time.elapsed();
    float f = time_Diff/1000.0;
    cout<<"Time string: "<<f<<endl;
    QTime time2;
    time2.start();
    for (int i=0;i<100000000;i++)
    {
        type *a = new DatabaseChar(20);
        char *x= new char[20];
        strncpy(x,"acefg               ",20);
        bool c=a->checkRightAndChange(x,20);
        if (!c) delete x;
        char *y= new char[53];
        strncpy(y,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",53);
        c=a->checkRightAndChange(y,53);
        if (!c) delete y;
        delete a;
        type *b = new DatabaseInt(5);
        char *z= new char[5];
        strncpy(z,"12345",5);
        c=b->checkRightAndChange(z,5);
        if (!c) delete z;
        delete b;
    }
    time_Diff = time2.elapsed();
    f = time_Diff/1000.0;
    cout<<"Time char: "<<f<<endl;
    }
    cout<<"Type test complete."<<endl;
}
