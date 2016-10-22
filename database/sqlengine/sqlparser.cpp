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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        value.copy< SQLAction* > (other.value);
        break;

      case 43: // Field
      case 44: // Type
        value.copy< SQLType* > (other.value);
        break;

      case 47: // Value
        value.copy< SQLValue* > (other.value);
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        value.copy< std::string > (other.value);
        break;

      case 42: // FieldList
        value.copy< std::vector<SQLType*>* > (other.value);
        break;

      case 46: // ValueList
        value.copy< std::vector<SQLValue*>* > (other.value);
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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        value.copy< SQLAction* > (v);
        break;

      case 43: // Field
      case 44: // Type
        value.copy< SQLType* > (v);
        break;

      case 47: // Value
        value.copy< SQLValue* > (v);
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        value.copy< std::string > (v);
        break;

      case 42: // FieldList
        value.copy< std::vector<SQLType*>* > (v);
        break;

      case 46: // ValueList
        value.copy< std::vector<SQLValue*>* > (v);
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
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<SQLValue*>* v, const location_type& l)
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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        value.template destroy< SQLAction* > ();
        break;

      case 43: // Field
      case 44: // Type
        value.template destroy< SQLType* > ();
        break;

      case 47: // Value
        value.template destroy< SQLValue* > ();
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        value.template destroy< std::string > ();
        break;

      case 42: // FieldList
        value.template destroy< std::vector<SQLType*>* > ();
        break;

      case 46: // ValueList
        value.template destroy< std::vector<SQLValue*>* > ();
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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        value.move< SQLAction* > (s.value);
        break;

      case 43: // Field
      case 44: // Type
        value.move< SQLType* > (s.value);
        break;

      case 47: // Value
        value.move< SQLValue* > (s.value);
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        value.move< std::string > (s.value);
        break;

      case 42: // FieldList
        value.move< std::vector<SQLType*>* > (s.value);
        break;

      case 46: // ValueList
        value.move< std::vector<SQLValue*>* > (s.value);
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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        value.move< SQLAction* > (that.value);
        break;

      case 43: // Field
      case 44: // Type
        value.move< SQLType* > (that.value);
        break;

      case 47: // Value
        value.move< SQLValue* > (that.value);
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        value.move< std::string > (that.value);
        break;

      case 42: // FieldList
        value.move< std::vector<SQLType*>* > (that.value);
        break;

      case 46: // ValueList
        value.move< std::vector<SQLValue*>* > (that.value);
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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        value.copy< SQLAction* > (that.value);
        break;

      case 43: // Field
      case 44: // Type
        value.copy< SQLType* > (that.value);
        break;

      case 47: // Value
        value.copy< SQLValue* > (that.value);
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        value.copy< std::string > (that.value);
        break;

      case 42: // FieldList
        value.copy< std::vector<SQLType*>* > (that.value);
        break;

      case 46: // ValueList
        value.copy< std::vector<SQLValue*>* > (that.value);
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
      case 40: // Stmt
      case 41: // SysStmt
      case 45: // QueryStmt
        yylhs.value.build< SQLAction* > ();
        break;

      case 43: // Field
      case 44: // Type
        yylhs.value.build< SQLType* > ();
        break;

      case 47: // Value
        yylhs.value.build< SQLValue* > ();
        break;

      case 28: // IDENTIFIER
      case 29: // VALUE_STRING
      case 30: // VALUE_INT
        yylhs.value.build< std::string > ();
        break;

      case 42: // FieldList
        yylhs.value.build< std::vector<SQLType*>* > ();
        break;

      case 46: // ValueList
        yylhs.value.build< std::vector<SQLValue*>* > ();
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
#line 71 "sqlparser.yy" // lalr1.cc:859
    {
                    driver.addAction(yystack_[0].value.as< SQLAction* > ());
                }
#line 1051 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 77 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1059 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 81 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 1067 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 87 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1075 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 91 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1083 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 95 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowDatabasesAction();
                }
#line 1091 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 99 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLUseDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 1099 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 103 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowTablesAction();
                }
#line 1107 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 107 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateTableAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<SQLType*>* > ());
                }
#line 1115 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 111 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropTableAction(yystack_[0].value.as< std::string > ());
                }
#line 1123 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 115 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDescAction(yystack_[0].value.as< std::string > ());
                }
#line 1131 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 121 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = new std::vector<SQLType*>();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1140 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 126 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = yystack_[2].value.as< std::vector<SQLType*>* > ();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1149 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 133 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[0].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                }
#line 1158 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 138 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[2].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[3].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->canNull = false;
                }
#line 1168 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 144 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->primaryType = true;
                }
#line 1178 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 152 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::INT;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1188 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 158 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::CHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1198 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 164 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::VARCHAR;
                    yylhs.value.as< SQLType* > ()->length = atoi(yystack_[1].value.as< std::string > ().c_str());
                }
#line 1208 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 172 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLInsertAction(yystack_[4].value.as< std::string > (), yystack_[1].value.as< std::vector<SQLValue*>* > ());
                }
#line 1216 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 178 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLValue*>* > () = new std::vector<SQLValue*>();
                    yylhs.value.as< std::vector<SQLValue*>* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1225 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 183 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLValue*>* > () = yystack_[2].value.as< std::vector<SQLValue*>* > ();
                    yylhs.value.as< std::vector<SQLValue*>* > ()->push_back(yystack_[0].value.as< SQLValue* > ());
                }
