#ifndef QUERYCONDITION_H
#define QUERYCONDITION_H

#include "../sqlengine/sqlstruct.h"

struct SelectorPair
{
    int tableIndex;
    int columnIndex;
};

struct ConditionPair
{
    SQLOperand operand;

    // left Value
    SelectorPair left;

    // right Value
    bool rightIsValue;
    SelectorPair right;
    SQLValue rightValue;
};

struct QueryCondition {
    static bool match(SQLOperand op, char type,
                      const std::string& left, bool leftIsNull,
                      const std::string& right, bool rightIsNull);
    static bool typeComparable(char t1, char t2);
    static bool typeComparable(SQLValue::LiteralType literal, char type);
    static bool indexOperatable(SQLOperand operand);
    static SQLOperand getInverseOperand(SQLOperand operand);
private:
    static int matchString(const std::string& left, const std::string& right) const;
    static int matchInteger(const std::string& left, const std::string& right) const;
    static int matchIntegerCond(const char* s, int ls,
                                const char* l, int ll) const;
};


#endif // QUERYCONDITION_H
