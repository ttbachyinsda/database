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
#line 29 "sqlparser.yy" // lalr1.cc:413

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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        value.copy< SQLAction* > (other.value);
        break;

      case 61: // CheckClause
        value.copy< SQLCheck* > (other.value);
        break;

      case 62: // CheckClauseList
        value.copy< SQLCheckGroup* > (other.value);
        break;

      case 59: // WhereClause
        value.copy< SQLCondition* > (other.value);
        break;

      case 60: // WhereClauseList
        value.copy< SQLConditionGroup* > (other.value);
        break;

      case 67: // Operand
        value.copy< SQLOperand > (other.value);
        break;

      case 64: // Column
        value.copy< SQLSelector* > (other.value);
        break;

      case 65: // Selector
      case 66: // SelectorList
        value.copy< SQLSelectorGroup* > (other.value);
        break;

      case 63: // SetClause
        value.copy< SQLSetGroup* > (other.value);
        break;

      case 68: // TableList
        value.copy< SQLTableGroup* > (other.value);
        break;

      case 53: // Field
      case 54: // Type
        value.copy< SQLType* > (other.value);
        break;

      case 58: // Value
        value.copy< SQLValue* > (other.value);
        break;

      case 57: // ValueList
        value.copy< SQLValueGroup* > (other.value);
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        value.copy< std::string > (other.value);
        break;

      case 52: // FieldList
        value.copy< std::vector<SQLType*>* > (other.value);
        break;

      case 56: // ValueLists
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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        value.copy< SQLAction* > (v);
        break;

      case 61: // CheckClause
        value.copy< SQLCheck* > (v);
        break;

      case 62: // CheckClauseList
        value.copy< SQLCheckGroup* > (v);
        break;

      case 59: // WhereClause
        value.copy< SQLCondition* > (v);
        break;

      case 60: // WhereClauseList
        value.copy< SQLConditionGroup* > (v);
        break;

      case 67: // Operand
        value.copy< SQLOperand > (v);
        break;

      case 64: // Column
        value.copy< SQLSelector* > (v);
        break;

      case 65: // Selector
      case 66: // SelectorList
        value.copy< SQLSelectorGroup* > (v);
        break;

      case 63: // SetClause
        value.copy< SQLSetGroup* > (v);
        break;

      case 68: // TableList
        value.copy< SQLTableGroup* > (v);
        break;

      case 53: // Field
      case 54: // Type
        value.copy< SQLType* > (v);
        break;

      case 58: // Value
        value.copy< SQLValue* > (v);
        break;

      case 57: // ValueList
        value.copy< SQLValueGroup* > (v);
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        value.copy< std::string > (v);
        break;

      case 52: // FieldList
        value.copy< std::vector<SQLType*>* > (v);
        break;

      case 56: // ValueLists
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
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLCheck* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SQLCheckGroup* v, const location_type& l)
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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        value.template destroy< SQLAction* > ();
        break;

      case 61: // CheckClause
        value.template destroy< SQLCheck* > ();
        break;

      case 62: // CheckClauseList
        value.template destroy< SQLCheckGroup* > ();
        break;

      case 59: // WhereClause
        value.template destroy< SQLCondition* > ();
        break;

      case 60: // WhereClauseList
        value.template destroy< SQLConditionGroup* > ();
        break;

      case 67: // Operand
        value.template destroy< SQLOperand > ();
        break;

      case 64: // Column
        value.template destroy< SQLSelector* > ();
        break;

      case 65: // Selector
      case 66: // SelectorList
        value.template destroy< SQLSelectorGroup* > ();
        break;

      case 63: // SetClause
        value.template destroy< SQLSetGroup* > ();
        break;

      case 68: // TableList
        value.template destroy< SQLTableGroup* > ();
        break;

      case 53: // Field
      case 54: // Type
        value.template destroy< SQLType* > ();
        break;

      case 58: // Value
        value.template destroy< SQLValue* > ();
        break;

      case 57: // ValueList
        value.template destroy< SQLValueGroup* > ();
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        value.template destroy< std::string > ();
        break;

      case 52: // FieldList
        value.template destroy< std::vector<SQLType*>* > ();
        break;

      case 56: // ValueLists
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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        value.move< SQLAction* > (s.value);
        break;

      case 61: // CheckClause
        value.move< SQLCheck* > (s.value);
        break;

      case 62: // CheckClauseList
        value.move< SQLCheckGroup* > (s.value);
        break;

      case 59: // WhereClause
        value.move< SQLCondition* > (s.value);
        break;

      case 60: // WhereClauseList
        value.move< SQLConditionGroup* > (s.value);
        break;

      case 67: // Operand
        value.move< SQLOperand > (s.value);
        break;

      case 64: // Column
        value.move< SQLSelector* > (s.value);
        break;

      case 65: // Selector
      case 66: // SelectorList
        value.move< SQLSelectorGroup* > (s.value);
        break;

      case 63: // SetClause
        value.move< SQLSetGroup* > (s.value);
        break;

      case 68: // TableList
        value.move< SQLTableGroup* > (s.value);
        break;

      case 53: // Field
      case 54: // Type
        value.move< SQLType* > (s.value);
        break;

      case 58: // Value
        value.move< SQLValue* > (s.value);
        break;

      case 57: // ValueList
        value.move< SQLValueGroup* > (s.value);
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        value.move< std::string > (s.value);
        break;

      case 52: // FieldList
        value.move< std::vector<SQLType*>* > (s.value);
        break;

      case 56: // ValueLists
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
  SQLParser::make_CHECK (const location_type& l)
  {
    return symbol_type (token::CHECK, l);
  }

  SQLParser::symbol_type
  SQLParser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
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
  SQLParser::make_INDEX (const location_type& l)
  {
    return symbol_type (token::INDEX, l);
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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        value.move< SQLAction* > (that.value);
        break;

      case 61: // CheckClause
        value.move< SQLCheck* > (that.value);
        break;

      case 62: // CheckClauseList
        value.move< SQLCheckGroup* > (that.value);
        break;

      case 59: // WhereClause
        value.move< SQLCondition* > (that.value);
        break;

      case 60: // WhereClauseList
        value.move< SQLConditionGroup* > (that.value);
        break;

      case 67: // Operand
        value.move< SQLOperand > (that.value);
        break;

      case 64: // Column
        value.move< SQLSelector* > (that.value);
        break;

      case 65: // Selector
      case 66: // SelectorList
        value.move< SQLSelectorGroup* > (that.value);
        break;

      case 63: // SetClause
        value.move< SQLSetGroup* > (that.value);
        break;

      case 68: // TableList
        value.move< SQLTableGroup* > (that.value);
        break;

      case 53: // Field
      case 54: // Type
        value.move< SQLType* > (that.value);
        break;

      case 58: // Value
        value.move< SQLValue* > (that.value);
        break;

      case 57: // ValueList
        value.move< SQLValueGroup* > (that.value);
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        value.move< std::string > (that.value);
        break;

      case 52: // FieldList
        value.move< std::vector<SQLType*>* > (that.value);
        break;

      case 56: // ValueLists
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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        value.copy< SQLAction* > (that.value);
        break;

      case 61: // CheckClause
        value.copy< SQLCheck* > (that.value);
        break;

      case 62: // CheckClauseList
        value.copy< SQLCheckGroup* > (that.value);
        break;

      case 59: // WhereClause
        value.copy< SQLCondition* > (that.value);
        break;

      case 60: // WhereClauseList
        value.copy< SQLConditionGroup* > (that.value);
        break;

      case 67: // Operand
        value.copy< SQLOperand > (that.value);
        break;

      case 64: // Column
        value.copy< SQLSelector* > (that.value);
        break;

      case 65: // Selector
      case 66: // SelectorList
        value.copy< SQLSelectorGroup* > (that.value);
        break;

      case 63: // SetClause
        value.copy< SQLSetGroup* > (that.value);
        break;

      case 68: // TableList
        value.copy< SQLTableGroup* > (that.value);
        break;

      case 53: // Field
      case 54: // Type
        value.copy< SQLType* > (that.value);
        break;

      case 58: // Value
        value.copy< SQLValue* > (that.value);
        break;

      case 57: // ValueList
        value.copy< SQLValueGroup* > (that.value);
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        value.copy< std::string > (that.value);
        break;

      case 52: // FieldList
        value.copy< std::vector<SQLType*>* > (that.value);
        break;

      case 56: // ValueLists
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
      case 50: // Stmt
      case 51: // SysStmt
      case 55: // QueryStmt
        yylhs.value.build< SQLAction* > ();
        break;

      case 61: // CheckClause
        yylhs.value.build< SQLCheck* > ();
        break;

      case 62: // CheckClauseList
        yylhs.value.build< SQLCheckGroup* > ();
        break;

      case 59: // WhereClause
        yylhs.value.build< SQLCondition* > ();
        break;

      case 60: // WhereClauseList
        yylhs.value.build< SQLConditionGroup* > ();
        break;

      case 67: // Operand
        yylhs.value.build< SQLOperand > ();
        break;

      case 64: // Column
        yylhs.value.build< SQLSelector* > ();
        break;

      case 65: // Selector
      case 66: // SelectorList
        yylhs.value.build< SQLSelectorGroup* > ();
        break;

      case 63: // SetClause
        yylhs.value.build< SQLSetGroup* > ();
        break;

      case 68: // TableList
        yylhs.value.build< SQLTableGroup* > ();
        break;

      case 53: // Field
      case 54: // Type
        yylhs.value.build< SQLType* > ();
        break;

      case 58: // Value
        yylhs.value.build< SQLValue* > ();
        break;

      case 57: // ValueList
        yylhs.value.build< SQLValueGroup* > ();
        break;

      case 36: // IDENTIFIER
      case 37: // VALUE_STRING
      case 38: // VALUE_INT
        yylhs.value.build< std::string > ();
        break;

      case 52: // FieldList
        yylhs.value.build< std::vector<SQLType*>* > ();
        break;

      case 56: // ValueLists
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
#line 82 "sqlparser.yy" // lalr1.cc:859
    {
                    driver.addAction(yystack_[0].value.as< SQLAction* > ());
                }
#line 1456 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 88 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1464 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 92 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1472 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 98 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1480 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 102 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1488 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 106 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowDatabasesAction();
                }
