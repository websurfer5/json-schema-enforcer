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
#include "stype-array-number-all.hh"
#include "parser-array-number-all.hh"
#include <iostream>

   static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, double value);
   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
   static void foo_foo_unput_string(yyscan_t yyscanner, const std::string& str);
%}

%x ITEM_VALUE
%x SSTATE_0
%x SSTATE_1

%%
"["  	{
     	    yy_push_state(SSTATE_0, yyextra->scaninfo);
     	    return LEFT_BRACKET;
     	}
"]"  	{
     	    yy_pop_state(yyextra->scaninfo);
     	    return RIGHT_BRACKET;
     	}
.  	{
   	    REJECT;
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
<SSTATE_0>[-+]?[0-9]+(\.[0-9]+)?[[:space:]]*:[[:space:]]*  	{
                                                           	    yy_push_state(SSTATE_1, yyextra->scaninfo);
                                                           	    foo_foo_unput_string(yyscanner, yytext);
                                                           	    return TOKEN_1;
                                                           	}
<SSTATE_0>[[:space:]]  	{
                       	}
<SSTATE_1>-[0-9]+  	{
                   	    yy_pop_state(yyextra->scaninfo);
                   	    yylval->long_type = std::stol(yytext);
                   	    
                   	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                   	        return 0;
                   	    
                   	    return NEG_INTEGER;
                   	}
<SSTATE_1>[+]?[0-9]+  	{
                      	    yy_pop_state(yyextra->scaninfo);
                      	    yylval->long_type = std::stol(yytext);
                      	    
                      	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                      	        return 0;
                      	    
                      	    return NON_NEG_INTEGER;
                      	}
<SSTATE_1>[-+]?[0-9]+\.[0-9]*  	{
                               	    yy_pop_state(yyextra->scaninfo);
                               	    yylval->double_type = std::stod(yytext);
                               	    
                               	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->double_type))
                               	        return 0;
                               	    
                               	    return FLOATING_POINT;
                               	}

%%

static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, double value)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    if ((double)((long)(value/5.500000)) != (value/5.500000))
	    {
	        std::cerr << "validation error: " << yytext << " is not a multiple of 5.500000" << std::endl;
	        return false;
	    }
	    
	    if (value > 110.050000)
	    {
	        std::cerr << "validation error: " << yytext << " is greater than 110.050000" << std::endl;
	        return false;
	    }
	    
	    if (value < -11.050000)
	    {
	        std::cerr << "validation error: " << yytext << " is less than -11.050000" << std::endl;
	        return false;
	    }
	    
	    if (value >= 110.000000)
	    {
	        std::cerr << "validation error: " << yytext << " is not less than 110.000000" << std::endl;
	        return false;
	    }
	    
	    if (value <= -11.000000)
	    {
	        std::cerr << "validation error: " << yytext << " is not greater than -11.000000" << std::endl;
	        return false;
	    }
	    
	    return true;
}

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

static void foo_foo_unput_string(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

