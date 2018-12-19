%option prefix="foo_foo_"
%option extra-type="foo::Bar *"
%option noyywrap nodefault yylineno reentrant bison-bridge stack

%{
namespace foo
{
    class Bar;
}

#include <string>
#include "Bar.hh"
#include "stype-object-string-all.hh"
#include "parser-object-string-all.hh"

   static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str);
%}

%x ITEM_ARRAY
%x ITEM_OBJECT
%x ITEM_VALUE
%x PARSE_ARRAY_KEY
%x PARSE_ITEM_KEY
%x PARSE_OBJECT_KEY
%x QUOTED
%x SSTATE_0
%x SSTATE_1
%x SSTATE_10
%x SSTATE_11
%x SSTATE_12
%x SSTATE_13
%x SSTATE_14
%x SSTATE_15
%x SSTATE_2
%x SSTATE_3
%x SSTATE_4
%x SSTATE_5
%x SSTATE_6
%x SSTATE_7
%x SSTATE_8
%x SSTATE_9

%%
"{"  	{
     	    yy_push_state(SSTATE_0, yyextra->scaninfo);
     	    return LEFT_BRACE;
     	}
"}"  	{
     	    yy_pop_state(yyextra->scaninfo);
     	    return RIGHT_BRACE;
     	}
[[:space:]]  	{
             	}
<ITEM_ARRAY>","  	{
                 	    return COMMA;
                 	}
<ITEM_ARRAY>"]"  	{
                 	    yy_pop_state(yyextra->scaninfo);
                 	    return RIGHT_BRACKET;
                 	}
<ITEM_ARRAY>.  	{
               	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
               	    unput(*yytext);
               	}
<ITEM_ARRAY>[[:space:]]  	{
                         	}
<ITEM_OBJECT>","  	{
                  	    return COMMA;
                  	}
<ITEM_OBJECT>":"  	{
                  	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                  	    return COLON;
                  	}
<ITEM_OBJECT>"\""  	{
                   	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                   	    unput(*yytext);
                   	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                   	}
<ITEM_OBJECT>"}"  	{
                  	    yy_pop_state(yyextra->scaninfo);
                  	    return RIGHT_BRACE;
                  	}
<ITEM_OBJECT>[[:space:]]  	{
                          	}
<ITEM_VALUE>"["  	{
                 	    yy_push_state(ITEM_ARRAY, yyextra->scaninfo);
                 	    return LEFT_BRACKET;
                 	}
<ITEM_VALUE>"\""  	{
                  	    BEGIN QUOTED;
                  	    yyextra->quoted_str.clear();
                  	}
<ITEM_VALUE>"false"  	{
                     	    yy_pop_state(yyextra->scaninfo);
                     	    return B_FALSE;
                     	}
<ITEM_VALUE>"null"  	{
                    	    yy_pop_state(yyextra->scaninfo);
                    	    return NULL_TOKEN;
                    	}
<ITEM_VALUE>"true"  	{
                    	    yy_pop_state(yyextra->scaninfo);
                    	    return B_TRUE;
                    	}
<ITEM_VALUE>"{"  	{
                 	    yy_push_state(ITEM_OBJECT, yyextra->scaninfo);
                 	    return LEFT_BRACE;
                 	}
<ITEM_VALUE>-[0-9]+  	{
                     	    yy_pop_state(yyextra->scaninfo);
                     	    yylval->long_type = std::stol(yytext);
                     	    return NEG_INTEGER;
                     	}
<ITEM_VALUE>[+]?[0-9]+  	{
                        	    yy_pop_state(yyextra->scaninfo);
                        	    yylval->long_type = std::stol(yytext);
                        	    return NON_NEG_INTEGER;
                        	}
<ITEM_VALUE>[-+]?[0-9]+\.[0-9]*  	{
                                 	    yy_pop_state(yyextra->scaninfo);
                                 	    yylval->double_type = std::stod(yytext);
                                 	    return FLOATING_POINT;
                                 	}
<ITEM_VALUE>[[:space:]]  	{
                         	}
<PARSE_ARRAY_KEY>"\""  	{
                       	    yy_push_state(QUOTED, yyextra->scaninfo);
                       	}
<PARSE_ARRAY_KEY>[[:space:]]*:[[:space:]]*"["  	{
                                               	    yy_pop_state(yyextra->scaninfo);
                                               	}
<PARSE_ITEM_KEY>"\""  	{
                      	    yy_push_state(QUOTED, yyextra->scaninfo);
                      	}
<PARSE_ITEM_KEY>[[:space:]]*:[[space:]]*  	{
                                          	    yy_pop_state(yyextra->scaninfo);
                                          	    return COLON;
                                          	}
<PARSE_OBJECT_KEY>"\""  	{
                        	    yy_push_state(QUOTED, yyextra->scaninfo);
                        	}
<PARSE_OBJECT_KEY>[[:space:]]*:[[:space:]]*"{"  	{
                                                	    yy_pop_state(yyextra->scaninfo);
                                                	}
<QUOTED>"\""  	{
              	    yy_pop_state(yyextra->scaninfo);
              	    yylval->std__string_type = yyextra->quoted_str;
              	    return QUOTED_STRING;
              	}
<QUOTED>"\\/"  	{
               	    yyextra->quoted->str += '/';
               	}
<QUOTED>"\\\""  	{
                	    yyextra->quoted->str += '\"';
                	}
<QUOTED>"\\\\"  	{
                	    yyextra->quoted->str += '\\';
                	}
