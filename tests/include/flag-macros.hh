// flag-macros.hh
//
// Copyright 2018 Jeffrey Kintscher <websurfer@surf2c.net>
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#ifndef __FLAG_MACROS_HH
#define __FLAG_MACROS_HH

#include <set>

#endif  // __FLAG_MACROS_HH

#if defined(DEF_FLAG)
#   undef DEF_FLAG
#endif

{
    static std::set<FLAG_TYPE_ENUM> _full_set;

#ifdef TEST_ALL_VALUES
#   define DEF_FLAG(fname, str_name) \
    _full_set.insert(FLAG_TYPE::type_##fname);

#   include FLAGS_FILE
#   undef DEF_FLAG
#endif  // TEST_ALL_VALUES

#   define DEF_FLAG(fname, str_name)                                    \
    BOOST_CHECK(!TEST_OBJECT.is_##fname());                             \
    BOOST_CHECK(TEST_OBJECT != FLAG_TYPE::type_##fname);

#   include FLAGS_FILE
#   undef DEF_FLAG
    BOOST_CHECK(TEST_OBJECT.get_type() == FLAG_TYPE::type_Unknown);
    BOOST_CHECK(TEST_OBJECT.get_type_name().empty());

#ifdef TEST_ALL_VALUES

    std::set<FLAG_TYPE_ENUM>::const_iterator it;

    for (it = _full_set.begin(); it != _full_set.end(); it++)
    {

#       define DEF_FLAG(fname, str_name)                \
            case FLAG_TYPE::type_##fname:               \
                TEST_OBJECT = FLAG_TYPE::type_##fname;  \
                break;

        switch (*it)
        {
#           include FLAGS_FILE

            default:
                TEST_OBJECT = FLAG_TYPE::type_Unknown;
        }

#       undef DEF_FLAG

#       define DEF_FLAG(fname, str_name)                                        \
        if (*it == FLAG_TYPE::type_##fname)                                     \
        {                                                                       \
            BOOST_CHECK(TEST_OBJECT.is_##fname());                              \
            BOOST_CHECK(TEST_OBJECT == FLAG_TYPE::type_##fname);                \
            BOOST_CHECK(TEST_OBJECT.get_type() == FLAG_TYPE::type_##fname);     \
            BOOST_CHECK_EQUAL(TEST_OBJECT.get_type_name(), str_name);           \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            BOOST_CHECK(!TEST_OBJECT.is_##fname());                             \
            BOOST_CHECK(TEST_OBJECT != FLAG_TYPE::type_##fname);                \
        }

#       include FLAGS_FILE
#       undef DEF_FLAG
    }

    for (it = _full_set.begin(); it != _full_set.end(); it++)
    {

#       define DEF_FLAG(fname, str_name)                \
            case FLAG_TYPE::type_##fname:               \
                TEST_OBJECT = str_name;  \
                break;

        switch (*it)
        {
#           include FLAGS_FILE

            default:
                TEST_OBJECT.clear();
        }

#       undef DEF_FLAG

#       define DEF_FLAG(fname, str_name)                                        \
        if (*it == FLAG_TYPE::type_##fname)                                     \
        {                                                                       \
            BOOST_CHECK(TEST_OBJECT.is_##fname());                              \
            BOOST_CHECK(TEST_OBJECT == FLAG_TYPE::type_##fname);                \
            BOOST_CHECK(TEST_OBJECT.get_type() == FLAG_TYPE::type_##fname);     \
            BOOST_CHECK_EQUAL(TEST_OBJECT.get_type_name(), str_name);           \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            BOOST_CHECK(!TEST_OBJECT.is_##fname());                             \
            BOOST_CHECK(TEST_OBJECT != FLAG_TYPE::type_##fname);                \
        }

#       include FLAGS_FILE
#       undef DEF_FLAG
    }

#endif  // TEST_ALL_VALUES
}
