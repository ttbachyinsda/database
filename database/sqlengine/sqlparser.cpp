// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

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

#line 37 "sqlparser.cpp" // lalr1.cc:398

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "sqlparser.hpp"

// User implementation prologue.

#line 51 "sqlparser.cpp" // lalr1.cc:406
// Unqualified %code blocks.
#line 30 "sqlparser.yy" // lalr1.cc:407

   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "sqldriver.h"

#undef yylex
#define yylex scanner.yylex

#line 65 "sqlparser.cpp" // lalr1.cc:407


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
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 151 "sqlparser.cpp" // lalr1.cc:473

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
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        value.copy< SQLAction* > (other.value);
        break;

      case 60: // CheckClause
        value.copy< SQLCheck* > (other.value);
        break;

      case 61: // CheckClauseList
        value.copy< SQLCheckGroup* > (other.value);
        break;

      case 58: // WhereClause
        value.copy< SQLCondition* > (other.value);
        break;

      case 59: // WhereClauseList
        value.copy< SQLConditionGroup* > (other.value);
        break;

      case 66: // Operand
        value.copy< SQLOperand > (other.value);
        break;

      case 63: // Column
        value.copy< SQLSelector* > (other.value);
        break;

      case 64: // Selector
      case 65: // SelectorList
        value.copy< SQLSelectorGroup* > (other.value);
        break;

      case 62: // SetClause
        value.copy< SQLSetGroup* > (other.value);
        break;

      case 67: // TableList
        value.copy< SQLTableGroup* > (other.value);
        break;

      case 52: // Field
      case 53: // Type
        value.copy< SQLType* > (other.value);
        break;

      case 57: // Value
        value.copy< SQLValue* > (other.value);
        break;

      case 56: // ValueList
        value.copy< SQLValueGroup* > (other.value);
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        value.copy< std::string > (other.value);
        break;

      case 51: // FieldList
        value.copy< std::vector<SQLType*>* > (other.value);
        break;

      case 55: // ValueLists
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
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        value.copy< SQLAction* > (v);
        break;

      case 60: // CheckClause
        value.copy< SQLCheck* > (v);
        break;

      case 61: // CheckClauseList
        value.copy< SQLCheckGroup* > (v);
        break;

      case 58: // WhereClause
        value.copy< SQLCondition* > (v);
        break;

      case 59: // WhereClauseList
        value.copy< SQLConditionGroup* > (v);
        break;

      case 66: // Operand
        value.copy< SQLOperand > (v);
        break;

      case 63: // Column
        value.copy< SQLSelector* > (v);
        break;

      case 64: // Selector
      case 65: // SelectorList
        value.copy< SQLSelectorGroup* > (v);
        break;

      case 62: // SetClause
        value.copy< SQLSetGroup* > (v);
        break;

      case 67: // TableList
        value.copy< SQLTableGroup* > (v);
        break;

      case 52: // Field
      case 53: // Type
        value.copy< SQLType* > (v);
        break;

      case 57: // Value
        value.copy< SQLValue* > (v);
        break;

      case 56: // ValueList
        value.copy< SQLValueGroup* > (v);
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        value.copy< std::string > (v);
        break;

      case 51: // FieldList
        value.copy< std::vector<SQLType*>* > (v);
        break;

      case 55: // ValueLists
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
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        value.template destroy< SQLAction* > ();
        break;

      case 60: // CheckClause
        value.template destroy< SQLCheck* > ();
        break;

      case 61: // CheckClauseList
        value.template destroy< SQLCheckGroup* > ();
        break;

      case 58: // WhereClause
        value.template destroy< SQLCondition* > ();
        break;

      case 59: // WhereClauseList
        value.template destroy< SQLConditionGroup* > ();
        break;

      case 66: // Operand
        value.template destroy< SQLOperand > ();
        break;

      case 63: // Column
        value.template destroy< SQLSelector* > ();
        break;

      case 64: // Selector
      case 65: // SelectorList
        value.template destroy< SQLSelectorGroup* > ();
        break;

      case 62: // SetClause
        value.template destroy< SQLSetGroup* > ();
        break;

      case 67: // TableList
        value.template destroy< SQLTableGroup* > ();
        break;

      case 52: // Field
      case 53: // Type
        value.template destroy< SQLType* > ();
        break;

      case 57: // Value
        value.template destroy< SQLValue* > ();
        break;

      case 56: // ValueList
        value.template destroy< SQLValueGroup* > ();
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        value.template destroy< std::string > ();
        break;

      case 51: // FieldList
        value.template destroy< std::vector<SQLType*>* > ();
        break;

      case 55: // ValueLists
        value.template destroy< std::vector<SQLValueGroup*>* > ();
        break;

      default:
        break;
    }

  }

  template <typename Base>
  inline
  void
  SQLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        value.move< SQLAction* > (s.value);
        break;

      case 60: // CheckClause
        value.move< SQLCheck* > (s.value);
        break;

      case 61: // CheckClauseList
        value.move< SQLCheckGroup* > (s.value);
        break;

      case 58: // WhereClause
        value.move< SQLCondition* > (s.value);
        break;

      case 59: // WhereClauseList
        value.move< SQLConditionGroup* > (s.value);
        break;

      case 66: // Operand
        value.move< SQLOperand > (s.value);
        break;

      case 63: // Column
        value.move< SQLSelector* > (s.value);
        break;

      case 64: // Selector
      case 65: // SelectorList
        value.move< SQLSelectorGroup* > (s.value);
        break;

      case 62: // SetClause
        value.move< SQLSetGroup* > (s.value);
        break;

      case 67: // TableList
        value.move< SQLTableGroup* > (s.value);
        break;

      case 52: // Field
      case 53: // Type
        value.move< SQLType* > (s.value);
        break;

      case 57: // Value
        value.move< SQLValue* > (s.value);
        break;

      case 56: // ValueList
        value.move< SQLValueGroup* > (s.value);
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        value.move< std::string > (s.value);
        break;

      case 51: // FieldList
        value.move< std::vector<SQLType*>* > (s.value);
        break;

      case 55: // ValueLists
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
     : type (empty)
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
  SQLParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
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
    : state (empty)
  {}

  inline
  SQLParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  SQLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  SQLParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  SQLParser::symbol_number_type
  SQLParser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
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
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        value.move< SQLAction* > (that.value);
        break;

      case 60: // CheckClause
        value.move< SQLCheck* > (that.value);
        break;

      case 61: // CheckClauseList
        value.move< SQLCheckGroup* > (that.value);
        break;

      case 58: // WhereClause
        value.move< SQLCondition* > (that.value);
        break;

      case 59: // WhereClauseList
        value.move< SQLConditionGroup* > (that.value);
        break;

      case 66: // Operand
        value.move< SQLOperand > (that.value);
        break;

      case 63: // Column
        value.move< SQLSelector* > (that.value);
        break;

      case 64: // Selector
      case 65: // SelectorList
        value.move< SQLSelectorGroup* > (that.value);
        break;

      case 62: // SetClause
        value.move< SQLSetGroup* > (that.value);
        break;

      case 67: // TableList
        value.move< SQLTableGroup* > (that.value);
        break;

      case 52: // Field
      case 53: // Type
        value.move< SQLType* > (that.value);
        break;

      case 57: // Value
        value.move< SQLValue* > (that.value);
        break;

      case 56: // ValueList
        value.move< SQLValueGroup* > (that.value);
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        value.move< std::string > (that.value);
        break;

      case 51: // FieldList
        value.move< std::vector<SQLType*>* > (that.value);
        break;

      case 55: // ValueLists
        value.move< std::vector<SQLValueGroup*>* > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty;
  }

  inline
  SQLParser::stack_symbol_type&
  SQLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        value.copy< SQLAction* > (that.value);
        break;

      case 60: // CheckClause
        value.copy< SQLCheck* > (that.value);
        break;

      case 61: // CheckClauseList
        value.copy< SQLCheckGroup* > (that.value);
        break;

      case 58: // WhereClause
        value.copy< SQLCondition* > (that.value);
        break;

      case 59: // WhereClauseList
        value.copy< SQLConditionGroup* > (that.value);
        break;

      case 66: // Operand
        value.copy< SQLOperand > (that.value);
        break;

      case 63: // Column
        value.copy< SQLSelector* > (that.value);
        break;

      case 64: // Selector
      case 65: // SelectorList
        value.copy< SQLSelectorGroup* > (that.value);
        break;

      case 62: // SetClause
        value.copy< SQLSetGroup* > (that.value);
        break;

      case 67: // TableList
        value.copy< SQLTableGroup* > (that.value);
        break;

      case 52: // Field
      case 53: // Type
        value.copy< SQLType* > (that.value);
        break;

      case 57: // Value
        value.copy< SQLValue* > (that.value);
        break;

      case 56: // ValueList
        value.copy< SQLValueGroup* > (that.value);
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        value.copy< std::string > (that.value);
        break;

      case 51: // FieldList
        value.copy< std::vector<SQLType*>* > (that.value);
        break;

      case 55: // ValueLists
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
  SQLParser::yy_lr_goto_state_ (state_type yystate, int yylhs)
  {
    int yyr = yypgoto_[yylhs - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yylhs - yyntokens_];
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
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// $$ and @$.
    stack_symbol_type yylhs;

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
    yypush_ (YY_NULL, 0, yyla);

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
    if (yyempty)
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
        yyempty = false;
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

    // Discard the token being shifted.
    yyempty = true;

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
    yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
    /* Variants are always initialized to an empty instance of the
       correct type. The default $$=$1 action is NOT applied when using
       variants.  */
      switch (yyr1_[yyn])
    {
      case 49: // Stmt
      case 50: // SysStmt
      case 54: // QueryStmt
        yylhs.value.build< SQLAction* > ();
        break;

      case 60: // CheckClause
        yylhs.value.build< SQLCheck* > ();
        break;

      case 61: // CheckClauseList
        yylhs.value.build< SQLCheckGroup* > ();
        break;

      case 58: // WhereClause
        yylhs.value.build< SQLCondition* > ();
        break;

      case 59: // WhereClauseList
        yylhs.value.build< SQLConditionGroup* > ();
        break;

      case 66: // Operand
        yylhs.value.build< SQLOperand > ();
        break;

      case 63: // Column
        yylhs.value.build< SQLSelector* > ();
        break;

      case 64: // Selector
      case 65: // SelectorList
        yylhs.value.build< SQLSelectorGroup* > ();
        break;

      case 62: // SetClause
        yylhs.value.build< SQLSetGroup* > ();
        break;

      case 67: // TableList
        yylhs.value.build< SQLTableGroup* > ();
        break;

      case 52: // Field
      case 53: // Type
        yylhs.value.build< SQLType* > ();
        break;

      case 57: // Value
        yylhs.value.build< SQLValue* > ();
        break;

      case 56: // ValueList
        yylhs.value.build< SQLValueGroup* > ();
        break;

      case 35: // IDENTIFIER
      case 36: // VALUE_STRING
      case 37: // VALUE_INT
        yylhs.value.build< std::string > ();
        break;

      case 51: // FieldList
        yylhs.value.build< std::vector<SQLType*>* > ();
        break;

      case 55: // ValueLists
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
#line 83 "sqlparser.yy" // lalr1.cc:846
    {
                    driver.addAction(yystack_[0].value.as< SQLAction* > ());
                }
#line 1452 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 4:
#line 89 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1460 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 5:
#line 93 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1468 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 6:
#line 99 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1476 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 7:
#line 103 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1484 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 8:
#line 107 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowDatabasesAction();
                }
#line 1492 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 9:
#line 111 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLUseDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1500 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 10:
#line 115 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowTablesAction();
                }
