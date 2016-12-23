#include "testsql.h"
#include "../sqlengine/sqldriver.h"
#include "../sqlengine/sqlstruct.h"
#include <fstream>
#include <iostream>
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
        sqlDriver.execute(input);
        if (sqlDriver.getLastSucceeded() == false) {
            cout << "\033[31m ERROR: \033[0m" << sqlDriver.getErrorMessages()[0] << endl;
        } else {
            if (sqlDriver.getWarningMessages().size() != 0)
                cout << "\033[33m WARNING: \033[0m" << sqlDriver.getWarningMessages()[0] << endl;
            else
                cout << "Succeeded!" << endl;
            if (sqlDriver.hasResult())
                sqlDriver.getResult()->dumpToConsole();
        }
    }
}

void TestSQL::startTestFile(const char* filename)
{
    cout << "Now Start SQL Test..." << endl;
    ifstream in(filename, ios::in);
    istreambuf_iterator<char> beg(in), end;
    string data(beg, end);
    in.close();
    SQLDriver sqlDriver(workingDir);
    sqlDriver.execute(data);
    if (sqlDriver.getLastSucceeded() == false) {
        cout << "\033[31m ERROR: \033[0m" << sqlDriver.getErrorMessages()[0] << endl;
    } else {
        if (sqlDriver.getWarningMessages().size() != 0)
            cout << "\033[33m WARNING: \033[0m" << sqlDriver.getWarningMessages()[0] << endl;
        else
            cout << "Succeeded!" << endl;
        if (sqlDriver.hasResult())
            sqlDriver.getResult()->dumpToConsole();
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
