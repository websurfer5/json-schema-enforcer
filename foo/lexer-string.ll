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

   static void foo_foo_unput_string_0(const std::string& str);
%}

%x QUOTED

%%
"\""  	{
      	    yy_push_state(QUOTED, yyextra->scaninfo);
      	    return TOKEN_0;
      	}
<QUOTED>"\""  	{
              	    yy_pop_state(yyextra->scaninfo);
              	    yylval->std__string_type = yyextra->quoted_str;
              	    return QUOTED_STRING;
              	}

%%

static void foo_foo_unput_string_0(const std::string& str)
{
	    for (std::string::reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

