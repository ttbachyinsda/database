#include "testsql.h"
#include "../sqlengine/sqldriver.h"
#include "../sqlengine/sqlstruct.h"
#include <fstream>
#include <iostream>
#include <QTime>
using namespace std;

TestSQL::TestSQL()
{
    workingDir = "./";
}

void TestSQL::startTestInteractive()
{
    cout << "Graceful Database v1.1 SQL-Testing Interactive Interface" << endl;
    cout << "Copyright (c) 2016, Tsinghua University" << endl;
    cout << "Distributed under MIT License with NO WARRANTY." << endl;
    SQLDriver sqlDriver(workingDir);
    while (true) {
        cout << "\033[32mGSQL>\033[0m ";
        std::string input;
        getline(cin, input);
        if (input == "quit")
            break;
        QTime timer;
        timer.start();
        if (input.substr(0, 4) == "exec") {
            string filename = input.substr(5);
            ifstream in(filename, ios::in);
            istreambuf_iterator<char> beg(in), end;
            string data(beg, end);
            in.close();
            sqlDriver.execute(data);
        } else {
            sqlDriver.execute(input);
        }
        if (sqlDriver.getLastSucceeded() == false) {
            cout << "\033[31m ERROR: \033[0m" << sqlDriver.getErrorMessages()[0] << endl;
        } else {
            if (sqlDriver.hasResult())
                sqlDriver.getResult()->dumpToConsole();
            if (sqlDriver.getWarningMessages().size() != 0)
                cout << "\033[33m WARNING: \033[0m" << sqlDriver.getWarningMessages()[0] << endl;
            else
                cout << "OK." << endl;
            cout << "Affected Rows = " << sqlDriver.getLastAffectedRows() <<
                    ", time elapsed = " << timer.elapsed() / 1000.0 << endl;
        }
    }
}

void TestSQL::startTestBlob()
{
    SQLDriver sqlDriver(workingDir);
    sqlDriver.execute("drop database a;create database a;use a;drop table img;create table img (id int(4), image varbinary(), primary key(id));");
    checkPoint(&sqlDriver);
    sqlDriver.storeBinaryFile("img", "1", "104.jpg");
    checkPoint(&sqlDriver);
    sqlDriver.getBinaryFile("img", "1", "out.jpg");
    checkPoint(&sqlDriver);
    sqlDriver.execute("select * from img;\n");
    checkPoint(&sqlDriver);
    sqlDriver.execute("delete from img where id = 1;");
    checkPoint(&sqlDriver);
    sqlDriver.execute("select * from img;\n");
    checkPoint(&sqlDriver);

}

void TestSQL::checkPoint(SQLDriver *d)
{
    if (d->getLastSucceeded() == false) {
        cout << "\033[31m ERROR: \033[0m" << d->getErrorMessages()[0] << endl;
    } else {
        if (d->getWarningMessages().size() != 0)
            cout << "\033[33m WARNING: \033[0m" << d->getWarningMessages()[0] << endl;
        else
            cout << "Succeeded!" << endl;
        if (d->hasResult())
            d->getResult()->dumpToConsole();
    }
}

void TestSQL::startTestFile(const char* filename, const std::string& dump)
{
    cout << "Now Start SQL Test..." << endl;
    ifstream in(filename, ios::in);
    istreambuf_iterator<char> beg(in), end;
    string data(beg, end);
    in.close();
    SQLDriver sqlDriver(workingDir);
    sqlDriver.execute("use orderDB;" + data);
    if (sqlDriver.getLastSucceeded() == false) {
        cout << "\033[31m ERROR: \033[0m" << sqlDriver.getErrorMessages()[0] << endl;
    } else {
        if (sqlDriver.getWarningMessages().size() != 0)
            cout << "\033[33m WARNING: \033[0m" << sqlDriver.getWarningMessages()[0] << endl;
        else
            cout << "Succeeded!" << endl;
        if (sqlDriver.hasResult()) {
            sqlDriver.getResult()->dumpToFile(dump);
        }
    }
}

void TestSQL::startTestString(const std::string &str, const string &filename)
{
    cout << "Query:" << endl;
    cout << str << endl;
    cout << "========================" << endl;
    SQLDriver sqlDriver(workingDir);
    sqlDriver.execute(str);
    if (sqlDriver.getLastSucceeded() == false) {
        cout << "\033[31m ERROR: \033[0m" << sqlDriver.getErrorMessages()[0] << endl;
    } else {
        if (sqlDriver.getWarningMessages().size() != 0)
            cout << "\033[33m WARNING: \033[0m" << sqlDriver.getWarningMessages()[0] << endl;
        else
            cout << "Succeeded!" << endl;
        if (sqlDriver.hasResult()) {
            sqlDriver.getResult()->dumpToConsole();
            sqlDriver.getResult()->dumpToFile(filename);
        }
    }
}
