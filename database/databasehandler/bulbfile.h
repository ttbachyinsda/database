#ifndef BULBFILE_H
#define BULBFILE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
typedef char* BufType;
using namespace std;
#ifdef __linux
#define PARA O_RDWR
#elif __APPLE__
#define PARA O_RDWR
#else
#define PARA O_RDWR|O_BINARY
#endif
class BulbFile
{
public:
    BulbFile();
    BulbFile(string filename);
    int put(char* input,int size);
    int put(const char* input,int size);
    string get(int offset,int size);
    char* getc(int offset,int size);
    void setfilename(string filename,bool reconstruct = false);
    unsigned long get_file_size(const char *path);
    ~BulbFile();
private:
    string filename;
    int fm;
    int totalsize;
};

#endif // BULBFILE_H
