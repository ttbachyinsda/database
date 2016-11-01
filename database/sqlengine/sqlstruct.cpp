#include "sqlstruct.h"
#include <cstring>
#include <iostream>

const char *const SQLType::INT = "INT";
const char *const SQLType::CHAR = "CHAR";
const char *const SQLType::VARCHAR = "VARCHAR";

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

void SQLResult::dumpToConsole()
{
    for (std::string& t : title) {
        std::cout << t << "\t";
    }
    std::cout << "\n";
    for (std::vector<std::string>& r : data) {
        for (std::string& t : r) {
            std::cout << t << "\t";
        }
        std::cout << "\n";
    }
}
