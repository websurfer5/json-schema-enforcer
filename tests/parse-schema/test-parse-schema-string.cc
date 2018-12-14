// test-schema-string.cc
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

BOOST_AUTO_TEST_CASE( parse_schema_string )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_string));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_str_content_encoding());
    BOOST_CHECK(!sd.root_item.has_str_content_media_type());
    BOOST_CHECK(!sd.root_item.has_str_n_max_length());
    BOOST_CHECK(!sd.root_item.has_str_n_min_length());
    BOOST_CHECK(!sd.root_item.has_str_pattern());
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_encoding(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_media_type(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_max_length(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_min_length(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_pattern(), "");
}

BOOST_AUTO_TEST_CASE( parse_schema_string_maxLength )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_string_maxLength));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_str_content_encoding());
    BOOST_CHECK(!sd.root_item.has_str_content_media_type());
    BOOST_CHECK(sd.root_item.has_str_n_max_length());
    BOOST_CHECK(!sd.root_item.has_str_n_min_length());
    BOOST_CHECK(!sd.root_item.has_str_pattern());
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_encoding(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_media_type(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_max_length(), 256);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_min_length(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_pattern(), "");
}

BOOST_AUTO_TEST_CASE( parse_schema_string_minLength )
{
    jsonschemaenforcer::SchemaData sd;

    BOOST_CHECK(sd.parse_schema(str_schema_input_json_string_minLength));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_str_content_encoding());
    BOOST_CHECK(!sd.root_item.has_str_content_media_type());
    BOOST_CHECK(!sd.root_item.has_str_n_max_length());
    BOOST_CHECK(sd.root_item.has_str_n_min_length());
    BOOST_CHECK(!sd.root_item.has_str_pattern());
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_encoding(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_media_type(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_max_length(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_min_length(), 100);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_pattern(), "");
}

BOOST_AUTO_TEST_CASE( parse_schema_string_pattern )
{
    jsonschemaenforcer::SchemaData sd;


    BOOST_CHECK(sd.parse_schema(str_schema_input_json_string_pattern));
    BOOST_CHECK(!sd.root_item.empty());
    BOOST_CHECK(!sd.root_item.has_str_content_encoding());
    BOOST_CHECK(!sd.root_item.has_str_content_media_type());
    BOOST_CHECK(!sd.root_item.has_str_n_max_length());
    BOOST_CHECK(!sd.root_item.has_str_n_min_length());
    BOOST_CHECK(sd.root_item.has_str_pattern());
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_encoding(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_content_media_type(), "");
    BOOST_CHECK_EQUAL(sd.root_item.get_string_max_length(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_min_length(), 0);
    BOOST_CHECK_EQUAL(sd.root_item.get_string_pattern(), "test[123]+");
}


BOOST_AUTO_TEST_SUITE_END()
