#ifndef __STYPE_ARRAY_MINITEMS_ADDITIONALITEMS_HH
#define __STYPE_ARRAY_MINITEMS_ADDITIONALITEMS_HH

#include "Bar.hh"
#include <string>

struct FOO_FOO_STYPE
{
    bool bool_type;
    double double_type;
    long long_type;
    JsonItem JsonItem_type;
    JsonItemList JsonItemList_type;
    JsonItemMap JsonItemMap_type;
    std::string std__string_type;
};

typedef struct FOO_FOO_STYPE FOO_FOO_STYPE;
#endif  // __STYPE_ARRAY_MINITEMS_ADDITIONALITEMS_HH
