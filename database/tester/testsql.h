#ifndef TESTSQL_H
#define TESTSQL_H

#include <string>
class SQLDriver;

class TestSQL
{
public:
    std::string workingDir;
    TestSQL();
    void startTestFile(const char*, const std::string& dump);
    void startTestString(const std::string& str, const std::string& filename);
    void startTestInteractive();
    void startTestBlob();
    void checkPoint(SQLDriver* d);
};

#endif // TESTSQL_H
