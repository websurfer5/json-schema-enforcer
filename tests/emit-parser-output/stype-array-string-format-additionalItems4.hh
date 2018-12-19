#ifndef __STYPE_ARRAY_STRING_FORMAT_ADDITIONALITEMS4_HH
#define __STYPE_ARRAY_STRING_FORMAT_ADDITIONALITEMS4_HH

#include "Bar.hh"
#include <string>

struct FOO_FOO_STYPE
{
    bool bool_type;
    double double_type;
    long long_type;
    foo::JsonItem foo__JsonItem_type;
    foo::JsonItemMap foo__JsonItemMap_type;
    foo::JsonItemVector foo__JsonItemVector_type;
    std::string std__string_type;
};

typedef struct FOO_FOO_STYPE YYSTYPE;
#endif  // __STYPE_ARRAY_STRING_FORMAT_ADDITIONALITEMS4_HH
