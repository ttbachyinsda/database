%skeleton "lalr1.cc"
%require  "3.0"
%output "sqlparser.cpp"
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
   #include <sstream>

   /* include for all driver functions */
   #include "sqldriver.h"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token CREATE DROP SHOW USE DESC
%token DATABASE DATABASES TABLE TABLES
%token INT VARCHAR CHAR DOUBLE BIGINT DATETIME VARBINARY
%token IS NOT NUL PRIMARY KEY
%token CHECK IN LIKE
%token FOREIGN REFERENCES

%token INSERT INTO VALUES DELETE FROM
%token UPDATE SET WHERE SELECT AND INDEX
%token MASTER ENCRYPTION DECRYPTION PASSWORD OPEN

%token GROUP BY
%token MAX MIN AVG SUM

%token NOT_EQUAL GREATER_EQUAL LESS_EQUAL

%token <std::string> IDENTIFIER VALUE_STRING VALUE_INT
%token <std::string> VALUE_DATE VALUE_DECIMAL VALUE_LINT
%token ';' '(' ')' ',' '=' '>' '<'

%type <SQLAction*> Stmt SysStmt QueryStmt
%type <std::vector<SQLType*>*> FieldList
%type <SQLType*> Type Field
%type <SQLValue*> Value
%type <SQLValueGroup*> ValueList
%type <std::vector<SQLValueGroup*>*> ValueLists
%type <SQLCondition*> WhereClause
%type <SQLConditionGroup*> WhereClauseList
%type <SQLSelector*> Column GroupColumn
%type <SQLSelectorGroup*> Selector SelectorList
%type <SQLSetGroup*> SetClause
%type <SQLTableGroup*> TableList GroupByClause
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
                | CREATE INDEX IDENTIFIER '(' IDENTIFIER ')'
                {
                    $$ = new SQLCreateIndexAction($3, $5);
                }
                | DROP INDEX IDENTIFIER '(' IDENTIFIER ')'
                {
                    $$ = new SQLDropIndexAction($3, $5);
                }
                | CREATE MASTER KEY ENCRYPTION BY PASSWORD '=' VALUE_STRING
                {
                    $$ = new SQLEncryptAction($8);
                }
                | OPEN MASTER KEY DECRYPTION BY PASSWORD '=' VALUE_STRING
                {
                    $$ = new SQLDecryptAction($8);
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
                | IDENTIFIER Type FOREIGN KEY REFERENCES IDENTIFIER '(' IDENTIFIER ')'
                {
                    $$ = $2;
                    $$->identifier = $1;
                    $$->hasForeignKey = true;
                    $$->foreignKey = new SQLSelector();
                    $$->foreignKey->databaseName = $6;
                    $$->foreignKey->tableName = $8;
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
                | BIGINT '(' ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::LINT;
                    $$->length = 8;
                }
                | DOUBLE '(' ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::REAL;
                    $$->length = 8;
                }
                | DATETIME '(' ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::DATE;
                    $$->length = 8;
                }
                | VARBINARY '(' ')'
                {
                    $$ = new SQLType();
                    $$->type = SQLType::BULB;
                    $$->length = 8;
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
                | SELECT Selector FROM TableList GroupByClause
                {
                    $$ = new SQLGroupSelectAction($2, $5, $4);
                }
                ;

GroupByClause   : /* empty */
                {
                    $$ = 0;
                }
                | GROUP BY TableList
                {
                    $$ = $3;
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
                | VALUE_DATE
                {
                    $$ = new SQLValue();
                    $$->type = SQLValue::DATE;
                    $$->content = $1;
                    $$->parseDate();
                }
                | VALUE_DECIMAL
                {
                    $$ = new SQLValue();
                    $$->type = SQLValue::DECIMAL;
                    $$->content = $1;
                    $$->parseReal();
                }
                | VALUE_LINT
                {
                    $$ = new SQLValue();
                    $$->type = SQLValue::LONGINT;
                    $$->content = $1;
                    $$->parseLong();
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
                    $$->selector = $1;
                }
                | Column Operand Value
                {
                    $$ = new SQLCheck();
                    $$->isChoice = false;
                    $$->operand = $2;
                    $$->value = *($3);
                    delete $3;
                    $$->selector = $1;
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
                | GroupColumn
                {
                    $$ = $1;
                }
                ;

GroupColumn     : SUM '(' IDENTIFIER ')'
                {
                    $$ = new SQLSelector();
                    $$->tableName = $3;
                    $$->groupMethod = SUM;
                }
                | AVG '(' IDENTIFIER ')'
                {
                    $$ = new SQLSelector();
                    $$->tableName = $3;
                    $$->groupMethod = AVG;
                }
                | MAX '(' IDENTIFIER ')'
                {
                    $$ = new SQLSelector();
                    $$->tableName = $3;
                    $$->groupMethod = MAX;
                }
                | MIN '(' IDENTIFIER ')'
                {
                    $$ = new SQLSelector();
                    $$->tableName = $3;
                    $$->groupMethod = MIN;
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
                | LIKE          { $$ = SQLOperand::LIKE;          }
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
    std::stringstream sstr;
    sstr << "Syntax error at line " << l.begin.line << ", column " << l.begin.column << ".";
    driver.addErrorMessage(sstr.str());
}