<QUOTED>"\\b"  	{
               	    yyextra->quoted->str += '\b';
               	}
<QUOTED>"\\f"  	{
               	    yyextra->quoted->str += '\f';
               	}
<QUOTED>"\\n"  	{
               	    yyextra->quoted->str += '\n';
               	}
<QUOTED>"\\r"  	{
               	    yyextra->quoted->str += '\r';
               	}
<QUOTED>"\\t"  	{
               	    yyextra->quoted->str += '\t';
               	}
<QUOTED>\\u[0-9a-fA-F]{4}  	{
                           	    uint16_t uval;
                           	    
                           	    uval = ((yytext[2] <= '9') ? (yytext[2] - '0') : ((yytext[2] & 0x07) + 9)) << 12;
                           	    uval += ((yytext[3] <= '9') ? (yytext[3] - '0') : ((yytext[3] & 0x07) + 9)) << 8;
                           	    uval += ((yytext[4] <= '9') ? (yytext[4] - '0') : ((yytext[4] & 0x07) + 9)) << 4;
                           	    uval += ((yytext[5] <= '9') ? (yytext[5] - '0') : ((yytext[5] & 0x07) + 9));
                           	    
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
<SSTATE_0>","  	{
               	    return COMMA;
               	}
<SSTATE_0>"\""  	{
                	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                	    unput(*yytext);
                	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                	    return TOKEN_10;
                	}
<SSTATE_0>"\"foo10\""[[:space:]]*:[[:space:]]*  	{
                                                	    yy_push_state(SSTATE_15, yyextra->scaninfo);
                                                	    foo_foo_unput_string_0(yyscanner, yytext);
                                                	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                                	    return TOKEN_9;
                                                	}
<SSTATE_0>"\"foo1\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_2, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_0;
                                               	}
<SSTATE_0>"\"foo2\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_4, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_1;
                                               	}
<SSTATE_0>"\"foo3\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_6, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_2;
                                               	}
<SSTATE_0>"\"foo4\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_8, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_3;
                                               	}
<SSTATE_0>"\"foo5\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_10, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_4;
                                               	}
<SSTATE_0>"\"foo6\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_12, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_5;
                                               	}
<SSTATE_0>"\"foo7\""[[:space:]]*:[[:space:]]*  	{
                                               	    yy_push_state(SSTATE_13, yyextra->scaninfo);
                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                               	    return TOKEN_6;
                                               	}
<SSTATE_0>"\"foo8\""  	{
                      	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                      	    foo_foo_unput_string_0(yyscanner, yytext);
                      	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                      	    return TOKEN_7;
                      	}
<SSTATE_0>"\"foo9\""  	{
                      	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                      	    foo_foo_unput_string_0(yyscanner, yytext);
                      	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                      	    return TOKEN_8;
                      	}
<SSTATE_0>"}"  	{
               	    yy_pop_state(yyextra->scaninfo);
               	    return RIGHT_BRACE;
               	}
<SSTATE_0>[[:space:]]  	{
                       	}
<SSTATE_1>"\"[^\"]*test[123]+[^\"]*\""  	{
                                        	    BEGIN ITEM_VALUE;
                                        	    foo_foo_unput_string_0(yyscanner, yytext);
                                        	}
<SSTATE_10>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){0,258}\""  	{
                                                                                                       	    BEGIN SSTATE_9;
                                                                                                       	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                       	}
<SSTATE_11>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""  	{
                                                                                                 	    BEGIN ITEM_VALUE;
                                                                                                 	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                 	}
<SSTATE_12>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){0,259}\""  	{
                                                                                                       	    BEGIN SSTATE_11;
                                                                                                       	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                       	}
<SSTATE_13>"\"[^\"]*test[680]+[^\"]*\""  	{
                                         	    BEGIN ITEM_VALUE;
                                         	    foo_foo_unput_string_0(yyscanner, yytext);
                                         	}
<SSTATE_14>"\"[^\"]*test[456]+[^\"]*\""  	{
                                         	    BEGIN ITEM_VALUE;
                                         	    foo_foo_unput_string_0(yyscanner, yytext);
                                         	}
<SSTATE_15>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){12,}\""  	{
                                                                                                     	    BEGIN SSTATE_14;
                                                                                                     	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                     	}
<SSTATE_2>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){10,256}\""  	{
                                                                                                       	    BEGIN SSTATE_1;
                                                                                                       	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                       	}
<SSTATE_3>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""  	{
                                                                                                	    BEGIN ITEM_VALUE;
                                                                                                	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                	}
<SSTATE_4>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){11,257}\""  	{
                                                                                                       	    BEGIN SSTATE_3;
                                                                                                       	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                       	}
<SSTATE_5>"\"[^\"]*test[456]+[^\"]*\""  	{
                                        	    BEGIN ITEM_VALUE;
                                        	    foo_foo_unput_string_0(yyscanner, yytext);
                                        	}
<SSTATE_6>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){12,}\""  	{
                                                                                                    	    BEGIN SSTATE_5;
                                                                                                    	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                    	}
<SSTATE_7>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""  	{
                                                                                                	    BEGIN ITEM_VALUE;
                                                                                                	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                	}
<SSTATE_8>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){13,}\""  	{
                                                                                                    	    BEGIN SSTATE_7;
                                                                                                    	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                    	}
<SSTATE_9>"\"[^\"]*test[789]+[^\"]*\""  	{
                                        	    BEGIN ITEM_VALUE;
                                        	    foo_foo_unput_string_0(yyscanner, yytext);
                                        	}

%%

static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

