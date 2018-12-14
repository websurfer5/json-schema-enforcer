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
#include "stype-object.hh"
#include "parser-object.hh"

   static void foo_foo_append_utf16_escaped_char_0(std::string& str, const char *esc_seq);
   static void foo_foo_unput_string_0(const std::string& str);
%}

%x ITEM_ARRAY
%x ITEM_OBJECT
%x ITEM_VALUE
%x PARSE_ARRAY_KEY
%x PARSE_ITEM_KEY
%x PARSE_OBJECT_KEY
%x QUOTED

%%
"{"  	{
     	    yy_push_state(ITEM_OBJECT, yyextra->scaninfo);
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
                   	    unput(*text);
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
                           	    foo_foo_append_utf16_escaped_char_0(yyextra->quoted_str, yytext);
                           	}

%%

static void foo_foo_append_utf16_escaped_char_0(std::string& str, const char *esc_seq)
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

static void foo_foo_unput_string_0(const std::string& str)
{
	    for (std::string::reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

