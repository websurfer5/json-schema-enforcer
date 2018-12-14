/*
**  schema-lexer.ll
**
*
* Copyright 2018 Jeffrey Kintscher <websurfer@surf2c.net>
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*/

%option prefix="schema_parser_"
%option noyywrap nodefault yylineno reentrant bison-bridge stack
%option extra-type="jsonschemaenforcer::SchemaData *"

%{
    #include "config.h"

namespace jsonschemaenforcer
{
    class SchemaData;
}

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <string>
#include "SchemaData.hh"
#include "schema-stype.hh"
#include "schema-parser.hh"

static void append_utf16_escaped_char(std::string& str, const char *esc_seq);
static void begin_quoted_string(jsonschemaenforcer::SchemaData *sd);
void schema_parser_error(jsonschemaenforcer::SchemaData *sd, const char *s, ...);
static void schema_parser_fatal_error(yyconst char msg[], yyscan_t yyscanner);
bool schema_parser_set_input_buffer(jsonschemaenforcer::SchemaData& sd, const char *str);

#define YY_FATAL_ERROR(msg)     schema_parser_fatal_error(msg, yyscanner);
%}

%x ERROR_RECOVERY
%x IGNORE
%x ITEM_VALUE
%x JSON
%x PROPS
%x QUOTED
%x VALUE_ARRAY

%%

<<EOF>>                     { return EOF_TOKEN; }
[[:space:]]                 { /* unquoted whitespace */ }
":"                         { std::cout << "token: COLON" << std::endl << "new state: ITEM_VALUE" << std::endl; yy_push_state(ITEM_VALUE, yyextra->scaninfo); return COLON; }
","                         { std::cout << "token: COMMA" << std::endl; return COMMA; }
"{"                         {
                                std::cout << "token: LEFT_BRACE" << std::endl << "new state: INITIAL" << std::endl; 
                                yy_push_state(INITIAL, yyextra->scaninfo);
                                return LEFT_BRACE;
                            }
"["                         { std::cout << "token: LEFT_BRACKET" << std::endl; return LEFT_BRACKET; }
"}"                         {
                                std::cout << "token: RIGHT_BRACE" << std::endl; 
                                yy_pop_state(yyextra->scaninfo);
                                std::cout << "new state: " << YYSTATE << std::endl;
                                return RIGHT_BRACE;
                            }
"]"                         { std::cout << "token: RIGHT_BRACKET" << std::endl; return RIGHT_BRACKET; }
"\"additionalItems\""       { std::cout << "token: ADDITIONAL_ITEMS" << std::endl; yyextra->last_key = yytext; return ADDITIONAL_ITEMS; }
"\"additionalProperties\""  { std::cout << "token: ADDITIONAL_PROPERTIES" << std::endl; yyextra->last_key = yytext; return ADDITIONAL_PROPERTIES; }
"\"allOf\""[[:space:]]*":"[[:space:]]*"["   {
                                std::cout << "token: ALL_OF_COLON_LEFT_BRACKET" << std::endl; 
                                yyextra->last_key = yytext;
                                return ALL_OF_COLON_LEFT_BRACKET;
                            }
"\"anyOf\""[[:space:]]*":"[[:space:]]*"["   {
                                std::cout << "token: ANY_OF_COLON_LEFT_BRACKET" << std::endl; 
                                yyextra->last_key = yytext;
                                return ANY_OF_COLON_LEFT_BRACKET;
                            }
"\"contains\""              {
                                std::cout << "token: CONTAINS" << std::endl << "new state: JSON" << std::endl;
                                yyextra->last_key = yytext;
                                yy_push_state(JSON, yyextra->scaninfo);
                                return CONTAINS;
                            }
"\"contentEncoding\""       { std::cout << "token: CONTENT_ENCODING" << std::endl; yyextra->last_key = yytext; return CONTENT_ENCODING; }
"\"contentMediaType\""      { std::cout << "token: CONTENT_MEDIA_TYPE" << std::endl; yyextra->last_key = yytext; return CONTENT_MEDIA_TYPE; }
"\"default\""               { std::cout << "token: DEFAULT" << std::endl; yyextra->last_key = yytext; return DEFAULT; }
"\"definitions\""[[:space:]]*":"[[:space:]]*"{"   {
                                std::cout << "token: DEFINITIONS_COLON_LBRACE" << std::endl << "new state: PROPS" << std::endl; 
                                yyextra->last_key = yytext;
                                yy_push_state(PROPS, yyextra->scaninfo);
                                return DEFINITIONS_COLON_LBRACE;
                            }
