#ifndef DATABASETEXT_H
#define DATABASETEXT_H

#include "../databasehandler/bulbfile.h"
#include "databasetype.h"
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define MAX_CHAR_SIZE 255
class DatabaseText : public DataBaseType {
public:
    DatabaseText();
    DatabaseText(bool cannull);
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
    ~DatabaseText();

private:
    void change(string input);
    void change(char* input, int size);
    void changetoNull();
    int nowoffset;
};

#endif // DATABASETEXT_H
