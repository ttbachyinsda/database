#ifndef UIC_H
#define UIC_H

#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "typehandler/type.h"

class UIC
{
public:
    UIC();
    static bool equal(char* s1,char* s2,int len);
    static bool equal(char* s1,const char* s2,int len);
    static bool equal(const char* s1,char* s2,int len);
    static void convert(type* t1, char* s1);
    static type* reconvert(char *s1,int size);
};

#endif // UIC_H
