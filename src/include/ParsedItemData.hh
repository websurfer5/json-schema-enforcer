// ParsedItemData.hh
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

#ifndef __JSONSCHEMAENFORCER_PARSED_ITEM_DATA_HH
#define __JSONSCHEMAENFORCER_PARSED_ITEM_DATA_HH

namespace jsonschemaenforcer
{
    class ParsedItemData;
}

#include "config.h"
#include "FormatType.hh"
#include "ItemType.hh"
#include "JsonItem.hh"
#include "SchemaItem.hh"
#include "stddefs.hh"
#include <string>

namespace jsonschemaenforcer
{
    class ParsedItemData
    {
    public:
        ParsedItemData();
        ParsedItemData(const ParsedItemData& idata);
        ~ParsedItemData();

        ParsedItemData& operator =(const ParsedItemData& idata);
        ParsedItemData& operator |=(const ParsedItemData& idata);
        inline ParsedItemData operator |(const ParsedItemData& idata)
        {
            return ParsedItemData(*this).operator |=(idata);
        }
        bool operator ==(const ParsedItemData& idata) const;
        bool operator !=(const ParsedItemData& idata) const { return !this->operator ==(idata); }

        inline void add_item_type(const ItemType& _type) { type_set.insert(_type); };
        bool add_item_examples(const JsonItem &jitem);
        void clear();
        bool empty() const;
        void set_item_type(const ItemType& _type);

        //
        // has item type functions
        //

#       define DEF_FLAG(fname, str_name) \
        inline bool has_##fname##_type() const { return (type_set.find(ItemType::type_##fname) != type_set.end()); };

#       include "ItemType-vars.hh"
#       undef DEF_FLAG

        //
        // set value functions
        //

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        inline void func_set(vtype _##vname) \
        {                                           \
            vname = _##vname;                       \
            flag_name = true;                       \
        };                                          \
        inline vtype func_get() const { return vname; };

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        inline void func_set(const objtype& _##vname) \
        {                                           \
            vname = _##vname;                       \
            flag_name = true;                       \
        };                                          \
        inline const objtype& func_get() const { return vname; };

#       define DEF_FLAG(fname, value, func_set, func_clear) \
        inline void func_set()         { fname = true; };   \
        inline void func_set(bool b)   { fname = b; };      \
        inline void func_clear()       { fname = false; };  \
        inline bool is_##fname() const { return fname; };

#       include "ParsedItemData-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG

        //
        // define variables
        //

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
            vtype vname; \
            bool flag_name;

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            objtype vname; \
            bool flag_name;

#       define DEF_FLAG(fname, value, func_set, func_clear) \
            bool fname;

#       include "ParsedItemData-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG
    };
}

#endif  // __JSONSCHEMAENFORCER_PARSED_ITEM_DATA_HH
