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
#include "tester/testmd5.h"
#include "tester/testhashflexible.h"
#include "tester/testbulbfile.h"
#include "layer/qmlif.h"

//#include "layer/pythonif.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
using namespace std;

int main(int argc, char* argv[])
{

    TestSQL t;
    string sql = "use orderDB;";
    sql += "create index orders(quantity);";
    sql += "SELECT book.title,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;";


    //    sql += " select customer_id, quantity from orders where customer_id=304403;";
//    sql += "SELECT customer_id,SUM(quantity) FROM orders GROUP BY customer_id;";
//    sql += "SELECT book.title,book.id,orders.book_id,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;";
//    sql += "SELECT orders.quantity, orders.customer_id, customer.name, customer.id FROM orders, customer WHERE orders.customer_id = customer.id AND orders.quantity > 8;";
    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/1_val.txt");

//    t.startTestFile("book.sql");
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


//    testgroup xyz;
//    xyz.begintest();

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

//    testregex yza;
//    yza.begintest();

//    testmd5 zab;
//    zab.begintest();

//    testhashflexible ace;
//    ace.begintest();

//    testbulbfile ceo;
//    ceo.begintest();

    return 0;
}
