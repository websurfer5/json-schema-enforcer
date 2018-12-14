// SchemaItem.hh
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

#ifndef __JSONSCHEMAENFORCER_SCHEMA_ITEM_HH
#define __JSONSCHEMAENFORCER_SCHEMA_ITEM_HH

namespace jsonschemaenforcer
{
    class ParsedItemData;
}

#include "config.h"
#include "FormatType.hh"
#include "ItemType.hh"
#include "JsonItem.hh"
#include "stddefs.hh"
#include <iostream>
#include <list>
#include <string>

namespace jsonschemaenforcer
{
    class SchemaData;
    class SchemaItem;
    typedef std::list<SchemaItem> SchemaItemList;

    class SchemaItem
    {
    public:

        SchemaItem();
        SchemaItem(const SchemaItem& sitem);
        ~SchemaItem();

        SchemaItem& operator =(const SchemaItem& sitem);
        bool operator ==(const SchemaItem& sitem) const;
        inline bool operator !=(const SchemaItem& sitem) const { return !(this->operator ==(sitem)); };

        inline void add_item_type(const ItemType& _type) { type_set.insert(_type); };
        void clear();
        bool define_item(const std::string& _key, const ParsedItemData& idata);
        bool define_dependency_array(const std::string& _key, const StdStringList& s_list);
        bool empty() const;
        inline std::string emit_parser(SchemaData& sd,
                                       const std::string& start_state) const
        {
            return emit_parser(sd, start_state, "");
        };
        std::string emit_integer_parser_rules(SchemaData& sd,
                                              const std::string& start_state,
                                              const std::string& key_validation_state) const;
        std::string emit_number_parser_rules(SchemaData& sd,
                                                         const std::string& start_state,
                                                         const std::string& key_validation_state) const;
        std::string emit_string_parser_rules(SchemaData& sd,
                                             const std::string& start_state,
                                             const std::string& key_validation_state) const;
        std::string emit_object_parser_rules(SchemaData& sd,
                                             const std::string& start_state,
                                             const std::string& key_validation_state) const;
        std::string emit_array_parser_rules(SchemaData& sd,
                                            const std::string& start_state,
                                            const std::string& key_validation_state) const;
        // std::string emit_boolean_parser_rules(SchemaData& sd, const std::string& start_state) const;
        // std::string emit_null_parser_rules(SchemaData& sd, const std::string& start_state) const;

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        void func_set(vtype _##vname); \
        inline vtype func_get() const { return vname; }; \
        inline bool has_##vname() const { return flag_name; };

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        void func_set(const objtype& _##vname); \
        inline const objtype& func_get() const { return vname; }; \
        inline bool has_##vname() const { return flag_name; };

#       define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        void func_set(const objtype& obj);    \
        const objtype& func_get() const; \
        inline bool has_##vname() const { return flag_name; };

#       define DEF_FLAG(fname, value, func_set, func_clear) \
        inline void func_set()         { fname = true; };   \
        inline void func_set(bool b)   { fname = b; };      \
        inline void func_clear()       { fname = false; };  \
        inline bool is_##fname() const { return fname; };

#       include "SchemaItem-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_OBJ_PTR
#       undef DEF_FLAG

        //
        // has item type functions
        //

#       define DEF_FLAG(fname, str_name) \
        inline bool has_##fname##_type() const { return (type_set.find(ItemType::type_##fname) != type_set.end()); };

#       include "ItemType-vars.hh"
#       undef DEF_FLAG

    protected:
        //
        // The set_data templated function ensures that a real
        // only gets assigned to an integer variable if the real
        // value is an integer.
        //

        template <class T, class U>
        bool set_data(bool& b_var1, bool b_var2, T& var1, const U& var2,
                      const std::string& prop_type, const std::string& var_name)
        {
            bool error = false;

            if (b_var2)
            {
                if (var2 != (T) var2)
                {
                    b_var1 = false;
                    error = true;
                    std::cerr << __FUNCTION__ << "(): \"" << var_name << "\" property value is not "
                              << prop_type << ": " << var2 << std::endl;
                }
                else
                {
                    b_var1 = true;
                    var1 = (T) var2;
                }
            }
            else
                b_var1 = false;

            return !error;
        }

        std::string emit_parser(SchemaData& sd,
                                const std::string& start_state,
                                const std::string& key_validation_state) const;
        void emit_array_rule(SchemaData& sd,
                             std::string& rule_str,
                             bool& first,
                             const SchemaItem& item,
                             const std::string& array_state,
                             const std::string& item_tag) const;
        void emit_default_rules(SchemaData& sd) const;
        void emit_object_rule(SchemaData& sd,
                              std::string& rule_str,
                              bool& first,
                              const SchemaItem& item,
                              const std::string& object_state,
                              const std::string& prop_names_state) const;
        bool is_vanilla() const;
        bool set_array_data(const ParsedItemData& idata);
        bool set_integer_data(const ParsedItemData& idata);
        bool set_number_data(const ParsedItemData& idata);
        bool set_object_data(const ParsedItemData& idata);
        bool set_string_data(const ParsedItemData& idata);

    public:
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
            vtype vname; \
            bool flag_name;

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            objtype vname; \
            bool flag_name;

#       define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            objtype *vname; \
            bool flag_name;

#       define DEF_FLAG(fname, value, func_set, func_clear) \
            bool fname;

#       include "SchemaItem-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_OBJ_PTR
#       undef DEF_FLAG
    };
}

#endif  // __JSONSCHEMAENFORCER_SCHEMA_ITEM_HH
