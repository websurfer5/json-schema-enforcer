// test-Token-class.cc
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

#include <boost/test/unit_test.hpp>
#include "Token.hh"

#define VARS_FILE       "Token-vars.hh"
#define TEST_OBJECT     token1
#define TEST_NAMESPACE  jsonschemaenforcer

BOOST_AUTO_TEST_SUITE( Tokin_class_test_suite )

BOOST_AUTO_TEST_CASE( test_Token_class )
{
    jsonschemaenforcer::Token token1;

    BOOST_CHECK(token1.empty());
#   include "var-obj-macros.hh"
    BOOST_CHECK(token1.empty());

#   define TEST_ALL_VALUES
    token1.clear();
    BOOST_CHECK(token1.empty());
#   include "var-obj-macros.hh"
#   undef TEST_ALL_VALUES
    BOOST_CHECK(!token1.empty());
    token1.clear();
}

BOOST_AUTO_TEST_SUITE_END()
