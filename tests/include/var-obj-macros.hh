// var-obj-macros.hh
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

//
// Before including this file, define CHECK_VAR
// with the strinified vairable name.
//
// #define CHECK_VAR    "foo"
//
// Define VARS_FILE with the name of
// the header file containing the DEF_VAR
// and DEF_OBJ instanciations.
//
// #define "ParsedItemData-vars.hh"
//

//
// these macros only need to be defined once
//

#ifndef __VAR_OBJ_MACROS_HH
#define __VAR_OBJ_MACROS_HH

#include <set>
#include <string>

#define IF_VAR_IN_SET(_v, _vset) \
    if (_vset.find(#_v) != _vset.end())

#define ADD_VAR_TO_SET(_v, _vset) \
    _vset.insert(#_v);

#endif  // __VAR_OBJ_MACROS_HH

//
// these macros need to be included every time
//

#if defined(DEF_VAR)
#    undef DEF_VAR
#endif

#if defined (DEF_OBJ)
#    undef DEF_OBJ
#endif

#if defined (DEF_OBJ_PTR)
#    undef DEF_OBJ_PTR
#endif

#if defined(DEF_FLAG)
#   undef DEF_FLAG
#endif

{
    static struct std::set<std::string> _used_test_params_set,
                                        _unused_test_params_set;

#ifdef TEST_ALL_VALUES
#   define DEF_VAR(_vtype, _vname, _value, _test_value, _flag_name, _flag_value, _func_set, _func_get) \
    ADD_VAR_TO_SET(_vname, _unused_test_params_set);

#   define DEF_OBJ(_objtype, _vname, _initfunc, _emptyfunc, _test_value, _flag_name, _flag_value, _func_set, _func_get)   \
    ADD_VAR_TO_SET(_vname, _unused_test_params_set);

#   define DEF_OBJ_PTR(_objtype, _vname, _initfunc, _emptyfunc, _test_value, _flag_name, _flag_value, _func_set, _func_get)   \
    ADD_VAR_TO_SET(_vname, _unused_test_params_set);

#   define DEF_FLAG(fname, value, func_set, func_clear)
    ADD_VAR_TO_SET(fname, _unused_test_params_set);

#   include VARS_FILE
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG
#endif  // TEST_ALL_VALUES

#   define DEF_VAR(_vtype, _vname, _value, _test_value, _flag_name, _flag_value, _func_set, _func_get) \
    IF_VAR_IN_SET(_vname, _used_test_params_set) \
    { \
        TEST_OBJECT._func_set(_test_value); \
        BOOST_CHECK_EQUAL(TEST_OBJECT._vname, _test_value); \
        BOOST_CHECK_EQUAL(TEST_OBJECT._flag_name, true); \
    } \
    else \
    { \
        BOOST_CHECK_EQUAL(TEST_OBJECT._vname, _value); \
        BOOST_CHECK_EQUAL(TEST_OBJECT._flag_name, _flag_value); \
    }

#   define DEF_OBJ(_objtype, _vname, _initfunc, _emptyfunc, _test_value, _flag_name, _flag_value, _func_set, _func_get) \
    IF_VAR_IN_SET(_vname, _used_test_params_set) \
    { \
        TEST_OBJECT._func_set(TEST_NAMESPACE::_objtype(_test_value)); \
        BOOST_CHECK(TEST_OBJECT._vname == TEST_NAMESPACE::_objtype(_test_value)); \
        BOOST_CHECK_EQUAL(TEST_OBJECT._flag_name, true); \
    } \
    else \
    { \
        BOOST_CHECK(TEST_OBJECT._vname._emptyfunc()); \
        BOOST_CHECK_EQUAL(TEST_OBJECT._flag_name, _flag_value); \
    }

#   define DEF_OBJ_PTR(_objtype, _vname, _initfunc, _emptyfunc, _test_value, _flag_name, _flag_value, _func_set, _func_get) \
    IF_VAR_IN_SET(_vname, _used_test_params_set) \
    { \
        TEST_OBJECT._func_set(TEST_NAMESPACE::_objtype(_test_value)); \
        BOOST_CHECK(TEST_OBJECT._vname != NULL);    \
        if (TEST_OBJECT._vname)  \
            BOOST_CHECK(*TEST_OBJECT._vname == TEST_NAMESPACE::_objtype(_test_value)); \
        BOOST_CHECK_EQUAL(TEST_OBJECT._flag_name, true); \
    } \
    else \
    { \
        BOOST_CHECK(TEST_OBJECT._vname == NULL); \
        if (TEST_OBJECT._vname) \
            BOOST_CHECK(TEST_OBJECT._vname->_emptyfunc());   \
        BOOST_CHECK_EQUAL(TEST_OBJECT._flag_name, _flag_value); \
    }


#   define DEF_FLAG(fname, value, func_set, func_clear) \
    IF_VAR_IN_SET(fname, _used_test_params_set)         \
    {                                                   \
        BOOST_CHECK(!TEST_OBJECT.is_##fname());         \
        TEST_OBJECT.func_set();                         \
        BOOST_CHECK(TEST_OBJECT.is_##fname());          \
        TEST_OBJECT.func_clear();                       \
        BOOST_CHECK(!TEST_OBJECT.is_##fname());         \
        TEST_OBJECT.func_set(true);                     \
        BOOST_CHECK(TEST_OBJECT.is_##fname());          \
        TEST_OBJECT.func_set(false);                    \
        BOOST_CHECK(!TEST_OBJECT.is_##fname());         \
        TEST_OBJECT.func_set();                         \
        BOOST_CHECK(TEST_OBJECT.is_##fname());          \
    }                                                   \
    else                                                \
    {                                                   \
        BOOST_CHECK(!TEST_OBJECT.is_##fname());         \
    }

#   include VARS_FILE

#ifdef TEST_ALL_VALUES

    std::set<std::string> full_set = _unused_test_params_set;
    std::set<std::string>::const_iterator it;

    for (it = full_set.begin(); it != full_set.end(); it++)
    {
        TEST_OBJECT.clear();
        _used_test_params_set.insert(*it);
        _unused_test_params_set.erase(*it);
#       include VARS_FILE
    }

#endif  // TEST_ALL_VALUES
}

#undef TEST_ALL_VALUES
#undef DEF_VAR
#undef DEF_OBJ
#undef DEF_OBJ_PTR
#undef DEF_FLAG
