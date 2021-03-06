%{
namespace foo
{
    class Bar;
}
%}

%define api.prefix {foo_foo_}
%define api.pure full
%define parse.lac full
%define parse.error verbose

%{
#include "stype-number-exclusiveMinimum.hh"
#include "lexer-number-exclusiveMinimum.hh"
#include "Bar.hh"
#include <iostream>
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token <double_type> FLOATING_POINT
%token <long_type> NEG_INTEGER
%token <long_type> NON_NEG_INTEGER
%token TOKEN_0

%type <double_type> number
%type <foo__JsonItem_type> number_0

%destructor { $$.clear(); } <foo__JsonItem_type>;

%start number_0

%%

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

number_0:
    TOKEN_0 number
        {
            $$.set_number($2);
        }
    ;

