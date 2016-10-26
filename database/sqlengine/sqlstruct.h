#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H

#include <string>
#include <vector>

struct SQLType
{
    // Not using enumerate type for future efficiency considerations
    static const char *const INT;
    static const char *const CHAR;
    static const char *const VARCHAR;

    bool primaryType;
    bool canNull;
    int length;
    const char* type;
    std::string identifier;

    SQLType() {
        primaryType = false;
        type = SQLType::CHAR;
        canNull = true;
    }

    void dump() const;
};

struct SQLValue
{
    enum {
        ENUMERATE, STRING, NUL
    } type;

    std::string content;

    SQLValue() {
        type = SQLValue::STRING;
    }

    void dump() const;
};

typedef std::vector<SQLValue*> SQLValueGroup;

enum SQLOperand
{
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL
};

struct SQLSelector
{
    std::string databaseName;
    std::string tableName;

    bool hasPrefix() const { return databaseName.size() != 0; }

    void dump() const;
};

struct SQLSelectorGroup
{
    bool allMatched;
    std::vector<SQLSelector*> selectors;

    SQLSelectorGroup() { allMatched = true; }
    ~SQLSelectorGroup() {
        for (SQLSelector* it : selectors) {
            delete it;
        }
        selectors.clear();
    }

    void dump() const;
};

struct SQLCondition
{
    SQLOperand operand;

    enum {
        VALUE, COLUMN
    } type;

    SQLSelector lValue;
    SQLSelector rValueColumn;
    SQLValue rValue;

    void dump() const;
};

typedef std::vector<SQLCondition*> SQLConditionGroup;

struct SQLSet
{
    std::string identifier;
    SQLValue value;

    void dump() const;
};

typedef std::vector<SQLSet*> SQLSetGroup;
typedef std::vector<std::string> SQLTableGroup;

#endif // SQLSTRUCT_H
