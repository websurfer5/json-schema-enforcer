
// test-FormatType-class.cc
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
// Build fails on Ubuntu 16.04LTS using g++ 5.4 and boost 1.58 with errors
// about problems in the std::set template class definition
// included by boost/test/unit_test.hpp.  It works with boost 1.68, so the
// workaround is to include <set> for older versions of boost.
//

#include <boost/version.hpp>

#if BOOST_VERSION < 106800
#   include <set>
#endif

#include <boost/test/unit_test.hpp>
#include "FormatType.hh"

#define FLAGS_FILE      "FormatType-vars.hh"
#define FLAG_TYPE       jsonschemaenforcer::FormatType
#define FLAG_TYPE_ENUM  jsonschemaenforcer::FormatType::FormatTypeEnum
#define TEST_OBJECT     ftype

BOOST_AUTO_TEST_SUITE( FormatType_class_test_suite )

BOOST_AUTO_TEST_CASE( test_FormatType_class )
{
    jsonschemaenforcer::FormatType ftype;

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

    ftype.clear();
#   include "flag-macros.hh"

    ftype = "foo";
#   include "flag-macros.hh"

    jsonschemaenforcer::FormatType ftype2(jsonschemaenforcer::FormatType::type_Hostname);
    BOOST_CHECK_EQUAL(ftype2.get_type(), jsonschemaenforcer::FormatType::type_Hostname);

    jsonschemaenforcer::FormatType ftype3("ipv6");
    BOOST_CHECK_EQUAL(ftype3.get_type(), jsonschemaenforcer::FormatType::type_Ipv6);

    jsonschemaenforcer::FormatType ftype4(ftype2);
    BOOST_CHECK_EQUAL(ftype4.get_type(), jsonschemaenforcer::FormatType::type_Hostname);

    BOOST_CHECK(ftype == ftype);
    BOOST_CHECK(ftype != ftype2);
    BOOST_CHECK(ftype != ftype3);
    BOOST_CHECK(ftype != ftype4);

    BOOST_CHECK(ftype2 != ftype);
    BOOST_CHECK(ftype2 == ftype2);
    BOOST_CHECK(ftype2 != ftype3);
    BOOST_CHECK(ftype2 == ftype4);

    BOOST_CHECK(ftype3 != ftype);
    BOOST_CHECK(ftype3 != ftype2);
    BOOST_CHECK(ftype3 == ftype3);
    BOOST_CHECK(ftype3 != ftype4);

    BOOST_CHECK(ftype4 != ftype);
    BOOST_CHECK(ftype4 == ftype2);
    BOOST_CHECK(ftype4 != ftype3);
    BOOST_CHECK(ftype4 == ftype4);

    ftype4.clear();

    BOOST_CHECK(ftype4 == ftype);
    BOOST_CHECK(ftype4 != ftype2);
    BOOST_CHECK(ftype4 != ftype3);
    BOOST_CHECK(ftype4 == ftype4);

    ftype4 = ftype3;

    BOOST_CHECK(ftype4 != ftype);
    BOOST_CHECK(ftype4 != ftype2);
    BOOST_CHECK(ftype4 == ftype3);
    BOOST_CHECK(ftype4 == ftype4);

    BOOST_CHECK(ftype4 == "ipv6");
    BOOST_CHECK("ipv6" == ftype4);
    BOOST_CHECK(ftype4 == std::string("ipv6"));
    BOOST_CHECK(std::string("ipv6") == ftype4);

    BOOST_CHECK(ftype != "ipv6");
    BOOST_CHECK("ipv6" != ftype);
    BOOST_CHECK(ftype != std::string("ipv6"));
    BOOST_CHECK(std::string("ipv6") != ftype);

    BOOST_CHECK(ftype != "foo");
    BOOST_CHECK("foo" != ftype);
    BOOST_CHECK(ftype != std::string("foo"));
    BOOST_CHECK(std::string("foo") != ftype);
}

BOOST_AUTO_TEST_SUITE_END()
