#include "mainwindow.h"
#include <QApplication>
#include <QQmlExtensionPlugin>
#include <iostream>
#include "tester/testtype.h"
#include "tester/testtable.h"
using namespace std;
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    testtype t;
    t.begintest(false);
    testtable u;
    u.begintest();
    return 0;
}
