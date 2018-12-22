// test-Json-class.cc
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
#include "json.hh"
#include <stdexcept>
#include <iostream>

BOOST_AUTO_TEST_SUITE( Json_class_test_suite )

BOOST_AUTO_TEST_CASE( test_Json_class_1 )
{
    foo::JsonItem jitem1,
                  jitem2;

    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = false;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_REQUIRE_NO_THROW(jitem1.boolean());
    BOOST_CHECK_EQUAL(jitem1.boolean(), false);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1.clear();
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = true;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_REQUIRE_NO_THROW(jitem1.boolean());
    BOOST_CHECK_EQUAL(jitem1.boolean(), true);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = 5.25;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.number());
    BOOST_CHECK_EQUAL(jitem1.number(), 5.25);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1.set_null();
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1.clear();
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = 4;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.number());
    BOOST_CHECK_EQUAL(jitem1.number(), 4);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = 11L;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.number());
    BOOST_CHECK_EQUAL(jitem1.number(), 11);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = 22U;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.number());
    BOOST_CHECK_EQUAL(jitem1.number(), 22);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = 33UL;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.number());
    BOOST_CHECK_EQUAL(jitem1.number(), 33);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = (float) 6.5;
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.number());
    BOOST_CHECK_EQUAL(jitem1.number(), 6.5);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1.clear();
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = std::string("bar");
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.string());
    BOOST_CHECK_EQUAL(jitem1.string(), "bar");
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1 = "barbar";
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(jitem1.string());
    BOOST_CHECK_EQUAL(jitem1.string(), "barbar");
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1.clear();
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(!jitem1.is_string());
    BOOST_CHECK(jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    jitem1.set_string("foo");
    BOOST_CHECK(!jitem1.is_array());
    BOOST_CHECK(!jitem1.is_boolean());
    BOOST_CHECK(!jitem1.is_null());
    BOOST_CHECK(!jitem1.is_number());
    BOOST_CHECK(!jitem1.is_object());
    BOOST_CHECK(jitem1.is_string());
    BOOST_CHECK(!jitem1.empty());
    BOOST_CHECK_THROW(jitem1.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem1.number(), std::invalid_argument);
    BOOST_CHECK_NO_THROW(jitem1.string());
    BOOST_CHECK_EQUAL(jitem1.string(), "foo");
    BOOST_CHECK_THROW(jitem1["bar"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem1[7], std::invalid_argument);

    foo::JsonItem jitem3(true);
    BOOST_CHECK(!jitem3.is_array());
    BOOST_CHECK(jitem3.is_boolean());
    BOOST_CHECK(!jitem3.is_null());
    BOOST_CHECK(!jitem3.is_number());
    BOOST_CHECK(!jitem3.is_object());
    BOOST_CHECK(!jitem3.is_string());
    BOOST_CHECK(!jitem3.empty());
    BOOST_REQUIRE_NO_THROW(jitem3.boolean());
    BOOST_CHECK_EQUAL(jitem3.boolean(), true);
    BOOST_CHECK_THROW(jitem3.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem3.string(), std::invalid_argument);

    jitem2.append_array_item(jitem1);
    BOOST_CHECK(jitem2.is_array());
    BOOST_CHECK(!jitem2.is_boolean());
    BOOST_CHECK(!jitem2.is_null());
    BOOST_CHECK(!jitem2.is_number());
    BOOST_CHECK(!jitem2.is_object());
    BOOST_CHECK(!jitem2.is_string());
    BOOST_CHECK(!jitem2.empty());
    BOOST_CHECK_THROW(jitem2.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem2.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem2.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem2["bar"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem2[7], std::out_of_range);
    BOOST_CHECK_NO_THROW(jitem2[0]);
    BOOST_CHECK(jitem2[0].is_string());
    BOOST_CHECK(jitem2[0] == jitem1);
    BOOST_CHECK(jitem1 == jitem2[0]);
    BOOST_CHECK_EQUAL(jitem2[0].string(), "foo");

    jitem2.append_array_item(jitem3);
    BOOST_CHECK_NO_THROW(jitem2[0]);
    BOOST_CHECK(jitem2[0].is_string());
    BOOST_CHECK(jitem2[0] == jitem1);
    BOOST_CHECK(jitem1 == jitem2[0]);
    BOOST_CHECK_EQUAL(jitem2[0].string(), "foo");
    BOOST_CHECK_NO_THROW(jitem2[1]);
    BOOST_CHECK(jitem2[1].is_boolean());
    BOOST_CHECK(jitem2[1] == jitem3);
    BOOST_CHECK(jitem3 == jitem2[1]);

    jitem2.append_array_item(foo::JsonItem());
    jitem2.append_array_item(foo::JsonItem(4));
    jitem2.append_array_item(foo::JsonItem(40L));
    jitem2.append_array_item(foo::JsonItem(50U));
    jitem2.append_array_item(foo::JsonItem(60UL));
    jitem2.append_array_item(foo::JsonItem("bar"));
    jitem2.append_array_item(foo::JsonItem(std::string("barbar")));
    jitem2.append_array_item(foo::JsonItem().append_array_item(true));
    BOOST_CHECK_NO_THROW(jitem2[0]);
    BOOST_CHECK(jitem2[0].is_string());
    BOOST_CHECK(jitem2[0] == jitem1);
    BOOST_CHECK(jitem1 == jitem2[0]);
    BOOST_CHECK_EQUAL(jitem2[0].string(), "foo");
    BOOST_CHECK_NO_THROW(jitem2[1]);
    BOOST_CHECK(jitem2[1].is_boolean());
    BOOST_CHECK(jitem2[1] == jitem3);
    BOOST_CHECK(jitem3 == jitem2[1]);
    BOOST_CHECK_NO_THROW(jitem2[2]);
    BOOST_CHECK(jitem2[2].is_null());
    BOOST_CHECK_NO_THROW(jitem2[3]);
    BOOST_CHECK(jitem2[3].is_number());
    BOOST_CHECK_EQUAL(jitem2[3].number(), 4);
    BOOST_CHECK_NO_THROW(jitem2[4]);
    BOOST_CHECK(jitem2[4].is_number());
    BOOST_CHECK_EQUAL(jitem2[4].number(), 40);
    BOOST_CHECK_NO_THROW(jitem2[5]);
    BOOST_CHECK(jitem2[5].is_number());
    BOOST_CHECK_EQUAL(jitem2[5].number(), 50);
    BOOST_CHECK_NO_THROW(jitem2[6]);
    BOOST_CHECK(jitem2[6].is_number());
    BOOST_CHECK_EQUAL(jitem2[6].number(), 60);
    BOOST_CHECK_NO_THROW(jitem2[7]);
    BOOST_CHECK(jitem2[7].is_string());
    BOOST_CHECK_EQUAL(jitem2[7].string(), "bar");
    BOOST_CHECK_NO_THROW(jitem2[8]);
    BOOST_CHECK(jitem2[8].is_string());
    BOOST_CHECK_EQUAL(jitem2[8].string(), "barbar");
    BOOST_REQUIRE_NO_THROW(jitem2[9]);
    BOOST_CHECK(jitem2[9].is_array());
    BOOST_REQUIRE_NO_THROW(jitem2[9][0]);
    BOOST_CHECK(jitem2[9][0].is_boolean());
    BOOST_CHECK_EQUAL(jitem2[9][0].boolean(), true);
    jitem2[9].append_array_item("foo");
    jitem2[9].append_array_item(std::string("foofoo"));
    jitem2[9].append_array_item();
    jitem2[9].append_array_item(7.5);
    BOOST_REQUIRE_NO_THROW(jitem2[9][1]);
    BOOST_CHECK(jitem2[9][1].is_string());
    BOOST_CHECK_EQUAL(jitem2[9][1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem2[9][2]);
    BOOST_CHECK(jitem2[9][2].is_string());
    BOOST_CHECK_EQUAL(jitem2[9][2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem2[9][3]);
    BOOST_CHECK(jitem2[9][3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem2[9][4]);
    BOOST_CHECK(jitem2[9][4].is_number());
    BOOST_CHECK_EQUAL(jitem2[9][4].number(), 7.5);

    foo::JsonItemVector jvect;

    jvect = jitem2[9].array();
    BOOST_REQUIRE_EQUAL(jvect.size(), 5U);

    BOOST_REQUIRE_NO_THROW(jitem2.append_array(jitem2[9].array()));
    BOOST_REQUIRE_NO_THROW(jitem2[10]);
    BOOST_CHECK(jitem2[10].is_boolean());
    BOOST_CHECK_EQUAL(jitem2[10].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem2[11]);
    BOOST_CHECK(jitem2[11].is_string());
    BOOST_CHECK_EQUAL(jitem2[11].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem2[12]);
    BOOST_CHECK(jitem2[12].is_string());
    BOOST_CHECK_EQUAL(jitem2[12].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem2[13]);
    BOOST_CHECK(jitem2[13].is_null());
    BOOST_REQUIRE_NO_THROW(jitem2[14]);
    BOOST_CHECK(jitem2[14].is_number());
    BOOST_CHECK_EQUAL(jitem2[14].number(), 7.5);

    BOOST_REQUIRE_NO_THROW(jitem2.append_array_item(jitem2[9]));
    BOOST_CHECK(jitem2[15].is_array());
    BOOST_REQUIRE_NO_THROW(jitem2[15][0]);
    BOOST_CHECK(jitem2[15][0].is_boolean());
    BOOST_CHECK_EQUAL(jitem2[15][0].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem2[15][1]);
    BOOST_CHECK(jitem2[15][1].is_string());
    BOOST_CHECK_EQUAL(jitem2[15][1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem2[15][2]);
    BOOST_CHECK(jitem2[15][2].is_string());
    BOOST_CHECK_EQUAL(jitem2[15][2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem2[15][3]);
    BOOST_CHECK(jitem2[15][3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem2[15][4]);
    BOOST_CHECK(jitem2[15][4].is_number());
    BOOST_CHECK_EQUAL(jitem2[15][4].number(), 7.5);

    foo::JsonItem jitem4;
    jitem4.set_array(jitem2[9].array());
    BOOST_CHECK(jitem4.is_array());
    BOOST_REQUIRE_NO_THROW(jitem4[0]);
    BOOST_CHECK(jitem4[0].is_boolean());
    BOOST_CHECK_EQUAL(jitem4[0].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem4[1]);
    BOOST_CHECK(jitem4[1].is_string());
    BOOST_CHECK_EQUAL(jitem4[1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem4[2]);
    BOOST_CHECK(jitem4[2].is_string());
    BOOST_CHECK_EQUAL(jitem4[2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem4[3]);
    BOOST_CHECK(jitem4[3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem4[4]);
    BOOST_CHECK(jitem4[4].is_number());
    BOOST_CHECK_EQUAL(jitem4[4].number(), 7.5);

    jitem4.clear();
    BOOST_CHECK(!jitem4.is_array());
    BOOST_CHECK(!jitem4.is_boolean());
    BOOST_CHECK(jitem4.is_null());
    BOOST_CHECK(!jitem4.is_number());
    BOOST_CHECK(!jitem4.is_object());
    BOOST_CHECK(!jitem4.is_string());
    BOOST_CHECK(jitem4.empty());
    BOOST_CHECK_THROW(jitem4.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem4.number(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem4.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem4["foo"], std::invalid_argument);
    BOOST_CHECK_THROW(jitem4[7], std::invalid_argument);

    jitem4.set_object_item("bool", true);
    BOOST_CHECK(!jitem4.is_array());
    BOOST_CHECK(!jitem4.is_boolean());
    BOOST_CHECK(!jitem4.is_null());
    BOOST_CHECK(!jitem4.is_number());
    BOOST_CHECK(jitem4.is_object());
    BOOST_CHECK(!jitem4.is_string());
    BOOST_CHECK(!jitem4.empty());
    BOOST_CHECK_THROW(jitem4.array(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem4.boolean(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem4.number(), std::invalid_argument);
    BOOST_CHECK_NO_THROW(jitem4.object());
    BOOST_CHECK_THROW(jitem4.string(), std::invalid_argument);
    BOOST_CHECK_THROW(jitem4["foo"], std::out_of_range);
    BOOST_CHECK_THROW(jitem4[7], std::invalid_argument);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 1U);
    BOOST_CHECK_NO_THROW(jitem4["bool"]);
    BOOST_CHECK(jitem4["bool"].is_boolean());
    BOOST_CHECK_EQUAL(jitem4["bool"].boolean(), true);

    jitem4.set_object_item("string", "bar");
    BOOST_CHECK_EQUAL(jitem4.object().size(), 2U);
    BOOST_CHECK_NO_THROW(jitem4["string"]);
    BOOST_CHECK(jitem4["string"].is_string());
    BOOST_CHECK_EQUAL(jitem4["string"].string(), "bar");

    jitem4.set_object_item("int", -5);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 3U);
    BOOST_CHECK_NO_THROW(jitem4["int"]);
    BOOST_CHECK(jitem4["int"].is_number());
    BOOST_CHECK_EQUAL(jitem4["int"].number(), -5);

    jitem4.set_object_item("unsigned", 6U);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 4U);
    BOOST_CHECK_NO_THROW(jitem4["unsigned"]);
    BOOST_CHECK(jitem4["unsigned"].is_number());
    BOOST_CHECK_EQUAL(jitem4["unsigned"].number(), 6);

    jitem4.set_object_item("long", -7L);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 5U);
    BOOST_CHECK_NO_THROW(jitem4["long"]);
    BOOST_CHECK(jitem4["long"].is_number());
    BOOST_CHECK_EQUAL(jitem4["long"].number(), -7);

    jitem4.set_object_item("unsigned long", 8UL);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 6U);
    BOOST_CHECK_NO_THROW(jitem4["unsigned long"]);
    BOOST_CHECK(jitem4["unsigned long"].is_number());
    BOOST_CHECK_EQUAL(jitem4["unsigned long"].number(), 8);

    jitem4.set_object_item("float", (float) -9.5);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 7U);
    BOOST_CHECK_NO_THROW(jitem4["float"]);
    BOOST_CHECK(jitem4["float"].is_number());
    BOOST_CHECK_EQUAL(jitem4["float"].number(), -9.5);

    jitem4.set_object_item("double", (double) -10.25);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 8U);
    BOOST_CHECK_NO_THROW(jitem4["double"]);
    BOOST_CHECK(jitem4["double"].is_number());
    BOOST_CHECK_EQUAL(jitem4["double"].number(), -10.25);

    jitem4.set_object_item("null", foo::JsonItem());
    BOOST_CHECK_EQUAL(jitem4.object().size(), 9U);
    BOOST_CHECK_NO_THROW(jitem4["null"]);
    BOOST_CHECK(jitem4["null"].is_null());

    jitem4.set_object_item("array", jitem2[9]);
    BOOST_CHECK_EQUAL(jitem4.object().size(), 10U);
    BOOST_CHECK_NO_THROW(jitem4["array"]);
    BOOST_CHECK(jitem4["array"].is_array());
    BOOST_REQUIRE_NO_THROW(jitem4["array"][0]);
    BOOST_CHECK(jitem4["array"][0].is_boolean());
    BOOST_CHECK_EQUAL(jitem4["array"][0].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem4["array"][1]);
    BOOST_CHECK(jitem4["array"][1].is_string());
    BOOST_CHECK_EQUAL(jitem4["array"][1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem4["array"][2]);
    BOOST_CHECK(jitem4["array"][2].is_string());
    BOOST_CHECK_EQUAL(jitem4["array"][2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem4["array"][3]);
    BOOST_CHECK(jitem4["array"][3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem4["array"][4]);
    BOOST_CHECK(jitem4["array"][4].is_number());
    BOOST_CHECK_EQUAL(jitem4["array"][4].number(), 7.5);

    jitem4.set_object_item("array2", jitem2[9].array());
    BOOST_CHECK_EQUAL(jitem4.object().size(), 11U);
    BOOST_CHECK_NO_THROW(jitem4["array2"]);
    BOOST_CHECK(jitem4["array2"].is_array());
    BOOST_REQUIRE_NO_THROW(jitem4["array2"][0]);
    BOOST_CHECK(jitem4["array2"][0].is_boolean());
    BOOST_CHECK_EQUAL(jitem4["array2"][0].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem4["array2"][1]);
    BOOST_CHECK(jitem4["array2"][1].is_string());
    BOOST_CHECK_EQUAL(jitem4["array2"][1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem4["array2"][2]);
    BOOST_CHECK(jitem4["array2"][2].is_string());
    BOOST_CHECK_EQUAL(jitem4["array2"][2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem4["array2"][3]);
    BOOST_CHECK(jitem4["array2"][3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem4["array2"][4]);
    BOOST_CHECK(jitem4["array2"][4].is_number());
    BOOST_CHECK_EQUAL(jitem4["array2"][4].number(), 7.5);

    jitem4.set_object_item("object", foo::JsonItem().set_object_item("2", 2));
    BOOST_CHECK_EQUAL(jitem4.object().size(), 12U);
    BOOST_CHECK_NO_THROW(jitem4["object"]);
    BOOST_CHECK(jitem4["object"].is_object());
    BOOST_CHECK_NO_THROW(jitem4["object"]["2"]);
    BOOST_CHECK_EQUAL(jitem4["object"].object().size(), 1U);
    BOOST_CHECK(jitem4["object"]["2"].is_number());

    jitem2.append_array_item(jitem4);
    BOOST_CHECK_NO_THROW(jitem2[16]);
    BOOST_CHECK(jitem2[16].is_object());
    BOOST_CHECK_EQUAL(jitem2[16].object().size(), 12U);
    BOOST_REQUIRE_NO_THROW(jitem2[16]["bool"]);
    BOOST_CHECK_EQUAL(jitem2[16]["bool"].boolean(), true);
    BOOST_CHECK_NO_THROW(jitem2[16]["string"]);
    BOOST_CHECK(jitem2[16]["string"].is_string());
    BOOST_CHECK_EQUAL(jitem2[16]["string"].string(), "bar");
    BOOST_CHECK_NO_THROW(jitem2[16]["int"]);
    BOOST_CHECK(jitem2[16]["int"].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["int"].number(), -5);
    BOOST_CHECK_NO_THROW(jitem2[16]["unsigned"]);
    BOOST_CHECK(jitem2[16]["unsigned"].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["unsigned"].number(), 6);
    BOOST_CHECK_NO_THROW(jitem2[16]["long"]);
    BOOST_CHECK(jitem2[16]["long"].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["long"].number(), -7);
    BOOST_CHECK_NO_THROW(jitem2[16]["unsigned long"]);
    BOOST_CHECK(jitem2[16]["unsigned long"].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["unsigned long"].number(), 8);
    BOOST_CHECK_NO_THROW(jitem2[16]["float"]);
    BOOST_CHECK(jitem2[16]["float"].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["float"].number(), -9.5);
    BOOST_CHECK_NO_THROW(jitem2[16]["double"]);
    BOOST_CHECK(jitem2[16]["double"].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["double"].number(), -10.25);
    BOOST_CHECK_NO_THROW(jitem2[16]["null"]);
    BOOST_CHECK(jitem2[16]["null"].is_null());
    BOOST_CHECK_NO_THROW(jitem2[16]["array"]);
    BOOST_CHECK(jitem2[16]["array"].is_array());
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array"][0]);
    BOOST_CHECK(jitem2[16]["array"][0].is_boolean());
    BOOST_CHECK_EQUAL(jitem2[16]["array"][0].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array"][1]);
    BOOST_CHECK(jitem2[16]["array"][1].is_string());
    BOOST_CHECK_EQUAL(jitem2[16]["array"][1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array"][2]);
    BOOST_CHECK(jitem2[16]["array"][2].is_string());
    BOOST_CHECK_EQUAL(jitem2[16]["array"][2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array"][3]);
    BOOST_CHECK(jitem2[16]["array"][3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array"][4]);
    BOOST_CHECK(jitem2[16]["array"][4].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["array"][4].number(), 7.5);
    BOOST_CHECK_NO_THROW(jitem2[16]["array2"]);
    BOOST_CHECK(jitem2[16]["array2"].is_array());
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array2"][0]);
    BOOST_CHECK(jitem2[16]["array2"][0].is_boolean());
    BOOST_CHECK_EQUAL(jitem2[16]["array2"][0].boolean(), true);
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array2"][1]);
    BOOST_CHECK(jitem2[16]["array2"][1].is_string());
    BOOST_CHECK_EQUAL(jitem2[16]["array2"][1].string(), "foo");
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array2"][2]);
    BOOST_CHECK(jitem2[16]["array2"][2].is_string());
    BOOST_CHECK_EQUAL(jitem2[16]["array2"][2].string(), "foofoo");
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array2"][3]);
    BOOST_CHECK(jitem2[16]["array2"][3].is_null());
    BOOST_REQUIRE_NO_THROW(jitem2[16]["array2"][4]);
    BOOST_CHECK(jitem2[16]["array2"][4].is_number());
    BOOST_CHECK_EQUAL(jitem2[16]["array2"][4].number(), 7.5);
}

BOOST_AUTO_TEST_SUITE_END()
