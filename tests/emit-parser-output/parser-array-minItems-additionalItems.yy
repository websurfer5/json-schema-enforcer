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
#include "stype-array-minItems-additionalItems.hh"
#include "lexer-array-minItems-additionalItems.hh"
#include "Bar.hh"
#include <iostream>
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token COMMA
%token LEFT_BRACKET
%token <long_type> NEG_INTEGER
%token <long_type> NON_NEG_INTEGER
%token <std__string_type> QUOTED_STRING
%token RIGHT_BRACKET
%token TOKEN_0

%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item_0
%type <foo__JsonItemVector_type> array_items_0
%type <long_type> integer
%type <foo__JsonItem_type> integer_0

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
    LEFT_BRACKET TOKEN_0 integer_0
    COMMA TOKEN_0 integer_0
    COMMA TOKEN_0 integer_0
    array_items_0 RIGHT_BRACKET
        {
            $$.append_array_item($3);
            $$.append_array_item($6);
            $$.append_array_item($9);
            $$.append_array($10);

            if ($$.array().size() < 8)
            {
                std::cerr << "validation error: array has fewer than 8 items" << std::endl;
                YYABORT;
            }

        }
    ;

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

array_item_0:
    TOKEN_0 QUOTED_STRING
        {
            foo::JsonItem jitem;
            jitem.set_string($2);
            $$.append_array_item(jitem);
        }
    ;

integer_0:
    integer
        {
            $$.set_number($1);
        }
    ;

