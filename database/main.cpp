#include <iostream>
#include "tester/testsql.h"
#include "tester/testdatabase.h"
#include "tester/testtype.h"
#include "tester/testflexible.h"
#include "tester/testiterator.h"
#include "layer/qmlif.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
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

//    testiterator w;
//    w.begintest();

//    testflexible x;
//    x.begintest();
    qmlRegisterType<QMLif>("thjdb.QMLif",1,0,"QMLif");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QPM_INIT(engine)
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
