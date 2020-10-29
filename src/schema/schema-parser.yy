//schema-parser.yy
//
// Copyright 2018 Jeffrey Kintscher <websurfer@surf2c.net>
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

%{
#include "config.h"

namespace jsonschemaenforcer
{
    class SchemaData;
}
%}

%define api.prefix {schema_parser_}
%define api.pure full
%define parse.lac full
%define parse.error verbose

%{
#include "schema-stype.hh"
#include "schema-lexer.hh"
#include "SchemaData.hh"
#include "ItemType.hh"
#include <iostream>
#include <map>
#include <regex>

#define SCHEMA_LEX_PARAM sd->scaninfo

void schema_parser_error(jsonschemaenforcer::SchemaData *sd, const char *s, ...);

namespace jsonschemaenforcer
{
    static bool validate_regex(const std::string& pattern);
}

#define BOOL_STR(b)     (b ? "true" : "false")
%}

%lex-param { yyscan_t SCHEMA_LEX_PARAM }
%parse-param { jsonschemaenforcer::SchemaData *sd }

%token ADDITIONAL_ITEMS ADDITIONAL_PROPERTIES ALL_OF_COLON_LEFT_BRACKET
%token ANY_OF_COLON_LEFT_BRACKET
%token B_FALSE B_TRUE
%token COLON COMMA CONTAINS CONTENT_ENCODING CONTENT_MEDIA_TYPE
%token DEFAULT DEFINITIONS_COLON_LBRACE DEPENDENCIES_COLON_LBRACE DESCRIPTION
%token ELSE ENUM_COLON_LEFT_BRACKET EOF_TOKEN EXAMPLES EXCLUSIVE_MAXIMUM EXCLUSIVE_MINIMUM
%token FORMAT
%token <dval> FLOATING_POINT
%token ID IF_ITEM ITEMS ITEMS_ARRAY
%token LEFT_BRACE LEFT_BRACKET
%token MAX_ITEMS MAX_LENGTH MAX_PROPERTIES MAXIMUM MIN_ITEMS MIN_LENGTH
%token MIN_PROPERTIES MINIMUM MULTIPLE_OF
%token <ival> NEG_INTEGER NON_NEG_INTEGER
%token NOT_ITEM NULL_TOKEN
%token ONE_OF_COLON_LEFT_BRACKET
%token PATTERN PATTERN_PROPERTIES_COLON_BRACE
%token <ival> POS_INTEGER
%token PROPERTIES_COLON_LBRACE PROPERTY_NAMES
%token <sval> QUOTED_STRING
%token READ_ONLY REF REQUIRED RIGHT_BRACE RIGHT_BRACKET
%token SCHEMA
%token THEN TITLE TYPE_TOKEN
%token UNIQUE_ITEMS
%token WRITE_ONLY

%type <bval> boolean
%type <bval> can_have_additional_properties_item
%type <bval> items_item_always_true
%type <bval> read_only_item
%type <bval> unique_items_item
%type <bval> write_only_item

%type <dval> maximum_item max_properties_item min_properties_item
%type <dval> minimum_item multiple_of
%type <dval> number

%type <idata> definition_item
%type <idata> properties_item_definition

%type <format_type> format_item

%type <itype> type_item

%type <ival> exclusive_maximum_item exclusive_minimum_item
%type <ival> max_items_item max_length_item min_items_item min_length_item

%type <jitem> default_item
%type <jitem> examples_item
%type <jitem> json_array json_array_element json_object json_object_item

%type <jitem_list> contains_item
%type <jitem_list> enum_item
%type <jitem_list> json_array_elements

%type <jitem_map> json_object_items

%type <sitem> additional_items_item additional_properties_item
%type <sitem> dependencies_property
%type <sitem> else_item
%type <sitem> if_item
%type <sitem> not_item
%type <sitem> properties_item properties_item_schema property_names_item
%type <sitem> then_item

