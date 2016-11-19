#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H

#include <string>
#include <vector>
#include <list>

struct SQLValue
{
    enum {
        ENUMERATE, STRING, NUL
    } type;

    std::string content;

    SQLValue() {
        type = SQLValue::STRING;
    }

    bool typeFitChar(char c) {
        if (c == 'I' && type == ENUMERATE)
            return true;
        if ((c == 'V' || c == 'C') && type == STRING)
            return true;
        // Insert or where clause (NULL is always acceptable)
        // But NULL is not comparable (< > <= >= ...)
        return (type == NUL);
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

struct SQLCheck
{
    bool isChoice;
    SQLValueGroup* choiceList;
    SQLOperand operand;
    SQLValue value;
};
typedef std::vector<SQLCheck*> SQLCheckGroup;

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

    bool isCheck;
    SQLCheckGroup* checkGroup;

    SQLType() {
        isCheck = false;
        checkGroup = NULL;
        primaryType = false;
        type = SQLType::CHAR;
        canNull = true;
    }

    ~SQLType() {
        if (isCheck && checkGroup) {
            for (SQLCheck* c : *checkGroup)
                delete c;
            delete checkGroup;
        }
    }

    void dump() const;
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

class SQLResult
{
    const int columns;
    std::list<std::string> title;
    std::list<std::vector<std::string> > data;
public:
    SQLResult(int col) : columns(col) {}
    ~SQLResult() {}

    void addNew() {
        data.push_back(std::vector<std::string>(columns));
    }

    void setData(int idx, const std::string& str) {
        if (idx >= columns) return;
        if (data.size() == 0) return;
        data.back().at(idx) = str;
    }
    void addTitleField(const std::string& str) {
        title.push_back(str);
    }

    std::string toJSON();

    void dumpToConsole();
};

#endif // SQLSTRUCT_H
