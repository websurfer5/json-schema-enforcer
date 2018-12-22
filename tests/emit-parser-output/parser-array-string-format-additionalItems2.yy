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
#include "stype-array-string-format-additionalItems2.hh"
#include "lexer-array-string-format-additionalItems2.hh"
#include "Bar.hh"
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
extern void foo_foo_set_format_start_state_0(yyscan_t yyscanner);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token COMMA
%token LEFT_BRACKET
%token <std__string_type> QUOTED_STRING
%token RIGHT_BRACKET
%token TOKEN_0
%token TOKEN_1
%token TOKEN_2

%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item_0
%type <foo__JsonItemVector_type> array_items_0
%type <foo__JsonItem_type> string_0
%type <foo__JsonItem_type> string_1

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;
%destructor { $$.clear(); } <std__string_type>;

%start array_0

%%

array_item_0:
     string_1
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

array_0:
    LEFT_BRACKET  string_0
    array_items_0 RIGHT_BRACKET
        {
            $$.append_array_item($2);
            $$.append_array($3);
        }
    ;

string_0:
    TOKEN_1 QUOTED_STRING
        {
            $$.set_string($2);
        }
    ;

string_1:
    TOKEN_2 QUOTED_STRING
        {
            $$.set_string($2);
        }
    ;

