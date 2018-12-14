// test-SchemaItem-class.cc
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
#include "SchemaItem.hh"

#define VARS_FILE       "SchemaItem-vars.hh"
#define TEST_OBJECT     sitem1
#define TEST_NAMESPACE  jsonschemaenforcer

BOOST_AUTO_TEST_SUITE( SchemaItem_class_test_suite )

BOOST_AUTO_TEST_CASE( test_SchemaItem_class )
{
    jsonschemaenforcer::ParsedItemData idata_integer,
                                 idata_number,
                                 idata_intnum1,
                                 idata_intnum2,
                                 idata_intnum3,
                                 idata_intnum4,
                                 idata_intnum5,
                                 idata_string;
    jsonschemaenforcer::SchemaItem sitem_integer,
                             sitem_number,
                             sitem_string,
                             sitem1;

    //
    // initialize ParsedItemData vars
    //

    idata_integer.set_item_type(jsonschemaenforcer::ItemType::type_Integer);
    idata_integer.set_item_exclusive_maximum(1);
    idata_integer.set_item_exclusive_minimum(2);
    idata_integer.set_item_maximum(3);
    idata_integer.set_item_minimum(4);
    idata_integer.set_item_multiple_of(5);

    idata_number.set_item_type(jsonschemaenforcer::ItemType::type_Number);
    idata_number.set_item_exclusive_maximum(1.1);
    idata_number.set_item_exclusive_minimum(2.1);
    idata_number.set_item_maximum(3.1);
    idata_number.set_item_minimum(4.1);
    idata_number.set_item_multiple_of(5.1);

    idata_intnum1.set_item_type(jsonschemaenforcer::ItemType::type_Integer);
    idata_intnum1.set_item_exclusive_maximum(1);
    idata_intnum1.set_item_exclusive_minimum(2.1);
    idata_intnum1.set_item_maximum(3.1);
    idata_intnum1.set_item_minimum(4.1);
    idata_intnum1.set_item_multiple_of(5.1);

    idata_intnum2.set_item_type(jsonschemaenforcer::ItemType::type_Integer);
    idata_intnum2.set_item_exclusive_maximum(1.1);
    idata_intnum2.set_item_exclusive_minimum(2);
    idata_intnum2.set_item_maximum(3.1);
    idata_intnum2.set_item_minimum(4.1);
    idata_intnum2.set_item_multiple_of(5.1);

    idata_intnum3.set_item_type(jsonschemaenforcer::ItemType::type_Integer);
    idata_intnum3.set_item_exclusive_maximum(1.1);
    idata_intnum3.set_item_exclusive_minimum(2.1);
    idata_intnum3.set_item_maximum(3);
    idata_intnum3.set_item_minimum(4.1);
    idata_intnum3.set_item_multiple_of(5.1);

    idata_intnum4.set_item_type(jsonschemaenforcer::ItemType::type_Integer);
    idata_intnum4.set_item_exclusive_maximum(1.1);
    idata_intnum4.set_item_exclusive_minimum(2.1);
    idata_intnum4.set_item_maximum(3.1);
    idata_intnum4.set_item_minimum(4);
    idata_intnum4.set_item_multiple_of(5.1);

    idata_intnum5.set_item_type(jsonschemaenforcer::ItemType::type_Integer);
    idata_intnum5.set_item_exclusive_maximum(1.1);
    idata_intnum5.set_item_exclusive_minimum(2.1);
    idata_intnum5.set_item_maximum(3.1);
    idata_intnum5.set_item_minimum(4.1);
    idata_intnum5.set_item_multiple_of(5);

    idata_string.set_item_type(jsonschemaenforcer::ItemType::type_String);
    idata_string.set_item_max_length(256);
    idata_string.set_item_min_length(128);
    idata_string.set_item_pattern("foo[123]+");

    //
    // test object defaults
    //

    BOOST_CHECK(sitem1.empty());
#   include "var-obj-macros.hh"
    BOOST_CHECK(sitem1.empty());
    // BOOST_CHECK_EQUAL(sitem1.array_n_max_items, 0);
    // BOOST_CHECK_EQUAL(sitem1.array_n_min_items, 0);
    // BOOST_CHECK(sitem1.array_properties.empty());
    // BOOST_CHECK(!sitem1.array_b_unique);
    // BOOST_CHECK(!sitem1.b_has_array_max_items);
    // BOOST_CHECK(!sitem1.b_has_array_min_items);
    // BOOST_CHECK(!sitem1.b_has_array_properties);
    // BOOST_CHECK(!sitem1.b_has_array_unique);
    // BOOST_CHECK(!sitem1.b_has_int_exclusive_maximum);
    // BOOST_CHECK(!sitem1.b_has_int_exclusive_minimum);
    // BOOST_CHECK(!sitem1.b_has_int_maximum);
    // BOOST_CHECK(!sitem1.b_has_int_minimum);
    // BOOST_CHECK(!sitem1.b_has_int_multiple_of);
    // BOOST_CHECK(!sitem1.b_has_num_exclusive_maximum);
    // BOOST_CHECK(!sitem1.b_has_num_exclusive_minimum);
    // BOOST_CHECK(!sitem1.b_has_num_exclusive_minimum);
    // BOOST_CHECK(!sitem1.b_has_num_minimum);
    // BOOST_CHECK(!sitem1.b_has_num_multiple_of);
    // BOOST_CHECK(!sitem1.b_has_str_n_max_length);
    // BOOST_CHECK(!sitem1.b_has_str_n_min_length);
    // BOOST_CHECK(!sitem1.b_has_str_pattern);
    // BOOST_CHECK_EQUAL(sitem1.int_exclusive_maximum, 0);
    // BOOST_CHECK_EQUAL(sitem1.int_exclusive_minimum, 0);
    // BOOST_CHECK_EQUAL(sitem1.int_maximum, 0);
    // BOOST_CHECK_EQUAL(sitem1.int_minimum, 0);
    // BOOST_CHECK_EQUAL(sitem1.int_multiple_of, 0);
    // BOOST_CHECK_EQUAL(sitem1.item_type, jsonschemaenforcer::ItemType::type_Unknown);
    // BOOST_CHECK_EQUAL(sitem1.key, "");
    // BOOST_CHECK_EQUAL(sitem1.num_exclusive_maximum, 0);
    // BOOST_CHECK_EQUAL(sitem1.num_exclusive_minimum, 0);
    // BOOST_CHECK_EQUAL(sitem1.num_maximum, 0);
    // BOOST_CHECK_EQUAL(sitem1.num_minimum, 0);
    // BOOST_CHECK_EQUAL(sitem1.num_multiple_of, 0);
    // BOOST_CHECK_EQUAL(sitem1.str_n_max_length, 0);
    // BOOST_CHECK_EQUAL(sitem1.str_n_min_length, 0);
    // BOOST_CHECK_EQUAL(sitem1.str_pattern, "");
    // BOOST_CHECK(sitem1.get_type_name().empty());

    //
    // check setting values
    //

#   define TEST_ALL_VALUES
    sitem1.clear();
    BOOST_CHECK(sitem1.empty());
#   include "var-obj-macros.hh"
#   undef TEST_ALL_VALUES
    BOOST_CHECK(!sitem1.empty());
    sitem1.clear();

    //
    // test itegers/numbers
    //

    BOOST_CHECK(sitem_integer.define_item("key_int", idata_integer));
    BOOST_CHECK(sitem_integer.has_Integer_type());
    BOOST_CHECK_EQUAL(sitem_integer.key, "key_int");
    BOOST_CHECK_EQUAL(sitem_integer.int_exclusive_maximum, 1);
    BOOST_CHECK_EQUAL(sitem_integer.int_exclusive_minimum, 2);
    BOOST_CHECK_EQUAL(sitem_integer.int_maximum, 3);
    BOOST_CHECK_EQUAL(sitem_integer.int_minimum, 4);
    BOOST_CHECK_EQUAL(sitem_integer.int_multiple_of, 5);
    BOOST_CHECK_EQUAL(sitem_integer.num_exclusive_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_exclusive_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_multiple_of, 0);
    BOOST_CHECK(!sitem_integer.array_b_unique);
    BOOST_CHECK(!sitem_integer.b_has_array_max_items);
    BOOST_CHECK(!sitem_integer.b_has_array_min_items);
    BOOST_CHECK(!sitem_integer.b_has_array_properties);
    BOOST_CHECK(!sitem_integer.b_has_array_unique);
    BOOST_CHECK(sitem_integer.b_has_int_exclusive_maximum);
    BOOST_CHECK(sitem_integer.b_has_int_exclusive_minimum);
    BOOST_CHECK(sitem_integer.b_has_int_maximum);
    BOOST_CHECK(sitem_integer.b_has_int_minimum);
    BOOST_CHECK(sitem_integer.b_has_int_multiple_of);
    BOOST_CHECK(!sitem_integer.b_has_num_exclusive_maximum);
    BOOST_CHECK(!sitem_integer.b_has_num_exclusive_minimum);
    BOOST_CHECK(!sitem_integer.b_has_num_exclusive_minimum);
    BOOST_CHECK(!sitem_integer.b_has_num_minimum);
    BOOST_CHECK(!sitem_integer.b_has_num_multiple_of);
    BOOST_CHECK(!sitem_integer.b_has_str_n_max_length);
    BOOST_CHECK(!sitem_integer.b_has_str_n_min_length);
    BOOST_CHECK(!sitem_integer.b_has_str_pattern);

    BOOST_CHECK(sitem_number.define_item("key_num", idata_number));
    BOOST_CHECK(sitem_number.has_Number_type());
    BOOST_CHECK_EQUAL(sitem_number.key, "key_num");
    BOOST_CHECK_EQUAL(sitem_number.int_exclusive_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_exclusive_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_multiple_of, 0);
    BOOST_CHECK_EQUAL(sitem_number.num_exclusive_maximum, 1.1);
    BOOST_CHECK_EQUAL(sitem_number.num_exclusive_minimum, 2.1);
    BOOST_CHECK_EQUAL(sitem_number.num_maximum, 3.1);
    BOOST_CHECK_EQUAL(sitem_number.num_minimum, 4.1);
    BOOST_CHECK_EQUAL(sitem_number.num_multiple_of, 5.1);
    BOOST_CHECK(!sitem_number.array_b_unique);
    BOOST_CHECK(!sitem_number.b_has_array_max_items);
    BOOST_CHECK(!sitem_number.b_has_array_min_items);
    BOOST_CHECK(!sitem_number.b_has_array_properties);
    BOOST_CHECK(!sitem_number.b_has_array_unique);
    BOOST_CHECK(!sitem_number.b_has_int_exclusive_maximum);
    BOOST_CHECK(!sitem_number.b_has_int_exclusive_minimum);
    BOOST_CHECK(!sitem_number.b_has_int_maximum);
    BOOST_CHECK(!sitem_number.b_has_int_minimum);
    BOOST_CHECK(!sitem_number.b_has_int_multiple_of);
    BOOST_CHECK(sitem_number.b_has_num_exclusive_maximum);
    BOOST_CHECK(sitem_number.b_has_num_exclusive_minimum);
    BOOST_CHECK(sitem_number.b_has_num_exclusive_minimum);
    BOOST_CHECK(sitem_number.b_has_num_minimum);
    BOOST_CHECK(sitem_number.b_has_num_multiple_of);
    BOOST_CHECK(!sitem_number.b_has_str_n_max_length);
    BOOST_CHECK(!sitem_number.b_has_str_n_min_length);
    BOOST_CHECK(!sitem_number.b_has_str_pattern);

    BOOST_CHECK(!sitem1.define_item("key_intnum1", idata_intnum1));
    sitem1.clear();
    BOOST_CHECK(!sitem1.define_item("key_intnum2", idata_intnum2));
    sitem1.clear();
    BOOST_CHECK(!sitem1.define_item("key_intnum3", idata_intnum3));
    sitem1.clear();
    BOOST_CHECK(!sitem1.define_item("key_intnum4", idata_intnum4));
    sitem1.clear();
    BOOST_CHECK(!sitem1.define_item("key_intnum5", idata_intnum5));

    //
    // test strings
    //

    BOOST_CHECK(sitem_string.define_item("key_string", idata_string));
    BOOST_CHECK_EQUAL(sitem_number.int_exclusive_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_exclusive_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_number.int_multiple_of, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_exclusive_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_exclusive_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_maximum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_minimum, 0);
    BOOST_CHECK_EQUAL(sitem_integer.num_multiple_of, 0);
    BOOST_CHECK(sitem_string.has_String_type());
    BOOST_CHECK_EQUAL(sitem_string.key, "key_string");
    BOOST_CHECK_EQUAL(sitem_string.str_n_max_length, 256);
    BOOST_CHECK_EQUAL(sitem_string.str_n_min_length, 128);
    BOOST_CHECK_EQUAL(sitem_string.str_pattern, "foo[123]+");
    BOOST_CHECK(!sitem_string.array_b_unique);
    BOOST_CHECK(!sitem_string.b_has_array_max_items);
    BOOST_CHECK(!sitem_string.b_has_array_min_items);
    BOOST_CHECK(!sitem_string.b_has_array_properties);
    BOOST_CHECK(!sitem_string.b_has_array_unique);
    BOOST_CHECK(!sitem_string.b_has_int_exclusive_maximum);
    BOOST_CHECK(!sitem_string.b_has_int_exclusive_minimum);
    BOOST_CHECK(!sitem_string.b_has_int_maximum);
    BOOST_CHECK(!sitem_string.b_has_int_minimum);
    BOOST_CHECK(!sitem_string.b_has_int_multiple_of);
    BOOST_CHECK(!sitem_string.b_has_num_exclusive_maximum);
    BOOST_CHECK(!sitem_string.b_has_num_exclusive_minimum);
    BOOST_CHECK(!sitem_string.b_has_num_exclusive_minimum);
    BOOST_CHECK(!sitem_string.b_has_num_minimum);
    BOOST_CHECK(!sitem_string.b_has_num_multiple_of);
    BOOST_CHECK(sitem_string.b_has_str_n_max_length);
    BOOST_CHECK(sitem_string.b_has_str_n_min_length);
    BOOST_CHECK(sitem_string.b_has_str_pattern);

    //
    // test equality
    //

    sitem1.clear();
    BOOST_CHECK(sitem1 != sitem_integer);
    BOOST_CHECK(sitem1 != sitem_number);
    BOOST_CHECK(sitem1 != sitem_string);
    BOOST_CHECK(sitem_string != sitem1);
    BOOST_CHECK(sitem_string != sitem_integer);
    BOOST_CHECK(sitem_string != sitem_number);
    BOOST_CHECK(sitem_integer != sitem1);
    BOOST_CHECK(sitem_integer != sitem_number);
    BOOST_CHECK(sitem_integer != sitem_string);
    BOOST_CHECK(sitem_number != sitem1);
    BOOST_CHECK(sitem_number != sitem_integer);
    BOOST_CHECK(sitem_number != sitem_string);

    sitem1 = sitem_integer;
    BOOST_CHECK(sitem1 == sitem_integer);
    BOOST_CHECK(sitem1 != sitem_number);
    BOOST_CHECK(sitem1 != sitem_string);
    BOOST_CHECK(sitem_integer == sitem1);
    BOOST_CHECK(sitem_integer != sitem_number);
    BOOST_CHECK(sitem_integer != sitem_string);
    BOOST_CHECK(sitem_number != sitem1);
    BOOST_CHECK(sitem_number != sitem_integer);
    BOOST_CHECK(sitem_number != sitem_string);
    BOOST_CHECK(sitem_string != sitem1);
    BOOST_CHECK(sitem_string != sitem_integer);
    BOOST_CHECK(sitem_string != sitem_number);

    sitem1 = sitem_number;
    BOOST_CHECK(sitem1 != sitem_integer);
    BOOST_CHECK(sitem1 == sitem_number);
    BOOST_CHECK(sitem1 != sitem_string);
    BOOST_CHECK(sitem_integer != sitem1);
    BOOST_CHECK(sitem_integer != sitem_number);
    BOOST_CHECK(sitem_integer != sitem_string);
    BOOST_CHECK(sitem_number == sitem1);
    BOOST_CHECK(sitem_number != sitem_integer);
    BOOST_CHECK(sitem_number != sitem_string);
    BOOST_CHECK(sitem_string != sitem1);
    BOOST_CHECK(sitem_string != sitem_integer);
    BOOST_CHECK(sitem_string != sitem_number);

    sitem1 = sitem_string;
    BOOST_CHECK(sitem1 != sitem_integer);
    BOOST_CHECK(sitem1 != sitem_number);
    BOOST_CHECK(sitem1 == sitem_string);
    BOOST_CHECK(sitem_string == sitem1);
    BOOST_CHECK(sitem_string != sitem_integer);
    BOOST_CHECK(sitem_string != sitem_number);
    BOOST_CHECK(sitem_integer != sitem1);
    BOOST_CHECK(sitem_integer != sitem_number);
    BOOST_CHECK(sitem_integer != sitem_string);
    BOOST_CHECK(sitem_number != sitem1);
    BOOST_CHECK(sitem_number != sitem_integer);
    BOOST_CHECK(sitem_number != sitem_string);
}

BOOST_AUTO_TEST_SUITE_END()
