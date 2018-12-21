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
#include "stype-object-nested1.hh"
#include "parser-object-nested1.hh"
#include <iostream>

   static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, double value);
   static bool foo_foo_value_meets_constraints_1(yyscan_t yyscanner, long value);
   static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str);
%}

%x ITEM_ARRAY
%x ITEM_OBJECT
%x ITEM_VALUE
%x PARSE_ARRAY_KEY
%x PARSE_ITEM_KEY
%x PARSE_KEY_0
%x PARSE_KEY_1
%x PARSE_OBJECT_KEY
%x QUOTED
%x SSTATE_0
%x SSTATE_1
%x SSTATE_10
%x SSTATE_11
%x SSTATE_12
%x SSTATE_13
%x SSTATE_14
%x SSTATE_2
%x SSTATE_3
%x SSTATE_4
%x SSTATE_5
%x SSTATE_6
%x SSTATE_7
%x SSTATE_8
%x SSTATE_9

%%
-[0-9]+  	{
         	    yy_pop_state(yyextra->scaninfo);
         	    yylval->long_type = std::stol(yytext);
         	    return NEG_INTEGER;
         	}
[+]?[0-9]+  	{
            	    yy_pop_state(yyextra->scaninfo);
            	    yylval->long_type = std::stol(yytext);
            	    return NON_NEG_INTEGER;
            	}
[-+]?[0-9]+\.[0-9]*  	{
                     	    yy_pop_state(yyextra->scaninfo);
                     	    yylval->double_type = std::stod(yytext);
                     	    return FLOATING_POINT;
                     	}
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
<PARSE_KEY_0>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""[[:space:]]*:[[:space:]]*  	{
                                                                                                                            	    BEGIN PARSE_ITEM_KEY;
                                                                                                                            	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                                            	}
<PARSE_KEY_0>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""[[:space:]]*:[[:space:]]*"["  	{
                                                                                                                               	    BEGIN PARSE_ARRAY_KEY;
                                                                                                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                                               	}
<PARSE_KEY_0>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""[[:space:]]*:[[:space:]]*"{"  	{
                                                                                                                               	    BEGIN PARSE_OBJECT_KEY;
                                                                                                                               	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                                               	}
<PARSE_KEY_1>"\"[^\"]*foo[a-z]bar[^\"]*\""[[:space:]]*:[[:space:]]*  	{
                                                                     	    BEGIN PARSE_ITEM_KEY;
                                                                     	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                     	}
<PARSE_KEY_1>"\"[^\"]*foo[a-z]bar[^\"]*\""[[:space:]]*:[[:space:]]*"["  	{
                                                                        	    BEGIN PARSE_ARRAY_KEY;
                                                                        	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                        	}
<PARSE_KEY_1>"\"[^\"]*foo[a-z]bar[^\"]*\""[[:space:]]*:[[:space:]]*"{"  	{
                                                                        	    BEGIN PARSE_OBJECT_KEY;
                                                                        	    foo_foo_unput_string_0(yyscanner, yytext);
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
               	    yyextra->quoted_str += '/';
               	}
<QUOTED>"\\\""  	{
                	    yyextra->quoted_str += '\"';
                	}
<QUOTED>"\\\\"  	{
                	    yyextra->quoted_str += '\\';
                	}
<QUOTED>"\\b"  	{
               	    yyextra->quoted_str += '\b';
               	}
<QUOTED>"\\f"  	{
               	    yyextra->quoted_str += '\f';
               	}
<QUOTED>"\\n"  	{
               	    yyextra->quoted_str += '\n';
               	}
<QUOTED>"\\r"  	{
               	    yyextra->quoted_str += '\r';
               	}
<QUOTED>"\\t"  	{
               	    yyextra->quoted_str += '\t';
               	}
