#include "json.hh"
#include "yyscan.hh"
#include <string>

#ifndef __FOO_BAR_HH
#define __FOO_BAR_HH

namespace foo
{
    class Bar
    {
    public:
        Bar() {};

        std::string quoted_str;
        yyscan_t scaninfo;
    };
}

#endif  // __FOO_BAR_HH
