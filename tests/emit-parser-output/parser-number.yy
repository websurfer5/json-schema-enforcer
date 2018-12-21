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
#include "stype-number.hh"
#include "lexer-number.hh"
#include "Bar.hh"
#include <string>

%}


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
    number
        {
            $$.set_number($1);
        }
    ;