<QUOTED>\\u[0-9a-fA-F]{4}  	{
                           	    uint16_t uval;
                           	    yyextra->quoted_str = "";
                           	    
                           	    uval = ((yytext[2] <= '9') ? (yytext[2] - '0') : ((yytext[2] & 0x07) + 9)) << 12;
                           	    uval += ((yytext[3] <= '9') ? (yytext[3] - '0') : ((yytext[3] & 0x07) + 9)) << 8;
                           	    uval += ((yytext[4] <= '9') ? (yytext[4] - '0') : ((yytext[4] & 0x07) + 9)) << 4;
                           	    uval += ((yytext[5] <= '9') ? (yytext[5] - '0') : ((yytext[5] & 0x07) + 9));
                           	    
                           	    if (uval < 0x0080)
                           	        yyextra->quoted_str += uval & 0xff;
                           	    else if (uval < 0x0800)
                           	    {
                           	        yyextra->quoted_str += (uval >> 6) | 0xc0;
                           	        yyextra->quoted_str += (uval & 0x3f) | 0x80;
                           	    }
                           	    else
                           	    {
                           	        yyextra->quoted_str += (uval >> 12) | 0xe0;
                           	        yyextra->quoted_str += ((uval >> 6) & 0x3f) | 0x80;
                           	        yyextra->quoted_str += (uval & 0x3f) | 0x80;
                           	    }
                           	}
<SSTATE_0>","  	{
               	    return COMMA;
               	}
<SSTATE_0>"\""  	{
                	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                	    unput(*yytext);
                	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                	    return TOKEN_19;
                	}
<SSTATE_0>"\"bar2\""[[:space]]*:[[:space:]]*"{"  	{
                                                 	    yy_push_state(SSTATE_14, yyextra->scaninfo);
                                                 	    foo_foo_unput_string_0(yyscanner, yytext);
                                                 	    yy_push_state(PARSE_OBJECT_KEY, yyextra->scaninfo);
                                                 	    return TOKEN_16;
                                                 	}
<SSTATE_0>"\"bar\""[[:space]]*:[[:space:]]*"{"  	{
                                                	    yy_push_state(SSTATE_3, yyextra->scaninfo);
                                                	    foo_foo_unput_string_0(yyscanner, yytext);
                                                	    yy_push_state(PARSE_OBJECT_KEY, yyextra->scaninfo);
                                                	    return TOKEN_1;
                                                	}
<SSTATE_0>"\"foo-int-plain\""  	{
                               	    foo_foo_unput_string_0(yyscanner, yytext);
                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                               	    return TOKEN_15;
                               	}
<SSTATE_0>"\"foo-int\""[[:space:]]*:[[:space:]]*  	{
                                                  	    yy_push_state(SSTATE_13, yyextra->scaninfo);
                                                  	    foo_foo_unput_string_0(yyscanner, yytext);
                                                  	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                                  	    return TOKEN_14;
                                                  	}
<SSTATE_0>"\"foo-num-plain\""  	{
                               	    foo_foo_unput_string_0(yyscanner, yytext);
                               	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                               	    return TOKEN_13;
                               	}
<SSTATE_0>"\"foo-num\""[[:space:]]*:[[:space:]]*  	{
                                                  	    yy_push_state(SSTATE_12, yyextra->scaninfo);
                                                  	    foo_foo_unput_string_0(yyscanner, yytext);
                                                  	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                                  	    return TOKEN_12;
                                                  	}
<SSTATE_0>"\"foo\""[[:space:]]*:[[:space:]]*  	{
                                              	    yy_push_state(SSTATE_2, yyextra->scaninfo);
                                              	    foo_foo_unput_string_0(yyscanner, yytext);
                                              	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                                              	    return TOKEN_0;
                                              	}
<SSTATE_0>"}"  	{
               	    yy_pop_state(yyextra->scaninfo);
               	    return RIGHT_BRACE;
               	}
<SSTATE_0>[[:space:]]  	{
                       	}
<SSTATE_1>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""  	{
                                                                                                	    BEGIN ITEM_VALUE;
                                                                                                	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                	}
<SSTATE_10>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""  	{
                                                                                                 	    BEGIN ITEM_VALUE;
                                                                                                 	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                 	}
<SSTATE_11>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){2,40}\""  	{
                                                                                                      	    BEGIN SSTATE_10;
                                                                                                      	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                      	}
<SSTATE_12>-[0-9]+  	{
                    	    yy_pop_state(yyextra->scaninfo);
                    	    yylval->long_type = std::stol(yytext);
                    	    
                    	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                    	        return 0;
                    	    
                    	    return NEG_INTEGER;
                    	}
<SSTATE_12>[+]?[0-9]+  	{
                       	    yy_pop_state(yyextra->scaninfo);
                       	    yylval->long_type = std::stol(yytext);
                       	    
                       	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                       	        return 0;
                       	    
                       	    return NON_NEG_INTEGER;
                       	}
