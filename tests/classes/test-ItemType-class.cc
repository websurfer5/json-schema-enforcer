// test-ItemType-class.cc
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
#include "ItemType.hh"

#define FLAGS_FILE      "ItemType-vars.hh"
#define FLAG_TYPE       jsonschemaenforcer::ItemType
#define FLAG_TYPE_ENUM  jsonschemaenforcer::ItemType::JsonItemType
#define TEST_OBJECT     itype

BOOST_AUTO_TEST_SUITE( ItemType_class_test_suite )

BOOST_AUTO_TEST_CASE( test_ItemType_class )
{
    jsonschemaenforcer::ItemType itype;

#   if defined(TEST_ALL_VALUES)
#       undef TEST_ALL_VALUES
#   endif

#   if defined(TEST_VALUE)
#       undef TEST_VALUES
#   endif

#   include "flag-macros.hh"

#   define TEST_ALL_VALUES
#   include "flag-macros.hh"
#   undef TEST_ALL_VALUES

    itype.clear();
#   include "flag-macros.hh"

    itype = "foo";
#   include "flag-macros.hh"

    jsonschemaenforcer::ItemType itype2(jsonschemaenforcer::ItemType::type_Number);
    BOOST_CHECK_EQUAL(itype2.get_type(), jsonschemaenforcer::ItemType::type_Number);

    jsonschemaenforcer::ItemType itype3("string");
    BOOST_CHECK_EQUAL(itype3.get_type(), jsonschemaenforcer::ItemType::type_String);

    jsonschemaenforcer::ItemType itype4(itype2);
    BOOST_CHECK_EQUAL(itype4.get_type(), jsonschemaenforcer::ItemType::type_Number);

    BOOST_CHECK(itype == itype);
    BOOST_CHECK(itype != itype2);
    BOOST_CHECK(itype != itype3);
    BOOST_CHECK(itype != itype4);

    BOOST_CHECK(itype2 != itype);
    BOOST_CHECK(itype2 == itype2);
    BOOST_CHECK(itype2 != itype3);
    BOOST_CHECK(itype2 == itype4);

    BOOST_CHECK(itype3 != itype);
    BOOST_CHECK(itype3 != itype2);
    BOOST_CHECK(itype3 == itype3);
    BOOST_CHECK(itype3 != itype4);

    BOOST_CHECK(itype4 != itype);
    BOOST_CHECK(itype4 == itype2);
    BOOST_CHECK(itype4 != itype3);
    BOOST_CHECK(itype4 == itype4);

    itype4.clear();

    BOOST_CHECK(itype4 == itype);
    BOOST_CHECK(itype4 != itype2);
    BOOST_CHECK(itype4 != itype3);
    BOOST_CHECK(itype4 == itype4);

    itype4 = itype3;

    BOOST_CHECK(itype4 != itype);
    BOOST_CHECK(itype4 != itype2);
    BOOST_CHECK(itype4 == itype3);
    BOOST_CHECK(itype4 == itype4);

    BOOST_CHECK(itype4 == "string");
    BOOST_CHECK("string" == itype4);
    BOOST_CHECK(itype4 == std::string("string"));
    BOOST_CHECK(std::string("string") == itype4);

    BOOST_CHECK(itype != "string");
    BOOST_CHECK("string" != itype);
    BOOST_CHECK(itype != std::string("string"));
    BOOST_CHECK(std::string("string") != itype);

    BOOST_CHECK(itype != "foo");
    BOOST_CHECK("foo" != itype);
    BOOST_CHECK(itype != std::string("foo"));
    BOOST_CHECK(std::string("foo") != itype);
}

BOOST_AUTO_TEST_SUITE_END()
