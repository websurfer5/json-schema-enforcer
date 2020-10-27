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
#include "stype-array-string-format-additionalItems4.hh"
#include "lexer-array-string-format-additionalItems4.hh"
#include "Bar.hh"
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

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

%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item_0
%type <foo__JsonItemVector_type> array_items_0
%type <foo__JsonItem_type> string_0

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;
%destructor { $$.clear(); } <std__string_type>;

%start array_0

%%

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

array_item_0:
    TOKEN_0 QUOTED_STRING
        {
            foo::JsonItem jitem;
            jitem.set_string($2);
            $$.append_array_item(jitem);
        }
    ;

string_0:
    TOKEN_1 QUOTED_STRING
        {
            $$.set_string($2);
        }
    ;