#line 1508 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 11:
#line 119 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateTableAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<SQLType*>* > ());
                }
#line 1516 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 12:
#line 123 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropTableAction(yystack_[0].value.as< std::string > ());
                }
#line 1524 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 13:
#line 127 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLDescAction(yystack_[0].value.as< std::string > ());
                }
#line 1532 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 14:
#line 133 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = new std::vector<SQLType*>();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1541 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 15:
#line 138 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = yystack_[2].value.as< std::vector<SQLType*>* > ();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1550 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 16:
#line 145 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = yystack_[0].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                }
#line 1559 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 17:
#line 150 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = yystack_[2].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[3].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->canNull = false;
                }
#line 1569 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 18:
#line 156 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->primaryType = true;
                }
#line 1579 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 19:
#line 162 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->isCheck = true;
                    yylhs.value.as< SQLType* > ()->checkGroup = yystack_[1].value.as< SQLCheckGroup* > ();
                }
#line 1589 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 20:
#line 170 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::INT;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1599 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 21:
#line 176 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::CHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1609 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 22:
#line 182 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::VARCHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1619 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 23:
#line 190 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLInsertAction(yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::vector<SQLValueGroup*>* > ());
                }
#line 1627 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 24:
#line 194 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLDeleteAction(yystack_[2].value.as< std::string > (), yystack_[0].value.as< SQLConditionGroup* > ());
                }
