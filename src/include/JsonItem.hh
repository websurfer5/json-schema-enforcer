// JsonItem.hh
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

#ifndef __JSONSCHEMAENFORCER_JSON_ITEM_HH
#define __JSONSCHEMAENFORCER_JSON_ITEM_HH

#include "config.h"
#include <list>
#include <map>
#include <string>

namespace jsonschemaenforcer
{
    class JsonItem;
    typedef std::list<JsonItem> JsonItemList;
    typedef std::map<std::string, JsonItem> JsonItemMap;

    class JsonItem
    {
    public:
        typedef enum
        {
            type_Array      = 0,
            type_Boolean    = 1,
            type_Null       = 2,
            type_Number     = 3,
            type_Object     = 4,
            type_String     = 5,
            type_last_enum  = 6
        } JsonType;

        JsonItem();
        JsonItem(const JsonItem& jitem);

        JsonItem& operator =(const JsonItem& jitem);
        bool operator ==(const JsonItem& jitem) const;
        inline bool operator !=(const JsonItem& jitem) const { return !(this->operator ==(jitem)); };
        bool operator <(const JsonItem& jitem) const;

        bool append_array(const JsonItem& jitem);
        void append_array_item(const JsonItem& jitem);
        void clear();
        void clear_item_values();
        void clear_values();
        inline const std::string& get_key() const { return key; };
        inline const size_t get_array_size() const { return (is_array() ? child_list.size() : 0); };
        inline size_t get_properties_count() const { return (is_object() ? child_map.size() : 0); };
        inline bool is_array() const { return (type == type_Array); };
        inline bool is_boolean() const { return (type == type_Boolean); };
        inline bool is_null() const { return (type == type_Null); };
        inline bool is_number() const { return (type == type_Number); };
        inline bool is_object() const { return (type == type_Object); };
        inline bool is_string() const { return (type == type_String); };
        inline void set_array(const JsonItemList& jitem_list)
        {
            set_array("", jitem_list);
        }
        void set_array(const std::string& _key, const JsonItemList& jitem_list);
        inline void set_boolean(bool b)
        {
            set_boolean("", b);
        };
        inline void set_boolean(const std::string& _key, bool b)
        {
            clear_values();
            bool_value = b;
            type = type_Boolean;
            set_key(_key);
        };
        inline void set_key(const std::string& _key)
        {
            key = _key;
        };
        inline void set_null()
        {
            clear();
        }
        inline void set_null(const std::string& _key)
        {
            clear_values();
            set_key(_key);
        }
        inline void set_number(double num)
        {
            set_number("", num);
        }
        inline void set_number(const std::string& _key, double num)
        {
            clear_values();
            num_value = num;
            type = type_Number;
            set_key(_key);
        };
        inline void set_object(JsonItemMap& jitem_map)
        {
            set_object("", jitem_map);
        }
        inline void set_object(const std::string& _key, JsonItemMap& jitem_map)
        {
            clear_values();
            child_map = jitem_map;
            type = type_Object;
            set_key(_key);
        };
        inline void set_string(const std::string& str)
        {
            set_string("", str);
        };
        inline void set_string(const std::string& _key, const std::string& str)
        {
            clear_values();
            str_value = str;
            type = type_String;
            set_key(_key);
        };

        bool bool_value;
        double num_value;
        JsonItemList child_list;
        JsonItemMap child_map;
        JsonType type;
        std::string key,
                    str_value;
    };
}
#endif  // __JSONSCHEMAENFORCER_JSON_ITEM_HH
