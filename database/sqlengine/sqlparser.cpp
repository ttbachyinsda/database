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
      case 28: // Stmt
      case 29: // SysStmt
        value.copy< SQLAction* > (other.value);
        break;

      case 31: // Field
      case 32: // Type
        value.copy< SQLType* > (other.value);
        break;

      case 21: // VALUE_INT
        value.copy< int > (other.value);
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        value.copy< std::string > (other.value);
        break;

      case 30: // FieldList
        value.copy< std::vector<SQLType*>* > (other.value);
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
      case 28: // Stmt
      case 29: // SysStmt
        value.copy< SQLAction* > (v);
        break;

      case 31: // Field
      case 32: // Type
        value.copy< SQLType* > (v);
        break;

      case 21: // VALUE_INT
        value.copy< int > (v);
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        value.copy< std::string > (v);
        break;

      case 30: // FieldList
        value.copy< std::vector<SQLType*>* > (v);
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
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
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
      case 28: // Stmt
      case 29: // SysStmt
        value.template destroy< SQLAction* > ();
        break;

      case 31: // Field
      case 32: // Type
        value.template destroy< SQLType* > ();
        break;

      case 21: // VALUE_INT
        value.template destroy< int > ();
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        value.template destroy< std::string > ();
        break;

      case 30: // FieldList
        value.template destroy< std::vector<SQLType*>* > ();
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
      case 28: // Stmt
      case 29: // SysStmt
        value.move< SQLAction* > (s.value);
        break;

      case 31: // Field
      case 32: // Type
        value.move< SQLType* > (s.value);
        break;

      case 21: // VALUE_INT
        value.move< int > (s.value);
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        value.move< std::string > (s.value);
        break;

      case 30: // FieldList
        value.move< std::vector<SQLType*>* > (s.value);
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
  SQLParser::make_VALUE_INT (const int& v, const location_type& l)
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
      case 28: // Stmt
      case 29: // SysStmt
        value.move< SQLAction* > (that.value);
        break;

      case 31: // Field
      case 32: // Type
        value.move< SQLType* > (that.value);
        break;

      case 21: // VALUE_INT
        value.move< int > (that.value);
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        value.move< std::string > (that.value);
        break;

      case 30: // FieldList
        value.move< std::vector<SQLType*>* > (that.value);
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
      case 28: // Stmt
      case 29: // SysStmt
        value.copy< SQLAction* > (that.value);
        break;

      case 31: // Field
      case 32: // Type
        value.copy< SQLType* > (that.value);
        break;

      case 21: // VALUE_INT
        value.copy< int > (that.value);
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        value.copy< std::string > (that.value);
        break;

      case 30: // FieldList
        value.copy< std::vector<SQLType*>* > (that.value);
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
      case 28: // Stmt
      case 29: // SysStmt
        yylhs.value.build< SQLAction* > ();
        break;

      case 31: // Field
      case 32: // Type
        yylhs.value.build< SQLType* > ();
        break;

      case 21: // VALUE_INT
        yylhs.value.build< int > ();
        break;

      case 19: // IDENTIFIER
      case 20: // VALUE_STRING
        yylhs.value.build< std::string > ();
        break;

      case 30: // FieldList
        yylhs.value.build< std::vector<SQLType*>* > ();
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
#line 67 "sqlparser.yy" // lalr1.cc:859
    {
                    driver.addAction(yystack_[0].value.as< SQLAction* > ());
                }
#line 948 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 73 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = yystack_[1].value.as< SQLAction* > ();
                }
#line 956 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 80 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 964 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 84 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 972 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 88 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowDatabasesAction();
                }
#line 980 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 92 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLUseDatabaseAction(yystack_[0].value.as< std::string > ());
                }
#line 988 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 96 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLShowTablesAction();
                }
#line 996 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 100 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLCreateTableAction(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<SQLType*>* > ());
                }
#line 1004 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 104 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDropTableAction(yystack_[0].value.as< std::string > ());
                }
#line 1012 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 108 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLAction* > () = new SQLDescAction(yystack_[0].value.as< std::string > ());
                }
#line 1020 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 114 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = new std::vector<SQLType*>();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1029 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 119 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<SQLType*>* > () = yystack_[2].value.as< std::vector<SQLType*>* > ();
                    yylhs.value.as< std::vector<SQLType*>* > ()->push_back(yystack_[0].value.as< SQLType* > ());
                }
#line 1038 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 126 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[0].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                }
#line 1047 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 131 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = yystack_[2].value.as< SQLType* > ();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[3].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->canNull = false;
                }
#line 1057 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 137 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->identifier = yystack_[1].value.as< std::string > ();
                    yylhs.value.as< SQLType* > ()->primaryType = true;
                }
#line 1067 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 145 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::INT;
                    yylhs.value.as< SQLType* > ()->length = yystack_[1].value.as< int > ();
                }
