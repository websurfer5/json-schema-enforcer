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
#include "stype-integer-multipleOf.hh"
#include "parser-integer-multipleOf.hh"

   static bool foo_foo_value_meets_constraints_0(long value);
   static void foo_foo_unput_string_0(const std::string& str);
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
[-+]?[0-9]+[[:space:]]*:[[:space:]]*  	{
                                      	    yy_push_state(SSTATE_0, yyextra->scaninfo);
                                      	    foo_foo_unput_string_0(yytext);
                                      	    return TOKEN_0;
                                      	}

%%

static bool foo_foo_value_meets_constraints_0(long value)
{
	    if ((((long)((value/5)) * 5) != value)
	        {
	                std::cerr << "validation error: " << yytext << " is not a multiple of 5" << std::endl;
	                return 0;
	            }
	            
	    return true;
}

static void foo_foo_unput_string_0(const std::string& str)
{
	    for (std::string::reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

