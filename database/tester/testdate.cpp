#include "testdate.h"

testdate::testdate()
{
}
void testdate::beginpretest()
{
//    auto s = system_clock::now();
//
//    auto nowt = s;
//    auto dp = floor<days>(nowt);
//    std::cout << dp << '\n';
//    auto ymd = year_month_day{ dp };
//    std::cout << ymd << '\n';
//    auto time = make_time(nowt - dp);
//    std::cout << time << '\n';
//
//    int y = 2015;
//    auto ymd2 = year_month_day{ year{ y } / 6 / 8 };
//    std::cout << ymd2 << '\n';
//
//    auto time2 = make_time(hours{ 5 }, minutes{ 7 }, seconds{ 9 }, nanoseconds{ 22 }, 0);
//    std::cout << time2 << '\n';
//
//    auto cha = time2.to_duration() - time.to_duration();
//
//    std::cout << cha << '\n';
//    if (cha < cha.zero()) {
//        std::cout << "time2<time1" << std::endl;
//    } else {
//        std::cout << "time1<time2" << std::endl;
//    }
//    std::cout << cha << '\n';
//
//    bool yes = ymd2 < ymd;
//    std::cout << yes << '\n';
//
//    sys_days symd2 = ymd2;
//    sys_days symd = ymd;
//    auto q = (symd2 - symd);
//
//    cha += q;
//
//    std::cout << cha << '\n';
//
//    auto nowt1 = nowt + cha;
//
//    std::cout << nowt1 << '\n';
//
//    auto nowt2 = time2.to_duration() + symd2;
//
//    auto sst = s;
//    sst = nowt2;
//
//    std::cout << nowt2 << '\n';
//
//    std::cout << nowt2 - nowt << '\n';
//
//    auto totalcha = nowt2 - nowt;
//
//    //totalcha=totalcha.zero();
//    //totalcha=-totalcha;
//    std::cout << (totalcha < totalcha.zero()) << std::endl;
//    std::cout << (totalcha == totalcha.zero()) << std::endl;
//    std::cout << (totalcha > totalcha.zero()) << std::endl;
//
//    std::cout << "size = " << sizeof(sst) << '\n';
}

void testdate::begintest()
{
    auto datetype = UIC::reconvert("Date", 8, true);

    auto thisdate = system_clock::now();

    cout << "now date = " << thisdate << endl;

    char s[8];
    memcpy(s, &thisdate, 8);

    datetype->checkRightAndChangec(s, 8, false);

    char dest[8];
    memcpy(dest, datetype->getdata(), 8);
    time_point<system_clock, chrono::nanoseconds> destdate;
    memcpy(&destdate, dest, 8);

    std::cout << (destdate == thisdate) << std::endl;

    time_point<system_clock, chrono::nanoseconds> temp1 = static_cast<sys_days>(year_month_day{ year{ 2013 } / 6 / 8 }) + make_time(hours{ 5 }, minutes{ 7 }, seconds{ 9 }, nanoseconds{ 22 }, 0).to_duration();

    cout << temp1 << endl;

    time_point<system_clock, chrono::nanoseconds> temp2 = static_cast<sys_days>(year_month_day{ year{ 2018 } / 6 / 8 }) + make_time(hours{ 5 }, minutes{ 7 }, seconds{ 9 }, nanoseconds{ 22 }, 0).to_duration();

    cout << temp2 << endl;

    char s1[8], s2[8];
    memcpy(s1, &temp1, 8);
    memcpy(s2, &temp2, 8);
    string ss1(s1, 8), ss2(s2, 8);
    string rs[3];
    rs[0] = "FRTO";
    rs[1] = ss1;
    rs[2] = ss2;
    datetype->readcondition(rs);

    cout << datetype->checkRight(ss1) << endl;
    cout << datetype->checkRight(ss2) << endl;
    cout << datetype->checkRightc(s, 8) << endl;
}
