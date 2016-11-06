//
// Created by jameshuang on 16-10-19.
//

#ifndef DATABASE_SQLLEXER_H
#define DATABASE_SQLLEXER_H

#if !defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif

#include "sqlparser.hpp"
#include "location.hh"

namespace yy {

    class SQLLexer : public yyFlexLexer {
    public:

        SQLLexer(std::istream *in, SQLDriver *drv)
            : yyFlexLexer(in), driver(drv) {
            loc = new yy::SQLParser::location_type();
        }

        virtual ~SQLLexer() {
            delete loc;
        }

        //get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual int yylex(yy::SQLParser::semantic_type *const lval,
                          yy::SQLParser::location_type *location);

    private:
        yy::SQLParser::semantic_type *yylval = nullptr;
        yy::SQLParser::location_type *loc = nullptr;
        SQLDriver *const driver;
    };

}

#endif //DATABASE_SQLLEXER_H
