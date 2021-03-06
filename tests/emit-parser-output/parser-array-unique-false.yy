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
#include "stype-array-unique-false.hh"
#include "lexer-array-unique-false.hh"
#include "Bar.hh"
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
extern void foo_foo_set_item_array_start_state_0(yyscan_t yyscanner);

#define FOO_FOO_PARAM sd->scaninfo
%}

%lex-param { yyscan_t FOO_FOO_PARAM }
%parse-param { foo::Bar *sd }

%token B_FALSE
%token B_TRUE
%token COLON
%token COMMA
%token <double_type> FLOATING_POINT
%token LEFT_BRACE
%token LEFT_BRACKET
%token <long_type> NEG_INTEGER
%token <long_type> NON_NEG_INTEGER
%token NULL_TOKEN
%token <std__string_type> QUOTED_STRING
%token RIGHT_BRACE
%token RIGHT_BRACKET
%token TOKEN_0

%type <foo__JsonItem_type> array
%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item
%type <foo__JsonItemVector_type> array_items
%type <bool_type> boolean
%type <long_type> integer
%type <foo__JsonItem_type> integer_0
%type <double_type> number
%type <foo__JsonItem_type> object
%type <foo__JsonItem_type> object_item
%type <foo__JsonItemMap_type> object_items

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemMap_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;
%destructor { $$.clear(); } <std__string_type>;

%start array_0

%%

boolean:
    B_FALSE
        {
            $$ = false;
        }
    | B_TRUE
        {
            $$ = true;
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

empty_object:
    LEFT_BRACE RIGHT_BRACE
    ;

empty_array:
    LEFT_BRACKET RIGHT_BRACKET
    ;

array_0:
    LEFT_BRACKET TOKEN_0 integer_0
    COMMA TOKEN_0 integer_0
    COMMA TOKEN_0 integer_0
        {
            foo_foo_set_item_array_start_state_0(sd->scaninfo);
        }
    array_items RIGHT_BRACKET
        {
            $$.append_array_item($3);
            $$.append_array_item($6);
            $$.append_array_item($9);
            $$.append_array($11);
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

object_item:
    QUOTED_STRING COLON QUOTED_STRING
        {
            $$.set_object_item($1, $3);
        }
    | QUOTED_STRING COLON number
        {
            $$.set_object_item($1, $3);
        }
    | QUOTED_STRING COLON boolean
        {
            $$.set_object_item($1, $3);
        }
    | QUOTED_STRING COLON array
        {
            $$.set_object_item($1, $3);
        }
    | QUOTED_STRING COLON object
        {
            $$.set_object_item($1, $3);
        }
    | QUOTED_STRING COLON NULL_TOKEN
        {
            $$.set_object_item($1);
        }
    ;

array_items:
    array_item
        {
            $$.clear();
            $$.push_back($1);
        }
    | array_items COMMA array_item
        {
            $$ = $1;
            $$.push_back($3);
        }
    ;

array_item:
    boolean
        {
            $$.set_boolean($1);
        }
    | number
        {
            $$ = $$.set_number($1);
        }
    | array
        {
            $$ = $1;
        }
    | object
        {
            $$ = $1;
        }
    | NULL_TOKEN
        {
            $$ = $$.set_null();
        }
    | QUOTED_STRING
        {
            $$ = $$.set_string($1);
        }
    ;

array:
    empty_array
        {
            $$.clear();
        }
    | LEFT_BRACKET array_items RIGHT_BRACKET
        {
            $$.set_array($2);
        }
    ;

object:
    empty_object
        {
            $$.clear();
        }
    | LEFT_BRACE object_items RIGHT_BRACE
        {
            $$.set_object($2);
        }
    ;

integer_0:
    integer
        {
            $$.set_number($1);
        }
    ;

object_items:
    object_item
        {
            $$.clear();
            $$ = $1.object();
        }
    | object_items COMMA object_item
        {
            $$ = $1;
            $$.insert($3.object().cbegin(), $3.object().cend());
        }
    ;