#line 1077 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 151 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::CHAR;
                    yylhs.value.as< SQLType* > ()->length = yystack_[1].value.as< int > ();
                }
#line 1087 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 157 "sqlparser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< SQLType* > () = new SQLType();
                    yylhs.value.as< SQLType* > ()->type = SQLType::VARCHAR;
                    yylhs.value.as< SQLType* > ()->length = yystack_[1].value.as< int > ();
                }
#line 1097 "sqlparser.cpp" // lalr1.cc:859
    break;


#line 1101 "sqlparser.cpp" // lalr1.cc:859
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


  const signed char SQLParser::yypact_ninf_ = -24;

  const signed char SQLParser::yytable_ninf_ = -1;

  const signed char
  SQLParser::yypact_[] =
  {
     -24,     0,   -24,     3,     4,     6,     1,     2,   -24,    -3,
       5,     7,     8,     9,   -24,   -24,   -24,   -24,   -24,   -24,
      10,   -24,   -24,    -1,    11,    -4,   -23,   -24,    12,    13,
      14,    15,    16,   -24,    -1,    20,    19,    21,    22,    18,
     -24,    -2,    17,    23,    24,   -24,   -24,   -24,   -24,   -24
  };

  const unsigned char
  SQLParser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     0,     3,     0,
       0,     0,     0,     0,     7,     9,     8,    12,     4,     5,
       0,     6,    11,     0,     0,     0,     0,    13,     0,     0,
       0,     0,    15,    10,     0,     0,     0,     0,     0,     0,
      14,     0,     0,     0,     0,    16,    17,    18,    20,    19
  };

  const signed char
  SQLParser::yypgoto_[] =
  {
     -24,   -24,   -24,   -24,   -24,   -11,   -24
  };

  const signed char
  SQLParser::yydefgoto_[] =
  {
      -1,     1,     8,     9,    26,    27,    32
  };

  const unsigned char
  SQLParser::yytable_[] =
  {
       2,    33,    34,     3,     4,     5,     6,     7,    29,    30,
      31,    10,    12,    11,    13,    14,    24,    15,    25,    18,
      16,    17,    46,    40,    19,     0,    20,    21,    22,    28,
       0,    39,     0,    23,    45,    35,    36,    37,    38,    41,
      42,    47,    43,    44,     0,     0,     0,    48,    49
  };

  const signed char
  SQLParser::yycheck_[] =
  {
       0,    24,    25,     3,     4,     5,     6,     7,    12,    13,
      14,     8,     8,    10,    10,     9,    17,    11,    19,    22,
      19,    19,    24,    34,    19,    -1,    19,    19,    19,    18,
      -1,    15,    -1,    23,    16,    23,    23,    23,    23,    19,
      21,    24,    21,    21,    -1,    -1,    -1,    24,    24
  };

  const unsigned char
  SQLParser::yystos_[] =
  {
       0,    27,     0,     3,     4,     5,     6,     7,    28,    29,
       8,    10,     8,    10,     9,    11,    19,    19,    22,    19,
      19,    19,    19,    23,    17,    19,    30,    31,    18,    12,
      13,    14,    32,    24,    25,    23,    23,    23,    23,    15,
      31,    19,    21,    21,    21,    16,    24,    24,    24,    24
  };

  const unsigned char
  SQLParser::yyr1_[] =
  {
       0,    26,    27,    27,    28,    29,    29,    29,    29,    29,
      29,    29,    29,    30,    30,    31,    31,    31,    32,    32,
      32
  };

  const unsigned char
  SQLParser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     3,     3,     2,     2,     2,
       6,     3,     2,     1,     3,     2,     4,     5,     4,     4,
       4
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SQLParser::yytname_[] =
  {
  "$end", "error", "$undefined", "CREATE", "DROP", "SHOW", "USE", "DESC",
  "DATABASE", "DATABASES", "TABLE", "TABLES", "INT", "VARCHAR", "CHAR",
  "NOT", "NUL", "PRIMARY", "KEY", "IDENTIFIER", "VALUE_STRING",
  "VALUE_INT", "';'", "'('", "')'", "','", "$accept", "Program", "Stmt",
  "SysStmt", "FieldList", "Field", "Type", YY_NULLPTR
  };


  const unsigned char
  SQLParser::yyrline_[] =
  {
       0,    65,    65,    66,    72,    79,    83,    87,    91,    95,
      99,   103,   107,   113,   118,   125,   130,   136,   144,   150,
     156
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
      23,    24,     2,     2,    25,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
    };
    const unsigned int user_token_number_max_ = 276;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1452 "sqlparser.cpp" // lalr1.cc:1167
#line 164 "sqlparser.yy" // lalr1.cc:1168



void yy::SQLParser::error( const location_type &l, const std::string &err_message )
{
   driver.addErrorMessage("数据库提醒您语法错误！");
}
