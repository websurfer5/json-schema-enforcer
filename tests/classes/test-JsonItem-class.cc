// test-JsonItem-class.cc
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
#include "JsonItem.hh"

BOOST_AUTO_TEST_SUITE( JsonItem_class_test_suite )

BOOST_AUTO_TEST_CASE( test_JsonItem_class_1 )
{
    jsonschemaenforcer::JsonItem j1;
    jsonschemaenforcer::JsonItemList jlist1,
                               jlist2;
    jsonschemaenforcer::JsonItemMap jmap1,
                              jmap2;

    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Null);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_boolean("foo", false);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Boolean);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_boolean(true);
    jlist1.push_back(j1);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, true);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Boolean);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_key("foo");
    jlist2.push_back(j1);
    jmap1["foo"] = j1;
    jmap2["foo"] = j1;
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, true);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Boolean);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_null();
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Null);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_null("foofoo");
    jlist2.push_back(j1);
    jmap2["foofoo"] = j1;
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Null);
    BOOST_CHECK_EQUAL(j1.key, "foofoo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_number(5);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 5);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Number);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_number("foo", 20);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 20);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Number);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_string("bar");
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_String);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "bar");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_string("foo", "barbar");
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_String);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "barbar");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);

    j1.set_array(jlist1);
    BOOST_CHECK(j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK_EQUAL(j1.child_list.size(), 1U);
    BOOST_CHECK(j1.child_list == jlist1);
    BOOST_CHECK_EQUAL(j1.child_list.begin()->key, "");
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Array);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 1U);

    j1.set_array("foo", jlist2);
    BOOST_CHECK(j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK_EQUAL(j1.child_list.size(), 2U);
    BOOST_CHECK_EQUAL(j1.child_list.begin()->key, "");
    BOOST_CHECK_EQUAL(j1.child_list.rbegin()->key, "");
    BOOST_CHECK(j1.child_list != jlist2);
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Array);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 2U);

    j1.set_object(jmap1);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK_EQUAL(j1.child_map.size(), 1U);
    BOOST_CHECK(j1.child_map == jmap1);
    BOOST_CHECK_EQUAL(j1.child_map.cbegin()->first, "foo");
    BOOST_CHECK_EQUAL(j1.child_map.cbegin()->second.key, "foo");
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Object);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 1U);

    j1.set_object("foo", jmap2);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK_EQUAL(j1.child_map.size(), 2U);
    BOOST_CHECK(j1.child_map == jmap2);
    BOOST_CHECK_EQUAL(j1.child_map.cbegin()->first, "foo");
    BOOST_CHECK_EQUAL(j1.child_map.cbegin()->second.key, "foo");
    BOOST_CHECK_EQUAL(j1.child_map.crbegin()->first, "foofoo");
    BOOST_CHECK_EQUAL(j1.child_map.crbegin()->second.key, "foofoo");
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Object);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 2U);
    BOOST_CHECK_EQUAL(j1.get_array_size(), 0U);
}

BOOST_AUTO_TEST_CASE( test_JsonItem_class_2 )
{
    jsonschemaenforcer::JsonItem j1,
                           j2;

    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Null);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK(j1 == j2);
    BOOST_CHECK(j2 == j1);
    BOOST_CHECK(!(j1 != j2));
    BOOST_CHECK(!(j2 != j1));

    j2.bool_value = true;
    j2.num_value = 5;
    j2.type = jsonschemaenforcer::JsonItem::type_String;
    j2.key = "foo";
    j2.str_value = "bar";
    j2.child_list.push_back(j2);
    j2.child_map[j2.key] = j2;
    BOOST_CHECK(!(j1 == j2));
    BOOST_CHECK(!(j2 == j1));
    BOOST_CHECK(j1 != j2);
    BOOST_CHECK(j2 != j1);
    BOOST_CHECK_EQUAL(j2.get_properties_count(), 0U);

    jsonschemaenforcer::JsonItem j3(j2);
    BOOST_CHECK(j1 != j2);
    BOOST_CHECK(j1 != j3);
    BOOST_CHECK(j2 != j1);
    BOOST_CHECK(j2 == j3);
    BOOST_CHECK(j3 != j1);
    BOOST_CHECK(j3 == j2);
    BOOST_CHECK_EQUAL(j3.get_properties_count(), 0U);

    j3.clear();
    BOOST_CHECK(j1 != j2);
    BOOST_CHECK(j1 == j3);
    BOOST_CHECK(j2 != j1);
    BOOST_CHECK(j2 != j3);
    BOOST_CHECK(j3 == j1);
    BOOST_CHECK(j3 != j2);

    j3 = j2;
    BOOST_CHECK(j1 != j2);
    BOOST_CHECK(j1 != j3);
    BOOST_CHECK(j2 != j1);
    BOOST_CHECK(j2 == j3);
    BOOST_CHECK(j3 != j1);
    BOOST_CHECK(j3 == j2);
}

BOOST_AUTO_TEST_CASE( test_JsonItem_class_3 )
{
    jsonschemaenforcer::JsonItem j1,
                           j2;

    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(!j1.is_boolean());
    BOOST_CHECK(j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, false);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Null);
    BOOST_CHECK_EQUAL(j1.key, "");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);
    BOOST_CHECK(j1 == j2);
    BOOST_CHECK(j2 == j1);
    BOOST_CHECK(!(j1 != j2));
    BOOST_CHECK(!(j2 != j1));


    j1.set_boolean("foo", true);
    BOOST_CHECK(!j1.is_array());
    BOOST_CHECK(j1.is_boolean());
    BOOST_CHECK(!j1.is_null());
    BOOST_CHECK(!j1.is_number());
    BOOST_CHECK(!j1.is_object());
    BOOST_CHECK(!j1.is_string());
    BOOST_CHECK_EQUAL(j1.bool_value, true);
    BOOST_CHECK_EQUAL(j1.num_value, 0);
    BOOST_CHECK(j1.child_list.empty());
    BOOST_CHECK(j1.child_map.empty());
    BOOST_CHECK(j1.type == jsonschemaenforcer::JsonItem::type_Boolean);
    BOOST_CHECK_EQUAL(j1.key, "foo");
    BOOST_CHECK_EQUAL(j1.str_value, "");
    BOOST_CHECK_EQUAL(j1.get_properties_count(), 0U);

    j2.set_key("bar");
    j2.append_array_item(j1);
    BOOST_CHECK(j2.is_array());
    BOOST_CHECK(!j2.is_boolean());
    BOOST_CHECK(!j2.is_null());
    BOOST_CHECK(!j2.is_number());
    BOOST_CHECK(!j2.is_object());
    BOOST_CHECK(!j2.is_string());
    BOOST_CHECK_EQUAL(j2.bool_value, false);
    BOOST_CHECK_EQUAL(j2.num_value, 0);
    BOOST_CHECK_EQUAL(j2.child_list.size(), 1U);
    BOOST_CHECK(j2.child_list.begin()->is_boolean());
    BOOST_CHECK(j2.child_map.empty());
    BOOST_CHECK(j2.type == jsonschemaenforcer::JsonItem::type_Array);
    BOOST_CHECK_EQUAL(j2.key, "bar");
    BOOST_CHECK_EQUAL(j2.str_value, "");
    BOOST_CHECK_EQUAL(j2.get_properties_count(), 0U);
    BOOST_CHECK(j2.child_list.begin()->get_key().empty());
    BOOST_CHECK(j2.child_list.begin()->is_boolean());
    BOOST_CHECK_EQUAL(j2.child_list.begin()->bool_value, true);
}

BOOST_AUTO_TEST_SUITE_END()
