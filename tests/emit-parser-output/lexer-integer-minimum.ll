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
#include "stype-integer-minimum.hh"
#include "parser-integer-minimum.hh"
#include <iostream>

   static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, long value);
   static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str);
%}

%x SSTATE_0

%%
[-+]?[0-9]+[[:space:]]*:[[:space:]]*  	{
                                      	    yy_push_state(SSTATE_0, yyextra->scaninfo);
                                      	    foo_foo_unput_string_0(yyscanner, yytext);
                                      	    return TOKEN_0;
                                      	}
<SSTATE_0>-[0-9]+  	{
                   	    yy_pop_state(yyextra->scaninfo);
                   	    yylval->long_type = std::stol(yytext);
                   	    
                   	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                   	        return false;
                   	    
                   	    return NEG_INTEGER;
                   	}
<SSTATE_0>[+]?[0-9]+  	{
                      	    yy_pop_state(yyextra->scaninfo);
                      	    yylval->long_type = std::stol(yytext);
                      	    
                      	    if (!foo_foo_value_meets_constraints_0(yyextra->scaninfo, yylval->long_type))
                      	        return false;
                      	    
                      	    return NON_NEG_INTEGER;
                      	}

%%

static bool foo_foo_value_meets_constraints_0(yyscan_t yyscanner, long value)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    if (value < -10)
	            {
	                std::cerr << "validation error: " << yytext << " is less than -10" << std::endl;
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

