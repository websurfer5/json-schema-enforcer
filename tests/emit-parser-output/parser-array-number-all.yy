%{
namespace foo
{
    class Bar;
}
%}

%define api.prefix {foo_foo_}
%define api.pure full
%define parse.lac full
%error-verbose

%{
#include "stype-array-number-all.hh"
#include "lexer-array-number-all.hh"
#include "Bar.hh"
#include <iostream>
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token COMMA
%token <double_type> FLOATING_POINT
%token LEFT_BRACKET
%token <long_type> NEG_INTEGER
%token <long_type> NON_NEG_INTEGER
%token RIGHT_BRACKET
%token TOKEN_0
%token TOKEN_1

%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item_0
%type <foo__JsonItemVector_type> array_items_0
%type <double_type> number
%type <foo__JsonItem_type> number_0

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;

%start array_0

%%

array_item_0:
     number_0
        {
            $$ = $1;
        }
    ;

number:
    FLOATING_POINT
        {
            $$ = $1;
        }
    | NEG_INTEGER
        {
            $$ = $1;
        }
    | NON_NEG_INTEGER
        {
            $$ = $1;
        }
    ;

empty_array:
    LEFT_BRACKET RIGHT_BRACKET
    ;

number_0:
    TOKEN_1 number
        {
            $$.set_number($2);
        }
    ;

array_items_0:
    array_item_0
         {
             $$.clear();
             $$.push_back($1);
         }
    | array_items_0 COMMA array_item_0
         {
             $$ = $1;
             $$.push_back($3);
         }
    ;

array_0:
    empty_array
        {
            $$.clear();
        }
    | LEFT_BRACKET array_items_0 RIGHT_BRACKET
        {
            $$.set_array($2);
        }
    ;

