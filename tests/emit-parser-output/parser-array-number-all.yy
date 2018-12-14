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
#include "stype-array-number-all.hh"
#include "lexer-array-number-all.hh"
#include "Bar.hh"
#include <string>

%}

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

%type <foo__JsonItem_type> array
%type <foo__JsonItem_type> array_0
%type <foo__JsonItem_type> array_item
%type <foo__JsonItem_type> array_item_0
%type <foo__JsonItemList_type> array_items
%type <foo__JsonItemList_type> array_items_0
%type <bool_type> boolean
%type <double_type> number
%type <foo__JsonItem_type> number_0
%type <foo__JsonItem_type> object
%type <foo__JsonItem_type> object_item
%type <foo__JsonItemMap_type> object_items

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemList_type>;
%destructor { $$.clear(); } <foo__JsonItemMap_type>;
%destructor { $$.clear(); } <std__string_type>;

%start array_0

%%

array_item_0:
     number_0
        {
            $$ = $1;
        }
    ;

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

number_0:
    TOKEN_1 number
        {
            $$.set_number($2);
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

array_items_0:
    array_item_0
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

array_0:
    empty_array
        {
            $$.clear();
        }
    | LEFT_BRACKET array_items_0 RIGHT_BRACKET
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

