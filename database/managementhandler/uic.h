#ifndef UIC_H
#define UIC_H

#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "typehandler/databasetype.h"

typedef int FileIterator;
typedef char* BufType;
class UIC {
public:
    UIC();
    static bool equal(char* s1, char* s2, int len);
    static bool equal(char* s1, const char* s2, int len);
    static bool equal(const char* s1, char* s2, int len);
    static void convert(DataBaseType* t1, char* s1);
    static DataBaseType* reconvert(char* s1, int size);
    static DataBaseType* reconvert(string s1, int size);
    static int chartoint(char* s1); //length = 4
    static void inttochar(int i1, char* s1); //length = 4
    static void readchar(BufType b, FileIterator& iterator, char* dest, int size_t);
    static int readint(BufType b, FileIterator& iterator);
    static void writechar(BufType b, FileIterator& iterator, char* source, int size_t);
    static void writechar(BufType b, FileIterator& iterator, const char* source, int size_t);
    static void writecharandjump(BufType b, FileIterator& iterator, char* source, int size_t, int jumpsize);
    static void writecharandjump(BufType b, FileIterator& iterator, const char* source, int size_t, int jumpsize);
    static void writeint(BufType b, FileIterator& iterator, int source);
    static string readstring(BufType b, FileIterator& iterator, int size_t);
    static string readstringandjump(BufType b, FileIterator& iterator, int size_t, int jumpsize);
    static DataBaseType** copytype(DataBaseType** input, int inputlen);
};

#endif // UIC_H
