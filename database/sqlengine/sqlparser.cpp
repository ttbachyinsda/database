// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "sqlparser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "sqlparser.hpp"

// User implementation prologue.

#line 51 "sqlparser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 30 "sqlparser.yy" // lalr1.cc:413

   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "sqldriver.h"

#undef yylex
#define yylex scanner.yylex

#line 65 "sqlparser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 151 "sqlparser.cpp" // lalr1.cc:479

  /// Build a parser object.
  SQLParser::SQLParser (SQLLexer  &scanner_yyarg, SQLDriver  &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  SQLParser::~SQLParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  SQLParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        value.copy< SQLAction* > (other.value);
        break;

      case 56: // WhereClause
        value.copy< SQLCondition* > (other.value);
        break;

      case 57: // WhereClauseList
        value.copy< SQLConditionGroup* > (other.value);
        break;

      case 62: // Operand
        value.copy< SQLOperand > (other.value);
        break;

      case 59: // Column
        value.copy< SQLSelector* > (other.value);
        break;

      case 60: // Selector
      case 61: // SelectorList
        value.copy< SQLSelectorGroup* > (other.value);
        break;

      case 58: // SetClause
        value.copy< SQLSetGroup* > (other.value);
        break;

      case 63: // TableList
        value.copy< SQLTableGroup* > (other.value);
        break;

      case 50: // Field
      case 51: // Type
        value.copy< SQLType* > (other.value);
        break;

      case 55: // Value
        value.copy< SQLValue* > (other.value);
        break;

      case 54: // ValueList
        value.copy< SQLValueGroup* > (other.value);
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        value.copy< std::string > (other.value);
        break;

      case 49: // FieldList
        value.copy< std::vector<SQLType*>* > (other.value);
        break;

      case 53: // ValueLists
        value.copy< std::vector<SQLValueGroup*>* > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        value.copy< SQLAction* > (v);
        break;

      case 56: // WhereClause
        value.copy< SQLCondition* > (v);
        break;

      case 57: // WhereClauseList
        value.copy< SQLConditionGroup* > (v);
        break;

      case 62: // Operand
        value.copy< SQLOperand > (v);
        break;

      case 59: // Column
        value.copy< SQLSelector* > (v);
        break;

      case 60: // Selector
      case 61: // SelectorList
        value.copy< SQLSelectorGroup* > (v);
        break;

      case 58: // SetClause
        value.copy< SQLSetGroup* > (v);
        break;

      case 63: // TableList
        value.copy< SQLTableGroup* > (v);
        break;

      case 50: // Field
      case 51: // Type
        value.copy< SQLType* > (v);
        break;

      case 55: // Value
        value.copy< SQLValue* > (v);
        break;

      case 54: // ValueList
        value.copy< SQLValueGroup* > (v);
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        value.copy< std::string > (v);
        break;

      case 49: // FieldList
        value.copy< std::vector<SQLType*>* > (v);
        break;

      case 53: // ValueLists
        value.copy< std::vector<SQLValueGroup*>* > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLAction* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLCondition* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLConditionGroup* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLOperand v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLSelector* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLSelectorGroup* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLSetGroup* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLTableGroup* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLType* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLValue* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLValueGroup* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<SQLType*>* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<SQLValueGroup*>* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  SQLParser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        value.template destroy< SQLAction* > ();
        break;

      case 56: // WhereClause
        value.template destroy< SQLCondition* > ();
        break;

      case 57: // WhereClauseList
        value.template destroy< SQLConditionGroup* > ();
        break;

      case 62: // Operand
        value.template destroy< SQLOperand > ();
        break;

      case 59: // Column
        value.template destroy< SQLSelector* > ();
        break;

      case 60: // Selector
      case 61: // SelectorList
        value.template destroy< SQLSelectorGroup* > ();
        break;

      case 58: // SetClause
        value.template destroy< SQLSetGroup* > ();
        break;

      case 63: // TableList
        value.template destroy< SQLTableGroup* > ();
        break;

      case 50: // Field
      case 51: // Type
        value.template destroy< SQLType* > ();
        break;

      case 55: // Value
        value.template destroy< SQLValue* > ();
        break;

      case 54: // ValueList
        value.template destroy< SQLValueGroup* > ();
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        value.template destroy< std::string > ();
        break;

      case 49: // FieldList
        value.template destroy< std::vector<SQLType*>* > ();
        break;

      case 53: // ValueLists
        value.template destroy< std::vector<SQLValueGroup*>* > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  SQLParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  SQLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        value.move< SQLAction* > (s.value);
        break;

      case 56: // WhereClause
        value.move< SQLCondition* > (s.value);
        break;

      case 57: // WhereClauseList
        value.move< SQLConditionGroup* > (s.value);
        break;

      case 62: // Operand
        value.move< SQLOperand > (s.value);
        break;

      case 59: // Column
        value.move< SQLSelector* > (s.value);
        break;

      case 60: // Selector
      case 61: // SelectorList
        value.move< SQLSelectorGroup* > (s.value);
        break;

      case 58: // SetClause
        value.move< SQLSetGroup* > (s.value);
        break;

      case 63: // TableList
        value.move< SQLTableGroup* > (s.value);
        break;

      case 50: // Field
      case 51: // Type
        value.move< SQLType* > (s.value);
        break;

      case 55: // Value
        value.move< SQLValue* > (s.value);
        break;

      case 54: // ValueList
        value.move< SQLValueGroup* > (s.value);
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        value.move< std::string > (s.value);
        break;

      case 49: // FieldList
        value.move< std::vector<SQLType*>* > (s.value);
        break;

      case 53: // ValueLists
        value.move< std::vector<SQLValueGroup*>* > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  SQLParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  SQLParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  SQLParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  SQLParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  SQLParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  SQLParser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  SQLParser::symbol_type
  SQLParser::make_CREATE (const location_type& l)
  {
    return symbol_type (token::CREATE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_DROP (const location_type& l)
  {
    return symbol_type (token::DROP, l);
  }

  SQLParser::symbol_type
  SQLParser::make_SHOW (const location_type& l)
  {
    return symbol_type (token::SHOW, l);
  }

  SQLParser::symbol_type
  SQLParser::make_USE (const location_type& l)
  {
    return symbol_type (token::USE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_DESC (const location_type& l)
  {
    return symbol_type (token::DESC, l);
  }

  SQLParser::symbol_type
  SQLParser::make_DATABASE (const location_type& l)
  {
    return symbol_type (token::DATABASE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_DATABASES (const location_type& l)
  {
    return symbol_type (token::DATABASES, l);
  }

  SQLParser::symbol_type
  SQLParser::make_TABLE (const location_type& l)
  {
    return symbol_type (token::TABLE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_TABLES (const location_type& l)
  {
    return symbol_type (token::TABLES, l);
  }

  SQLParser::symbol_type
  SQLParser::make_INT (const location_type& l)
  {
    return symbol_type (token::INT, l);
  }

  SQLParser::symbol_type
  SQLParser::make_VARCHAR (const location_type& l)
  {
    return symbol_type (token::VARCHAR, l);
  }

  SQLParser::symbol_type
  SQLParser::make_CHAR (const location_type& l)
  {
    return symbol_type (token::CHAR, l);
  }

  SQLParser::symbol_type
  SQLParser::make_IS (const location_type& l)
  {
    return symbol_type (token::IS, l);
  }

  SQLParser::symbol_type
  SQLParser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  SQLParser::symbol_type
  SQLParser::make_NUL (const location_type& l)
  {
    return symbol_type (token::NUL, l);
  }

  SQLParser::symbol_type
  SQLParser::make_PRIMARY (const location_type& l)
  {
    return symbol_type (token::PRIMARY, l);
  }

  SQLParser::symbol_type
  SQLParser::make_KEY (const location_type& l)
  {
    return symbol_type (token::KEY, l);
  }

  SQLParser::symbol_type
  SQLParser::make_INSERT (const location_type& l)
  {
    return symbol_type (token::INSERT, l);
  }

  SQLParser::symbol_type
  SQLParser::make_INTO (const location_type& l)
  {
    return symbol_type (token::INTO, l);
  }

  SQLParser::symbol_type
  SQLParser::make_VALUES (const location_type& l)
  {
    return symbol_type (token::VALUES, l);
  }

  SQLParser::symbol_type
  SQLParser::make_DELETE (const location_type& l)
  {
    return symbol_type (token::DELETE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  SQLParser::symbol_type
  SQLParser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_SET (const location_type& l)
  {
    return symbol_type (token::SET, l);
  }

  SQLParser::symbol_type
  SQLParser::make_WHERE (const location_type& l)
  {
    return symbol_type (token::WHERE, l);
  }

  SQLParser::symbol_type
  SQLParser::make_SELECT (const location_type& l)
  {
    return symbol_type (token::SELECT, l);
  }

  SQLParser::symbol_type
  SQLParser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  SQLParser::symbol_type
  SQLParser::make_NOT_EQUAL (const location_type& l)
  {
    return symbol_type (token::NOT_EQUAL, l);
  }

  SQLParser::symbol_type
  SQLParser::make_GREATER_EQUAL (const location_type& l)
  {
    return symbol_type (token::GREATER_EQUAL, l);
  }

  SQLParser::symbol_type
  SQLParser::make_LESS_EQUAL (const location_type& l)
  {
    return symbol_type (token::LESS_EQUAL, l);
  }

  SQLParser::symbol_type
  SQLParser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }

  SQLParser::symbol_type
  SQLParser::make_VALUE_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::VALUE_STRING, v, l);
  }

  SQLParser::symbol_type
  SQLParser::make_VALUE_INT (const std::string& v, const location_type& l)
  {
    return symbol_type (token::VALUE_INT, v, l);
  }



  // by_state.
  inline
  SQLParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  SQLParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  SQLParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  SQLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  SQLParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  SQLParser::symbol_number_type
  SQLParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  SQLParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  SQLParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        value.move< SQLAction* > (that.value);
        break;

      case 56: // WhereClause
        value.move< SQLCondition* > (that.value);
        break;

      case 57: // WhereClauseList
        value.move< SQLConditionGroup* > (that.value);
        break;

      case 62: // Operand
        value.move< SQLOperand > (that.value);
        break;

      case 59: // Column
        value.move< SQLSelector* > (that.value);
        break;

      case 60: // Selector
      case 61: // SelectorList
        value.move< SQLSelectorGroup* > (that.value);
        break;

      case 58: // SetClause
        value.move< SQLSetGroup* > (that.value);
        break;

      case 63: // TableList
        value.move< SQLTableGroup* > (that.value);
        break;

      case 50: // Field
      case 51: // Type
        value.move< SQLType* > (that.value);
        break;

      case 55: // Value
        value.move< SQLValue* > (that.value);
        break;

      case 54: // ValueList
        value.move< SQLValueGroup* > (that.value);
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        value.move< std::string > (that.value);
        break;

      case 49: // FieldList
        value.move< std::vector<SQLType*>* > (that.value);
        break;

      case 53: // ValueLists
        value.move< std::vector<SQLValueGroup*>* > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  SQLParser::stack_symbol_type&
  SQLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        value.copy< SQLAction* > (that.value);
        break;

      case 56: // WhereClause
        value.copy< SQLCondition* > (that.value);
        break;

      case 57: // WhereClauseList
        value.copy< SQLConditionGroup* > (that.value);
        break;

      case 62: // Operand
        value.copy< SQLOperand > (that.value);
        break;

      case 59: // Column
        value.copy< SQLSelector* > (that.value);
        break;

      case 60: // Selector
      case 61: // SelectorList
        value.copy< SQLSelectorGroup* > (that.value);
        break;

      case 58: // SetClause
        value.copy< SQLSetGroup* > (that.value);
        break;

      case 63: // TableList
        value.copy< SQLTableGroup* > (that.value);
        break;

      case 50: // Field
      case 51: // Type
        value.copy< SQLType* > (that.value);
        break;

      case 55: // Value
        value.copy< SQLValue* > (that.value);
        break;

      case 54: // ValueList
        value.copy< SQLValueGroup* > (that.value);
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        value.copy< std::string > (that.value);
        break;

      case 49: // FieldList
        value.copy< std::vector<SQLType*>* > (that.value);
        break;

      case 53: // ValueLists
        value.copy< std::vector<SQLValueGroup*>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  SQLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  SQLParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  SQLParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  SQLParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  SQLParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SQLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SQLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SQLParser::debug_level_type
  SQLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SQLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline SQLParser::state_type
  SQLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  SQLParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  SQLParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SQLParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 47: // Stmt
      case 48: // SysStmt
      case 52: // QueryStmt
        yylhs.value.build< SQLAction* > ();
        break;

      case 56: // WhereClause
        yylhs.value.build< SQLCondition* > ();
        break;

      case 57: // WhereClauseList
        yylhs.value.build< SQLConditionGroup* > ();
        break;

      case 62: // Operand
        yylhs.value.build< SQLOperand > ();
        break;

      case 59: // Column
        yylhs.value.build< SQLSelector* > ();
        break;

      case 60: // Selector
      case 61: // SelectorList
        yylhs.value.build< SQLSelectorGroup* > ();
        break;

      case 58: // SetClause
        yylhs.value.build< SQLSetGroup* > ();
        break;

      case 63: // TableList
        yylhs.value.build< SQLTableGroup* > ();
        break;

      case 50: // Field
      case 51: // Type
        yylhs.value.build< SQLType* > ();
        break;

      case 55: // Value
        yylhs.value.build< SQLValue* > ();
        break;

      case 54: // ValueList
        yylhs.value.build< SQLValueGroup* > ();
        break;

      case 33: // IDENTIFIER
      case 34: // VALUE_STRING
      case 35: // VALUE_INT
        yylhs.value.build< std::string > ();
        break;

      case 49: // FieldList
        yylhs.value.build< std::vector<SQLType*>* > ();
        break;

      case 53: // ValueLists
        yylhs.value.build< std::vector<SQLValueGroup*>* > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 80 "sqlparser.yy" // lalr1.cc:859
    {
                    driver.addAction(yystack_[0].value.as< SQLAction* > ());
                }
#line 1368 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 86 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1376 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 90 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1384 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 96 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1392 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 100 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1400 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 104 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowDatabasesAction();
                }
#line 1408 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 108 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLUseDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1416 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 112 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowTablesAction();
                }
#line 1424 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 116 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateTableAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<SQLType*>* > ());
                }
#line 1432 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 120 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropTableAction(yystack_[0].value.as< std::string > ());
                }
#line 1440 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 124 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDescAction(yystack_[0].value.as< std::string > ());
                }
#line 1448 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 130 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = new std::vector<SQLType*>();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1457 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 135 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = yystack_[2].value.as< std::vector<SQLType*>* > ();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1466 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 142 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[0].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                }
#line 1475 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 147 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[2].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[3].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->canNull = false;
                }
#line 1485 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 153 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->primaryType = true;
                }
#line 1495 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 161 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::INT;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1505 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 167 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::CHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1515 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 173 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::VARCHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1525 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 181 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLInsertAction(yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::vector<SQLValueGroup*>* > ());
                }