<SSTATE_12>[-+]?[0-9]+\.[0-9]*  	{
                                	    yy_pop_state(yyextra->scaninfo);
                                	    yylval->double_type = std::stod(yytext);
                                	    
                                	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->double_type))
                                	        return 0;
                                	    
                                	    return FLOATING_POINT;
                                	}
<SSTATE_13>-[0-9]+  	{
                    	    yy_pop_state(yyextra->scaninfo);
                    	    yylval->long_type = std::stol(yytext);
                    	    
                    	    if (!foo_foo_value_meets_constraints_1(yyextra->scaninfo, yylval->long_type))
                    	        return false;
                    	    
                    	    return NEG_INTEGER;
                    	}
<SSTATE_13>[+]?[0-9]+  	{
                       	    yy_pop_state(yyextra->scaninfo);
                       	    yylval->long_type = std::stol(yytext);
                       	    
                       	    if (!foo_foo_value_meets_constraints_1(yyextra->scaninfo, yylval->long_type))
                       	        return false;
                       	    
                       	    return NON_NEG_INTEGER;
                       	}
<SSTATE_14>","  	{
                	    return COMMA;
                	}
<SSTATE_14>"\""  	{
                 	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                 	    unput(*yytext);
                 	    yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);
                 	    return TOKEN_18;
                 	}
<SSTATE_14>"\"foo[a-z]+\""  	{
                            	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                            	    foo_foo_unput_string_0(yyscanner, yytext);
                            	    yy_push_state(PARSE_KEY_1, yyextra->scaninfo);
                            	    return TOKEN_17;
                            	}
<SSTATE_14>"}"  	{
                	    yy_pop_state(yyextra->scaninfo);
                	    return RIGHT_BRACE;
                	}
<SSTATE_14>[[:space:]]  	{
                        	}
<SSTATE_2>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){20,}\""  	{
                                                                                                    	    BEGIN SSTATE_1;
                                                                                                    	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                    	}
<SSTATE_3>","  	{
               	    return COMMA;
               	}
<SSTATE_3>"\""  	{
                	    yy_push_state(SSTATE_11, yyextra->scaninfo);
                	    foo_foo_unput_string_0(yyscanner, yytext);
                	    return TOKEN_11;
                	}
<SSTATE_3>"\"bar[0-9]+\""  	{
                           	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                           	    foo_foo_unput_string_0(yyscanner, yytext);
                           	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                           	    return TOKEN_9;
                           	}
<SSTATE_3>"\"bar\""  	{
                     	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                     	    foo_foo_unput_string_0(yyscanner, yytext);
                     	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                     	    return TOKEN_3;
                     	}
<SSTATE_3>"\"foo-int-foo\""[[:space:]]*:[[:space:]]*  	{
                                                      	    yy_push_state(SSTATE_9, yyextra->scaninfo);
                                                      	    foo_foo_unput_string_0(yyscanner, yytext);
                                                      	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                                                      	    return TOKEN_6;
                                                      	}
<SSTATE_3>"\"foo-int-plain\""  	{
                               	    foo_foo_unput_string_0(yyscanner, yytext);
                               	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                               	    return TOKEN_7;
                               	}
<SSTATE_3>"\"foo-int\""[[:space:]]*:[[:space:]]*  	{
                                                  	    yy_push_state(SSTATE_8, yyextra->scaninfo);
                                                  	    foo_foo_unput_string_0(yyscanner, yytext);
                                                  	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                                                  	    return TOKEN_5;
                                                  	}
<SSTATE_3>"\"foo-num\""[[:space:]]*:[[:space:]]*  	{
                                                  	    yy_push_state(SSTATE_7, yyextra->scaninfo);
                                                  	    foo_foo_unput_string_0(yyscanner, yytext);
                                                  	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                                                  	    return TOKEN_4;
                                                  	}
<SSTATE_3>"\"foo[0-9]+\""  	{
                           	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
                           	    foo_foo_unput_string_0(yyscanner, yytext);
                           	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                           	    return TOKEN_8;
                           	}