#line 1496 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 110 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLUseDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1504 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 114 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowTablesAction();
                }
#line 1512 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 118 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateTableAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<SQLType*>* > ());
                }
#line 1520 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 122 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropTableAction(yystack_[0].value.as< std::string > ());
                }
#line 1528 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 126 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDescAction(yystack_[0].value.as< std::string > ());
                }
#line 1536 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 130 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateIndexAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::string > ());
                }
#line 1544 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 134 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropIndexAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::string > ());
                }
#line 1552 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 140 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = new std::vector<SQLType*>();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1561 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 145 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = yystack_[2].value.as< std::vector<SQLType*>* > ();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1570 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 152 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[0].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                }
#line 1579 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 157 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[2].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[3].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->canNull = false;
                }
#line 1589 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 163 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->primaryType = true;
                }
#line 1599 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 169 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->isCheck = true;
                    yylhs.value.as< SQLType* > ()->checkGroup = yystack_[1].value.as< SQLCheckGroup* > ();
                }
#line 1609 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 177 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::INT;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1619 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 183 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::CHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1629 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 189 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::VARCHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1639 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 197 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLInsertAction(yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::vector<SQLValueGroup*>* > ());
                }
#line 1647 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 201 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDeleteAction(yystack_[2].value.as< std::string > (), yystack_[0].value.as< SQLConditionGroup* > ());
                }
