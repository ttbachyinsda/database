#ifndef TESTSQL_H
#define TESTSQL_H

#include <string>

class TestSQL
{
public:
    TestSQL();
    void startTestFile(const char*);
    void startTestString(const std::string& str);
    void startTestInteractive();
};

#endif // TESTSQL_H
