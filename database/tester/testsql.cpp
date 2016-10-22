#include "testsql.h"
#include "sqlengine/sqldriver.h"
#include <iostream>
using namespace std;

TestSQL::TestSQL()
{

}

void TestSQL::startTest()
{
    cout << "Now Start SQL Test..." << endl;
    SQLDriver sqlDriver;
//    sqlDriver.execute("SELECT * FROM tb WHERE row = 1");
    sqlDriver.execute("insert into mem values (30, NULL, 'OK!');Create table fuck (id int(10), ty char(30) not null, primary key(pkey));");
    cout << sqlDriver.getLastSucceeded() << endl;
    //cout << sqlDriver.getErrorMessages()[0] << endl;
}