#line 1655 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 205 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLUpdateAction(yystack_[4].value.as< std::string > (), yystack_[0].value.as< SQLConditionGroup* > (), yystack_[2].value.as< SQLSetGroup* > ());
                }
#line 1663 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 209 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLSelectAction(yystack_[2].value.as< SQLTableGroup* > (), yystack_[4].value.as< SQLSelectorGroup* > (), yystack_[0].value.as< SQLConditionGroup* > ());
                }
#line 1671 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 215 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLValueGroup*>* > () = new std::vector<SQLValueGroup*>();
                    yylhs.value.as< std::vector<SQLValueGroup*>* > ()->push_back(yystack_[1].value.as< SQLValueGroup* > ());
                }
#line 1680 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 220 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLValueGroup*>* > () = yystack_[4].value.as< std::vector<SQLValueGroup*>* > ();
                    yylhs.value.as< std::vector<SQLValueGroup*>* > ()->push_back(yystack_[1].value.as< SQLValueGroup* > ());
                }
#line 1689 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 226 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValueGroup* > () = new SQLValueGroup();
                    yylhs.value.as< SQLValueGroup* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1698 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 231 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValueGroup* > () = yystack_[2].value.as< SQLValueGroup* > ();
                    yylhs.value.as< SQLValueGroup* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1707 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 238 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::ENUMERATE;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1717 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 244 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::STRING;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1727 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 250 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::NUL;
                }