#line 1234 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 190 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::ENUMERATE;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1244 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 196 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::STRING;
                    yylhs.value.as< SQLValue* > ()->content = yystack_[0].value.as< std::string > ();
                }
#line 1254 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 202 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLValue* > () = new SQLValue();
                    yylhs.value.as< SQLValue* > ()->type = SQLValue::NUL;
                }
#line 1263 "sqlparser.cpp" // lalr1.cc:859
    break;


#line 1267 "sqlparser.cpp" // lalr1.cc:859
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


  const signed char SQLParser::yypact_ninf_ = -27;

  const signed char SQLParser::yytable_ninf_ = -1;

  const signed char
  SQLParser::yypact_[] =
  {
     -27,     0,   -27,     8,    13,    15,   -26,   -20,    -7,   -27,
     -14,    -9,    -3,     3,     4,     5,   -27,   -27,   -27,   -27,
       6,   -27,   -27,   -27,     7,   -27,   -27,    14,    -8,     9,
      18,    -2,    -6,   -27,   -15,    10,    11,    12,    16,    22,
     -27,    -8,   -27,   -27,   -27,    -4,   -27,    17,    19,    20,
      21,    24,   -27,   -27,   -15,    23,    25,    26,    27,   -27,
     -27,   -27,   -27,   -27,   -27
  };

  const unsigned char
  SQLParser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     8,    10,     9,    13,
       0,     4,     5,     6,     0,     7,    12,     0,     0,     0,
       0,     0,     0,    14,     0,     0,     0,     0,     0,    16,
      11,     0,    27,    26,    25,     0,    23,     0,     0,     0,
       0,     0,    15,    22,     0,     0,     0,     0,     0,    17,
      24,    18,    19,    21,    20
  };

  const signed char
  SQLParser::yypgoto_[] =
  {
     -27,   -27,   -27,   -27,   -27,    28,   -27,   -27,   -27,   -16
  };

  const signed char
  SQLParser::yydefgoto_[] =
  {
      -1,     1,     9,    10,    32,    33,    39,    11,    45,    46
  };

  const unsigned char
  SQLParser::yytable_[] =
  {
       2,    42,    18,     3,     4,     5,     6,     7,    19,    30,
      36,    37,    38,    20,    43,    44,    12,    21,    13,     8,
      31,    14,    22,    15,    16,    23,    17,    40,    41,    53,
      54,    24,    25,    26,    27,    29,    35,    51,    60,    28,
      59,    34,    47,    48,    49,    55,     0,     0,    50,    56,
      57,    58,     0,     0,     0,     0,    61,     0,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,    52
  };

  const signed char
  SQLParser::yycheck_[] =
  {
       0,    16,    28,     3,     4,     5,     6,     7,    28,    17,
      12,    13,    14,    20,    29,    30,     8,    31,    10,    19,
      28,     8,    31,    10,     9,    28,    11,    33,    34,    33,
      34,    28,    28,    28,    28,    21,    18,    15,    54,    32,
      16,    32,    32,    32,    32,    28,    -1,    -1,    32,    30,
      30,    30,    -1,    -1,    -1,    -1,    33,    -1,    33,    33,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41
  };

  const unsigned char
  SQLParser::yystos_[] =
  {
       0,    39,     0,     3,     4,     5,     6,     7,    19,    40,
      41,    45,     8,    10,     8,    10,     9,    11,    28,    28,
      20,    31,    31,    28,    28,    28,    28,    28,    32,    21,
      17,    28,    42,    43,    32,    18,    12,    13,    14,    44,
      33,    34,    16,    29,    30,    46,    47,    32,    32,    32,
      32,    15,    43,    33,    34,    28,    30,    30,    30,    16,
      47,    33,    33,    33,    33
  };

  const unsigned char
  SQLParser::yyr1_[] =
  {
       0,    38,    39,    39,    40,    40,    41,    41,    41,    41,
      41,    41,    41,    41,    42,    42,    43,    43,    43,    44,
      44,    44,    45,    46,    46,    47,    47,    47
  };

  const unsigned char
  SQLParser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     3,     2,     2,
       2,     6,     3,     2,     1,     3,     2,     4,     5,     4,
       4,     4,     7,     1,     3,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SQLParser::yytname_[] =
  {
  "$end", "error", "$undefined", "CREATE", "DROP", "SHOW", "USE", "DESC",
  "DATABASE", "DATABASES", "TABLE", "TABLES", "INT", "VARCHAR", "CHAR",
  "NOT", "NUL", "PRIMARY", "KEY", "INSERT", "INTO", "VALUES", "DELETE",
  "FROM", "UPDATE", "SET", "WHERE", "SELECT", "IDENTIFIER", "VALUE_STRING",
  "VALUE_INT", "';'", "'('", "')'", "','", "'='", "'>'", "'<'", "$accept",
  "Program", "Stmt", "SysStmt", "FieldList", "Field", "Type", "QueryStmt",
  "ValueList", "Value", YY_NULLPTR
  };


  const unsigned char
  SQLParser::yyrline_[] =
  {
       0,    69,    69,    70,    76,    80,    86,    90,    94,    98,
     102,   106,   110,   114,   120,   125,   132,   137,   143,   151,
     157,   163,   171,   177,   182,   189,   195,   201
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
      32,    33,     2,     2,    34,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
      37,    35,    36,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
    };
    const unsigned int user_token_number_max_ = 285;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1631 "sqlparser.cpp" // lalr1.cc:1167
#line 208 "sqlparser.yy" // lalr1.cc:1168



void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