#line 1533 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 185 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDeleteAction(yystack_[2].value.as< std::string > (), yystack_[0].value.as< SQLConditionGroup* > ());
                }
#line 1541 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 189 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLUpdateAction(yystack_[4].value.as< std::string > (), yystack_[0].value.as< SQLConditionGroup* > (), yystack_[2].value.as< SQLSetGroup* > ());
                }
#line 1549 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 193 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLSelectAction(yystack_[2].value.as< SQLTableGroup* > (), yystack_[4].value.as< SQLSelectorGroup* > (), yystack_[0].value.as< SQLConditionGroup* > ());
                }
#line 1557 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 199 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLValueGroup*>* > () = new std::vector<SQLValueGroup*>();
                    yylhs.value.as< std::vector<SQLValueGroup*>* > ()->push_back(yystack_[1].value.as< SQLValueGroup* > ());
                }
#line 1566 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 204 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLValueGroup*>* > () = yystack_[4].value.as< std::vector<SQLValueGroup*>* > ();
                    yylhs.value.as< std::vector<SQLValueGroup*>* > ()->push_back(yystack_[1].value.as< SQLValueGroup* > ());
                }
#line 1575 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 210 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValueGroup* > () = new SQLValueGroup();
                    yylhs.value.as< SQLValueGroup* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1584 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 215 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValueGroup* > () = yystack_[2].value.as< SQLValueGroup* > ();
                    yylhs.value.as< SQLValueGroup* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1593 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 222 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::ENUMERATE;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1603 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 228 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::STRING;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1613 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 234 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::NUL;
                }
