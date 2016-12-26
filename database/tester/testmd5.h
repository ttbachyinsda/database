#ifndef TESTMD5_H
#define TESTMD5_H
#include "../managementhandler/md5.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <gmp.h>
#include <gmpxx.h>
#include <mpfr.h>
#include <mpf2mpfr.h>
#include "../groupalgorithm/mpreal.h"
#include <sstream>
#include <iostream>
using mpfr::mpreal;
using namespace std;

class testmd5 {
public:
    testmd5();
    void begintest();
};

#endif // TESTMD5_H
