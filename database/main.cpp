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

#include "layer/json.hpp"
using json = nlohmann::json;
using namespace std;

int BulbFile::fm = -1;
int BulbFile::totalsize = 0;

int main(int argc, char* argv[])
{
//    TestSQL t;
//    t.workingDir = "/home/jameshuang/Study/database/database_wd";
//
//    string sql = "use orderDB;\n";
//    TestSQL t;
//    t.workingDir = "/home/jameshuang/Study/database/database_wd";
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/create.sql");
//    t.startTestFile("/home/jameshuang/Study/database/database_wd/sqls/customer.sql");
//    string sql = "use orderDB;\n";
//    sql += "update customer set gender='F', name='Great' where gender='M';\n";
//    sql += "select * from customer;\n";
//    string sql = "use orderDB;\n";
//printf("current working directory: %s\n", getcwd(NULL, NULL));
//    sql += "delete from customer where gender='F';\n";
//    sql += "select * from customer where gender='F';\n";
//    sql += "select SUM(id) from customer where id = 307000;\n";
//    sql += "drop table b; drop table a;\n";
//    sql += "create table a (id int(3), primary key(id), name varchar(4));\n";
//    sql += "create table b (bid int(4), primary key(bid), aid int(3) foreign key references a(id));";
//    sql += "insert into a values (1, 'Jame');\n";
//    sql += "insert into a values (2, 'Bob');\n";
//    sql += "insert into b values (0001, 2);\n";

//sql += "insert into a values (1997-03-08, 'James', 3);\n";
//    sql += "select * from book;\n";
//    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/3_val.txt");
//
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

//    SQLResult res(1);
//    res.addTitleField("name");
//    for (int i = 0; i < 100; ++ i) {
//        res.addNew();
//        res.setData(0, "123123");
//    }
//    json j, k;
//    j["result"] = true;
//    k = json::parse(j.dump());
//    cout << k.dump() << endl;
    
    
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

//        testgroup xyz;
//        xyz.begintest();

//    qmlRegisterType<QMLif>("thjdb.QMLif",1,0,"QMLif");
//    QGuiApplication app(argc, argv);
//    QQmlApplicationEngine engine;
//    QPM_INIT(engine);
//    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
//
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

//        testmd5 zab;
//        zab.begintest();

    testhashflexible ace;
    ace.begintest();

    //    testbulbfile ceo;
    //    ceo.begintest();

    return 0;
}