<SSTATE_3>"\"foo\""[[:space:]]*:[[:space:]]*  	{
                                              	    yy_push_state(SSTATE_6, yyextra->scaninfo);
                                              	    foo_foo_unput_string_0(yyscanner, yytext);
                                              	    yy_push_state(PARSE_KEY_0, yyextra->scaninfo);
                                              	    return TOKEN_2;
                                              	}
<SSTATE_3>"}"  	{
               	    yy_pop_state(yyextra->scaninfo);
               	    return RIGHT_BRACE;
               	}
<SSTATE_3>[[:space:]]  	{
                       	}
<SSTATE_4>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){3,}\""  	{
                                                                                                   	    BEGIN PARSE_KEY_0;
                                                                                                   	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                   	}
<SSTATE_5>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"])*\""  	{
                                                                                                	    BEGIN ITEM_VALUE;
                                                                                                	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                	}
<SSTATE_6>"\"((\\b)|(\\\\)|(\\/)|(\\f)|(\\n)|(\\r)|(\\t)|(\\\")|(\\u[0-9a-fA-F]{4})|[^\"]){30,}\""  	{
                                                                                                    	    BEGIN SSTATE_5;
                                                                                                    	    foo_foo_unput_string_0(yyscanner, yytext);
                                                                                                    	}
<SSTATE_7>-[0-9]+  	{
                   	    yy_pop_state(yyextra->scaninfo);
                   	    yylval->long_type = std::stol(yytext);
                   	    
                   	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                   	        return 0;
                   	    
                   	    return NEG_INTEGER;
                   	}
<SSTATE_7>[+]?[0-9]+  	{
                      	    yy_pop_state(yyextra->scaninfo);
                      	    yylval->long_type = std::stol(yytext);
                      	    
                      	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                      	        return 0;
                      	    
                      	    return NON_NEG_INTEGER;
                      	}
<SSTATE_7>[-+]?[0-9]+\.[0-9]*  	{
                               	    yy_pop_state(yyextra->scaninfo);
                               	    yylval->double_type = std::stod(yytext);
                               	    
                               	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->double_type))
                               	        return 0;
                               	    
                               	    return FLOATING_POINT;
                               	}
<SSTATE_8>-[0-9]+  	{
                   	    yy_pop_state(yyextra->scaninfo);
                   	    yylval->long_type = std::stol(yytext);
                   	    
                   	    if (!foo_foo_value_meets_constraints_1(yyextra->scaninfo, yylval->long_type))
                   	        return false;
                   	    
                   	    return NEG_INTEGER;
                   	}
<SSTATE_8>[+]?[0-9]+  	{
                      	    yy_pop_state(yyextra->scaninfo);
                      	    yylval->long_type = std::stol(yytext);
                      	    
                      	    if (!foo_foo_value_meets_constraints_1(yyextra->scaninfo, yylval->long_type))
                      	        return false;
                      	    
                      	    return NON_NEG_INTEGER;
                      	}
<SSTATE_9>-[0-9]+  	{
                   	    yy_pop_state(yyextra->scaninfo);
                   	    yylval->long_type = std::stol(yytext);
                   	    
                   	    if (!foo_foo_value_meets_constraints_1(yyextra->scaninfo, yylval->long_type))
                   	        return false;
                   	    
                   	    return NEG_INTEGER;
                   	}
<SSTATE_9>[+]?[0-9]+  	{
                      	    yy_pop_state(yyextra->scaninfo);
                      	    yylval->long_type = std::stol(yytext);
                      	    
                      	    if (!foo_foo_value_meets_constraints_1(yyextra->scaninfo, yylval->long_type))
                      	        return false;
                      	    
                      	    return NON_NEG_INTEGER;
                      	}

%%

static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, double value)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    if (value < 2.200000)
	    {
	        std::cerr << "validation error: " << yytext << " is less than 2.200000" << std::endl;
	        return false;
	    }
	    
	    return true;
}

static bool foo_foo_value_meets_constraints_1(yyscan_t yyscanner, long value)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    if ((((long)((value/4)) * 4) != value)
	        {
	                std::cerr << "validation error: " << yytext << " is not a multiple of 4" << std::endl;
	                return false;
	            }
	            
	    if (value > 20)
	            {
	                std::cerr << "validation error: " << yytext << " is greater than 20" << std::endl;
	                return false;
	            }
	            
	    return true;
}

static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