#line 1736 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 257 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::COLUMN;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    yylhs.value.as< SQLCondition* > ()->rValueColumn = *(yystack_[0].value.as< SQLSelector* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    delete yystack_[0].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->operand = yystack_[1].value.as< SQLOperand > ();

                }
#line 1751 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 268 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    yylhs.value.as< SQLCondition* > ()->rValue = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLCondition* > ()->operand = yystack_[1].value.as< SQLOperand > ();
                }
#line 1765 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 278 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->operand = SQLOperand::EQUAL;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->rValue.type = SQLValue::NUL;
                }
#line 1778 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 287 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->operand = SQLOperand::NOT_EQUAL;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[3].value.as< SQLSelector* > ());
                    delete yystack_[3].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->rValue.type = SQLValue::NUL;
                }
#line 1791 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 298 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLConditionGroup* > () = new SQLConditionGroup();
                    yylhs.value.as< SQLConditionGroup* > ()->push_back(yystack_[0].value.as< SQLCondition* > ());
                }
#line 1800 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 303 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLConditionGroup* > () = yystack_[2].value.as< SQLConditionGroup* > ();
                    yylhs.value.as< SQLConditionGroup* > ()->push_back(yystack_[0].value.as< SQLCondition* > ());
                }
#line 1809 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 310 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCheck* > () = new SQLCheck();
                    yylhs.value.as< SQLCheck* > ()->isChoice = true;
                    yylhs.value.as< SQLCheck* > ()->choiceList = yystack_[1].value.as< SQLValueGroup* > ();
                }
#line 1819 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 316 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCheck* > () = new SQLCheck();
                    yylhs.value.as< SQLCheck* > ()->isChoice = false;
                    yylhs.value.as< SQLCheck* > ()->operand = yystack_[1].value.as< SQLOperand > ();
                    yylhs.value.as< SQLCheck* > ()->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                }
#line 1831 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 326 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCheckGroup* > () = new SQLCheckGroup();
                    yylhs.value.as< SQLCheckGroup* > ()->push_back(yystack_[0].value.as< SQLCheck* > ());
                }
#line 1840 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 331 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLCheckGroup* > () = yystack_[2].value.as< SQLCheckGroup* > ();
                    yylhs.value.as< SQLCheckGroup* > ()->push_back(yystack_[0].value.as< SQLCheck* > ());
                }
