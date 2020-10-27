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
#include "stype-object-nested1.hh"
#include "lexer-object-nested1.hh"
#include "Bar.hh"
#include <iostream>
#include <string>

extern void foo_foo_error(foo::Bar *sd, const char *s, ...);

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
%token TOKEN_11
%token TOKEN_12
%token TOKEN_13
%token TOKEN_14
%token TOKEN_15
%token TOKEN_16
%token TOKEN_17
%token TOKEN_18
%token TOKEN_19
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
%type <long_type> integer
%type <foo__JsonItem_type> integer_0
%type <foo__JsonItem_type> integer_1
%type <foo__JsonItem_type> integer_2
%type <foo__JsonItem_type> integer_3
%type <foo__JsonItem_type> integer_4
%type <double_type> number
%type <foo__JsonItem_type> number_0
%type <foo__JsonItem_type> number_1
%type <foo__JsonItem_type> number_2
%type <foo__JsonItem_type> object
%type <foo__JsonItem_type> object_0
%type <foo__JsonItem_type> object_1
%type <foo__JsonItem_type> object_2
%type <foo__JsonItem_type> object_item
%type <foo__JsonItem_type> object_item_0
%type <foo__JsonItem_type> object_item_1
%type <foo__JsonItem_type> object_item_2
%type <foo__JsonItemMap_type> object_items
%type <foo__JsonItemMap_type> object_items_0
%type <foo__JsonItemMap_type> object_items_1
%type <foo__JsonItemMap_type> object_items_2
%type <foo__JsonItem_type> string_0
%type <foo__JsonItem_type> string_1
%type <foo__JsonItem_type> string_2
%type <foo__JsonItem_type> string_3
%type <foo__JsonItem_type> string_4
%type <foo__JsonItem_type> string_5
%type <foo__JsonItem_type> string_6

%destructor { $$.clear(); } <foo__JsonItem_type>;
%destructor { $$.clear(); } <foo__JsonItemMap_type>;
%destructor { $$.clear(); } <foo__JsonItemVector_type>;
%destructor { $$.clear(); } <std__string_type>;

%start object_2

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

object_2:
    LEFT_BRACE object_items_2 RIGHT_BRACE
        {
            if ($2.find("foo-num") == $2.end())
            {
                std::cerr << "Object missing required object property: \"foo-num\"" << std::endl;
                YYABORT;
            }

            if ($2.find("foo-int") == $2.end())
            {
                std::cerr << "Object missing required object property: \"foo-int\"" << std::endl;
                YYABORT;
            }

            $$.set_object($2);
        }
    ;

empty_array:
    LEFT_BRACKET RIGHT_BRACKET
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

string_0:
    TOKEN_0 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
        }
    ;

string_5:
    TOKEN_11 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
        }
    ;

number_1:
    TOKEN_12 QUOTED_STRING number
        {
            $$.set_object_item($2, $3);
        }
    ;

number_2:
    TOKEN_13 QUOTED_STRING COLON number
        {
            $$.set_object_item($2, $4);
        }
    ;

integer_3:
    TOKEN_14 QUOTED_STRING integer
        {
            $$.set_object_item($2, $3);
        }
    ;

integer_4:
    TOKEN_15 QUOTED_STRING COLON integer
        {
            $$.set_object_item($2, $4);
        }
    ;

object_1:
    TOKEN_16 QUOTED_STRING object_items_1 RIGHT_BRACE
        {
            if ($3.size() < 2)
            {
                std::cerr << "Object must have at least 2 properties, but only has " << $3.size() << std::endl;
                YYABORT;
            }

            $$.set_object_item($2, $3);
        }
    ;

string_6:
    TOKEN_17 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
        }
    ;

string_1:
    TOKEN_2 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
        }
    ;

string_2:
    TOKEN_3 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
        }
    ;

number_0:
    TOKEN_4 QUOTED_STRING number
        {
            $$.set_object_item($2, $3);
        }
    ;

integer_0:
    TOKEN_5 QUOTED_STRING integer
        {
            $$.set_object_item($2, $3);
        }
    ;

integer_1:
    TOKEN_6 QUOTED_STRING integer
        {
            $$.set_object_item($2, $3);
        }
    ;

integer_2:
    TOKEN_7 QUOTED_STRING COLON integer
        {
            $$.set_object_item($2, $4);
        }
    ;

string_3:
    TOKEN_8 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
        }
    ;

string_4:
    TOKEN_9 QUOTED_STRING QUOTED_STRING
        {
            $$.set_object_item($2, $3);
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
    | TOKEN_1 QUOTED_STRING object_items_0 RIGHT_BRACE
        {
            if ($3.size() > 5)
            {
                std::cerr << "Object must have at most 5 properties, but has " << $3.size() << std::endl;
                YYABORT;
            }

            $$.set_object_item($2, $3);
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

object_items_0:
    object_item_0
         {
             $$ = $1.object();
         }
    | object_items_0 COMMA object_item_0
         {
             $$ = $1;
             $$.insert($3.object().cbegin(), $3.object().cend());
         }
    ;

object_items_1:
    object_item_1
         {
             $$ = $1.object();
         }
    | object_items_1 COMMA object_item_1
         {
             $$ = $1;
             $$.insert($3.object().cbegin(), $3.object().cend());
         }
    ;

object_items_2:
    object_item_2
         {
             $$ = $1.object();
         }
    | object_items_2 COMMA object_item_2
         {
             $$ = $1;
             $$.insert($3.object().cbegin(), $3.object().cend());
         }
    ;

object_item_2:
    string_0
        {
            $$ = $1;
        }
    | object_0
        {
            $$ = $1;
        }
    | number_1
        {
            $$ = $1;
        }
    | number_2
        {
            $$ = $1;
        }
    | integer_3
        {
            $$ = $1;
        }
    | integer_4
        {
            $$ = $1;
        }
    | object_1
        {
            $$ = $1;
        }
    | TOKEN_19 QUOTED_STRING COLON QUOTED_STRING
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_19 QUOTED_STRING COLON number
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_19 QUOTED_STRING COLON boolean
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_19 QUOTED_STRING COLON array
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_19 QUOTED_STRING COLON object
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_19 QUOTED_STRING COLON NULL_TOKEN
        {
            $$.set_object_item($2);
        }
    ;

object_item_0:
    string_1
        {
            $$ = $1;
        }
    | string_2
        {
            $$ = $1;
        }
    | number_0
        {
            $$ = $1;
        }
    | integer_0
        {
            $$ = $1;
        }
    | integer_1
        {
            $$ = $1;
        }
    | integer_2
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
    ;

object_item_1:
    string_6
        {
            $$ = $1;
        }
    | TOKEN_18 QUOTED_STRING COLON QUOTED_STRING
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_18 QUOTED_STRING COLON number
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_18 QUOTED_STRING COLON boolean
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_18 QUOTED_STRING COLON array
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_18 QUOTED_STRING COLON object
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_18 QUOTED_STRING COLON NULL_TOKEN
        {
            $$.set_object_item($2);
        }
    ;

