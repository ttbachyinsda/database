#ifndef DATABASEINT_H
#define DATABASEINT_H
#include "type.h"
#include <bitset>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define MAX_INT_SIZE 255
class DatabaseInt : public type
{
public:
    DatabaseInt(int size);
    DatabaseInt(string input);
    bool checkRight(string input);
    bool checkRightAndChange(string input);
    int getSize();
    string getType();
private:
    void change(string input);
};

#endif // DATABASEINT_H