"\"dependencies\""[[:space:]]*":"[[:space:]]"{"   {
                                std::cout << "token: DEPENDENCIES_COLON_LBRACE" << std::endl << "new state: PROPS" << std::endl; 
                                yyextra->last_key = yytext;
                                yy_push_state(PROPS, yyextra->scaninfo);
                                return DEPENDENCIES_COLON_LBRACE;
                            }
"\"description\""           { std::cout << "token: DESCRIPTION" << std::endl; yyextra->last_key = yytext; return DESCRIPTION; }
"\"examples\""           { std::cout << "token: EXAMPLES" << std::endl; yyextra->last_key = yytext; return EXAMPLES; }
"\"else\""                  { std::cout << "token: ELSE" << std::endl; yyextra->last_key = yytext; return ELSE; }
"\"enum\""[[:space:]]*":"[[:space:]]*"["  {
                                std::cout << "token: ENUM_COLON_LEFT_BRACKET" << std::endl << "new state: JSON" << std::endl;
                                yyextra->last_key = yytext;
                                yy_push_state(JSON, yyextra->scaninfo);
                                return ENUM_COLON_LEFT_BRACKET;
                            }
"\"exclusiveMaximum\""      { std::cout << "token: EXCLUSIVE_MAXIMUM" << std::endl; yyextra->last_key = yytext; return EXCLUSIVE_MAXIMUM; }
"\"exclusiveMinimum\""      { std::cout << "token: EXCLUSIVE_MINIMUM" << std::endl; yyextra->last_key = yytext; return EXCLUSIVE_MINIMUM; }
"\"format\""                { std::cout << "token: FORMAT" << std::endl; yyextra->last_key = yytext; return FORMAT; }
"\"$id\""                   { std::cout << "token: ID" << std::endl; yyextra->last_key = yytext; return ID; }
"\"if\""                    { std::cout << "token: IF_ITEM" << std::endl; yyextra->last_key = yytext; return IF_ITEM; }
"\"items\""                 { std::cout << "token: ITEMS" << std::endl; yyextra->last_key = yytext; return ITEMS; }
"\"items\""[[:space:]]*:[[:space:]]*"[" { std::cout << "token: ITEMS_ARRAY" << std::endl; yyextra->last_key = yytext; return ITEMS_ARRAY; }
"\"maxItems\""              { std::cout << "token: MAX_ITEMS" << std::endl; yyextra->last_key = yytext; return MAX_ITEMS; }
"\"maxLength\""             { std::cout << "token: MAX_LENGTH" << std::endl; yyextra->last_key = yytext; return MAX_LENGTH; }
"\"maximum\""               { std::cout << "token: MAXIMUM" << std::endl; yyextra->last_key = yytext; return MAXIMUM; }
"\"maxProperties\""         { std::cout << "token: MAX_PROPERTIES" << std::endl; yyextra->last_key = yytext; return MAX_PROPERTIES; }
"\"minProperties\""         { std::cout << "token: MIN_PROPERTIES" << std::endl; yyextra->last_key = yytext; return MIN_PROPERTIES; }
"\"minItems\""              { std::cout << "token: MIN_ITEMS" << std::endl; yyextra->last_key = yytext; return MIN_ITEMS; }
"\"minLength\""             { std::cout << "token: MIN_LENGTH" << std::endl; yyextra->last_key = yytext; return MIN_LENGTH; }
"\"minimum\""               { std::cout << "token: MINIMUM" << std::endl; yyextra->last_key = yytext; return MINIMUM; }
"\"multipleOf\""            { std::cout << "token: MULTIPLE_OF" << std::endl; yyextra->last_key = yytext; return MULTIPLE_OF; }
"\"not\""                   { std::cout << "token: NOT_ITEM" << std::endl; yyextra->last_key = yytext; return NOT_ITEM; }
"\"oneOf\""[[:space:]]*":"[[:space:]]*"["   {
                                std::cout << "token: ONE_OF_COLON_LEFT_BRACKET" << std::endl; 
                                yyextra->last_key = yytext;
                                return ONE_OF_COLON_LEFT_BRACKET;
                            }
"\"pattern\""               { std::cout << "token: PATTERN" << std::endl; yyextra->last_key = yytext; return PATTERN; }
"\"patternProperties\""[[:space:]]*":"[[:space:]]*"{"   {
                                std::cout << "token: PATTERN_PROPERTIES_COLON_BRACE" << std::endl << "new state: PROPS" << std::endl; 
                                yyextra->last_key = yytext;
                                yy_push_state(PROPS, yyextra->scaninfo);
                                return PATTERN_PROPERTIES_COLON_BRACE;
                            }
