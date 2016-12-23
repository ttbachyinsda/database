#ifndef TESTSQL_H
#define TESTSQL_H

#include <string>

class TestSQL
{
public:
    std::string workingDir;
    TestSQL();
    void startTestFile(const char*);
    void startTestString(const std::string& str, const std::string& filename);
    void startTestInteractive();
};

#endif // TESTSQL_H
