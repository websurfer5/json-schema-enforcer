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
#include "stype-integer.hh"
#include "lexer-integer.hh"
#include "Bar.hh"
#include <string>

%}


%type <long_type> integer
%type <foo__JsonItem_type> integer_0

%destructor { $$.clear(); } <foo__JsonItem_type>;

%start integer_0

%%

integer:
    NEG_INTEGER
        {
            $$ = $1;
        }
    | NON_NEG_INTEGER
        {
            $$ = $1;
        }
    ;

integer_0:
    integer
        {
            $$.set_number($1);
        }
    ;

