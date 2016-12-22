#ifndef BULBFILE_H
#define BULBFILE_H

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
class BulbFile {
public:
    static int put(char* input, int size);
    static int put(const char* input, int size);
    static string get(int offset, int size);
    static char* getc(int offset, int size);
    static void setfilename(string filename, bool reconstruct = false);
    static unsigned long get_file_size(const char* path);

private:
    static string filename;
    static int fm;
    static int totalsize;
};

#endif // BULBFILE_H
