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
    sqlDriver.execute("INSERT INTO customer VALUES (300001, 'CHAD CABELLO', 'F');DELETE FROM publisher WHERE state='CA';UPDATE book SET title='Nine Times Nine' WHERE authors='Anthony Boucher';SELECT * FROM publisher WHERE nation='CA';SELECT title FROM book WHERE authors is null;SELECT book.title,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;");
//    sqlDriver.execute("delete from charis;");
    cout << sqlDriver.getLastSucceeded() << endl;
    //cout << sqlDriver.getErrorMessages()[0] << endl;
}
