#include "mainwindow.h"
#include "tester/testdatabase.h"
#include "tester/testiterator.h"
#include "tester/testtype.h"
#include "tester/testflexible.h"
#include <QApplication>
#include <QQmlExtensionPlugin>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
/*
    testtype t;
    t.begintest(false);

    testdatabase v;
    v.begintest();
    testiterator w;
    w.begintest();
    */
    testflexible x;
    x.begintest();

    return 0;
}
