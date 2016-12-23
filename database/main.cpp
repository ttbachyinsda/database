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

#include <sqlengine/sqldriver.h>
using namespace std;

int BulbFile::fm = -1;
int BulbFile::totalsize = 0;

int main(int argc, char* argv[])
{
    TestSQL t;
    t.workingDir = "/home/jameshuang/Study/database/database_wd";
    string sql = "use orderDB;\n";
    sql += "drop table temp;\n";
    sql += "CREATE TABLE temp (name varchar(20), id int(10) NOT NULL, gender char(1), primary key(id), check(gender in ('F', 'M')));\n";
//    sql += "create index orders(quantity);";
//    sql += "create index orders(customer_id);";
//    sql += "SELECT customer.name,book.title,orders.quantity FROM customer,book,orders WHERE orders.customer_id=customer.id AND orders.book_id=book.id AND orders.quantity > 2 AND orders.quantity <= 5;";

    sql += "insert into temp values ('James', 20, 'M'), ('Bob', 30, 'F'), ('Alice', 20, 'M');\n";

//    sql += "insert into temp values ('James', 20, 'M');\n";
//    sql += "insert into temp values ('Bob', 30, 'M');\n";

    //    sql += " select customer_id, quantity from orders where customer_id=304403;";
//    sql += "SELECT customer_id,SUM(quantity) FROM orders GROUP BY customer_id;";
//    sql += "SELECT book.title,book.id,orders.book_id,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;";
//    sql += "SELECT orders.quantity, orders.customer_id, customer.name, customer.id FROM orders, customer WHERE orders.customer_id = customer.id AND orders.quantity > 8;";
    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/3_val.txt");
/*
    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/create.sql");
    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/orders.sql");
    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/book.sql");
    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/publisher.sql");
    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/customer.sql");
*/
//    t.startTestInteractive();
/*

    BulbFile::setfilename("bulbfile.txt", true);
    //don't let this always be true, That's true only because we are testing.


    //    qmlRegisterType<QMLif>("thjdb.QMLif",1,0,"QMLif");
    //    QGuiApplication app(argc, argv);
    //    QQmlApplicationEngine engine;
    //    QPM_INIT(engine);
    //    engine.load(QUrl(QStringLiteral("qrc:/qml/loading.qml")));
    //    return app.exec();

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
*/
    return 0;
}
