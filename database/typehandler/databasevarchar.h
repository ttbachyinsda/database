#ifndef DATABASEVARCHAR_H
#define DATABASEVARCHAR_H
#include "databasetype.h"
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define MAX_CHAR_SIZE 255
class DatabaseVarchar : public DataBaseType {
public:
    DatabaseVarchar(int size);
    DatabaseVarchar(int size, bool cannull);
    /*
    DatabaseVarchar(string input,int maxsize);
    DatabaseVarchar(string input, bool cannull,int maxsize);
    DatabaseVarchar(char* input, int size,int maxsize);
    DatabaseVarchar(char* input, int size, bool cannull,int maxsize);
    */
    bool read(char* input, int inputlen, int& position);
    bool write(char* output, int& position);
    bool checkRight(string input);
    bool checkRight(string input, bool inputisnull);
    bool checkRightAndChange(string input);
    bool checkRightAndChange(string input, bool inputisnull);
    bool checkRightc(char* input, int size);
    bool checkRightc(char* input, int size, bool inputisnull);
    bool checkRightAndChangec(char* input, int size);
    bool checkRightAndChangec(char* input, int size, bool inputisnull);
    bool analysisc(char* input, int inputsize);
    bool analysis(string input);
    int getSize();
    int getRealSize();
    int getMaxSize();
    string getType();
    string output();
    ~DatabaseVarchar();

private:
    void change(string input);
    void change(char* input, int size);
    void changetoNull();
    int maxsize;
};
#endif // DATABASEVARCHAR_H
