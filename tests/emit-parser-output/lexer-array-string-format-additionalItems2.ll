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
#include "stype-array-string-format-additionalItems2.hh"
#include "parser-array-string-format-additionalItems2.hh"

   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
   extern void foo_foo_set_format_start_state_0(yyscan_t yyscanner);
   static void foo_foo_unput_string(yyscan_t yyscanner, const std::string& str);
%}

%x ITEM_VALUE
%x QUOTED
%x SSTATE_0
%x SSTATE_1
%x SSTATE_2
%x SSTATE_3

%%
"["  	{
     	    yy_push_state(SSTATE_0, yyextra->scaninfo);
     	    return LEFT_BRACKET;
     	}
"]"  	{
     	    yy_pop_state(yyextra->scaninfo);
     	    return RIGHT_BRACKET;
     	}
<QUOTED>"\""  	{
              	    yy_pop_state(yyextra->scaninfo);
              	    yylval->std__string_type = yyextra->quoted_str;
              	    return QUOTED_STRING;
              	}
<SSTATE_0>","  	{
               	    return COMMA;
               	}
<SSTATE_0>"\""  	{
                	    yy_push_state(SSTATE_1, yyextra->scaninfo);
                	    foo_foo_unput_string(yyscanner, yytext);
                	    return TOKEN_1;
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
<SSTATE_1>"\"((([02468][048]|[13579][26])00|[0-9][0-9](0[48]|[2468][048]|[13579][26]))-02-29)|([0-9]{4}-(0[13578]|1[02])-31)|([0-9]{4}-(0[13456789]|1[012])-(0[1-9]|[12][0-9]|30))|([0-9]{4}-(0[1-9]|1[012])-(0[1-9]|1[0-9]|2[0-8]))\"\""  	{
                                                                                                                                                                                                                                           	    BEGIN ITEM_VALUE;
                                                                                                                                                                                                                                           	    foo_foo_unput_string(yyscanner, yytext);
                                                                                                                                                                                                                                           	}
<SSTATE_2>","  	{
               	    return COMMA;
               	}
<SSTATE_2>"\""  	{
                	    yy_push_state(SSTATE_3, yyextra->scaninfo);
                	    foo_foo_unput_string(yyscanner, yytext);
                	    return TOKEN_2;
                	}
<SSTATE_2>"]"  	{
               	    yy_pop_state(yyextra->scaninfo);
               	    return RIGHT_BRACKET;
               	}
<SSTATE_2>[[:space:]]  	{
                       	}
<SSTATE_3>"\"((([02468][048]|[13579][26])00|[0-9][0-9](0[48]|[2468][048]|[13579][26]))-02-29)|([0-9]{4}-(0[13578]|1[02])-31)|([0-9]{4}-(0[13456789]|1[012])-(0[1-9]|[12][0-9]|30))|([0-9]{4}-(0[1-9]|1[012])-(0[1-9]|1[0-9]|2[0-8]))\"\""  	{
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
	    
	    BEGIN SSTATE_2;
}

static void foo_foo_unput_string(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

