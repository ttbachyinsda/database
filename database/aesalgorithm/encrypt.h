#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <iostream>
#include "aes.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "../managementhandler/md5.h"
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
typedef char* BufType;
using namespace std;
#ifndef PARA
#ifdef __linux
#define PARA O_RDWR
#elif __APPLE__
#define PARA O_RDWR
#else
#define PARA O_RDWR|O_BINARY
#endif
#endif
#define __iv__str "Iamattbachyinsda"
class Encrypt
{
public:
    static void encryptafile(string filepath,string password);
    static void decryptafile(string filepath,string password);
    static void destroyafile(string filepath);
    static BYTE* trytodecrypt(string filepath,string password);
    static unsigned long get_file_size(const char* path);
    static string trytoencryptastr(string str,string password);
    static string trytodecryptastr(string str,string password);
};

#endif // ENCRYPT_H
