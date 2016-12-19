#include "querycondition.h"
#include <cstring>
#include <regex>

bool QueryCondition::match(SQLOperand op, char type, const std::string &left,
                           bool leftIsNull, const std::string &right,
                           bool rightIsNull) {
    // type == 'I', 'C', 'V';
    if (leftIsNull != rightIsNull) return false;
    if (leftIsNull) return true;
    // both is not null.
    int cmpResult = 0;
    if (op != SQLOperand::LIKE) {
        if (type == 'I') cmpResult = matchInteger(left, right);
        else cmpResult = matchString(left, right);
    } else {
        std::regex r(right);
        if (std::regex_match(left, r))
            cmpResult = 1;
    }

    switch (op) {
        case SQLOperand::EQUAL:
            return cmpResult == 0;
        case SQLOperand::NOT_EQUAL:
            return cmpResult != 0;
        case SQLOperand::LESS:
            return cmpResult < 0;
        case SQLOperand::LESS_EQUAL:
            return cmpResult <= 0;
        case SQLOperand::GREATER:
            return cmpResult > 0;
        case SQLOperand::GREATER_EQUAL:
            return cmpResult >= 0;
        case SQLOperand::LIKE:
            return cmpResult != 0;
    }
    return false;
}

int QueryCondition::matchInteger(const std::string &left, const std::string &right) {
    if (left.size() < right.size())
        return matchIntegerCond(left.c_str(), (int) left.size(),
                                right.c_str(), (int) right.size());
    else
        return - matchIntegerCond(right.c_str(), (int) right.size(),
                                  left.c_str(), (int) left.size());
}

int QueryCondition::matchIntegerCond(const char *s, int ls, const char *l, int ll) {
    int margin = ll - ls;
    for (int i = 0; i < margin; ++ i)
        if (l[i] != '0') return -1;
    for (int i = 0; i < ls; ++ i) {
        if (s[i] > l[i + margin]) return 1;
        if (s[i] < l[i + margin]) return -1;
    }
    return 0;
}

int QueryCondition::matchString(const std::string &left, const std::string &right) {
    return strcmp(left.c_str(), right.c_str());
}

bool QueryCondition::typeComparable(char t1, char t2) {
    // Defines what can be compared.
    // 1. Varchar and Char can be compared anyway.
    // 2. Int and Int can compare.
    // 3. Real and Real can compare.
    return (t1 == 'V' && t2 == 'C') || (t1 == 'C' && t2 == 'V') ||
           (t1 == 'I' && t2 == 'I');
}

bool QueryCondition::typeComparable(SQLValue::LiteralType literal, char type) {
    if (type == 'I' && literal == SQLValue::LiteralType::ENUMERATE)
        return true;
    if ((type == 'V' || type == 'C') && literal == SQLValue::LiteralType::STRING)
        return true;
    // Insert or where clause (NULL is always acceptable)
    // But NULL is not comparable (< > <= >= ...)
    return (literal == SQLValue::LiteralType::NUL);
}

bool QueryCondition::indexOperatable(SQLOperand operand) {
    return (operand != SQLOperand::LIKE && operand != SQLOperand::NOT_EQUAL);
}

SQLOperand QueryCondition::getInverseOperand(SQLOperand operand) {
    if (operand == LESS_EQUAL) return GREATER_EQUAL;
    if (operand == LESS) return GREATER;
    if (operand == GREATER) return LESS;
    if (operand == GREATER_EQUAL) return LESS_EQUAL;
    return operand;
}
