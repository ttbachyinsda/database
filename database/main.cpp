#include <iostream>
#include "tester/testsql.h"
#include "tester/testdatabase.h"
using namespace std;

int main(int argc, char* argv[])
{
    TestSQL t;
    t.startTestFile("a.sql");
//    t.startTestInteractive();
    return 0;
}
