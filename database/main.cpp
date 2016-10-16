#include "mainwindow.h"
#include <QApplication>
#include <QQmlExtensionPlugin>
#include <iostream>
#include "tester/testtype.h"
#include "tester/testtable.h"
#include "tester/testdatabase.h"
using namespace std;
int main(int argc, char *argv[])
{
    testtype t;
    t.begintest(false);
    testtable u;
    u.begintest();
    testdatabase v;
    v.begintest();
    return 0;
}