#line 1622 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 241 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::COLUMN;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    yylhs.value.as< SQLCondition* > ()->rValueColumn = *(yystack_[0].value.as< SQLSelector* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    delete yystack_[0].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->operand = yystack_[1].value.as< SQLOperand > ();

                }
#line 1637 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 252 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    yylhs.value.as< SQLCondition* > ()->rValue = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLCondition* > ()->operand = yystack_[1].value.as< SQLOperand > ();
                }
#line 1651 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 262 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->operand = SQLOperand::EQUAL;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->rValue.type = SQLValue::NUL;
                }
#line 1664 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 271 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->operand = SQLOperand::NOT_EQUAL;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[3].value.as< SQLSelector* > ());
                    delete yystack_[3].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->rValue.type = SQLValue::NUL;
                }
#line 1677 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 282 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLConditionGroup* > () = new SQLConditionGroup();
                    yylhs.value.as< SQLConditionGroup* > ()->push_back(yystack_[0].value.as< SQLCondition* > ());
                }
#line 1686 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 287 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLConditionGroup* > () = yystack_[2].value.as< SQLConditionGroup* > ();
                    yylhs.value.as< SQLConditionGroup* > ()->push_back(yystack_[0].value.as< SQLCondition* > ());
                }
#line 1695 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 294 "sqlparser.yy" // lalr1.cc:859
    {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = yystack_[2].value.as< std::string > ();
                    thisValue->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLSetGroup* > () = new SQLSetGroup();
                    yylhs.value.as< SQLSetGroup* > ()->push_back(thisValue);
                }
