#ifndef __STYPE_STRING_MAXLENGTH_HH
#define __STYPE_STRING_MAXLENGTH_HH

#include "Bar.hh"
#include <string>

struct FOO_FOO_STYPE
{
    foo::JsonItem foo__JsonItem_type;
    std::string std__string_type;
};

typedef struct FOO_FOO_STYPE YYSTYPE;
#endif  // __STYPE_STRING_MAXLENGTH_HH
