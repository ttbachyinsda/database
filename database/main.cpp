#include <iostream>
#include "tester/testsql.h"
#include "tester/testdatabase.h"
#include "tester/testtype.h"
#include "tester/testflexible.h"
#include "tester/testiterator.h"
using namespace std;

int main(int argc, char* argv[])
{

//    TestSQL t;
//    t.startTestFile("a.sql");
//    t.startTestInteractive();
/*
    testtype t;
    t.begintest(false);
    testdatabase v;
    v.begintest();
    */
    testiterator w;
    w.begintest();

    testflexible x;
    x.begintest();


    return 0;
}
