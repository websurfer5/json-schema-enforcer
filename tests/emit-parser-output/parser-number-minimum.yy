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
#include "stype-number-minimum.hh"
#include "lexer-number-minimum.hh"
#include "Bar.hh"
#include <string>

%}

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

