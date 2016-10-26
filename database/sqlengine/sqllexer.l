%{
/* C++ string header, for string ops below */
#include <string>
#include <cstdlib>

/* Implementation of yyFlexScanner */
#include "sqllexer.h"
#include "sqldriver.h"
#undef  YY_DECL
#define YY_DECL int yy::SQLLexer::yylex( yy::SQLParser::semantic_type * const lval, yy::SQLParser::location_type *loc )

// /* typedef to make the returns for the tokens shorter */
using token = yy::SQLParser::token;
//
// /* define yyterminate as this instead of NULL */
// #define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}
%option debug
%option nodefault
%option yyclass="SQLLexer"
%option noyywrap
%option c++

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

([ \t]+)                { /* Just ignore */         }
(\r|\n|\r\n)            {  loc->lines();            }
(";"|"("|")"|","|"="|">"|"<"|"."|"*")       { return (int) yytext[0];   }

"<>"                    { return token::NOT_EQUAL;      }
"<="                    { return token::LESS_EQUAL;     }
">="                    { return token::GREATER_EQUAL;  }

(?i:"create")           { return token::CREATE;     }
(?i:"drop")             { return token::DROP;       }
(?i:"show")             { return token::SHOW;       }
(?i:"use")              { return token::USE;        }
(?i:"database")         { return token::DATABASE;   }
(?i:"databases")        { return token::DATABASES;  }
(?i:"table")            { return token::TABLE;      }
(?i:"tables")           { return token::TABLES;     }
(?i:"desc")             { return token::DESC;       }
(?i:"int")              { return token::INT;        }
(?i:"varchar")          { return token::VARCHAR;    }
(?i:"char")             { return token::CHAR;       }
(?i:"is")               { return token::IS;         }
(?i:"not")              { return token::NOT;        }
(?i:"null")             { return token::NUL;        }
(?i:"primary")          { return token::PRIMARY;    }
(?i:"key")              { return token::KEY;        }

(?i:"insert")           { return token::INSERT;     }
(?i:"into")             { return token::INTO;       }
(?i:"values")           { return token::VALUES;     }
(?i:"delete")           { return token::DELETE;     }
(?i:"update")           { return token::UPDATE;     }
(?i:"set")              { return token::SET;        }
(?i:"where")            { return token::WHERE;      }
(?i:"select")           { return token::SELECT;     }
(?i:"from")             { return token::FROM;       }
(?i:"and")              { return token::AND;        }

[0-9]+                  {
                            yylval->build<std::string>(yytext);
                            return token::VALUE_INT;
                        }

'[^']*'                 {
                            yylval->build<std::string>(yytext);
                            return token::VALUE_STRING;
                        }

[A-Za-z][_0-9A-Za-z]*   {
                            yylval->build<std::string>( yytext );
                            return token::IDENTIFIER;
                        }

.                       {
                            driver->addWarningMessage(
                                "Unrecognized character at line ...");
                        }
%%
