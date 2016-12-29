#include "databasehandler/bulbfile.h"
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
#include "layer/qmlif.h"
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sqlengine/sqldriver.h>

#include "layer/json.hpp"
using json = nlohmann::json;
using namespace std;


#define SQL_DEBUG

int main(int argc, char* argv[])
{
    TestSQL t;
    t.workingDir = ".";

#ifndef SQL_DEBUG
    if (argc == 1) {
        cout << "Here the UI starts..." << endl;
        qmlRegisterType<QMLif>("thjdb.QMLif",1,0,"QMLif");
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;
        QPM_INIT(engine);
        engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
        return app.exec();
    }

    if (argc == 2) {
        if (argv[1][0] == 'c' && argv[1][1] == 'm' && argv[1][2] == 'd') {
            t.startTestInteractive();
            return 0;
        } else {
            cout << "parameter 2 should be cmd." << endl;
            return 0;
        }
    }

    if (argc == 3) {
        t.startTestFile(argv[1], argv[2]);
    }

    return 0;

#else
//    string sql = "use orderDB;\n";
//    sql += "UPDATE book SET title='Nine Times Nine' WHERE authors='Anthony Boucher';\n";
//    sql += "select * from book;\n";
    string sql;
    sql = "create database test;use test; select * from uesr;";
    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/1_val.txt");
//    sql = "use test;";
//    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/1_val.txt");
//    sql = "select * from user;";
//    t.startTestString(sql, "/home/jameshuang/Desktop/Cross Validation/1_val.txt");
//    t.startTestBlob();
    return 0;
#endif
}
