#ifndef QUERYCONDITION_H
#define QUERYCONDITION_H

#include "../sqlengine/sqlstruct.h"

struct SelectorPair
{
    int tableIndex;
    int columnIndex;
};

struct ObseleteCondition
{
    SQLOperand operand;
    char lValueType;

    // left Value
    SelectorPair left;

    // right Value
    bool rightIsValue;
    SelectorPair right;
    SQLValue rightValue;

    bool compare(const std::string& left, bool leftIsNull,
                 const std::string& right, bool rightIsNull);
    int stringCompare(const std::string& left, const std::string& right) const;
    int integerCompare(const std::string& left, const std::string& right) const;
private:
    int integerConditionCompare(const char* s, int ls,
                                const char* l, int ll) const;
};

struct QueryCondition {
    static bool match(SQLOperand op, char type,
                      const std::string& left, bool leftIsNull,
                      const std::string& right, bool rightIsNull);
private:
    static int matchString(const std::string& left, const std::string& right) const;
    static int matchInteger(const std::string& left, const std::string& right) const;
    static int matchIntegerCond(const char* s, int ls,
                                const char* l, int ll) const;
};


#endif // QUERYCONDITION_H
