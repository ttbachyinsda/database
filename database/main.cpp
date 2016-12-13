#include <iostream>
#include "tester/testsql.h"
#include "tester/testdatabase.h"
#include "tester/testtype.h"
#include "tester/testflexible.h"
#include "tester/testiterator.h"
#include "tester/testdate.h"
#include "tester/testvirtual.h"
#include "tester/testgroup.h"
#include "tester/testregex.h"
#include "layer/qmlif.h"
//#include "layer/pythonif.h"
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

//    testvirtual x;
//    x.begintest();


    testgroup xyz;
    xyz.begintest();

//    qmlRegisterType<QMLif>("thjdb.QMLif",1,0,"QMLif");
//    QGuiApplication app(argc, argv);
//    QQmlApplicationEngine engine;
//    QPM_INIT(engine);
//    engine.load(QUrl(QStringLiteral("qrc:/qml/loading.qml")));
//    return app.exec();

//    string a = "create database student;\
//            use student;\
//            create table book (id int(10), name char(20));\
//            insert into book values (1, 'Good'), (2, 'Sth'), (3, 'Test');\
//            create table orders (id int(10), goods char(30), buyer char(10));\
//            insert into orders values (120, 'Soap','James'), (1, 'Laptop', 'John');\
//            select book.name, orders.buyer from book,orders where book.id = orders.id;";
//    open();
//    cout << execSQL(a) << endl;;
//    close();

//    testdate xx;
//    xx.begintest();

    testregex yza;
    yza.begintest();

    return 0;
}
