#include "comparealgo.h"

int CompareCHAR::strcmp(const char *s1, int l1, const char *s2, int l2)
{
    if (l1 < l2) return -1;
    if (l1 > l2) return 1;
    return strncmp(s1,s2,l1);
}
int CompareVARC::strcmp(const char *s1, int l1, const char *s2, int l2)
{
    if (l1 < l2) return -1;
    if (l1 > l2) return 1;
    return strncmp(s1,s2,l1);
}
int CompareINTE::strcmp(const char *s1, int l1, const char *s2, int l2)
{
    if (l1 < l2) return -1;
    if (l1 > l2) return 1;
    return strncmp(s1,s2,l1);
}
int CompareLINT::strcmp(const char *s1, int l1, const char *s2, int l2)
{
//    assert(l1 == 8);
//    assert(l2 == 8);
    if (l1 > l2) return 1;
    long long i1,i2;
    memcpy(&i1,s1,8);
    memcpy(&i2,s2,8);
    if (i1<i2) return -1;
    if (i1>i2) return 1;
    return 0;
}
int CompareREAL::strcmp(const char *s1, int l1, const char *s2, int l2)
{
    if (l1 > l2) return 1;
    double i1,i2;
    memcpy(&i1,s1,8);
    memcpy(&i2,s2,8);
    if (i1<i2) return -1;
    if (i1>i2) return 1;
    return 0;
}
int CompareDATE::strcmp(const char *s1, int l1, const char *s2, int l2)
{
    if (l1 > l2) return 1;
    time_point<system_clock,chrono::nanoseconds> i1,i2;
    memcpy(&i1,s1,8);
    memcpy(&i2,s2,8);
    if (i1<i2) return -1;
    if (i1>i2) return 1;
    return 0;
}
