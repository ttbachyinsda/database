#ifndef UIC_H
#define UIC_H

#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "typehandler/databasetype.h"

class UIC
{
public:
    UIC();
    static bool equal(char* s1,char* s2,int len);
    static bool equal(char* s1,const char* s2,int len);
    static bool equal(const char* s1,char* s2,int len);
    static void convert(DataBaseType* t1, char* s1);
    static DataBaseType* reconvert(char *s1,int size);
    static int chartoint(char* s1);             //length = 4
    static void inttochar(int i1,char* s1);     //length = 4
};

#endif // UIC_H
