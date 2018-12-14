#ifndef __STYPE_ARRAY_NUMBER_ALL_HH
#define __STYPE_ARRAY_NUMBER_ALL_HH

#include "Bar.hh"
#include <string>

struct FOO_FOO_STYPE
{
    bool bool_type;
    double double_type;
    long long_type;
    foo::JsonItem foo__JsonItem_type;
    foo::JsonItemList foo__JsonItemList_type;
    foo::JsonItemMap foo__JsonItemMap_type;
    std::string std__string_type;
};

typedef struct FOO_FOO_STYPE FOO_FOO_STYPE;
#endif  // __STYPE_ARRAY_NUMBER_ALL_HH
