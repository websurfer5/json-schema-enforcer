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
#include "stype-string.hh"
#include "parser-string.hh"

   extern void foo_foo_error(foo::Bar *sd, const char *s, ...);
%}

%x QUOTED

%%
"\""  	{
      	    yy_push_state(QUOTED, yyextra->scaninfo);
      	    return TOKEN_0;
      	}
.  	{
   	    REJECT;
   	}
<QUOTED>"\""  	{
              	    yy_pop_state(yyextra->scaninfo);
              	    yylval->std__string_type = yyextra->quoted_str;
              	    return QUOTED_STRING;
              	}

%%

void foo_foo_error(foo::Bar *sd, const char *s, ...)
{
}

