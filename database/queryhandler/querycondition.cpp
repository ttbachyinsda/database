#include "querycondition.h"
#include <cstring>


bool QueryCondition::compare(const std::string &left,
                             bool leftIsNull,
                             const std::string &right,
                             bool rightIsNull)
{
    // type == 'I', 'C', 'V';
    if (leftIsNull != rightIsNull) return false;
    if (leftIsNull) return true;
    // both is not null.
    int cmpResult = 0;
    if (lValueType == 'I') cmpResult = integerCompare(left, right);
    else cmpResult = stringCompare(left, right);

    switch (operand) {
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
    }
    return false;
}

int QueryCondition::stringCompare(const std::string &left,
                                   const std::string &right) const
{
    return strcmp(left.c_str(), right.c_str());
}

int QueryCondition::integerCompare(const std::string &left,
                                    const std::string &right) const
{
    if (left.size() < right.size())
        return integerConditionCompare(left.c_str(), left.size(), right.c_str(), right.size());
    else
        return - integerConditionCompare(right.c_str(), right.size(), left.c_str(), left.size());
}

int QueryCondition::integerConditionCompare(const char *s, int ls,
                                            const char *l, int ll) const
{
    int margin = ll - ls;
    for (int i = 0; i < margin; ++ i)
        if (l[i] != '0') return -1;
    for (int i = 0; i < ls; ++ i) {
        if (s[i] > l[i + margin]) return 1;
        if (s[i] < l[i + margin]) return -1;
    }
    return 0;
}