%type <sitemlist> all_of_item any_of_item array_schemas
%type <sitemlist> definitions_list dependencies_item dependencies_properties
%type <sitemlist> items_item
%type <sitemlist> one_of_item
%type <sitemlist> pattern_properties_list properties_items  properties_list

%type <sval> content_encoding_item content_media_type_item
%type <sval> description_item
%type <sval> id_item
%type <sval> pattern_item
%type <sval> ref_item
%type <sval> schema_item string_value
%type <sval> title_item

%type <slist> required_array
%type <slist> string_array string_list
%type <slist> type_array

%destructor { $$.clear(); } <format_type>;
%destructor { $$.clear(); } <idata>;
%destructor { $$.clear(); } <itype>;
%destructor { $$.clear(); } <jitem>;
%destructor { $$.clear(); } <jitem_list>
%destructor { $$.clear(); } <jitem_map>
%destructor { $$.clear(); } <sitem>;
%destructor { $$.clear(); } <sitemlist>;
%destructor { $$.clear(); } <sval>;
%destructor { $$.clear(); } <slist>

%start json_schema

%%

json_schema:
    properties_item_schema
        {
            std::cout << "json_schema 1" << std::endl;
            sd->set_root_item($1);
            YYACCEPT;
        }
    | EOF_TOKEN
        {
            sd->set_root_item(jsonschemaenforcer::SchemaItem());
            YYACCEPT;
        }
    | error
        {
            std::cout << "json_schema error" << std::endl;
            YYABORT;
        }
    ;

schema_item:
    SCHEMA string_value
        {
            std::cout << "schema_item 1" << std::endl;
            $$ = $2;
        }
    ;

id_item:
    ID string_value
        {
            std::cout << "id_item 1" << std::endl;
            $$ = $2;
        }
    ;

title_item:
    TITLE string_value
        {
            std::cout << "title_item 1" << std::endl;
            $$ = $2;
        }
    ;

description_item:
    DESCRIPTION string_value
        {
            std::cout << "description_item 1" << std::endl;
            $$ = $2;
        }
    ;

type_item:
    TYPE_TOKEN string_value
        {
            $$ = $2;
            std::cout << "type_item: " << $$.get_type_name() << std::endl;
        }

type_array:
    TYPE_TOKEN COLON string_array
        {
            std::cout << "type_array: " << $3.size() << std::endl;
            $$ = $3;
        }
    ;

definitions_list:
    DEFINITIONS_COLON_LBRACE properties_items RIGHT_BRACE
        {
            std::cout << "definitions_list 1" << std::endl;
            $$ = $2;
        }
    ;

properties_list:
    PROPERTIES_COLON_LBRACE RIGHT_BRACE
        {
            std::cout << "properties_list 1" << std::endl;
            $$.clear();
        }
    | PROPERTIES_COLON_LBRACE properties_items RIGHT_BRACE
        {
            std::cout << "properties_list 2" << std::endl;
            $$ = $2;
        }
    ;

pattern_properties_list:
    PATTERN_PROPERTIES_COLON_BRACE RIGHT_BRACE
        {
            std::cout << "pattern_properties_list 1" << std::endl;
            $$.clear();
        }
    | PATTERN_PROPERTIES_COLON_BRACE properties_items RIGHT_BRACE
        {
            std::cout << "pattern_properties_list 2" << std::endl;
            jsonschemaenforcer::SchemaItemList::const_iterator c_it;

            for (c_it = $2.cbegin(); c_it != $2.cend(); c_it++)
                if (!jsonschemaenforcer::validate_regex(c_it->get_key()))
                {
                    std::cout << "error: patternProperty \"" << c_it->get_key() << "\"" << std::endl;
                    YYABORT;
                }

            $$ = $2;
        }
    ;

properties_items:
    properties_item
        {
            std::cout << "properties_items 1" << std::endl;
            $$.clear();
            $$.push_back($1);
        }
    | properties_items COMMA properties_item
        {
            std::cout << "properties_items 2" << std::endl;
            $$ = $1;
            $$.push_back($3);
        }
    ;

