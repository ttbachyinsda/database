#ifndef DATABASETYPE_H
#define DATABASETYPE_H
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;
#define IS_NULL 1
#define IS_NOT_NULL 0
class DataBaseType {
public:
    DataBaseType();
    char* getdata();
    void printdata(string testinfo);
    bool getNullable();
    bool getisNull();
    char* getcondition();
    int getconditionsize();
    bool readcondition(char* input, int inputsize, int& position);
    bool readcondition(string* input);
    bool writecondition(char* input, int& position);
    void initialize(DataBaseType* input);
    int stringtoint(string text);
    virtual bool read(char* input, int inputlen, int& position) = 0;
    virtual bool write(char* output, int& position) = 0;
    virtual bool checkRight(string input) = 0;
    virtual bool checkRight(string input, bool inputisnull) = 0;
    virtual bool checkRightAndChange(string input) = 0;
    virtual bool checkRightAndChange(string input, bool inputisnull) = 0;
    virtual bool checkRightc(char* input, int size) = 0;
    virtual bool checkRightc(char* input, int size, bool inputisnull) = 0;
    virtual bool checkRightAndChangec(char* input, int size) = 0;
    virtual bool checkRightAndChangec(char* input, int size, bool inputisnull) = 0;
    virtual int getSize() = 0;
    virtual int getRealSize() = 0;
    virtual int getMaxSize() = 0;
    virtual string getType() = 0;
    virtual ~DataBaseType();
    virtual string output() = 0;
    virtual bool analysisc(char* input, int inputsize) = 0;
    virtual bool analysis(string input) = 0;
    void NullCondition();

protected:
    int size;
    char* data;
    bool Nullable;
    bool isNull;
    char* condition;
    int conditionsize;
    int compare(char* source, int sourcelength, char* dest, int destlength);
    int chartoint(char* s1);
};

#endif // DATABASETYPE_H