"\"properties\""[[:space:]]*":"[[:space:]]*"{"   {
                                std::cout << "token: PROPERTIES_COLON_LBRACE" << std::endl << "new state: PROPS" << std::endl; 
                                yyextra->last_key = yytext;
                                yy_push_state(PROPS, yyextra->scaninfo);
                                return PROPERTIES_COLON_LBRACE;
                            }
"\"propertyNames\""         { std::cout << "token: PROPERTY_NAMES" << std::endl; yyextra->last_key = yytext; return PROPERTY_NAMES; }
"\"readOnly\""              { std::cout << "token: READ_ONLY" << std::endl; yyextra->last_key = yytext; return READ_ONLY; }
"\"$ref\""                  { std::cout << "token: REF" << std::endl; yyextra->last_key = yytext; return REF; }
"\"required\""              { std::cout << "token: REQUIRED" << std::endl; yyextra->last_key = yytext; return REQUIRED; }
"\"$schema\""               { std::cout << "token: SCHEMA" << std::endl; yyextra->last_key = yytext; return SCHEMA; }
"\"then\""                  { std::cout << "token: THEN" << std::endl; yyextra->last_key = yytext; return THEN; }
"\"title\""                 { std::cout << "token: TITLE" << std::endl; yyextra->last_key = yytext; return TITLE; }
"\"type\""                  { std::cout << "token: TYPE_TOKEN" << std::endl; yyextra->last_key = yytext; return TYPE_TOKEN; }
"\"uniqueItems\""           { std::cout << "token: UNIQUE_ITEMS" << std::endl; yyextra->last_key = yytext; return UNIQUE_ITEMS; }
"\"writeOnly\""             { std::cout << "token: WRITE_ONLY" << std::endl; yyextra->last_key = yytext; return WRITE_ONLY; }
"\"[^\"]*\""                {
                                std::cout << "token: UNKNOWN_TOKEN" << std::endl; 
                                yyextra->last_key = yytext;
                                BEGIN IGNORE;
                                yyextra->nesting_level = 0;
                                // return UNKNOWN_TOKEN;
                            }
.                           {
                                BEGIN ERROR_RECOVERY;
                                unput(*yytext);
                                yyextra->nesting_level = 0;
                            }
<PROPS>[[:space:]]          { /* ignore whitespace outside of quotes */ }
<PROPS>\"                   { std::cout << "token: <PROPS> \"" << std::endl << "new state: QUOTED" << std::endl; begin_quoted_string(yyextra); }
<PROPS>"["                  { std::cout << "token: <PROPS> LEFT_BRACKET" << std::endl << "new state: VALUE_ARRAY" << std::endl; yy_push_state(VALUE_ARRAY, yyextra->scaninfo); return LEFT_BRACKET; }
<PROPS>"{"                  { std::cout << "token: <PROPS> LEFT_BRACE" << std::endl << "new state: INITIAL" << std::endl; yy_push_state(INITIAL, yyextra->scaninfo); return LEFT_BRACE; }
<PROPS>":"                  { std::cout << "token: <PROPS> COLON" << std::endl; return COLON; }
<PROPS>","                  { std::cout << "token: <PROPS> COMMA" << std::endl; return COMMA; }
<PROPS>"}"                  { std::cout << "token: <PROPS> RIGHT_BRACE" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; return RIGHT_BRACE; }
<PROPS>"false"              { std::cout << "token: <PROPS> B_FALSE" << std::endl; return B_FALSE; }
<PROPS>"true"               { std::cout << "token: <PROPS> B_TRUE" << std::endl; return B_TRUE; }