properties_item:
    QUOTED_STRING COLON properties_item_schema
        {
            std::cout << "properties_item 1: \"" << $1 << "\"" << std::endl;
            $$ = $3;
            $$.set_key($1);
        }
    | QUOTED_STRING COLON boolean
        {
            std::cout << "properties_item 1: \"" << $1 << "\"" << std::endl;
            $$.set_always_true($3);
            $$.set_key($1);
        }
    ;    

properties_item_schema:
    LEFT_BRACE properties_item_definition RIGHT_BRACE
        {
            std::cout << "properties_item_schema 1" << std::endl;
            
            if (!$$.define_item("", $2))
            {
                std::cout << "invalid item definition with types " << $$.get_type_set() << std::endl;
                YYABORT;
            }
        }
    ;

properties_item_definition:
    definition_item
        {
            std::cout << "properties_item_definition 1" << std::endl;
            $$ = $1;
        }
    | properties_item_definition COMMA definition_item
        {
            std::cout << "properties_item_definition 2" << std::endl;
            $$ = $1 | $3;
        }
    ;

definition_item:
    schema_item
        {
            std::cout << "definition_item schema_item" << std::endl;
            $$.set_item_schema($1);
        }
    | id_item
        {
            std::cout << "definition_item id_item" << std::endl;
            $$.set_item_id($1);
        }
    | title_item
        {
            std::cout << "definition_item title_item" << std::endl;
            $$.set_title($1);
        }
    | description_item
        {
            std::cout << "definition_item description_item" << std::endl;
            $$.set_item_description($1);
        }
    | type_item
        {
            std::cout << "definition_item type_item" << std::endl;
            $$.set_item_type($1);
        }
    | pattern_properties_list
        {
            std::cout << "definition_item pattern_properties_list" << std::endl;
            $$.set_item_pattern_properties($1);
        }
    | properties_list
        {
            std::cout << "definition_item properties_list" << std::endl;
            $$.set_item_properties($1);
        }
    | required_array
        {
            std::cout << "definition_item required_array" << std::endl;
            $$.set_item_required($1);
        }
    | dependencies_item
        {
            std::cout << "definition_item dependencies_item" << std::endl;
            $$.set_item_dependencies($1);
        }
    | min_items_item
        {
            std::cout << "definition_item min_items_item" << std::endl;
            $$.set_item_min_items($1);
        }
    | max_items_item
        {
            std::cout << "definition_item max_items_item" << std::endl;
            $$.set_item_max_items($1);
        }
    | unique_items_item
        {
            std::cout << "definition_item unique_items_item" << std::endl;
            $$.set_item_unique_items($1);
        }
    | exclusive_minimum_item
        {
            std::cout << "definition_item exclusive_minimum_item" << std::endl;
            $$.set_item_exclusive_minimum($1);
        }
    | exclusive_maximum_item
        {
            std::cout << "definition_item exclusive_maximum_item" << std::endl;
            $$.set_item_exclusive_maximum($1);
        }
    | minimum_item
        {
            std::cout << "definition_item minimum_item" << std::endl;
            $$.set_item_minimum($1);
        }
    | maximum_item
        {
            std::cout << "definition_item maximum_item" << std::endl;
            $$.set_item_maximum($1);
        }
    | items_item
        {
            std::cout << "definition_item items_item" << std::endl;

            if (!$1.empty())
                $1.begin()->set_first_array_item();

            $$.set_array_properties($1);
        }
    | items_item_always_true
        {
            std::cout << "definition_item items_item" << std::endl;
            $$.set_items_always_true($1);
        }
    | ref_item
        {
            std::cout << "definition_item ref_item" << std::endl;
            $$.set_item_ref($1);
        }
    | multiple_of
        {
            std::cout << "definition_item multipleOf" << std::endl;
            $$.set_item_multiple_of($1);
        }
    | pattern_item
        {
            std::cout << "definition_item pattern_item" << std::endl;
            $$.set_item_pattern($1);
        }
    | max_length_item
        {
            std::cout << "definition_item max_length_item" << std::endl;
            $$.set_item_max_length($1);
        }
    | min_length_item
        {
            std::cout << "definition_item min_length_item" << std::endl;
            $$.set_item_min_length($1);
        }
    | additional_items_item
        {
            std::cout << "definition_item additional_items_item" << std::endl;
            $$.set_item_additional_items($1);
        }
    | additional_properties_item
        {
            std::cout << "definition_item additional_properties_item" << std::endl;
            $$.set_item_additional_properties($1);
        }
    | can_have_additional_properties_item
        {
            std::cout << "definition_item can_have_additional_properties_item" << std::endl;
            $$.set_item_can_have_additional_properties($1);
        }
    | property_names_item
        {
            std::cout << "definition_item property_names_item" << std::endl;
            $$.set_item_property_names($1);
        }
    | contains_item
        {
            std::cout << "definition_item contains_item" << std::endl;
            $$.set_item_contains($1);
        }
    | max_properties_item
        {
            std::cout << "definition_item max_properties_item" << std::endl;
            $$.set_item_max_properties($1);
        }
    | min_properties_item
        {
            std::cout << "definition_item min_properties_item" << std::endl;
            $$.set_item_min_properties($1);
        }
    | one_of_item
        {
            std::cout << "definition_item one_of_item" << std::endl;
            $$.set_item_one_of($1);
        }
    | any_of_item
        {
            std::cout << "definition_item any_of_item" << std::endl;
            $$.set_item_any_of($1);
        }
    | all_of_item
        {
            std::cout << "definition_item all_of_item" << std::endl;
            $$.set_item_all_of($1);
        }
    | enum_item
        {
            std::cout << "definition_item enum_item" << std::endl;
            $$.set_item_enum($1);
        }
    | definitions_list
        {
            std::cout << "definition_item definitions_list" << std::endl;
            $$.set_item_definitions($1);
        }
    | format_item
        {
            std::cout << "definition_item format_item" << std::endl;
            $$.set_item_format_type($1);
            $$.add_item_type(jsonschemaenforcer::ItemType::type_String);
        }
    | not_item
        {
            std::cout << "definition_item not_item" << std::endl;
            $$.set_item_not_schema($1);
        }
    | if_item
        {
            std::cout << "definition_item if_item" << std::endl;
            $$.set_item_if_schema($1);
        }
    | else_item
        {
            std::cout << "definition_item else_item" << std::endl;
            $$.set_item_else_schema($1);
        }
    | then_item
        {
            std::cout << "definition_item then_item" << std::endl;
            $$.set_item_then_schema($1);
        }
    | content_encoding_item
        {
            std::cout << "definition_item content_encoding_item" << std::endl;
            $$.set_item_content_encoding($1);
        }
    | content_media_type_item
        {
            std::cout << "definition_item content_media_type_item" << std::endl;
            $$.set_item_content_media_type($1);
        }
    | default_item
        {
            std::cout << "definition_item default_item" << std::endl;
            $$.set_item_default_value($1);
        }
    | read_only_item
        {
            std::cout << "definition_item read_only_item" << std::endl;
            $$.set_item_read_only($1);
        }
    | write_only_item
        {
            std::cout << "definition_item write_only_item" << std::endl;
            $$.set_item_write_only($1);
        }
    | examples_item
        {
            std::cout << "definition_item examples_item" << std::endl;
            
            if (!$$.add_item_examples($1))
            {
                std::cout << "error: unable to append examples to examples array" << std::endl;
                YYABORT;
            }
        }
    | type_array
        {
            std::cout << "definition_item write_only_item" << std::endl;
            $$.set_item_type_list($1);
        }
    ;

