#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H

#include <string>

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


#endif // SQLSTRUCT_H
