// test-ParsedItemData-class.cc
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
#include "ParsedItemData.hh"

#define VARS_FILE       "ParsedItemData-vars.hh"
#define TEST_OBJECT     idata1
#define TEST_NAMESPACE  jsonschemaenforcer

BOOST_AUTO_TEST_SUITE( ParsedItemData_class_test_suite )

BOOST_AUTO_TEST_CASE( test_ParsedItemData_class )
{
    jsonschemaenforcer::ParsedItemData idata,
                                 idata1,
                                 idata2;
    jsonschemaenforcer::SchemaItem sitem;
    jsonschemaenforcer::SchemaItemList sitem_list;
    jsonschemaenforcer::StdStringList dependencies_list,
                                required_list;

    dependencies_list.clear();
    dependencies_list.push_back("foo");
    dependencies_list.push_back("bar");

    required_list.clear();
    required_list.push_back("abc");
    required_list.push_back("def");
    required_list.push_back("ghi");

    sitem_list.clear();
    sitem_list.push_back(sitem);

    //
    // check initial values
    //

    BOOST_CHECK(idata1.empty());
#   include "var-obj-macros.hh"
    BOOST_CHECK(idata1.empty());
    BOOST_CHECK(idata1 == idata2);
    BOOST_CHECK(idata2 == idata1);
    BOOST_CHECK((idata2 | idata1) == idata1);
    BOOST_CHECK((idata2 | idata1) == idata2);
    idata2 |= idata1;
    BOOST_CHECK(idata1 == idata2);
    BOOST_CHECK(idata2 == idata1);

    //
    // check setting values
    //

#   define TEST_ALL_VALUES
    idata1.clear();
    BOOST_CHECK(idata1.empty());
#   include "var-obj-macros.hh"
#   undef TEST_ALL_VALUES
    BOOST_CHECK(!idata1.empty());

    //
    // check initial values
    //

    BOOST_CHECK(idata1 != idata2);
    BOOST_CHECK(idata2 != idata1);
    BOOST_CHECK((idata1 | idata2) == idata1);
    BOOST_CHECK((idata1 | idata2) != idata2);
    BOOST_CHECK((idata2 | idata1) == idata1);
    BOOST_CHECK((idata2 | idata1) != idata2);
    idata2 |= idata1;
    BOOST_CHECK(idata1 == idata2);
    BOOST_CHECK(idata2 == idata1);
    BOOST_CHECK((idata1 | idata2) == idata1);
    BOOST_CHECK((idata1 | idata2) == idata2);
    BOOST_CHECK((idata2 | idata1) == idata1);
    BOOST_CHECK((idata2 | idata1) == idata2);

    idata1.clear();

    //
    // check assignment and equality
    //

    jsonschemaenforcer::ParsedItemData idata3(idata2);
    BOOST_CHECK(idata1 != idata3);
    BOOST_CHECK(idata2 == idata3);
    BOOST_CHECK(idata3 != idata1);
    BOOST_CHECK(idata3 == idata2);
    BOOST_CHECK((idata3 | idata1) != idata1);
    BOOST_CHECK((idata1 | idata3) != idata1);
    BOOST_CHECK((idata3 | idata1) == idata2);
    BOOST_CHECK((idata1 | idata3) == idata2);
    BOOST_CHECK((idata3 | idata2) != idata1);
    BOOST_CHECK((idata2 | idata3) != idata1);
    BOOST_CHECK((idata3 | idata2) == idata2);
    BOOST_CHECK((idata2 | idata3) == idata2);

    idata3 = idata1;
    BOOST_CHECK(idata1 == idata3);
    BOOST_CHECK(idata2 != idata3);
    BOOST_CHECK(idata3 == idata1);
    BOOST_CHECK(idata3 != idata2);
    BOOST_CHECK((idata3 | idata1) == idata1);
    BOOST_CHECK((idata1 | idata3) == idata1);
    BOOST_CHECK((idata3 | idata1) != idata2);
    BOOST_CHECK((idata1 | idata3) != idata2);
    BOOST_CHECK((idata3 | idata2) != idata1);
    BOOST_CHECK((idata2 | idata3) != idata1);
    BOOST_CHECK((idata3 | idata2) == idata2);
    BOOST_CHECK((idata2 | idata3) == idata2);

    idata3 = idata2;
    BOOST_CHECK(idata1 != idata3);
    BOOST_CHECK(idata2 == idata3);
    BOOST_CHECK(idata3 != idata1);
    BOOST_CHECK(idata3 == idata2);
    BOOST_CHECK((idata3 | idata1) != idata1);
    BOOST_CHECK((idata1 | idata3) != idata1);
    BOOST_CHECK((idata3 | idata1) == idata2);
    BOOST_CHECK((idata1 | idata3) == idata2);
    BOOST_CHECK((idata3 | idata2) != idata1);
    BOOST_CHECK((idata2 | idata3) != idata1);
    BOOST_CHECK((idata3 | idata2) == idata2);
    BOOST_CHECK((idata2 | idata3) == idata2);
}

BOOST_AUTO_TEST_SUITE_END()
