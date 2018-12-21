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
#include "stype-number.hh"
#include "parser-number.hh"

   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
%}


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

%%

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

