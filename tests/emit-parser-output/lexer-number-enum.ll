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
#include "stype-number-enum.hh"
#include "parser-number-enum.hh"

   static bool foo_foo_value_meets_constraints_0(double value);
   static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str);
%}

%x SSTATE_0

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
[-+]?[0-9]+(\.[0-9]+)?[[:space:]]*:[[:space:]]*  	{
                                                 	    yy_push_state(SSTATE_0, yyextra->scaninfo);
                                                 	    foo_foo_unput_string_0(yyscanner, yytext);
                                                 	    return TOKEN_0;
                                                 	}

%%

static bool foo_foo_value_meets_constraints_0(double value)
{
	    if (!(value == 5.100000 || value == 7.200000 || value == 10.250000))
	    {
	        std::cerr << "validation error: " << yytext << " is not one of 5.100000, 7.200000, 10.250000" << std::endl;
	        return 0;
	    }
	    
	    return true;
}

static void foo_foo_unput_string_0(yyscan_t yyscanner, const std::string& str)
{
	    struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
	    
	    for (std::string::const_reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