#line 1635 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 25:
#line 198 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLUpdateAction(yystack_[4].value.as< std::string > (), yystack_[0].value.as< SQLConditionGroup* > (), yystack_[2].value.as< SQLSetGroup* > ());
                }
#line 1643 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 26:
#line 202 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLAction* > () = new SQLSelectAction(yystack_[2].value.as< SQLTableGroup* > (), yystack_[4].value.as< SQLSelectorGroup* > (), yystack_[0].value.as< SQLConditionGroup* > ());
                }
#line 1651 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 27:
#line 208 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< std::vector<SQLValueGroup*>* > () = new std::vector<SQLValueGroup*>();
                    yylhs.value.as< std::vector<SQLValueGroup*>* > ()->push_back(yystack_[1].value.as< SQLValueGroup* > ());
                }
#line 1660 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 28:
#line 213 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< std::vector<SQLValueGroup*>* > () = yystack_[4].value.as< std::vector<SQLValueGroup*>* > ();
                    yylhs.value.as< std::vector<SQLValueGroup*>* > ()->push_back(yystack_[1].value.as< SQLValueGroup* > ());
                }
#line 1669 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 29:
#line 219 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLValueGroup* > () = new SQLValueGroup();
                    yylhs.value.as< SQLValueGroup* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1678 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 30:
