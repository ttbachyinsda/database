#include "sqlstruct.h"
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
    std::cout << "- SQL Value -" << std::endl;
    std::cout << "Type = " << type << std::endl;
    std::cout << "Content = " << content << std::endl;
}
