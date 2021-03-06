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
#include "stype-object-dependencies1.hh"
#include "lexer-object-dependencies1.hh"
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
%token TOKEN_2
%token TOKEN_3

%type <foo__JsonItem_type> array
%type <foo__JsonItem_type> array_item
%type <foo__JsonItemVector_type> array_items
%type <bool_type> boolean
%type <long_type> integer
%type <foo__JsonItem_type> integer_0
%type <double_type> number
%type <foo__JsonItem_type> number_0
%type <foo__JsonItem_type> object
%type <foo__JsonItem_type> object_0
%type <foo__JsonItem_type> object_item
%type <foo__JsonItem_type> object_item_0
%type <foo__JsonItemMap_type> object_items
%type <foo__JsonItemMap_type> object_items_0
%type <foo__JsonItem_type> string_0

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

number_0:
    TOKEN_0 QUOTED_STRING number
        {
            $$.set_object_item($2, $3);
        }
    ;

integer_0:
    TOKEN_1 QUOTED_STRING COLON integer
        {
            $$.set_object_item($2, $4);
        }
    ;

string_0:
    TOKEN_2 QUOTED_STRING QUOTED_STRING
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
    | LEFT_BRACE object_items_0 RIGHT_BRACE
        {
            if ($2.find("foo") == $2.end())
            {
                if ($2.find("foo") == $2.end())
                {
                    std::cerr << "Object missing dependency object property: \"foo\"" << std::endl;
                    YYABORT;
                }

                if ($2.find("bar") == $2.end())
                {
                    std::cerr << "Object missing dependency object property: \"bar\"" << std::endl;
                    YYABORT;
                }
            }

            $$.set_object($2);
        }
    ;

object_item_0:
    number_0
        {
            $$ = $1;
        }
    | integer_0
        {
            $$ = $1;
        }
    | string_0
        {
            $$ = $1;
        }
    | TOKEN_3 QUOTED_STRING COLON QUOTED_STRING
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_3 QUOTED_STRING COLON number
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_3 QUOTED_STRING COLON boolean
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_3 QUOTED_STRING COLON array
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_3 QUOTED_STRING COLON object
        {
            $$.set_object_item($2, $4);
        }
    | TOKEN_3 QUOTED_STRING COLON NULL_TOKEN
        {
            $$.set_object_item($2);
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

