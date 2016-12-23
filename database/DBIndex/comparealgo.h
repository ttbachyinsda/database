#ifndef COMPAREALGO_H
#define COMPAREALGO_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <assert.h>
using namespace std;
using namespace std::chrono;
class CompareAlgo
{
public:
    virtual int strcmp(char* s1,int l1,char* s2,int l2) = 0;
};
class CompareINTE: public CompareAlgo
{
public:
    int strcmp(char* s1,int l1,char* s2,int l2);
};
class CompareCHAR: public CompareAlgo
{
public:
    int strcmp(char* s1,int l1,char* s2,int l2);
};
class CompareLINT: public CompareAlgo
{
public:
    int strcmp(char* s1,int l1,char* s2,int l2);
};
class CompareREAL: public CompareAlgo
{
public:
    int strcmp(char* s1,int l1,char* s2,int l2);
};
class CompareVARC: public CompareAlgo
{
public:
    int strcmp(char* s1,int l1,char* s2,int l2);
};
class CompareDATE: public CompareAlgo
{
public:
    int strcmp(char* s1,int l1,char* s2,int l2);
};




#endif // COMPAREALGO_H
