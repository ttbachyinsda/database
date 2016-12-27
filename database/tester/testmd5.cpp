#include "testmd5.h"

testmd5::testmd5()
{
}
void testmd5::begintest()
{
//    long long k = 135812556;
//    char s[8];
//    memcpy(s, &k, 8);

//    long long temp;
//    memcpy(&temp, s, 8);
//    cout << temp << endl;

//    string ss(s, 8);
//    string md5string = MD5(ss).toStr();
//    cout << md5string << endl;

//    mpz_class thisint;
//    thisint.set_str(md5string.c_str(), 16);

//    thisint = thisint % 1024;
//    int comk = thisint.get_si();
//    cout << comk << endl;
    int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));
    mpreal a;
    a = "123456789123456789.123456789123456789";
    mpreal b = "12345678";
    stringstream sstream;
    sstream.precision(digits);
    sstream<<a+b;
    cout<<sstream.str()<<endl;
}
