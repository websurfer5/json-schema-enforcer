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
#include "stype-array-string-format-additionalItems5.hh"
#include "lexer-array-string-format-additionalItems5.hh"
#include "Bar.hh"
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
extern void foo_foo_set_format_start_state_0(yyscan_t yyscanner);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token COMMA
%token <double_type> FLOATING_POINT
%token LEFT_BRACKET
%token <long_type> NEG_INTEGER
%token <long_type> NON_NEG_INTEGER
%token <std__string_type> QUOTED_STRING
%token RIGHT_BRACKET
%token TOKEN_0
%token TOKEN_1

%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item_0
%type <foo__JsonItemVector_type> array_items_0
%type <double_type> number
%type <foo__JsonItem_type> number_0
%type <foo__JsonItem_type> string_0

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;
%destructor { $$.clear(); } <std__string_type>;

%start array_0

%%

array_item_0:
     string_0
        {
            $$ = $1;
        }
    ;

array_items_0:
    %empty
        {
            $$.clear();
        }
    | array_item_0
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

array_0:
    LEFT_BRACKET TOKEN_0 number_0
    array_items_0 RIGHT_BRACKET
        {
            $$.append_array_item($3);
            $$.append_array($4);
        }
    ;

string_0:
    TOKEN_1 QUOTED_STRING
        {
            $$.set_string($2);
        }
    ;

number_0:
    number
        {
            $$.set_number($1);
        }
    ;

