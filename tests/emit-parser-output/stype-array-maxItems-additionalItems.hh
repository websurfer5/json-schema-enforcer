#ifndef __STYPE_ARRAY_MAXITEMS_ADDITIONALITEMS_HH
#define __STYPE_ARRAY_MAXITEMS_ADDITIONALITEMS_HH

#include "Bar.hh"
#include <string>

struct FOO_FOO_STYPE
{
    long long_type;
    foo::JsonItem foo__JsonItem_type;
    foo::JsonItemVector foo__JsonItemVector_type;
    std::string std__string_type;
};

typedef struct FOO_FOO_STYPE YYSTYPE;
#endif  // __STYPE_ARRAY_MAXITEMS_ADDITIONALITEMS_HH
