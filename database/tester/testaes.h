#ifndef TESTAES_H
#define TESTAES_H

#include <iostream>
#include "../aesalgorithm/aes.h"
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
#ifdef __linux
#define PARA O_RDWR
#elif __APPLE__
#define PARA O_RDWR
#else
#define PARA O_RDWR | O_BINARY
#endif
class testaes
{
public:
    testaes();
    void begintest();
    void encryptafile(string filepath,string password);
    void decryptafile(string filepath,string password);
    unsigned long get_file_size(const char* path);
};

#endif // TESTAES_H