#line 224 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLValueGroup* > () = yystack_[2].value.as< SQLValueGroup* > ();
                    yylhs.value.as< SQLValueGroup* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1687 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 31:
#line 231 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::ENUMERATE;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1697 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 32:
#line 237 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::STRING;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1707 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 33:
#line 243 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::NUL;
                }
#line 1716 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 34:
#line 250 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::COLUMN;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    yylhs.value.as< SQLCondition* > ()->rValueColumn = *(yystack_[0].value.as< SQLSelector* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    delete yystack_[0].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->operand = yystack_[1].value.as< SQLOperand > ();

                }
#line 1731 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 35:
#line 261 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    yylhs.value.as< SQLCondition* > ()->rValue = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLCondition* > ()->operand = yystack_[1].value.as< SQLOperand > ();
                }
#line 1745 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 36:
#line 271 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->operand = SQLOperand::EQUAL;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[2].value.as< SQLSelector* > ());
                    delete yystack_[2].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->rValue.type = SQLValue::NUL;
                }
#line 1758 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 37:
#line 280 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCondition* > () = new SQLCondition();
                    yylhs.value.as< SQLCondition* > ()->type = SQLCondition::VALUE;
                    yylhs.value.as< SQLCondition* > ()->operand = SQLOperand::NOT_EQUAL;
                    yylhs.value.as< SQLCondition* > ()->lValue = *(yystack_[3].value.as< SQLSelector* > ());
                    delete yystack_[3].value.as< SQLSelector* > ();
                    yylhs.value.as< SQLCondition* > ()->rValue.type = SQLValue::NUL;
                }
#line 1771 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 38:
#line 291 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLConditionGroup* > () = new SQLConditionGroup();
                    yylhs.value.as< SQLConditionGroup* > ()->push_back(yystack_[0].value.as< SQLCondition* > ());
                }
#line 1780 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 39:
#line 296 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLConditionGroup* > () = yystack_[2].value.as< SQLConditionGroup* > ();
                    yylhs.value.as< SQLConditionGroup* > ()->push_back(yystack_[0].value.as< SQLCondition* > ());
                }
#line 1789 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 40:
#line 303 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCheck* > () = new SQLCheck();
                    yylhs.value.as< SQLCheck* > ()->isChoice = true;
                    yylhs.value.as< SQLCheck* > ()->choiceList = yystack_[1].value.as< SQLValueGroup* > ();
                }
#line 1799 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 41:
#line 309 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCheck* > () = new SQLCheck();
                    yylhs.value.as< SQLCheck* > ()->isChoice = false;
                    yylhs.value.as< SQLCheck* > ()->operand = yystack_[1].value.as< SQLOperand > ();
                    yylhs.value.as< SQLCheck* > ()->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                }
#line 1811 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 42:
#line 319 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCheckGroup* > () = new SQLCheckGroup();
                    yylhs.value.as< SQLCheckGroup* > ()->push_back(yystack_[0].value.as< SQLCheck* > ());
                }
