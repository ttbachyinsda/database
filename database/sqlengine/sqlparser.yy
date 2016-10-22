%skeleton "lalr1.cc"
%require  "3.0"
%output "sqlparser.cpp"
%debug
%defines
%define parser_class_name {SQLParser}

%code requires{
    class SQLDriver;
    namespace yy {
        class SQLLexer;
    }

#include "sqlaction.h"

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { SQLLexer  &scanner  }
%parse-param { SQLDriver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "sqldriver.h"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token CREATE DROP SHOW USE DESC
%token DATABASE DATABASES TABLE TABLES
%token INT VARCHAR CHAR
%token NOT NUL PRIMARY KEY

%token INSERT INTO VALUES DELETE FROM
%token UPDATE SET WHERE SELECT

%token <std::string> IDENTIFIER VALUE_STRING
%token <int>         VALUE_INT
%token ';' '(' ')' ',' '=' '>' '<'
/*%token SELECT UPDATE DELETE FROM*/

%type <SQLAction*> Stmt SysStmt
%type <std::vector<SQLType*>*> FieldList
%type <SQLType*> Type Field

%locations

%start Program

%%

Program         : /* empty & do nothing */
                | Program Stmt
                {
                    driver.addAction($2);
                }
                ;

Stmt            : SysStmt ';' // default as $$ = $1;
                {
                    $$ = $1;
                }
                /*| QueryStmt ';'*/
                ;

SysStmt         : CREATE DATABASE IDENTIFIER
                {
                    $$ = new SQLCreateDatabaseAction($3);
                }
                | DROP DATABASE IDENTIFIER
                {
                    $$ = new SQLDropDatabaseAction($3);
                }
                | SHOW DATABASES
                {
                    $$ = new SQLShowDatabasesAction();
                }
                | USE IDENTIFIER
                {
                    $$ = new SQLUseDatabaseAction($2);
                }
                | SHOW TABLES
                {
                    $$ = new SQLShowTablesAction();
                }
                | CREATE TABLE IDENTIFIER '(' FieldList ')'
                {
                    $$ = new SQLCreateTableAction($3, $5);
                }
                | DROP TABLE IDENTIFIER
                {
                    $$ = new SQLDropTableAction($3);
                }
                | DESC IDENTIFIER
                {
                    $$ = new SQLDescAction($2);
                }
                ;

FieldList       : Field
                {
                    $$ = new std::vector<SQLType*>();
                    $$->push_back($1);
                }
                | FieldList ',' Field
                {
                    $$ = $1;
                    $$->push_back($3);
                }
                ;

Field           : IDENTIFIER Type
                {
                    $$ = $2;
                    $$->identifier = $1;
                }
                | IDENTIFIER Type NOT NUL
                {
                    $$ = $2;
                    $$->identifier = $1;
                    $$->canNull = false;
                }
                | PRIMARY KEY '(' IDENTIFIER ')'
                {
                    $$ = new SQLType();
                    $$->identifier = $4;
                    $$->primaryType = true;
                }
                ;

Type            : INT '(' VALUE_INT ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::INT;
                    $$->length = $3;
                }
                | CHAR '(' VALUE_INT ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::CHAR;
                    $$->length = $3;
                }
                | VARCHAR '(' VALUE_INT ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::VARCHAR;
                    $$->length = $3;
                }
                ;

%%


void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