<JSON>[[:space:]]           { /* ignore whitespace outside of quotes */ }
<JSON>\"                    { std::cout << "token: <JSON> \"" << std::endl << "new state: QUOTED" << std::endl; begin_quoted_string(yyextra); }
<JSON>"{"                   { std::cout << "token: <JSON> LEFT_BRACE" << std::endl << "new state: JSON" << std::endl; yy_push_state(JSON, yyextra->scaninfo); return LEFT_BRACE; }
<JSON>"["                   { std::cout << "token: <JSON> LEFT_BRACKET" << std::endl << "new state: JSON" << std::endl; yy_push_state(JSON, yyextra->scaninfo); return LEFT_BRACKET; }
<JSON>":"                   { std::cout << "token: <JSON> COLON" << std::endl; return COLON; }
<JSON>","                   { std::cout << "token: <JSON> COMMA" << std::endl; return COMMA; }
<JSON>"}"                   { std::cout << "token: <JSON> RIGHT_BRACE" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; return RIGHT_BRACE; }
<JSON>"]"                   { std::cout << "token: <JSON> RIGHT_BRACKET" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; return RIGHT_BRACKET; }
<JSON>[-+]?[0-9]+\.[0-9]*   { yylval->dval = std::stod(yytext); return FLOATING_POINT; }
<JSON>-[0-9]+               { yylval->ival = std::stol(yytext); return NEG_INTEGER; }
<JSON>[+]?[0-9]+            { yylval->ival = std::stol(yytext); return NON_NEG_INTEGER; }
<JSON>"false"               { yylval->bval = false; return B_FALSE; }
<JSON>"true"                { yylval->bval = true; return B_TRUE; }

<ERROR_RECOVERY>[[:space:]] { /* ignore whitespace outside of quotes */ }
<ERROR_RECOVERY>"["         { std::cout << "token: <ERROR_RECOVERY> LEFT_BRACKET" << std::endl;yyextra->nesting_level++; }
<ERROR_RECOVERY>"{"         { std::cout << "token: <ERROR_RECOVERY> LEFT_BRACE" << std::endl; yyextra->nesting_level++; }
<ERROR_RECOVERY>"]"         {
                                std::cout << "token: <ERROR_RECOVERY> RIGHT_BRACKET" << std::endl;
                                if (!yyextra->nesting_level)
                                {
                                    BEGIN INITIAL;
                                    return RIGHT_BRACKET;
                                }
                                else
                                    yyextra->nesting_level--;
                            }
<ERROR_RECOVERY>"}"         {
                                std::cout << "token: <ERROR_RECOVERY> RIGHT_BRACE" << std::endl;
                                if (!yyextra->nesting_level)
                                {
                                    BEGIN INITIAL;
                                    return RIGHT_BRACE;
                                }
                                else
                                    yyextra->nesting_level--;
                            }
<ERROR_RECOVERY>","         {
                                std::cout << "token: <ERROR_RECOVERY> COMMA" << std::endl;
                                if (!yyextra->nesting_level)
                                {
                                    BEGIN INITIAL;
                                    return COMMA;
                                }
                            }
<ERROR_RECOVERY>"\"((\\\")|[^\"])*\"" {std::cout << "token: <ERROR_RECOVERY> string" << std::endl;}
<ERROR_RECOVERY>[-+]?[0-9]+ {std::cout << "token: <ERROR_RECOVERY> number" << std::endl;}
<ERROR_RECOVERY>.           {std::cout << "token: <ERROR_RECOVERY> char" << std::endl;}

<IGNORE>[[:space:]]         { /* ignore whitespace outside of quotes */ }
<IGNORE>"["                 { std::cout << "token: <IGNORE> LEFT_BRACKET" << std::endl;yyextra->nesting_level++; }
<IGNORE>"{"                 { std::cout << "token: <IGNORE> LEFT_BRACE" << std::endl; yyextra->nesting_level++; }
<IGNORE>"]"                 {
                                std::cout << "token: <IGNORE> RIGHT_BRACKET" << std::endl;

                                if (!yyextra->nesting_level)
                                {
                                    BEGIN INITIAL;
                                    unput(*yytext);
                                }
                                else
                                    yyextra->nesting_level--;
                            }
<IGNORE>"}"                 {
                                std::cout << "token: <IGNORE> RIGHT_BRACE" << std::endl;
                                
                                if (!yyextra->nesting_level)
                                {
                                    BEGIN INITIAL;
                                    unput(*yytext);
                                }
                                else
                                    yyextra->nesting_level--;
                            }
<IGNORE>","                 {
                                std::cout << "token: <IGNORE> COMMA" << std::endl;
                                
                                if (!yyextra->nesting_level)
                                {
                                    BEGIN INITIAL;
                                    unput(*yytext);
                                }
                            }
<IGNORE>"\"((\\\")|[^\"])*\"" { std::cout << "token: <IGNORE> QUOTED_STRING" << std::endl;}
<IGNORE>[-+]?(([0-9]+\.?[0-9]*)|([0-9]*\.[0-9]+))   {std::cout << "token: <IGNORE> NUMBER" << std::endl;}
<IGNORE>(true|false|null|:)   {std::cout << "token: <IGNORE> BOOLEAN" << std::endl;}
<IGNORE>.                   {
                                std::cout << "token: <IGNORE> UNKNOWN_TOKEN" << std::endl;
                                BEGIN ERROR_RECOVERY;
                                unput(*yytext);
                            }


