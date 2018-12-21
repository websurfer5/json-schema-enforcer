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
#include "stype-number-exclusiveMaximum.hh"
#include "parser-number-exclusiveMaximum.hh"
#include <iostream>

   static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, double value);
   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
   static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str);
%}

%x SSTATE_0

%%
[-+]?[0-9]+(\.[0-9]+)?[[:space:]]*:[[:space:]]*  	{
                                                 	    yy_push_state(SSTATE_0, yyextra->scaninfo);
                                                 	    foo_foo_unput_string_0(yyscanner, yytext);
                                                 	    return TOKEN_0;
                                                 	}
<SSTATE_0>-[0-9]+  	{
                   	    yy_pop_state(yyextra->scaninfo);
                   	    yylval->long_type = std::stol(yytext);
                   	    
                   	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                   	        return 0;
                   	    
                   	    return NEG_INTEGER;
                   	}
<SSTATE_0>[+]?[0-9]+  	{
                      	    yy_pop_state(yyextra->scaninfo);
                      	    yylval->long_type = std::stol(yytext);
                      	    
                      	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                      	        return 0;
                      	    
                      	    return NON_NEG_INTEGER;
                      	}
<SSTATE_0>[-+]?[0-9]+\.[0-9]*  	{
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
	    
	    if (value >= 110.000000)
	    {
	        std::cerr << "validation error: " << yytext << " is not less than 110.000000" << std::endl;
	        return false;
	    }
	    
	    return true;
}

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

