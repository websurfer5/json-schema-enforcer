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
#include "stype-object-string-all.hh"
#include "lexer-object-string-all.hh"
#include "Bar.hh"
#include <string>

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
%token TOKEN_1
%token TOKEN_10
%token TOKEN_2
%token TOKEN_3
%token TOKEN_4
%token TOKEN_5
%token TOKEN_6
%token TOKEN_7
%token TOKEN_8
%token TOKEN_9

%type <foo__JsonItem_type> array
%type <foo__JsonItem_type> array_item
%type <foo__JsonItemVector_type> array_items
%type <bool_type> boolean
%type <double_type> number
%type <foo__JsonItem_type> object
%type <foo__JsonItem_type> object_0
%type <foo__JsonItem_type> object_item
%type <foo__JsonItem_type> object_item_0
%type <foo__JsonItemMap_type> object_items
%type <foo__JsonItemMap_type> object_items_0
%type <foo__JsonItem_type> string_0
%type <foo__JsonItem_type> string_1
%type <foo__JsonItem_type> string_2
%type <foo__JsonItem_type> string_3
%type <foo__JsonItem_type> string_4
%type <foo__JsonItem_type> string_5
%type <foo__JsonItem_type> string_6
%type <foo__JsonItem_type> string_7
%type <foo__JsonItem_type> string_8
%type <foo__JsonItem_type> string_9

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemMap_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;
%destructor { $$.clear(); } <std__string_type>;

%start object_0

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

object_item:
    QUOTED_STRING COLON QUOTED_STRING
        {
            $$.set_string($1, $3);
        }
    | QUOTED_STRING COLON number
        {
            $$.set_number($1, $3);
        }
    | QUOTED_STRING COLON boolean
        {
            $$.set_boolean($1, $3);
        }
    | QUOTED_STRING COLON array
        {
            $$ = $3;
            $$.set_key($1);
        }
    | QUOTED_STRING COLON object
        {
            $$ = $3;
            $$.set_key($1);
        }
    | QUOTED_STRING COLON NULL_TOKEN
        {
            $$.set_null($1);
        }
    ;

string_0:
    TOKEN_0 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_1:
    TOKEN_1 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_2:
    TOKEN_2 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_3:
    TOKEN_3 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_4:
    TOKEN_4 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_5:
    TOKEN_5 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_6:
    TOKEN_6 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_7:
    TOKEN_7 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_8:
    TOKEN_8 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
        }
    ;

string_9:
    TOKEN_9 QUOTED_STRING QUOTED_STRING
        {
            $$.set_string($2, $3);
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

object_0:
    empty_object
        {
            $$.clear();
        }
    | LEFT_BRACE object_items_0 RIGHT_BRACE
        {
            $$.set_object($2);
        }
    ;

object_items:
    object_item
        {
            $$.clear();
            $$[$1.get_key()] = $1;
        }
    | object_items COMMA object_item
        {
            $$ = $1;
            $$[$3.get_key()] = $3;
        }
    ;

object_items_0:
    object_item_0
         {
             $$.clear();
             $$[$1.get_key()] = $1;
         }
    | object_items_0 COMMA object_item_0
         {
             $$ = $1;
             $$[$3.get_key()] = $3;
         }
    ;

object_item_0:
    string_0
        {
            $$ = $1;
        }
    | string_1
        {
            $$ = $1;
        }
    | string_2
        {
            $$ = $1;
        }
    | string_3
        {
            $$ = $1;
        }
    | string_4
        {
            $$ = $1;
        }
    | string_5
        {
            $$ = $1;
        }
    | string_6
        {
            $$ = $1;
        }
    | string_7
        {
            $$ = $1;
        }
    | string_8
        {
            $$ = $1;
        }
    | string_9
        {
            $$ = $1;
        }
    | TOKEN_10 QUOTED_STRING COLON QUOTED_STRING
        {
            $$.set_string($2, $4);
        }
    | TOKEN_10 QUOTED_STRING COLON number
        {
            $$.set_number($2, $4);
        }
    | TOKEN_10 QUOTED_STRING COLON boolean
        {
            $$.set_boolean($2, $4);
        }
    | TOKEN_10 QUOTED_STRING COLON array
        {
            $$ = $4;
            $$.set_key($2);
        }
    | TOKEN_10 QUOTED_STRING COLON object
        {
            $$ = $4;
            $$.set_key($2);
        }
    | TOKEN_10 QUOTED_STRING COLON NULL_TOKEN
        {
            $$.set_null($2);
        }
    ;

