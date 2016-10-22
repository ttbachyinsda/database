#include "sqlstruct.h"
#include <iostream>

const char *const SQLType::INT = "INT";
const char *const SQLType::CHAR = "CHAR";
const char *const SQLType::VARCHAR = "VARCHAR";

void SQLType::dump() const
{
    std::cout << "- SQL Type -" << std::endl;
    if (primaryType)
        std::cout << "Primary = " << primaryType << std::endl;
    else {
        std::cout << "Identifier = " << identifier << std::endl;
        std::cout << "Type = " << type << std::endl;
        std::cout << "Null = " << canNull << std::endl;
    }
}