required_array:
    REQUIRED COLON empty_array
        {
            std::cout << "required_array 1" << std::endl;
            $$.clear();
        }
    | REQUIRED COLON string_array
        {
            std::cout << "required_array 1" << std::endl;
            $$ = $3;
        }
    ;

dependencies_item:
    DEPENDENCIES_COLON_LBRACE RIGHT_BRACE
        {
            std::cout << "dependencies_item 1" << std::endl;
            $$.clear();
        }
    | DEPENDENCIES_COLON_LBRACE dependencies_properties RIGHT_BRACE
        {
            std::cout << "dependencies_item 1" << std::endl;
            $$ = $2;
        }
    ;

dependencies_properties:
    dependencies_property
        {
            std::cout << "dependencies_properties 1" << std::endl;
            $$.clear();
            $$.push_back($1);
        }
    | dependencies_properties COMMA dependencies_property
        {
            std::cout << "dependencies_properties 1" << std::endl;
            $$ = $1;
            $$.push_back($3);
        }
    ;

dependencies_property:
    QUOTED_STRING COLON string_array
        {
            std::cout << "dependencies_property array" << std::endl;
            $$.define_dependency_array($1, $3);
        }
    | properties_item
        {
            std::cout << "dependencies_property properties_item" << std::endl;
            $$ = $1;
        }
    ;

