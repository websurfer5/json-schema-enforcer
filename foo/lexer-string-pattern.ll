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
#include "stype-string-pattern.hh"
#include "parser-string-pattern.hh"

   static void foo_foo_unput_string_0(const std::string& str);
%}

%x ITEM_VALUE
%x QUOTED
%x SSTATE_0

%%
"\""  	{
      	    yy_push_state(SSTATE_0, yyextra->scaninfo);
      	    foo_foo_unput_string_0(yytext);
      	    return TOKEN_0;
      	}
<QUOTED>"\""  	{
              	    yy_pop_state(yyextra->scaninfo);
              	    yylval->std__string_type = yyextra->quoted_str;
              	    return QUOTED_STRING;
              	}
<SSTATE_0>"\"[^\"]*test[123]+[^\"]*\""  	{
                                        	    BEGIN ITEM_VALUE;
                                        	    foo_foo_unput_string_0(yytext);
                                        	}

%%

static void foo_foo_unput_string_0(const std::string& str)
{
	    for (std::string::reverse_iterator it=str.rbegin(); it != str.rend(); it++)
	        unput(*it);
}