#line 1708 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 303 "sqlparser.yy" // lalr1.cc:859
    {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = yystack_[2].value.as< std::string > ();
                    thisValue->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLSetGroup* > () = yystack_[4].value.as< SQLSetGroup* > ();
                    yylhs.value.as< SQLSetGroup* > ()->push_back(thisValue);
                }
#line 1721 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 314 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelector* > () = new SQLSelector();
                    yylhs.value.as< SQLSelector* > ()->databaseName = yystack_[2].value.as< std::string > ();
                    yylhs.value.as< SQLSelector* > ()->tableName = yystack_[0].value.as< std::string > ();
                }
#line 1731 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 320 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelector* > () = new SQLSelector();
                    yylhs.value.as< SQLSelector* > ()->tableName = yystack_[0].value.as< std::string > ();
                }
#line 1740 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 327 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = new SQLSelectorGroup();
                    yylhs.value.as< SQLSelectorGroup* > ()->allMatched = true;
                }
#line 1749 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 332 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = yystack_[0].value.as< SQLSelectorGroup* > ();
                    yylhs.value.as< SQLSelectorGroup* > ()->allMatched = false;
                }
#line 1758 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 339 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = new SQLSelectorGroup();
                    yylhs.value.as< SQLSelectorGroup* > ()->selectors.push_back(yystack_[0].value.as< SQLSelector* > ());
                }
