#ifndef __STYPE_ARRAY_NUMBER_HH
#define __STYPE_ARRAY_NUMBER_HH

#include "Bar.hh"

struct FOO_FOO_STYPE
{
    double double_type;
    long long_type;
    foo::JsonItem foo__JsonItem_type;
    foo::JsonItemVector foo__JsonItemVector_type;
};

typedef struct FOO_FOO_STYPE YYSTYPE;
#endif  // __STYPE_ARRAY_NUMBER_HH
