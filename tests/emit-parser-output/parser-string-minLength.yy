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
#include "stype-string-minLength.hh"
#include "lexer-string-minLength.hh"
#include "Bar.hh"
#include <string>

%}

%token <std__string_type> QUOTED_STRING
%token TOKEN_0

%type <foo__JsonItem_type> string_0

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <std__string_type>;

%start string_0

%%

string_0:
    TOKEN_0 QUOTED_STRING
        {
            $$.set_string($2);
        }
    ;

