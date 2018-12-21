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
#include "stype-integer-exclusiveMaximum.hh"
#include "lexer-integer-exclusiveMaximum.hh"
#include "Bar.hh"
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token <long_type> NEG_INTEGER
%token <long_type> NON_NEG_INTEGER
%token TOKEN_0

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
    TOKEN_0 integer
        {
            $$.set_number($2);
        }
    ;

