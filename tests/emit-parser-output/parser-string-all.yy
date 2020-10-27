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
#include "stype-string-all.hh"
#include "lexer-string-all.hh"
#include "Bar.hh"
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

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

