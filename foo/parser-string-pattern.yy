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
#include "stype-string-pattern.hh"
#include "lexer-string-pattern.hh"
#include "Bar.hh"
#include <string>

%}

%token <std__string_type> QUOTED_STRING
%token TOKEN_0

%type <JsonItem_type> string_0

%destructor { $$.clear(); } <JsonItem_type>;
%destructor { $$.clear(); } <std__string_type>;

%start string_0

%%

string_0:
    TOKEN_0 QUOTED_STRING
        {
            $$.set_string($2);
        }
    ;