#line 1767 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 344 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = yystack_[2].value.as< SQLSelectorGroup* > ();
                    yylhs.value.as< SQLSelectorGroup* > ()->selectors.push_back(yystack_[0].value.as< SQLSelector* > ());
                }
#line 1776 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 350 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::EQUAL;         }
#line 1782 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 351 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::NOT_EQUAL;     }
#line 1788 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 352 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::LESS;          }
#line 1794 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 353 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::GREATER;       }
#line 1800 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 354 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::LESS_EQUAL;    }
#line 1806 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 355 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::GREATER_EQUAL; }
#line 1812 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 359 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLTableGroup* > () = new SQLTableGroup();
                    yylhs.value.as< SQLTableGroup* > ()->push_back(yystack_[0].value.as< std::string > ());
                }
#line 1821 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 364 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLTableGroup* > () = yystack_[2].value.as< SQLTableGroup* > ();
                    yylhs.value.as< SQLTableGroup* > ()->push_back(yystack_[0].value.as< std::string > ());
                }
#line 1830 "sqlparser.cpp" // lalr1.cc:859
    break;


#line 1834 "sqlparser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  SQLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  SQLParser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char SQLParser::yypact_ninf_ = -61;

  const signed char SQLParser::yytable_ninf_ = -1;

  const signed char
  SQLParser::yypact_[] =
  {
     -61,     5,   -61,     6,    43,    45,   -26,   -20,     2,     8,
      -4,    -7,   -61,    16,    19,    10,    25,    33,    34,   -61,
     -61,   -61,   -61,    35,    37,    47,    28,   -61,   -61,    48,
      30,   -61,   -61,   -61,    38,   -61,   -61,    52,    50,    49,
      51,    53,    54,   -16,    41,    54,    39,   -24,   -61,   -61,
     -21,   -61,    61,    36,     0,   -61,     7,    42,   -61,    56,
       4,     7,    54,    55,    54,    57,    58,    59,    60,    62,
      67,   -61,   -16,   -61,   -61,   -61,    22,   -61,    63,    54,
      46,   -61,   -61,   -61,   -61,   -61,   -61,   -13,   -61,    56,
      64,    56,   -61,    65,    66,    68,    70,    72,   -61,   -61,
       7,     7,   -61,    74,   -61,   -61,   -61,     7,    69,    71,
      73,    75,   -61,   -61,    26,   -61,   -61,   -61,   -61,   -61,
     -61,   -61
  };

  const unsigned char
  SQLParser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     8,
      10,     9,    13,     0,     0,     0,    42,    43,    45,     0,
      44,     4,     5,     6,     0,     7,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    53,
       0,    46,     0,     0,     0,    14,     0,    22,    37,    23,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      16,    11,     0,    32,    31,    30,     0,    28,     0,     0,
       0,    48,    52,    51,    47,    50,    49,     0,    39,    24,
       0,    25,    54,     0,     0,     0,     0,     0,    15,    26,
       0,     0,    38,     0,    35,    34,    33,     0,     0,     0,
       0,     0,    17,    29,     0,    36,    40,    18,    19,    21,
      20,    27
  };

  const signed char
  SQLParser::yypgoto_[] =
  {
     -61,   -61,   -61,   -61,   -61,    20,   -61,   -61,   -61,    -8,
     -60,    15,    -5,   -61,   -11,   -61,   -61,   -61,   -61
  };

  const signed char
  SQLParser::yydefgoto_[] =
  {
      -1,     1,    12,    13,    54,    55,    70,    14,    57,    76,
      77,    58,    59,    47,    60,    29,    30,    87,    50
  };

  const unsigned char
  SQLParser::yytable_[] =
  {
      28,    88,    52,    62,    73,     2,    64,    21,     3,     4,
       5,     6,     7,    22,    15,    63,    16,    53,    65,    80,
      26,    74,    75,    23,    73,     8,    26,   105,     9,    25,
      10,    51,    24,    11,    81,    82,    83,    27,    71,    72,
     113,    74,    75,    33,    84,    85,    86,   116,    67,    68,
      69,    17,    31,    18,    19,    32,    20,    89,    34,    91,
      99,   100,   103,   104,   121,   100,    35,    36,    37,    42,
      38,    40,    41,    39,    44,    43,   106,    45,    56,    61,
      66,    78,    46,    97,    48,    79,    49,    26,    90,   112,
      92,   115,    98,   114,   102,    93,    94,    95,   108,    96,
     101,   109,     0,   110,   107,   111,     0,   117,     0,   118,
       0,   119,     0,   120
  };

  const signed char
  SQLParser::yycheck_[] =
  {
      11,    61,    18,    27,    17,     0,    27,    33,     3,     4,
       5,     6,     7,    33,     8,    39,    10,    33,    39,    15,
      33,    34,    35,    21,    17,    20,    33,    87,    23,    33,
      25,    42,    24,    28,    30,    31,    32,    44,    38,    39,
     100,    34,    35,    33,    40,    41,    42,   107,    12,    13,
      14,     8,    36,    10,     9,    36,    11,    62,    33,    64,
      38,    39,    16,    17,    38,    39,    33,    33,    33,    39,
      33,    43,    24,    26,    22,    37,    87,    27,    37,    40,
      19,    39,    33,    16,    33,    29,    33,    33,    33,    17,
      33,    17,    72,   101,    79,    37,    37,    37,    33,    37,
      37,    35,    -1,    35,    40,    35,    -1,    38,    -1,    38,
      -1,    38,    -1,    38
  };

  const unsigned char
  SQLParser::yystos_[] =
  {
       0,    46,     0,     3,     4,     5,     6,     7,    20,    23,
      25,    28,    47,    48,    52,     8,    10,     8,    10,     9,
      11,    33,    33,    21,    24,    33,    33,    44,    59,    60,
      61,    36,    36,    33,    33,    33,    33,    33,    33,    26,
      43,    24,    39,    37,    22,    27,    33,    58,    33,    33,
      63,    59,    18,    33,    49,    50,    37,    53,    56,    57,
      59,    40,    27,    39,    27,    39,    19,    12,    13,    14,
      51,    38,    39,    17,    34,    35,    54,    55,    39,    29,
      15,    30,    31,    32,    40,    41,    42,    62,    55,    57,
      33,    57,    33,    37,    37,    37,    37,    16,    50,    38,
      39,    37,    56,    16,    17,    55,    59,    40,    33,    35,
      35,    35,    17,    55,    54,    17,    55,    38,    38,    38,
      38,    38
  };

  const unsigned char
  SQLParser::yyr1_[] =
  {
       0,    45,    46,    46,    47,    47,    48,    48,    48,    48,
      48,    48,    48,    48,    49,    49,    50,    50,    50,    51,
      51,    51,    52,    52,    52,    52,    53,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      62,    62,    62,    63,    63
  };

  const unsigned char
  SQLParser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     3,     2,     2,
       2,     6,     3,     2,     1,     3,     2,     4,     5,     4,
       4,     4,     5,     5,     6,     6,     3,     5,     1,     3,
       1,     1,     1,     3,     3,     3,     4,     1,     3,     3,
       5,     3,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SQLParser::yytname_[] =
  {
  "$end", "error", "$undefined", "CREATE", "DROP", "SHOW", "USE", "DESC",
  "DATABASE", "DATABASES", "TABLE", "TABLES", "INT", "VARCHAR", "CHAR",
  "IS", "NOT", "NUL", "PRIMARY", "KEY", "INSERT", "INTO", "VALUES",
  "DELETE", "FROM", "UPDATE", "SET", "WHERE", "SELECT", "AND", "NOT_EQUAL",
  "GREATER_EQUAL", "LESS_EQUAL", "IDENTIFIER", "VALUE_STRING", "VALUE_INT",
  "';'", "'('", "')'", "','", "'='", "'>'", "'<'", "'.'", "'*'", "$accept",
  "Program", "Stmt", "SysStmt", "FieldList", "Field", "Type", "QueryStmt",
  "ValueLists", "ValueList", "Value", "WhereClause", "WhereClauseList",
  "SetClause", "Column", "Selector", "SelectorList", "Operand",
  "TableList", YY_NULLPTR
  };


  const unsigned short int
  SQLParser::yyrline_[] =
  {
       0,    78,    78,    79,    85,    89,    95,    99,   103,   107,
     111,   115,   119,   123,   129,   134,   141,   146,   152,   160,
     166,   172,   180,   184,   188,   192,   198,   203,   209,   214,
     221,   227,   233,   240,   251,   261,   270,   281,   286,   293,
     302,   313,   319,   326,   331,   338,   343,   350,   351,   352,
     353,   354,   355,   358,   363
  };

  // Print the state stack on the debug stream.
  void
  SQLParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  SQLParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  SQLParser::token_number_type
  SQLParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,    44,     2,    39,     2,    43,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      42,    40,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
    };
    const unsigned int user_token_number_max_ = 290;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2241 "sqlparser.cpp" // lalr1.cc:1167
#line 370 "sqlparser.yy" // lalr1.cc:1168



void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
