#ifndef DATABASEINT_H
#define DATABASEINT_H
#include "databasetype.h"
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define MAX_INT_SIZE 255
class DatabaseInt : public DataBaseType {
public:
    DatabaseInt(int size);
    DatabaseInt(string input);
    DatabaseInt(char* input, int size);
    bool checkRight(string input);
    bool checkRightAndChange(string input);
    bool checkRight(char* input, int size);
    bool checkRightAndChange(char* input, int size);
    int getSize();
    string getType();
    ~DatabaseInt();
    string output();

private:
    void change(string input);
    void change(char* input, int size);
};

#endif // DATABASEINT_H
