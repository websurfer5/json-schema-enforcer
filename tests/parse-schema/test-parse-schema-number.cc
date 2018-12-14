// test-schema-number.cc
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
#include "json-strings.hh"
#include "SchemaData.hh"

BOOST_AUTO_TEST_SUITE( parse_schema_test_suite )

BOOST_AUTO_TEST_CASE( parse_schema_number_all )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number_all));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(sd.root_item.has_num_maximum());
    BOOST_CHECK(sd.root_item.has_num_minimum());
    BOOST_CHECK(sd.root_item.has_num_multiple_of());
    BOOST_CHECK_CLOSE(sd.root_item.get_num_exclusive_maximum(), 110.1, 2);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_exclusive_minimum(), -11.05, 2);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_maximum(), 110.1, 2);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_minimum(), -11.05, 2);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_multiple_of(), 5.5, 2);
}

BOOST_AUTO_TEST_CASE( parse_schema_number_exclusiveMaximum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number_exclusiveMaximum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(sd.root_item.has_num_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_num_maximum());
    BOOST_CHECK(!sd.root_item.has_num_minimum());
    BOOST_CHECK(!sd.root_item.has_num_multiple_of());
    BOOST_CHECK_CLOSE(sd.root_item.get_num_exclusive_maximum(), 110.1, 2);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_number_exclusiveMinimum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number_exclusiveMinimum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_maximum());
    BOOST_CHECK(sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_num_maximum());
    BOOST_CHECK(!sd.root_item.has_num_minimum());
    BOOST_CHECK(!sd.root_item.has_num_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_maximum(), 0);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_exclusive_minimum(), -11.05, 2);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_number_maximum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number_maximum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(sd.root_item.has_num_maximum());
    BOOST_CHECK(!sd.root_item.has_num_minimum());
    BOOST_CHECK(!sd.root_item.has_num_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_minimum(), 0);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_maximum(), 110.05, 2);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_number_minimum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number_minimum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_num_maximum());
    BOOST_CHECK(sd.root_item.has_num_minimum());
    BOOST_CHECK(!sd.root_item.has_num_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_maximum(), 0);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_minimum(), -11.05, 2);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_number_multipleOf )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number_multipleOf));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_num_maximum());
    BOOST_CHECK(!sd.root_item.has_num_minimum());
    BOOST_CHECK(sd.root_item.has_num_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_minimum(), 0);
    BOOST_CHECK_CLOSE(sd.root_item.get_num_multiple_of(), 5.5, 2);
}

BOOST_AUTO_TEST_CASE( parse_schema_number )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_number));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_num_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_num_maximum());
    BOOST_CHECK(!sd.root_item.has_num_minimum());
    BOOST_CHECK(!sd.root_item.has_num_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_num_multiple_of(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
