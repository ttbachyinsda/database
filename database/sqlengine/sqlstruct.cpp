#include "sqlstruct.h"
#include "../layer/json.hpp"
#include "../managementhandler/uic.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <chrono>
#include "../typehandler/chrono_io.h"
#include "../typehandler/date.h"

using namespace date;
using namespace std::chrono;

using json = nlohmann::json;
const char *const SQLType::INT = "INT";
const char *const SQLType::CHAR = "CHAR";
const char *const SQLType::VARCHAR = "VARCHAR";
const char *const SQLType::REAL = "REAL";
const char *const SQLType::DATE = "DATE";
const char *const SQLType::LINT = "LINT";
const char *const SQLType::BULB = "BULB";

void SQLType::dump() const
{
    std::cout << "- SQL Type -" << std::endl;
    if (primaryType) {
        std::cout << "Primary = " << primaryType << std::endl;
        std::cout << "Identifier = " << identifier << std::endl;
    }
    else {
        std::cout << "Identifier = " << identifier << std::endl;
        std::cout << "Length = " << length << std::endl;
        std::cout << "Type = " << type << std::endl;
        std::cout << "Null = " << canNull << std::endl;
    }
}

void SQLValue::dump() const
{
    std::cout << "SQLValue (Type = " << type << ", Content = "
              << content << ")" << std::endl;
}

void SQLValue::parseDate() {
    std::vector<std::string> splitRes = UIC::stringSplit(content, "-");
    int year = atoi(splitRes[0].c_str());
    int month = atoi(splitRes[1].c_str());
    int date = atoi(splitRes[2].c_str());
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> timestamp;
    timestamp = static_cast<date::sys_days>(date::year_month_day{ date::year{year} / month / date });
    if (splitRes.size() == 6) {
        int hour = atoi(splitRes[3].c_str());
        int minute = atoi(splitRes[4].c_str());
        int second = atoi(splitRes[5].c_str());
        auto smallTime = date::make_time(std::chrono::hours{hour},
                                         std::chrono::minutes{minute},
                                         std::chrono::seconds{second},
                                         std::chrono::nanoseconds{ 0 }, 0).to_duration();
        timestamp += smallTime;
    }
    content.clear();
    content.reserve(8);
    for (int i = 0; i < 8; ++ i)
        content.push_back(*((char*)(&timestamp) + i));
}

void SQLValue::parseReal()
{
    std::vector<std::string> splitRes = UIC::stringSplit(content, ".");
    int integerPart = atoi(splitRes[0].c_str());
    int decimalPart = atoi(splitRes[1].c_str());
    double targetValue = integerPart + (double) decimalPart / pow(10, splitRes[1].size());
    content.clear();
    content.reserve(8);
    for (int i = 0; i < 8; ++ i)
        content.push_back(*((char*)(&targetValue) + i));
}

void SQLValue::parseLong()
{
    long long targetValue = atoll(content.c_str());
    content.clear();
    content.reserve(8);
    for (int i = 0; i < 8; ++ i)
        content.push_back(*((char*)(&targetValue) + i));
}

void SQLCondition::dump() const
{
    std::cout << "- SQL Condition -" << std::endl;
    lValue.dump();
    std::cout << ' ' << operand << ' ';
    if (type == SQLCondition::VALUE)
        rValue.dump();
    else
        rValueColumn.dump();
}

void SQLSet::dump() const
{
    std::cout << "SQLSet: Let " << identifier << " = ";
    value.dump();
}

void SQLSelector::dump() const
{
    if (hasPrefix())
        std::cout << databaseName << "." << tableName;
    else
        std::cout << tableName;
}

void SQLSelectorGroup::dump() const
{
    if (allMatched)
        std::cout << "Everything!";
    else
    {
        for (SQLSelector* s : selectors) {
            s->dump();
            std::cout << ' ';
        }
    }
}

std::string SQLResult::toJSON()
{
    json res;
    for (std::vector<std::string>& r : data) {
        json now;
        for (std::string& t : r) {
            now.push_back(t);
        }
        res.push_back(now);
    }
    return res.dump();
}

void SQLResult::dumpToConsole()
{
    for (std::string& t : title) {
        std::cout << t << "\t";
    }
    std::cout << std::endl;
    for (std::vector<std::string>& r : data) {
        for (std::string& t : r) {
            std::cout << t << "\t";
        }
        std::cout << std::endl;
    }
}

void SQLResult::dumpToFile(const std::string &filename)
{
    std::ofstream fout(filename);
    if (!fout) return;
    for (std::vector<std::string>& r : data) {
        for (std::string& t : r) {
            fout << t << "\t";
        }
        fout << "\n";
    }
    fout.close();
}
