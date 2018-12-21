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
#include "stype-array-string-format-additionalItems1.hh"
#include "parser-array-string-format-additionalItems1.hh"

   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
   extern void foo_foo_set_format_start_state_0(yyscan_t yyscanner);
   static void foo_foo_unput_string(yyscan_t yyscanner, const std::string& str);
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
%x SSTATE_2

%%
"["  	{
     	    yy_push_state(SSTATE_0, yyextra->scaninfo);
     	    return LEFT_BRACKET;
     	}
"]"  	{
     	    yy_pop_state(yyextra->scaninfo);
     	    return RIGHT_BRACKET;
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
<SSTATE_0>"]"  	{
               	    yy_pop_state(yyextra->scaninfo);
               	    return RIGHT_BRACKET;
               	}
<SSTATE_0>.  	{
             	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
             	    unput(*yytext);
             	    return TOKEN_0;
             	}
<SSTATE_0>[[:space:]]  	{
                       	}
<SSTATE_1>","  	{
               	    return COMMA;
               	}
<SSTATE_1>"\""  	{
                	    yy_push_state(SSTATE_2, yyextra->scaninfo);
                	    foo_foo_unput_string(yyscanner, yytext);
                	    return TOKEN_1;
                	}
<SSTATE_1>"]"  	{
               	    yy_pop_state(yyextra->scaninfo);
               	    return RIGHT_BRACKET;
               	}
<SSTATE_1>[[:space:]]  	{
                       	}
<SSTATE_2>"\"((([02468][048]|[13579][26])00|[0-9][0-9](0[48]|[2468][048]|[13579][26]))-02-29)|([0-9]{4}-(0[13578]|1[02])-31)|([0-9]{4}-(0[13456789]|1[012])-(0[1-9]|[12][0-9]|30))|([0-9]{4}-(0[1-9]|1[012])-(0[1-9]|1[0-9]|2[0-8]))\"\""  	{
                                                                                                                                                                                                                                           	    BEGIN ITEM_VALUE;
                                                                                                                                                                                                                                           	    foo_foo_unput_string(yyscanner, yytext);
                                                                                                                                                                                                                                           	}

%%

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

void foo_foo_set_format_start_state_0(yyscan_t yyscanner)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    BEGIN SSTATE_1;
}

static void foo_foo_unput_string(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