#line 1820 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 43:
#line 324 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLCheckGroup* > () = yystack_[2].value.as< SQLCheckGroup* > ();
                    yylhs.value.as< SQLCheckGroup* > ()->push_back(yystack_[0].value.as< SQLCheck* > ());
                }
#line 1829 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 44:
#line 331 "sqlparser.yy" // lalr1.cc:846
    {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = yystack_[2].value.as< std::string > ();
                    thisValue->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLSetGroup* > () = new SQLSetGroup();
                    yylhs.value.as< SQLSetGroup* > ()->push_back(thisValue);
                }
#line 1842 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 45:
#line 340 "sqlparser.yy" // lalr1.cc:846
    {
                    SQLSet* thisValue = new SQLSet();
                    thisValue->identifier = yystack_[2].value.as< std::string > ();
                    thisValue->value = *(yystack_[0].value.as< SQLValue* > ());
                    delete yystack_[0].value.as< SQLValue* > ();
                    yylhs.value.as< SQLSetGroup* > () = yystack_[4].value.as< SQLSetGroup* > ();
                    yylhs.value.as< SQLSetGroup* > ()->push_back(thisValue);
                }
#line 1855 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 46:
#line 351 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLSelector* > () = new SQLSelector();
                    yylhs.value.as< SQLSelector* > ()->databaseName = yystack_[2].value.as< std::string > ();
                    yylhs.value.as< SQLSelector* > ()->tableName = yystack_[0].value.as< std::string > ();
                }
#line 1865 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 47:
#line 357 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLSelector* > () = new SQLSelector();
                    yylhs.value.as< SQLSelector* > ()->tableName = yystack_[0].value.as< std::string > ();
                }
#line 1874 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 48:
#line 364 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLSelectorGroup* > () = new SQLSelectorGroup();
                    yylhs.value.as< SQLSelectorGroup* > ()->allMatched = true;
                }
#line 1883 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 49:
#line 369 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLSelectorGroup* > () = yystack_[0].value.as< SQLSelectorGroup* > ();
                    yylhs.value.as< SQLSelectorGroup* > ()->allMatched = false;
                }
#line 1892 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 50:
#line 376 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLSelectorGroup* > () = new SQLSelectorGroup();
                    yylhs.value.as< SQLSelectorGroup* > ()->selectors.push_back(yystack_[0].value.as< SQLSelector* > ());
                }
#line 1901 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 51:
#line 381 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLSelectorGroup* > () = yystack_[2].value.as< SQLSelectorGroup* > ();
                    yylhs.value.as< SQLSelectorGroup* > ()->selectors.push_back(yystack_[0].value.as< SQLSelector* > ());
                }
#line 1910 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 52:
#line 387 "sqlparser.yy" // lalr1.cc:846
    { yylhs.value.as< SQLOperand > () = SQLOperand::EQUAL;         }
#line 1916 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 53:
#line 388 "sqlparser.yy" // lalr1.cc:846
    { yylhs.value.as< SQLOperand > () = SQLOperand::NOT_EQUAL;     }
#line 1922 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 54:
#line 389 "sqlparser.yy" // lalr1.cc:846
    { yylhs.value.as< SQLOperand > () = SQLOperand::LESS;          }
#line 1928 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 55:
#line 390 "sqlparser.yy" // lalr1.cc:846
    { yylhs.value.as< SQLOperand > () = SQLOperand::GREATER;       }
#line 1934 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 56:
#line 391 "sqlparser.yy" // lalr1.cc:846
    { yylhs.value.as< SQLOperand > () = SQLOperand::LESS_EQUAL;    }
#line 1940 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 57:
#line 392 "sqlparser.yy" // lalr1.cc:846
    { yylhs.value.as< SQLOperand > () = SQLOperand::GREATER_EQUAL; }
#line 1946 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 58:
#line 396 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLTableGroup* > () = new SQLTableGroup();
                    yylhs.value.as< SQLTableGroup* > ()->push_back(yystack_[0].value.as< std::string > ());
                }
#line 1955 "sqlparser.cpp" // lalr1.cc:846
    break;

  case 59:
#line 401 "sqlparser.yy" // lalr1.cc:846
    {
                    yylhs.value.as< SQLTableGroup* > () = yystack_[2].value.as< SQLTableGroup* > ();
                    yylhs.value.as< SQLTableGroup* > ()->push_back(yystack_[0].value.as< std::string > ());
                }