#line 1849 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 338 "sqlparser.yy" // lalr1.cc:859
    {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = yystack_[2].value.as< std::string > ();
                    thisValue->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLSetGroup* > () = new SQLSetGroup();
                    yylhs.value.as< SQLSetGroup* > ()->push_back(thisValue);
                }
#line 1862 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 347 "sqlparser.yy" // lalr1.cc:859
    {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = yystack_[2].value.as< std::string > ();
                    thisValue->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLSetGroup* > () = yystack_[4].value.as< SQLSetGroup* > ();
                    yylhs.value.as< SQLSetGroup* > ()->push_back(thisValue);
                }
#line 1875 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 358 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelector* > () = new SQLSelector();
                    yylhs.value.as< SQLSelector* > ()->databaseName = yystack_[2].value.as< std::string > ();
                    yylhs.value.as< SQLSelector* > ()->tableName = yystack_[0].value.as< std::string > ();
                }
#line 1885 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 364 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelector* > () = new SQLSelector();
                    yylhs.value.as< SQLSelector* > ()->tableName = yystack_[0].value.as< std::string > ();
                }
#line 1894 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 371 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = new SQLSelectorGroup();
                    yylhs.value.as< SQLSelectorGroup* > ()->allMatched = true;
                }
#line 1903 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 376 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = yystack_[0].value.as< SQLSelectorGroup* > ();
                    yylhs.value.as< SQLSelectorGroup* > ()->allMatched = false;
                }
#line 1912 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 383 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = new SQLSelectorGroup();
                    yylhs.value.as< SQLSelectorGroup* > ()->selectors.push_back(yystack_[0].value.as< SQLSelector* > ());
                }
#line 1921 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 388 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLSelectorGroup* > () = yystack_[2].value.as< SQLSelectorGroup* > ();
                    yylhs.value.as< SQLSelectorGroup* > ()->selectors.push_back(yystack_[0].value.as< SQLSelector* > ());
                }
#line 1930 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 394 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::EQUAL;         }
#line 1936 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 395 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::NOT_EQUAL;     }
#line 1942 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 396 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::LESS;          }
#line 1948 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 397 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::GREATER;       }
#line 1954 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 398 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::LESS_EQUAL;    }
#line 1960 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 399 "sqlparser.yy" // lalr1.cc:859
    { yylhs.value.as< SQLOperand > () = SQLOperand::GREATER_EQUAL; }
#line 1966 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 403 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLTableGroup* > () = new SQLTableGroup();
                    yylhs.value.as< SQLTableGroup* > ()->push_back(yystack_[0].value.as< std::string > ());
                }
#line 1975 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 408 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLTableGroup* > () = yystack_[2].value.as< SQLTableGroup* > ();
                    yylhs.value.as< SQLTableGroup* > ()->push_back(yystack_[0].value.as< std::string > ());
                }
#line 1984 "sqlparser.cpp" // lalr1.cc:859
    break;


