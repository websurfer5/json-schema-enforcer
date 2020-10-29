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
#include "stype-integer.hh"
#include "parser-integer.hh"

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
.  	{
   	    REJECT;
   	}

%%

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

