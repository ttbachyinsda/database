#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H

#include <string>
#include <vector>
#include <list>

struct SQLValue
{
    enum LiteralType {
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
    LESS_EQUAL,
    LIKE
};
struct SQLSelector;
struct SQLCheck
{
    SQLSelector* selector;
    bool isChoice;
    SQLValueGroup* choiceList;
    SQLOperand operand;
    SQLValue value;
    ~SQLCheck() {
        if (isChoice) {
            for (SQLValue* sv : *choiceList) {
                delete sv;
            }
            delete choiceList;
        }
        delete selector;
    }
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

enum SQLGroupMethod {
    MAX, MIN, SUM, AVG, BLANK
};

struct SQLSelector
{
    std::string databaseName;
    std::string tableName;

    SQLGroupMethod groupMethod;

    bool hasPrefix() const { return databaseName.size() != 0; }

    void dump() const;

    SQLSelector() { groupMethod = BLANK; }
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
        data.push_back(std::vector<std::string>((unsigned long) columns));
    }

    void setData(int idx, const std::string& str) {
        if (idx >= columns) return;
        if (data.size() == 0) return;
        data.back().at((unsigned long) idx) = str;
    }
    void addTitleField(const std::string& str) {
        title.push_back(str);
    }

    std::string toJSON();

    void dumpToConsole();
};

#endif // SQLSTRUCT_H