<ITEM_VALUE>[[:space:]]     { /* ignore whitespace outside of quotes */ }
<ITEM_VALUE>"false"         { std::cout << "token: <ITEM_VALUE> B_FALSE" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; return B_FALSE; }
<ITEM_VALUE>"true"          { std::cout << "token: <ITEM_VALUE> B_TRUE" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; return B_TRUE; }
<ITEM_VALUE>[-+]?[0-9]+\.   {
                                std::cout << "token: <ITEM_VALUE> malformed number" << std::endl; 
                                BEGIN ERROR_RECOVERY;
                                unput(*yytext);
                                yyextra->nesting_level = 0;
                            }
<ITEM_VALUE>[-+]?[0-9]+\.[0-9]+ { std::cout << "token: <ITEM_VALUE> float" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; yylval->dval = std::stod(yytext); return FLOATING_POINT; }
<ITEM_VALUE>-[0-9]+         { std::cout << "token: <ITEM_VALUE> NEG_INTEGER" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; yylval->ival = std::stol(yytext); return NEG_INTEGER; }
<ITEM_VALUE>[+]?[0-9]+      { std::cout << "token: <ITEM_VALUE> NON_NEG_INTEGER" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; yylval->ival = std::stol(yytext); return NON_NEG_INTEGER; }
<ITEM_VALUE>"{"             { 
                                std::cout << "token: <ITEM_VALUE> LEFT_BRACE" << std::endl << "new state: INITAL" << std::endl; 
                                BEGIN INITIAL;
                                // yy_push_state(INITIAL, yyextra->scaninfo);
                                return LEFT_BRACE;
                            }
<ITEM_VALUE>"["             {
                                std::cout << "token: <ITEM_VALUE> LEFT_BRACKET" << std::endl; 
                                BEGIN VALUE_ARRAY;
                                return LEFT_BRACKET;
                            }
<ITEM_VALUE>"null"          { std::cout << "token: <ITEM_VALUE> NULL_TOKEN" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl; return NULL_TOKEN; }
<ITEM_VALUE>"\""            {
                                std::cout << "token: <ITEM_VALUE> opening quote" << std::endl; 
                                yyextra->quoted_str = "";
                                yyextra->qs_has_cr_or_lf = false;
                                BEGIN QUOTED;
                            }
<ITEM_VALUE>.               {
                                std::cout << "token: <ITEM_VALUE> unknown" << std::endl; 
                                BEGIN ERROR_RECOVERY;
                                unput(*yytext);
                                yyextra->nesting_level = 0;
                            }

<QUOTED>"\\\""              { yyextra->quoted_str += '\"'; }
<QUOTED>"\\\\"              { yyextra->quoted_str += '\\'; }
<QUOTED>"\\/"               { yyextra->quoted_str += '/'; }
<QUOTED>"\\b"               { yyextra->quoted_str += '\b'; }
<QUOTED>"\\f"               { yyextra->quoted_str += '\f'; }
<QUOTED>"\\n"               {
                                yyextra->quoted_str += '\n';
                                yyextra->qs_has_cr_or_lf = true;
                            }
<QUOTED>"\\r"               {
                                yyextra->quoted_str += '\r';
                                yyextra->qs_has_cr_or_lf = true;
                            }
<QUOTED>"\\t"               { yyextra->quoted_str += '\t'; }
<QUOTED>"\""                {
                                std::cout << "token: <QUOTED> closing quote" << std::endl;
                                yy_pop_state(yyextra->scaninfo);
                                std::cout << "new state: " << YYSTATE << std::endl;
                                yylval->sval = yyextra->quoted_str;
                                return QUOTED_STRING;
                            }
<QUOTED>\\u[0-9a-fA-F]{4}   {
                                append_utf16_escaped_char(yyextra->quoted_str, yytext);
                            }
<QUOTED>.                   { yyextra->quoted_str += yytext[0]; }

