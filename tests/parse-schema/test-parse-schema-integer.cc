// test-schema-integer.cc
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

BOOST_AUTO_TEST_CASE( parse_schema_integer_all )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer_all));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(sd.root_item.has_int_maximum());
    BOOST_CHECK(sd.root_item.has_int_minimum());
    BOOST_CHECK(sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 201);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), -11);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 200);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), -10);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 5);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer_exclusiveMaximum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer_exclusiveMaximum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_int_maximum());
    BOOST_CHECK(!sd.root_item.has_int_minimum());
    BOOST_CHECK(!sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 201);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer_exclusiveMinimum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer_exclusiveMinimum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_int_maximum());
    BOOST_CHECK(!sd.root_item.has_int_minimum());
    BOOST_CHECK(!sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), -11);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer_maximum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer_maximum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(sd.root_item.has_int_maximum());
    BOOST_CHECK(!sd.root_item.has_int_minimum());
    BOOST_CHECK(!sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 200);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer_minimum )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer_minimum));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_int_maximum());
    BOOST_CHECK(sd.root_item.has_int_minimum());
    BOOST_CHECK(!sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), -10);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer_multipleOf )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer_multipleOf));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_int_maximum());
    BOOST_CHECK(!sd.root_item.has_int_minimum());
    BOOST_CHECK(sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 5);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_integer));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_int_maximum());
    BOOST_CHECK(!sd.root_item.has_int_minimum());
    BOOST_CHECK(!sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 0);
}

BOOST_AUTO_TEST_CASE( parse_schema_integer_float )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(!sd.parse_schema(str_schema_input_json_integer_float));
    BOOST_CHECK(sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_maximum());
    BOOST_CHECK(!sd.root_item.has_int_exclusive_minimum());
    BOOST_CHECK(!sd.root_item.has_int_maximum());
    BOOST_CHECK(!sd.root_item.has_int_minimum());
    BOOST_CHECK(!sd.root_item.has_int_multiple_of());
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_exclusive_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_maximum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_minimum(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_int_multiple_of(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