#line 1964 "sqlparser.cpp" // lalr1.cc:846
    break;


#line 1968 "sqlparser.cpp" // lalr1.cc:846
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
    yypush_ (YY_NULL, yylhs);
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
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
    /* $$ was initialized before running the user action.  */
    YY_SYMBOL_PRINT ("Error: discarding", yylhs);
    yylhs.~stack_symbol_type();
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
    if (!yyempty)
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
        if (!yyempty)
          yy_destroy_ (YY_NULL, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULL, yystack_[0]);
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
  SQLParser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char SQLParser::yypact_ninf_ = -104;

  const signed char SQLParser::yytable_ninf_ = -1;

  const signed char
  SQLParser::yypact_[] =
  {
    -104,     2,  -104,     5,     9,    50,   -14,    -9,    19,    17,
      33,   -23,  -104,    43,    44,    48,    49,    51,    52,  -104,
    -104,  -104,  -104,    53,    54,    27,    29,  -104,  -104,    59,
      55,  -104,  -104,  -104,    58,  -104,  -104,    66,    62,    57,
      60,    63,    64,    40,    61,    64,    65,   -25,  -104,  -104,
     -19,  -104,    74,    67,    26,    25,  -104,    -3,    68,  -104,
      70,     3,    -3,    64,    69,    64,    73,    71,    64,    72,
      75,    76,    78,  -104,    40,  -104,  -104,  -104,    30,  -104,
      77,    64,    56,  -104,  -104,  -104,  -104,  -104,  -104,    13,
    -104,    70,    79,    70,  -104,    82,  -104,   -20,    20,    81,
      83,    85,    88,  -104,  -104,    -3,    -3,  -104,    95,  -104,
    -104,  -104,    -3,    84,    64,  -104,    80,    -3,    86,    87,
      89,  -104,  -104,    36,  -104,  -104,  -104,  -104,    -3,  -104,
    -104,  -104,  -104,  -104,    39,  -104
  };

  const unsigned char
  SQLParser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     8,
      10,     9,    13,     0,     0,     0,    47,    48,    50,     0,
      49,     4,     5,     6,     0,     7,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    58,
       0,    51,     0,     0,     0,     0,    14,     0,    23,    38,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    11,     0,    33,    32,    31,     0,    29,
       0,     0,     0,    53,    57,    56,    52,    55,    54,     0,
      44,    25,     0,    26,    59,     0,    42,     0,     0,     0,
       0,     0,     0,    15,    27,     0,     0,    39,     0,    36,
      35,    34,     0,     0,     0,    19,     0,     0,     0,     0,
       0,    17,    30,     0,    37,    45,    18,    43,     0,    41,
      20,    22,    21,    28,     0,    40
  };

  const signed char
  SQLParser::yypgoto_[] =
  {
    -104,  -104,  -104,  -104,  -104,    28,  -104,  -104,  -104,  -103,
     -61,    32,     4,    11,  -104,  -104,   -11,  -104,  -104,    34,
    -104
  };

  const signed char
  SQLParser::yydefgoto_[] =
  {
      -1,     1,    12,    13,    55,    56,    72,    14,    58,    78,
      79,    59,    60,    96,    97,    47,    61,    29,    30,    89,
      50
  };

  const unsigned char
  SQLParser::yytable_[] =
  {
      28,    90,     2,   123,    63,     3,     4,     5,     6,     7,
      65,   114,    26,    15,    75,    16,    64,    17,    82,    18,
     115,    21,    66,    27,     8,   134,    22,     9,   110,    10,
      75,    51,    11,    76,    77,    83,    84,    85,    69,    70,
      71,   116,    23,    24,   122,    86,    87,    88,    26,    76,
      77,   125,    83,    84,    85,    39,   129,    98,    52,    19,
      53,    20,    86,    87,    88,    73,    74,    91,    25,    93,
     104,   105,   108,   109,    40,    54,   133,   105,   111,   135,
     105,    31,    32,    33,    34,    41,    35,    36,    37,    38,
      44,    45,    46,    67,   102,    48,    42,    43,    49,    26,
      57,    81,   103,    98,    92,   121,    68,    62,    94,    80,
      95,    99,   124,   107,   100,   101,   106,   113,   118,   128,
     119,   112,   120,     0,   126,   127,   130,   131,     0,   132,
       0,     0,   117
  };

  const short int
  SQLParser::yycheck_[] =
  {
      11,    62,     0,   106,    29,     3,     4,     5,     6,     7,
      29,    31,    35,     8,    17,    10,    41,     8,    15,    10,
      40,    35,    41,    46,    22,   128,    35,    25,    89,    27,
      17,    42,    30,    36,    37,    32,    33,    34,    12,    13,
      14,    21,    23,    26,   105,    42,    43,    44,    35,    36,
      37,   112,    32,    33,    34,    28,   117,    68,    18,     9,
      20,    11,    42,    43,    44,    40,    41,    63,    35,    65,
      40,    41,    16,    17,    45,    35,    40,    41,    89,    40,
      41,    38,    38,    35,    35,    26,    35,    35,    35,    35,
      24,    29,    35,    19,    16,    35,    41,    39,    35,    35,
      39,    31,    74,   114,    35,    17,    39,    42,    35,    41,
      39,    39,    17,    81,    39,    39,    39,    35,    37,    39,
      37,    42,    37,    -1,    40,   114,    40,    40,    -1,    40,
      -1,    -1,    98
  };

  const unsigned char
  SQLParser::yystos_[] =
  {
       0,    48,     0,     3,     4,     5,     6,     7,    22,    25,
      27,    30,    49,    50,    54,     8,    10,     8,    10,     9,
      11,    35,    35,    23,    26,    35,    35,    46,    63,    64,
      65,    38,    38,    35,    35,    35,    35,    35,    35,    28,
      45,    26,    41,    39,    24,    29,    35,    62,    35,    35,
      67,    63,    18,    20,    35,    51,    52,    39,    55,    58,
      59,    63,    42,    29,    41,    29,    41,    19,    39,    12,
      13,    14,    53,    40,    41,    17,    36,    37,    56,    57,
      41,    31,    15,    32,    33,    34,    42,    43,    44,    66,
      57,    59,    35,    59,    35,    39,    60,    61,    63,    39,
      39,    39,    16,    52,    40,    41,    39,    58,    16,    17,
      57,    63,    42,    35,    31,    40,    21,    66,    37,    37,
      37,    17,    57,    56,    17,    57,    40,    60,    39,    57,
      40,    40,    40,    40,    56,    40
  };

  const unsigned char
  SQLParser::yyr1_[] =
  {
       0,    47,    48,    48,    49,    49,    50,    50,    50,    50,
      50,    50,    50,    50,    51,    51,    52,    52,    52,    52,
      53,    53,    53,    54,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    67,    67
  };

  const unsigned char
  SQLParser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     3,     2,     2,
       2,     6,     3,     2,     1,     3,     2,     4,     5,     4,
       4,     4,     4,     5,     5,     6,     6,     3,     5,     1,
       3,     1,     1,     1,     3,     3,     3,     4,     1,     3,
       5,     3,     1,     3,     3,     5,     3,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3
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
  "NOT_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", "IDENTIFIER", "VALUE_STRING",
  "VALUE_INT", "';'", "'('", "')'", "','", "'='", "'>'", "'<'", "'.'",
  "'*'", "$accept", "Program", "Stmt", "SysStmt", "FieldList", "Field",
  "Type", "QueryStmt", "ValueLists", "ValueList", "Value", "WhereClause",
  "WhereClauseList", "CheckClause", "CheckClauseList", "SetClause",
  "Column", "Selector", "SelectorList", "Operand", "TableList", YY_NULL
  };


  const unsigned short int
  SQLParser::yyrline_[] =
  {
       0,    81,    81,    82,    88,    92,    98,   102,   106,   110,
     114,   118,   122,   126,   132,   137,   144,   149,   155,   161,
     169,   175,   181,   189,   193,   197,   201,   207,   212,   218,
     223,   230,   236,   242,   249,   260,   270,   279,   290,   295,
     302,   308,   318,   323,   330,   339,   350,   356,   363,   368,
     375,   380,   387,   388,   389,   390,   391,   392,   395,   400
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
      39,    40,    46,     2,    41,     2,    45,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
      44,    42,    43,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
    };
    const unsigned int user_token_number_max_ = 292;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2387 "sqlparser.cpp" // lalr1.cc:1156
#line 407 "sqlparser.yy" // lalr1.cc:1157



void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