<VALUE_ARRAY>[[:space:]]    { /* ignore whitespace outside of quotes */ }
<VALUE_ARRAY>":"            { std::cout << "token: <VALUE_ARRAY> COLON" << std::endl; return COLON; }
<VALUE_ARRAY>","            { std::cout << "token: <VALUE_ARRAY> COMMA" << std::endl; return COMMA; }
<VALUE_ARRAY>"["            { std::cout << "token: <VALUE_ARRAY> LEFT_BRACKET" << std::endl; return LEFT_BRACKET; }
<VALUE_ARRAY>"\""           { std::cout << "token: <VALUE_ARRAY> opening quote" << std::endl << "new state: QUOTED" << std::endl; begin_quoted_string(yyextra); }
<VALUE_ARRAY>"]"            { std::cout << "token: <VALUE_ARRAY> RIGHT_BRACKET" << std::endl; yy_pop_state(yyextra->scaninfo); std::cout << "new state: " << YYSTATE << std::endl;return RIGHT_BRACKET; }
<VALUE_ARRAY>.              {
                                std::cout << "token: <VALUE_ARRAY> error" << std::endl;
                                BEGIN ERROR_RECOVERY;
                                unput(*yytext);
                                yyextra->nesting_level = 0;
                            }

%%

void schema_parser_error(jsonschemaenforcer::SchemaData *sd, const char *s, ...)
{
    size_t bufflen = 1024,
           needed;
    std::string vastring;
    va_list ap;
    yy_top_state(sd->scaninfo);
    va_start(ap, s);
    
    while (true)
    {
        char buff[bufflen];
        needed = vsnprintf(buff, bufflen, s, ap);
        
        if (needed < bufflen)
        {
            vastring = buff;
            break;
        }
        
        bufflen += 256;
    }
    
    va_end(ap);
    std::cout << "schema parser error: " << vastring << std::endl;
}

static void begin_quoted_string(jsonschemaenforcer::SchemaData *sd)
{
    sd->quoted_str = "";
    sd->qs_has_cr_or_lf = false;
    yy_push_state(QUOTED, sd->scaninfo);
}

/*
 * append_utf16_escaped_char() expects esc_seq to be a 6-character
 * C string starting with "\\u" followed by 4 hex digits.
 */
static void append_utf16_escaped_char(std::string& str, const char *esc_seq)
{
    uint16_t uval;
    
    uval = ((esc_seq[2] <= '9') ? (esc_seq[2] - '0') : ((esc_seq[2] & 0x07) + 9)) << 12;
    uval += ((esc_seq[3] <= '9') ? (esc_seq[3] - '0') : ((esc_seq[3] & 0x07) + 9)) << 8;
    uval += ((esc_seq[4] <= '9') ? (esc_seq[4] - '0') : ((esc_seq[4] & 0x07) + 9)) << 4;
    uval += ((esc_seq[5] <= '9') ? (esc_seq[5] - '0') : ((esc_seq[5] & 0x07) + 9));
    
    if (uval < 0x0080)
        str += uval & 0xff;
    else if (uval < 0x0800)
    {
        str += (uval >> 6) | 0xc0;
        str += (uval & 0x3f) | 0x80;
    }
    else
    {
        str += (uval >> 12) | 0xe0;
        str += ((uval >> 6) & 0x3f) | 0x80;
        str += (uval & 0x3f) | 0x80;
    }
}

static void schema_parser_fatal_error(yyconst char msg[], yyscan_t yyscanner)
{
    YY_EXTRA_TYPE pd = schema_parser_get_extra(yyscanner);

    /* yyg is used by the BEGIN macro */
    struct yyguts_t *yyg = (struct yyguts_t*) yyscanner;

    schema_parser_error(pd, msg);
    
    if (YYSTATE != ERROR_RECOVERY)
        yyextra->nesting_level = 0;
    
    BEGIN ERROR_RECOVERY;
}

namespace jsonschemaenforcer
{
    bool schema_parser_set_input_buffer(SchemaData& sd, const char *str)
    {
        if (!str)
        {
            std::cerr << "jsonschemaenforcer::schema_set_input_buffer() was passed a NULL pointer" << std::endl;
            return false;
        }

        if (sd.input_bp)
        {
            schema_parser__delete_buffer((YY_BUFFER_STATE) sd.input_bp, sd.scaninfo);
            sd.input_bp = NULL;
        }

        sd.input_bp = schema_parser__scan_string(str, sd.scaninfo);

        if (!sd.input_bp)
        {
            std::cerr << "jsonschemaenforcer::schema_parser__scan_string() failed" << std::endl;
            return false;
        }

        schema_parser__switch_to_buffer((YY_BUFFER_STATE) sd.input_bp, sd.scaninfo);
        return true;
    }
}
