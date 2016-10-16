#ifndef DATABASECHAR_H
#define DATABASECHAR_H
#include "databasetype.h"
#include <cstring>
#include <bitset>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define MAX_CHAR_SIZE 255
class DatabaseChar : public DataBaseType
{
public:
    DatabaseChar(int size);
    DatabaseChar(string input);
    DatabaseChar(char* input,int size);
    bool checkRight(string input);
    bool checkRightAndChange(string input);
    bool checkRight(char* input,int size);
    bool checkRightAndChange(char* input,int size);
    int getSize();
    string getType();
    string output();
    ~DatabaseChar();
private:
    void change(string input);
    void change(char* input,int size);
};

#endif // DATABASECHAR_H
