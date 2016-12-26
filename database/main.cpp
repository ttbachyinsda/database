#include "databasehandler/bulbfile.h"
#include "layer/qmlif.h"
#include "tester/testbulbfile.h"
#include "tester/testdatabase.h"
#include "tester/testdate.h"
#include "tester/testflexible.h"
#include "tester/testgroup.h"
#include "tester/testhashflexible.h"
#include "tester/testiterator.h"
#include "tester/testmd5.h"
#include "tester/testregex.h"
#include "tester/testsql.h"
#include "tester/testtype.h"
#include "tester/testvirtual.h"
#include "tester/testaes.h"
#include <iostream>
//#include "layer/pythonif.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlProperty>

#include <sqlengine/sqldriver.h>
using namespace std;

int BulbFile::fm = -1;
int BulbFile::totalsize = 0;

int main(int argc, char* argv[])
{
//    TestSQL t;
//    t.workingDir = "/home/jameshuang/Study/database/database_wd";
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/create.sql");
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/customer.sql");
//    string sql = "use orderDB;\n";
//printf("current working directory: %s\n", getcwd(NULL, NULL));
//    sql += "delete from customer where gender='F';\n";
//    sql += "select * from customer where gender='F';\n";
//    sql += "select * from customer where id>0;\n";

//    sql += "create index orders(customer_id);create index customer(id);";
//    sql += "SELECT customer.name,orders.quantity FROM customer,orders WHERE orders.customer_id=customer.id;";

//    sql += "insert into temp values ('James', 21, 'M'), ('Bob', 30, 'F'), ('Bob2', 30, 'M'), ('Alice', 40, 'M'), ('Tom', 25, 'F');\n";
//    sql += "insert into temp2 values (21, 'JM'), (40, 'AM'), (30, 'BF'), (30, 'BN'), (78, 'New');\n";

//    sql += "select temp.name, temp.id, temp2.id, temp2.tag from temp, temp2 where temp.id=temp2.id;\n";

//    sql += "insert into temp values ('James', 20, 'M');\n";
//    sql += "insert into temp values ('Bob', 30, 'M');\n";

    //    sql += " select customer_id, quantity from orders where customer_id=304403;";
//    sql += "SELECT customer_id,SUM(quantity) FROM orders GROUP BY customer_id;";
//    sql += "SELECT book.title,book.id,orders.book_id,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;";
//    sql += "SELECT orders.quantity, orders.customer_id, customer.name, customer.id FROM orders, customer WHERE orders.customer_id = customer.id AND orders.quantity > 8;";
//    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/3_val.txt");

//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/create.sql");
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/orders.sql");
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/book.sql");
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/publisher.sql");
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/customer.sql");

//    t.startTestInteractive();
//    BulbFile::setfilename("bulbfile.txt", true);
    //don't let this always be true, That's true only because we are testing.


    //    TestSQL t;
    //    t.startTestFile("a.sql");
    //    t.startTestInteractive();

//    testtype t;
//    t.begintest(false);
//    testdatabase v;
//    v.begintest();


    //    testiterator w;
    //    w.begintest();

    //    testvirtual x;
    //    x.begintest();

    BulbFile::setfilename("bulbfile.txt", true);
    //don't let this always be true, That's true only because we are testing.

        testgroup xyz;
        xyz.begintest();

//    qmlRegisterType<QMLif>("thjdb.QMLif",1,0,"QMLif");
//    QGuiApplication app(argc, argv);
//    QQmlApplicationEngine engine;
//    QPM_INIT(engine);
//    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

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
