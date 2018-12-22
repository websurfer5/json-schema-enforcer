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
#include "stype-array.hh"
#include "parser-array.hh"

   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
%}

%x ITEM_ARRAY
%x ITEM_VALUE

%%
"["  	{
     	    yy_push_state(ITEM_ARRAY, yyextra->scaninfo);
     	    return LEFT_BRACKET;
     	}
"]"  	{
     	    yy_pop_state(yyextra->scaninfo);
     	    return RIGHT_BRACKET;
     	}
<ITEM_ARRAY>.  	{
               	    yy_push_state(ITEM_VALUE, yyextra->scaninfo);
               	    unput(*yytext);
               	}

%%

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

