// JsonItem.cc
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

#include "config.h"
#include "JsonItem.hh"

namespace jsonschemaenforcer
{
    JsonItem::JsonItem()
    {
        clear();
    }

    JsonItem::JsonItem(const JsonItem& jitem)
    {
        this->operator =(jitem);
    }

    JsonItem& JsonItem::operator =(const JsonItem& jitem)
    {
        bool_value = jitem.bool_value;
        child_list = jitem.child_list;
        child_map = jitem.child_map;
        key = jitem.key;
        num_value = jitem.num_value;
        str_value = jitem.str_value;
        type = jitem.type;
        return *this;
    }

    bool JsonItem::operator ==(const JsonItem& jitem) const
    {
        return (bool_value == jitem.bool_value
                && num_value == jitem.num_value
                && child_list == jitem.child_list
                && child_map == jitem.child_map
                && type == jitem.type
                && key == jitem.key
                && str_value == jitem.str_value);
    }

    bool JsonItem::operator <(const JsonItem& jitem) const
    {
        if (type < jitem.type)
            return true;
        else if (type > jitem.type)
            return false;

        switch (jitem.type)
        {
            case JsonItem::type_Array :
                return (child_list < jitem.child_list);

            case JsonItem::type_Boolean :
                return (bool_value < jitem.bool_value);

            case JsonItem::type_Null :
                return false;

            case JsonItem::type_Number :
                return (num_value < jitem.num_value);

            case JsonItem::type_Object :
                return (child_map < jitem.child_map);

            case JsonItem::type_String :
                return (str_value < jitem.str_value);

            default:
                break;
        }
        return false;
    }

    void JsonItem::clear()
    {
        type = type_Null;
        clear_values();
    }

    void JsonItem::clear_values()
    {
        key.clear();
        clear_item_values();
    }

    void JsonItem::clear_item_values()
    {
        bool_value = false;
        child_list.clear();
        child_map.clear();
        num_value = 0;
        str_value.clear();
    }

    void JsonItem::set_array(const std::string& _key, const JsonItemList& jitem_list)
    {
        JsonItemList::const_iterator c_it;

        clear_values();

        for (c_it = jitem_list.cbegin(); c_it != jitem_list.cend(); c_it++)
        {
            child_list.push_back(*c_it);
            child_list.rbegin()->set_key("");
        }

        type = type_Array;
        set_key(_key);
    }

    bool JsonItem::append_array(const JsonItem& jitem)
    {
        bool success = false;

        if (is_null())
            set_array(jitem.child_list);
        else if (is_array())
            child_list.insert(child_list.end(), jitem.child_list.begin(), jitem.child_list.end());

        return success;
    }

    void JsonItem::append_array_item(const JsonItem& jitem)
    {
        if (!is_array())
        {
            clear_item_values();
            type = type_Array;
        }

        child_list.push_back(jitem);
        child_list.rbegin()->set_key("");
    }
}