#line 1988 "sqlparser.cpp" // lalr1.cc:859
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


  const signed char SQLParser::yypact_ninf_ = -114;

  const signed char SQLParser::yytable_ninf_ = -1;

  const signed char
  SQLParser::yypact_[] =
  {
    -114,     2,  -114,    12,    13,     5,   -18,    -5,    20,    40,
      44,   -21,  -114,    24,    42,    46,    47,    48,    49,    50,
      51,  -114,  -114,  -114,  -114,    53,    54,    63,    52,  -114,
    -114,    66,    55,  -114,  -114,  -114,    56,    59,  -114,  -114,
      60,    69,    65,    67,    68,    70,    71,    41,    72,    73,
      61,    71,    62,   -25,  -114,  -114,    25,  -114,    76,    74,
      -2,    27,  -114,    75,    77,    -4,    78,  -114,    79,     4,
      -4,    71,    81,    71,    83,    82,    71,    84,    85,    86,
      95,  -114,    41,  -114,  -114,  -114,  -114,  -114,    30,  -114,
      87,    71,    57,  -114,  -114,  -114,  -114,  -114,  -114,    19,
    -114,    79,    80,    79,  -114,    92,  -114,    29,     7,    64,
      91,    93,    98,  -114,  -114,    -4,    -4,  -114,   104,  -114,
    -114,  -114,    -4,    89,    71,  -114,    94,    -4,    96,    97,
      99,  -114,  -114,    34,  -114,  -114,  -114,  -114,    -4,  -114,
    -114,  -114,  -114,  -114,    37,  -114
  };

  const unsigned char
  SQLParser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     8,    10,     9,    13,     0,     0,     0,    49,    50,
      52,     0,    51,     4,     5,     6,     0,     0,     7,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,    60,     0,    53,     0,     0,
       0,     0,    16,     0,     0,     0,    25,    40,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    11,     0,    14,    15,    35,    34,    33,     0,    31,
       0,     0,     0,    55,    59,    58,    54,    57,    56,     0,
      46,    27,     0,    28,    61,     0,    44,     0,     0,     0,
       0,     0,     0,    17,    29,     0,     0,    41,     0,    38,
      37,    36,     0,     0,     0,    21,     0,     0,     0,     0,
       0,    19,    32,     0,    39,    47,    20,    45,     0,    43,
      22,    24,    23,    30,     0,    42
  };

  const signed char
  SQLParser::yypgoto_[] =
  {
    -114,  -114,  -114,  -114,  -114,    88,  -114,  -114,  -114,  -113,
     -69,    21,    -9,     8,  -114,  -114,   -11,  -114,  -114,    28,
    -114
  };

  const signed char
  SQLParser::yydefgoto_[] =
  {
      -1,     1,    12,    13,    61,    62,    80,    14,    66,    88,
      89,    67,    68,   106,   107,    53,    69,    31,    32,    99,
      56
  };

  const unsigned char
  SQLParser::yytable_[] =
  {
      30,   100,     2,   133,    71,     3,     4,     5,     6,     7,
      77,    78,    79,    85,    21,    28,    22,    72,    23,    92,
      15,    18,    16,    19,     8,   144,    29,     9,   126,    10,
     120,    24,    11,    86,    87,    57,    85,    93,    94,    95,
      93,    94,    95,    25,    17,    20,   132,    96,    97,    98,
      96,    97,    98,   135,    73,    28,    86,    87,   139,    58,
     124,    59,   101,    33,   103,   108,    26,    74,    81,    82,
     125,   114,   115,   118,   119,   143,   115,    60,   145,   115,
      27,    34,    35,    36,    37,    38,    39,    40,   121,    41,
      42,    43,    45,    50,    51,    75,    47,    46,    44,    48,
      49,    65,   128,    52,    54,    70,    55,    28,    63,    64,
      91,   112,   117,   108,    76,   131,    83,   102,    84,   104,
      90,   134,   105,   122,   109,   110,   111,   116,   123,   129,
     136,   130,   137,     0,   138,     0,   127,   140,   141,     0,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113
  };

  const short int
  SQLParser::yycheck_[] =
  {
      11,    70,     0,   116,    29,     3,     4,     5,     6,     7,
      12,    13,    14,    17,     9,    36,    11,    42,    36,    15,
       8,     8,    10,    10,    22,   138,    47,    25,    21,    27,
      99,    36,    30,    37,    38,    46,    17,    33,    34,    35,
      33,    34,    35,    23,    32,    32,   115,    43,    44,    45,
      43,    44,    45,   122,    29,    36,    37,    38,   127,    18,
      31,    20,    71,    39,    73,    76,    26,    42,    41,    42,
      41,    41,    42,    16,    17,    41,    42,    36,    41,    42,
      36,    39,    36,    36,    36,    36,    36,    36,    99,    36,
      36,    28,    26,    24,    29,    19,    40,    42,    46,    40,
      40,    40,    38,    36,    36,    43,    36,    36,    36,    36,
      31,    16,    91,   124,    40,    17,    41,    36,    41,    36,
      42,    17,    40,    43,    40,    40,    40,    40,    36,    38,
      41,    38,   124,    -1,    40,    -1,   108,    41,    41,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82
  };

  const unsigned char
  SQLParser::yystos_[] =
  {
       0,    49,     0,     3,     4,     5,     6,     7,    22,    25,
      27,    30,    50,    51,    55,     8,    10,    32,     8,    10,
      32,     9,    11,    36,    36,    23,    26,    36,    36,    47,
      64,    65,    66,    39,    39,    36,    36,    36,    36,    36,
      36,    36,    36,    28,    46,    26,    42,    40,    40,    40,
      24,    29,    36,    63,    36,    36,    68,    64,    18,    20,
      36,    52,    53,    36,    36,    40,    56,    59,    60,    64,
      43,    29,    42,    29,    42,    19,    40,    12,    13,    14,
      54,    41,    42,    41,    41,    17,    37,    38,    57,    58,
      42,    31,    15,    33,    34,    35,    43,    44,    45,    67,
      58,    60,    36,    60,    36,    40,    61,    62,    64,    40,
      40,    40,    16,    53,    41,    42,    40,    59,    16,    17,
      58,    64,    43,    36,    31,    41,    21,    67,    38,    38,
      38,    17,    58,    57,    17,    58,    41,    61,    40,    58,
      41,    41,    41,    41,    57,    41
  };

  const unsigned char
  SQLParser::yyr1_[] =
  {
       0,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    52,    52,    53,    53,
      53,    53,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    59,    59,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      68,    68
  };

  const unsigned char
  SQLParser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     3,     2,     2,
       2,     6,     3,     2,     6,     6,     1,     3,     2,     4,
       5,     4,     4,     4,     4,     5,     5,     6,     6,     3,
       5,     1,     3,     1,     1,     1,     3,     3,     3,     4,
       1,     3,     5,     3,     1,     3,     3,     5,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SQLParser::yytname_[] =
  {
  "$end", "error", "$undefined", "CREATE", "DROP", "SHOW", "USE", "DESC",
  "DATABASE", "DATABASES", "TABLE", "TABLES", "INT", "VARCHAR", "CHAR",
  "IS", "NOT", "NUL", "PRIMARY", "KEY", "CHECK", "IN", "INSERT", "INTO",
  "VALUES", "DELETE", "FROM", "UPDATE", "SET", "WHERE", "SELECT", "AND",
  "INDEX", "NOT_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", "IDENTIFIER",
  "VALUE_STRING", "VALUE_INT", "';'", "'('", "')'", "','", "'='", "'>'",
  "'<'", "'.'", "'*'", "$accept", "Program", "Stmt", "SysStmt",
  "FieldList", "Field", "Type", "QueryStmt", "ValueLists", "ValueList",
  "Value", "WhereClause", "WhereClauseList", "CheckClause",
  "CheckClauseList", "SetClause", "Column", "Selector", "SelectorList",
  "Operand", "TableList", YY_NULLPTR
  };


  const unsigned short int
  SQLParser::yyrline_[] =
  {
       0,    80,    80,    81,    87,    91,    97,   101,   105,   109,
     113,   117,   121,   125,   129,   133,   139,   144,   151,   156,
     162,   168,   176,   182,   188,   196,   200,   204,   208,   214,
     219,   225,   230,   237,   243,   249,   256,   267,   277,   286,
     297,   302,   309,   315,   325,   330,   337,   346,   357,   363,
     370,   375,   382,   387,   394,   395,   396,   397,   398,   399,
     402,   407
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
      40,    41,    47,     2,    42,     2,    46,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
      45,    43,    44,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38
    };
    const unsigned int user_token_number_max_ = 293;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2419 "sqlparser.cpp" // lalr1.cc:1167
#line 414 "sqlparser.yy" // lalr1.cc:1168



void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