string_array:
    LEFT_BRACKET string_list RIGHT_BRACKET
        {
            std::cout << "string_array" << std::endl;
            $$ = $2;
        }
    ;

min_items_item:
    MIN_ITEMS COLON NON_NEG_INTEGER
        {
            std::cout << "min_items_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

exclusive_maximum_item:
    EXCLUSIVE_MAXIMUM COLON number
        {
            std::cout << "exclusive_maximum_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

exclusive_minimum_item:
    EXCLUSIVE_MINIMUM COLON number
        {
            std::cout << "exclusive_minimum_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

max_items_item:
    MAX_ITEMS COLON NON_NEG_INTEGER
        {
            std::cout << "max_items_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

maximum_item:
    MAXIMUM COLON number
        {
            std::cout << "maximum_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

minimum_item:
    MINIMUM COLON number
        {
            std::cout << "minimum_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

unique_items_item:
    UNIQUE_ITEMS COLON boolean
        {
            std::cout << "unique_items_item 1: " << BOOL_STR($3) << std::endl;
            $$ = $3;
        }
    ;

items_item:
    ITEMS_ARRAY array_schemas RIGHT_BRACKET
        {
            std::cout << "items_item array_schemas" << std::endl;
            $$ = $2;
        }
    | ITEMS COLON LEFT_BRACE properties_item_definition RIGHT_BRACE
        {
            std::cout << "items_item properties_item_definition" << std::endl;
            jsonschemaenforcer::SchemaItem s_item;

            if (!s_item.define_item("", $4))
            {
                std::cout << "invalid item definition" << std::endl;
                YYABORT;
            }

            s_item.set_array_singleton_item();
            $$.clear();
            $$.push_back(s_item);
        }
    ;

items_item_always_true:
    ITEMS COLON boolean
        {
            std::cout << "items_item " << BOOL_STR($3) << std::endl;
            $$ = $3;
        }
    ;

multiple_of:
    MULTIPLE_OF COLON number
        {
            std::cout << "multiple_of 1: " << $3 << std::endl;
            $$ = $3;
        }

array_schemas:
    properties_item_schema
        {
            std::cout << "array_schemas 1" << std::endl;
            $$.clear();
            $$.push_back($1);
        }
    | array_schemas COMMA properties_item_schema
        {
            std::cout << "array_schemas 2" << std::endl;
            $$ = $1;
            $$.push_back($3);
        }
    ;


ref_item:
    REF string_value
        {
            std::cout << "ref_item 1" << std::endl;
            $$ = $2;
        }
    ;

pattern_item:
    PATTERN string_value
        {
            std::cout << "pattern_item 1: \"" << $2 << "\"" << std::endl;

            if (!jsonschemaenforcer::validate_regex($2))
            {
                std::cout << "invalid regex in pattern item: \"" << $2 << "\"" << std::endl;
                YYABORT;
            }
            else
            {
                $$ = $2;
            }
        }
    ;

max_length_item:
    MAX_LENGTH COLON NON_NEG_INTEGER
        {
            std::cout << "max_length_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

min_length_item:
    MIN_LENGTH COLON NON_NEG_INTEGER
        {
            std::cout << "min_length_item 1: " << $3 << std::endl;
            $$ = $3;
        }
    ;

additional_items_item:
    ADDITIONAL_ITEMS COLON properties_item_schema
        {
            std::cout << "additional_items_item 1" << std::endl;
            $$ = $3;
        }
    ;

additional_properties_item:
    ADDITIONAL_PROPERTIES COLON properties_item_schema
        {
            std::cout << "additional_properties_item properties_item_schema" << std::endl;
            $3.set_additional_property();
            $$ = $3;
        }
    ;

can_have_additional_properties_item:
    ADDITIONAL_PROPERTIES COLON boolean
        {
            std::cout << "additional_properties_item_false" << std::endl;
            $$ = $3;
        }
    ;

property_names_item:
    PROPERTY_NAMES COLON properties_item_schema
        {
            std::cout << "property_names_item 1" << std::endl;

            if (!$3.has_String_type())
            {
                std::cout << "error: propertyNames schema type must be \"string\".  Found:\"" << $3.get_type_set() << "\"" << std::endl;
                YYABORT;
            }

            $3.set_property_names_schema();
            $$ = $3;
        }
    ;

contains_item:
    CONTAINS COLON LEFT_BRACKET json_array_elements RIGHT_BRACKET
        {
            std::cout << "contains_item 1" << std::endl;
            $$ = $4;
        }

enum_item:
    ENUM_COLON_LEFT_BRACKET json_array_elements RIGHT_BRACKET
        {
            std::cout << "enum_item 1" << std::endl;
            $$ = $2;
        }

json_array:
    empty_array
        {
            std::cout << "json_array 1" << std::endl;
            $$.clear();
        }
    | LEFT_BRACKET json_array_elements RIGHT_BRACKET
        {
            std::cout << "json_array 2" << std::endl;
            $$.set_array($2);
        }
    ;

json_array_elements:
    json_array_element
        {
            std::cout << "json_array_elements 1" << std::endl;
            $$.clear();
            $$.push_back($1);
        }
    | json_array_elements COMMA json_array_element
        {
            std::cout << "json_array_elements 2" << std::endl;
            $$ = $1;
            $$.push_back($3);
        }
    ;

json_array_element:
    QUOTED_STRING
        {
            std::cout << "json_array_element QUOTED_STRING: \"" << $1 << "\"" << std::endl;
            $$.set_string($1);
        }
    | number
        {
            std::cout << "json_array_element number: " << $1 << std::endl;
            $$.set_number($1);
        }
    | boolean
        {
            std::cout << "json_array_element boolean: " << BOOL_STR($1) << std::endl;
            $$.set_boolean($1);
        }
    | json_array
        {
            std::cout << "json_array_element json_array" << std::endl;
            $$ = $1;
        }
    | json_object
        {
            std::cout << "json_array_element json_object" << std::endl;
            $$ = $1;
        }
    ;

json_object:
    LEFT_BRACE RIGHT_BRACE
        {
            std::cout << "json_object 1" << std::endl;
            $$.clear();
        }
    | LEFT_BRACE json_object_items RIGHT_BRACE
        {
            std::cout << "json_object 2" << std::endl;
            $$.set_object($2);
        }
    ;

json_object_items:
    json_object_item
        {
            std::cout << "json_object_items 1" << std::endl;
            $$.clear();
            $$[$1.key] = $1;
        }
    | json_object_items COMMA json_object_item
        {
            std::cout << "json_object_items 2" << std::endl;
            $$ = $1;
            $$[$3.key] = $3;
        }
    ;

json_object_item:
    QUOTED_STRING COLON QUOTED_STRING
        {
            std::cout << "json_object_item QUOTED_STRING: \"" << $1 << "\": \"" << $3 << "\"" << std::endl;
            $$.set_string($1, $3);
        }
    | QUOTED_STRING COLON number
        {
            std::cout << "json_object_item number: \"" << $1 << "\": " << $3 << std::endl;
            $$.set_number($1, $3);
        }
    | QUOTED_STRING COLON boolean
        {
            std::cout << "json_object_item boolean: \"" << $1 << "\": " << $3 << std::endl;
            $$.set_boolean($1, $3);
        }
    | QUOTED_STRING COLON json_array
        {
            std::cout << "json_object_item json_array: \"" << $1 << "\"" << std::endl;
            $$ = $3;
            $$.set_key($1);
        }
    | QUOTED_STRING COLON json_object
        {
            std::cout << "json_object_item json_object_item: \"" << $1 << "\"" << std::endl;
            $$ = $3;
            $$.set_key($1);
        }
    ;

max_properties_item:
    MAX_PROPERTIES COLON NON_NEG_INTEGER
        {
            std::cout << "max_properties_item: " << $3 << std::endl;
            $$ = $3;
        }
    ;

min_properties_item:
    MIN_PROPERTIES COLON NON_NEG_INTEGER
        {
            std::cout << "min_properties_item: " << $3 << std::endl;
            $$ = $3;
        }
    ;

one_of_item:
    ONE_OF_COLON_LEFT_BRACKET array_schemas RIGHT_BRACKET
        {
            std::cout << "one_of_item 1" << std::endl;
            $$ = $2;
        }
    ;

any_of_item:
    ANY_OF_COLON_LEFT_BRACKET array_schemas RIGHT_BRACKET
        {
            std::cout << "any_of_item 1" << std::endl;
            $$ = $2;
        }
    ;

all_of_item:
    ALL_OF_COLON_LEFT_BRACKET array_schemas RIGHT_BRACKET
        {
            std::cout << "all_of_item 1" << std::endl;
            $$ = $2;
        }
    ;

format_item:
    FORMAT string_value
        {
            std::cout << "format_item: \"" << $2 << "\"" << std::endl;
            $$ = $2;
        }
    ;

not_item:
    NOT_ITEM COLON properties_item_schema
        {
            std::cout << "not_item 1" << std::endl;
            $$ = $3;
        }
    ;

then_item:
    THEN COLON properties_item_schema
        {
            std::cout << "then_item 1" << std::endl;
            $$ = $3;
        }
    ;

else_item:
    ELSE COLON properties_item_schema
        {
            std::cout << "else_item 1" << std::endl;
            $$ = $3;
        }
    ;

if_item:
    IF_ITEM COLON properties_item_schema
        {
            std::cout << "if_item 1" << std::endl;
            $$ = $3;
        }
    ;

content_encoding_item:
    CONTENT_ENCODING string_value
        {
            std::cout << "content_encoding_item: \"" << $2 << "\"" << std::endl;
            $$ = $2;
        }
    ;

content_media_type_item:
    CONTENT_MEDIA_TYPE string_value
        {
            std::cout << "content_media_type_item: \"" << $2 << "\"" << std::endl;
            $$ = $2;
        }
    ;

default_item:
    DEFAULT COLON json_array_element
        {
            std::cout << "default_item 1" << std::endl;
            $$ = $3;
        }
    ;

read_only_item:
    READ_ONLY COLON boolean
        {
            std::cout << "read_only_item: " << BOOL_STR($3) << std::endl;
            $$ = $3;
        }
    ;

write_only_item:
    WRITE_ONLY COLON boolean
        {
            std::cout << "write_only_item: " << BOOL_STR($3) << std::endl;
            $$ = $3;
        }
    ;

examples_item:
    EXAMPLES COLON json_array
        {
            std::cout << "item_examples 1"<< std::endl;
            $$ = $3;
        }
    ;

empty_array:
    LEFT_BRACKET RIGHT_BRACKET
        { std::cout << "empty_array 1" << std::endl; }
    ;

string_value:
    COLON QUOTED_STRING
        {
            std::cout << "string_value 1" << std::endl;
            $$ = $2;
        }
    ;

string_list:
    QUOTED_STRING
        {
            std::cout << "string_list 1" << std::endl;
            $$.clear();
            $$.push_back($1);
        }
    | string_list COMMA QUOTED_STRING
        {
            std::cout << "string_list 2" << std::endl;
            $$ = $1;
            $$.push_back($3);
        }
    ;

boolean:
        B_TRUE
            {
                std::cout << "boolean true" << std::endl;
                $$ = 1;
            }
        | B_FALSE
            {
                std::cout << "boolean false" << std::endl;
                $$ = 0;
            }
        ;

number:
    FLOATING_POINT
        {
            std::cout << "number FLOATING_POINT: " << $1 << std::endl;
            $$ = $1;
        }
    | NON_NEG_INTEGER
        {
            std::cout << "number NON_NEG_INTEGER: " << $1 << std::endl;
            $$ = $1;
        }
    | NEG_INTEGER
        {
            std::cout << "number NEG_INTEGER: " << $1 << std::endl;
            $$ = $1;
        }
    ;
/*
unknown_item:
        UNKNOWN_TOKEN
        ;
*/

%%

namespace jsonschemaenforcer
{
    class _RegexErrorMap : public std::map<std::regex_constants::error_type, std::string>
    {
    public:
        _RegexErrorMap()
        {
            (*this)[std::regex_constants::error_collate] = "pattern contains an invalid collating element name";
            (*this)[std::regex_constants::error_ctype] = "pattern contains an invalid character class name";
            (*this)[std::regex_constants::error_escape] = "pattern contains an invalid escaped character or a trailing space";
            (*this)[std::regex_constants::error_backref] = "pattern contains an invalid back reference";
            (*this)[std::regex_constants::error_brack] = "pattern contains mismatched brackets ('[' and ']')";
            (*this)[std::regex_constants::error_paren] = "pattern contains mismatched parentheses ('(' and ')')";
            (*this)[std::regex_constants::error_brace] = "pattern contains mismatched braces ('{' and '}')";
            (*this)[std::regex_constants::error_badbrace] = "pattern contains an invalid range between braces ('{' and '}')";
            (*this)[std::regex_constants::error_range] = "pattern contains an invalid character range";
            (*this)[std::regex_constants::error_space] = "insufficient memory to compile pattern";
            (*this)[std::regex_constants::error_badrepeat] = "pattern contains a repeat specifier (one of *?+{) that is not preceded by a valid regular expression";
            (*this)[std::regex_constants::error_complexity] = "complexity of an attempted match against a regular expression exceeded a pre-set level";
            (*this)[std::regex_constants::error_stack] = "insufficient memory available to match pattern";
        };
    };

    static const _RegexErrorMap _regex_error_map;

    static bool validate_regex(const std::string& pattern)
    {
        bool success = true;

        try
        {
            std::regex r(pattern, std::regex::ECMAScript | std::regex::optimize);
        }
        catch (std::regex_error& e)
        {
            _RegexErrorMap::const_iterator it;

            success = false;
            std::cout << "error in pattern \"" << pattern << "\": " << e.code() << ": ";
            it = _regex_error_map.find(e.code());

            if (it != _regex_error_map.end())
                std::cout  << it->second;
            else
                std::cout << "unknown error";

            std::cout << std::endl;
        }

        return success;
    }
}
