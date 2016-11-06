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
%token IS NOT NUL PRIMARY KEY
%token CHECK IN

%token INSERT INTO VALUES DELETE FROM
%token UPDATE SET WHERE SELECT AND

%token NOT_EQUAL GREATER_EQUAL LESS_EQUAL

%token <std::string> IDENTIFIER VALUE_STRING VALUE_INT
%token ';' '(' ')' ',' '=' '>' '<'

%type <SQLAction*> Stmt SysStmt QueryStmt
%type <std::vector<SQLType*>*> FieldList
%type <SQLType*> Type Field
%type <SQLValue*> Value
%type <SQLValueGroup*> ValueList
%type <std::vector<SQLValueGroup*>*> ValueLists
%type <SQLCondition*> WhereClause
%type <SQLConditionGroup*> WhereClauseList
%type <SQLSelector*> Column
%type <SQLSelectorGroup*> Selector SelectorList
%type <SQLSetGroup*> SetClause
%type <SQLTableGroup*> TableList
%type <SQLOperand> Operand
%type <SQLCheck*> CheckClause
%type <SQLCheckGroup*> CheckClauseList

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
                | QueryStmt ';'
                {
                    $$ = $1;
                }
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
                | CHECK '(' CheckClauseList ')'
                {
                    $$ = new SQLType();
                    $$->isCheck = true;
                    $$->checkGroup = $3;
                }
                ;

Type            : INT '(' VALUE_INT ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::INT;
                    $$->length = atoi($3.c_str());
                }
                | CHAR '(' VALUE_INT ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::CHAR;
                    $$->length = atoi($3.c_str());
                }
                | VARCHAR '(' VALUE_INT ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::VARCHAR;
                    $$->length = atoi($3.c_str());
                }
                ;

QueryStmt       : INSERT INTO IDENTIFIER VALUES ValueLists
                {
                    $$ = new SQLInsertAction($3, $5);
                }
                | DELETE FROM IDENTIFIER WHERE WhereClauseList
                {
                    $$ = new SQLDeleteAction($3, $5);
                }
                | UPDATE IDENTIFIER SET SetClause WHERE WhereClauseList
                {
                    $$ = new SQLUpdateAction($2, $6, $4);
                }
                | SELECT Selector FROM TableList WHERE WhereClauseList
                {
                    $$ = new SQLSelectAction($4, $2, $6);
                }
                ;

ValueLists      : '(' ValueList ')'
                {
                    $$ = new std::vector<SQLValueGroup*>();
                    $$->push_back($2);
                }
                | ValueLists ',' '(' ValueList ')'
                {
                    $$ = $1;
                    $$->push_back($4);
                }

ValueList       : Value
                {
                    $$ = new SQLValueGroup();
                    $$->push_back($1);
                }
                | ValueList ',' Value
                {
                    $$ = $1;
                    $$->push_back($3);
                }
                ;

Value           : VALUE_INT
                {
                    $$ = new SQLValue();
                    $$->type = SQLValue::ENUMERATE;
                    $$->content = $1;
                }
                | VALUE_STRING
                {
                    $$ = new SQLValue();
                    $$->type = SQLValue::STRING;
                    $$->content = $1;
                }
                | NUL
                {
                    $$ = new SQLValue();
                    $$->type = SQLValue::NUL;
                }
                ;

WhereClause     : Column Operand Column
                {
                    $$ = new SQLCondition();
                    $$->type = SQLCondition::COLUMN;
                    $$->lValue = *($1);
                    $$->rValueColumn = *($3);
                    delete $1;
                    delete $3;
                    $$->operand = $2;

                }
                | Column Operand Value
                {
                    $$ = new SQLCondition();
                    $$->type = SQLCondition::VALUE;
                    $$->lValue = *($1);
                    $$->rValue = *($3);
                    delete $1;
                    delete $3;
                    $$->operand = $2;
                }
                | Column IS NUL
                {
                    $$ = new SQLCondition();
                    $$->type = SQLCondition::VALUE;
                    $$->operand = SQLOperand::EQUAL;
                    $$->lValue = *($1);
                    delete $1;
                    $$->rValue.type = SQLValue::NUL;
                }
                | Column IS NOT NUL
                {
                    $$ = new SQLCondition();
                    $$->type = SQLCondition::VALUE;
                    $$->operand = SQLOperand::NOT_EQUAL;
                    $$->lValue = *($1);
                    delete $1;
                    $$->rValue.type = SQLValue::NUL;
                }
                ;

WhereClauseList : WhereClause
                {
                    $$ = new SQLConditionGroup();
                    $$->push_back($1);
                }
                | WhereClauseList AND WhereClause
                {
                    $$ = $1;
                    $$->push_back($3);
                }
                ;

CheckClause     : Column IN '(' ValueList ')'
                {
                    $$ = new SQLCheck();
                    $$->isChoice = true;
                    $$->choiceList = $4;
                }
                | Column Operand Value
                {
                    $$ = new SQLCheck();
                    $$->isChoice = false;
                    $$->operand = $2;
                    $$->value = *($3);
                    delete $3;
                }
                ;

CheckClauseList : CheckClause
                {
                    $$ = new SQLCheckGroup();
                    $$->push_back($1);
                }
                | CheckClauseList AND CheckClause
                {
                    $$ = $1;
                    $$->push_back($3);
                }
                ;

SetClause       : IDENTIFIER '=' Value
                {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = $1;
                    thisValue->value = *($3);
                    delete $3;
                    $$ = new SQLSetGroup();
                    $$->push_back(thisValue);
                }
                | SetClause ',' IDENTIFIER '=' Value
                {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = $3;
                    thisValue->value = *($5);
                    delete $5;
                    $$ = $1;
                    $$->push_back(thisValue);
                }
                ;

Column          : IDENTIFIER '.' IDENTIFIER
                {
                    $$ = new SQLSelector();
                    $$->databaseName = $1;
                    $$->tableName = $3;
                }
                | IDENTIFIER
                {
                    $$ = new SQLSelector();
                    $$->tableName = $1;
                }
                ;

Selector        : '*'
                {
                    $$ = new SQLSelectorGroup();
                    $$->allMatched = true;
                }
                | SelectorList
                {
                    $$ = $1;
                    $$->allMatched = false;
                }
                ;

SelectorList    : Column
                {
                    $$ = new SQLSelectorGroup();
                    $$->selectors.push_back($1);
                }
                | SelectorList ',' Column
                {
                    $$ = $1;
                    $$->selectors.push_back($3);
                }
                ;

Operand         : '='           { $$ = SQLOperand::EQUAL;         }
                | NOT_EQUAL     { $$ = SQLOperand::NOT_EQUAL;     }
                | '<'           { $$ = SQLOperand::LESS;          }
                | '>'           { $$ = SQLOperand::GREATER;       }
                | LESS_EQUAL    { $$ = SQLOperand::LESS_EQUAL;    }
                | GREATER_EQUAL { $$ = SQLOperand::GREATER_EQUAL; }
                ;

TableList       : IDENTIFIER
                {
                    $$ = new SQLTableGroup();
                    $$->push_back($1);
                }
                | TableList ',' IDENTIFIER
                {
                    $$ = $1;
                    $$->push_back($3);
                }
                ;

%%


void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
