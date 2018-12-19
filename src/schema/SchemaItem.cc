// SchemaItem.cc
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
#include "ParsedItemData.hh"
#include "SchemaData.hh"
#include "SchemaItem.hh"
#include <iostream>
#include <string>
#include <typeinfo>

namespace jsonschemaenforcer
{
    const static std::string empty_str("");

#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get)
    /*  no macro body */

#   define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    /*  no macro body */

#   define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    static const objtype _empty_##vname;

#   define DEF_FLAG(fname, value, func_set, func_clear)
    /* no macro bosy */

#   include "SchemaItem-vars.hh"
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG

#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get)
    /*  no macro body */

#   define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    /*  no macro body */

#   define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        vname = NULL;

#   define DEF_FLAG(fname, value, func_set, func_clear)
    /* no macro body */

    SchemaItem::SchemaItem()
    {
#       include "SchemaItem-vars.hh"
        clear();
    }

    SchemaItem::SchemaItem(const SchemaItem& sitem)
    {
#       include "SchemaItem-vars.hh"
        this->operator =(sitem);
    }
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG


#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get)
    /*  no macro body */

#   define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    /*  no macro body */

#   define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        if (vname)         \
            delete vname;
#   define DEF_FLAG(fname, value, func_set, func_clear)
    /*  no macro body */

    SchemaItem::~SchemaItem()
    {
#       include "SchemaItem-vars.hh"
    }
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG

#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        vname = sitem.vname; \
        flag_name = sitem.flag_name;

#   define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        vname = sitem.vname; \
        flag_name = sitem.flag_name;

#   define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
        if (vname)                              \
            delete vname;                       \
                                                \
        if (sitem.vname)                        \
            vname = new objtype(*sitem.vname);  \
        else                                    \
            vname = NULL;                       \
                                                \
        flag_name = sitem.flag_name;

#   define DEF_FLAG(fname, value, func_set, func_clear) \
        fname = sitem.fname;

    SchemaItem& SchemaItem::operator =(const SchemaItem& sitem)
    {
        if (this != &sitem)
        {
#           include "SchemaItem-vars.hh"
        }
        return *this;
    }
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG

    bool SchemaItem::operator ==(const SchemaItem& sitem) const
    {
#       define DEF_FLAG(fname, value, func_set, func_clear) \
                && fname == sitem.fname

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
                && vname == sitem.vname \
                && flag_name == sitem.flag_name

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
                && vname == sitem.vname \
                && flag_name == sitem.flag_name

#       define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
                && ((vname && sitem.vname)          \
                        ? (*vname == *sitem.vname)  \
                        : (vname == sitem.vname))   \
                && flag_name == sitem.flag_name

        return (true
#               include "SchemaItem-vars.hh"
                );

#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_OBJ_PTR
#       undef DEF_FLAG
    }

    void SchemaItem::clear()
    {
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
            vname = value; \
            flag_name = flag_value;

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            vname.initfunc(); \
            flag_name = flag_value;

#       define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            if (vname)          \
                delete vname;   \
                                \
            vname = NULL;       \
            flag_name = flag_value;

#       define DEF_FLAG(fname, value, func_set, func_clear) \
            fname = value;

#       include "SchemaItem-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_OBJ_PTR
#       undef DEF_FLAG
    }

    bool SchemaItem::empty() const
    {
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
                || flag_name

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
                || flag_name

#       define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
                || flag_name

#       define DEF_FLAG(fname, value, func_set, func_clear) \
                || fname

        return !(false
#               include "SchemaItem-vars.hh"
               );

#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_OBJ_PTR
#       undef DEF_FLAG
    }

    bool SchemaItem::define_dependency_array(const std::string& _key, const StdStringList& s_list)
    {
        clear();
        set_key(_key);
        set_dependency_array(s_list);
        type_set.clear();
        type_set.insert(ItemType::type_DependencyArray);
        return true;
    }

    bool SchemaItem::define_item(const std::string& _key, const ParsedItemData& idata)
    {
        bool success = true;
        ItemTypeSet::const_iterator c_it;

        clear();
        set_key(_key);

        type_set.clear();
        type_set.insert(idata.type_set.begin(), idata.type_set.end());

        if (idata.b_has_ref)
            type_set.insert(ItemType::type_Ref);

        if (idata.b_has_description)
            set_description(idata.get_item_description());

        if (idata.b_has_one_of)
            set_bool_one_of(idata.get_item_one_of());

        if (idata.b_has_any_of)
            set_bool_any_of(idata.get_item_any_of());

        if (idata.b_has_all_of)
            set_bool_all_of(idata.get_item_all_of());

        if (idata.b_has_not_schema)
            set_bool_not_schema(idata.get_item_not_schema());

        if (idata.b_has_if_schema)
            set_bool_if_schema(idata.get_item_if_schema());

        if (idata.b_has_else_schema)
            set_bool_else_schema(idata.get_item_else_schema());

        if (idata.b_has_then_schema)
            set_bool_then_schema(idata.get_item_then_schema());

        if (idata.b_has_enum)
            set_enum_list(idata.get_item_enum());

        if (idata.b_has_definitions)
            set_definitions(idata.get_item_definitions());

        if (idata.b_has_format_type)
            set_format_type(idata.get_item_format_type());

        if (idata.b_has_default_value)
            set_json_default_value(idata.get_item_default_value());

        if (idata.b_has_read_only)
            set_bool_read_only(idata.get_item_read_only());

        if (idata.b_has_write_only)
            set_bool_write_only(idata.get_item_write_only());

        if (idata.b_has_examples)
            set_json_examples(idata.get_item_examples());


        for (c_it = type_set.begin(); success && c_it != type_set.end(); c_it++)
        {
            switch (*c_it)
            {
                case ItemType::type_Null:
                    success = true;
                    break;

                case ItemType::type_Boolean:
                    success = true;
                    break;

                case ItemType::type_Object:
                    success &= set_object_data(idata);
                    break;
                
                case ItemType::type_Array:
                    success &= set_array_data(idata);
                    break;
                
                case ItemType::type_Number:
                    success &= set_number_data(idata);
                    break;

                case ItemType::type_Integer :
                    success &= set_integer_data(idata);
                    break;

                case ItemType::type_Ref:
                    set_ref(idata.ref);
                    success = true;
                    break;
                
                case ItemType::type_String:
                    success &= set_string_data(idata);
                    break;
                
                case ItemType::type_Unknown:
                    if (b_has_enum
                        || b_has_format_type
                        || b_has_json_default_value
                        || b_has_bool_all_of)
                    {
                        type_set.insert(ItemType::type_Misc);
                        success = true;
                    }

                    break;
        
                default:
                    break;
            }
        }

        return success;
    }

    bool SchemaItem::set_array_data(const ParsedItemData& idata)
    {
        b_has_array_additional_items = idata.b_has_additional_items;
        b_has_array_contains = idata.b_has_contains;
        b_has_array_max_items = idata.b_has_max_items;
        b_has_array_min_items = idata.b_has_min_items;
        b_has_array_properties = idata.b_has_array_properties;
        b_has_array_unique = idata.b_has_unique;

        if (p_array_additional_items)
            delete p_array_additional_items;
        
        if (idata.b_has_additional_items)
        {
            p_array_additional_items = new SchemaItem(idata.additional_items);
            p_array_additional_items->set_additional_item();
        }
        else
            p_array_additional_items = NULL;

        if (idata.b_has_array_properties) array_properties = idata.array_properties;
        if (idata.b_has_contains) array_contains = idata.contains;
        if (idata.b_has_max_items) array_n_max_items = idata.max_items;
        if (idata.b_has_min_items) array_n_min_items = idata.min_items;
        if (idata.b_has_unique) array_b_unique = idata.b_unique;

        return true;
    }

    bool SchemaItem::set_integer_data(const ParsedItemData& idata)
    {
        bool error = false;

        error |= !set_data(b_has_int_exclusive_maximum, idata.b_has_exclusive_maximum, int_exclusive_maximum, idata.exclusive_maximum, "integer", "exclusiveMaximum");
        error |= !set_data(b_has_int_exclusive_minimum, idata.b_has_exclusive_minimum, int_exclusive_minimum, idata.exclusive_minimum, "integer", "exclusiveMinimum");
        error |= !set_data(b_has_int_maximum, idata.b_has_maximum, int_maximum, idata.maximum, "integer", "maximum");
        error |= !set_data(b_has_int_minimum, idata.b_has_minimum, int_minimum, idata.minimum, "integer", "minimum");
        error |= !set_data(b_has_int_multiple_of, idata.b_has_multiple_of, int_multiple_of, idata.multiple_of, "integer", "multipleOf");

        return !error;
    }

    bool SchemaItem::set_number_data(const ParsedItemData& idata)
    {
        bool error = false;

        error |= !set_data(b_has_num_exclusive_maximum, idata.b_has_exclusive_maximum, num_exclusive_maximum, idata.exclusive_maximum, "number", "exclusiveMaximum");
        error |= !set_data(b_has_num_exclusive_minimum, idata.b_has_exclusive_minimum, num_exclusive_minimum, idata.exclusive_minimum, "number", "exclusiveMinimum");
        error |= !set_data(b_has_num_maximum, idata.b_has_maximum, num_maximum, idata.maximum, "number", "maximum");
        error |= !set_data(b_has_num_minimum, idata.b_has_minimum, num_minimum, idata.minimum, "number", "minimum");
        error |= !set_data(b_has_num_multiple_of, idata.b_has_multiple_of, num_multiple_of, idata.multiple_of, "number", "multipleOf");

        return !error;
    }

    bool SchemaItem::set_object_data(const ParsedItemData& idata)
    {
        b_has_object_max_properties = idata.b_has_max_properties;
        b_has_object_min_properties = idata.b_has_min_properties;
        b_has_object_required = idata.b_has_required;
        b_has_object_properties = idata.b_has_properties;
        b_has_object_pattern_properties = idata.b_has_pattern_properties;
        b_has_object_dependencies = idata.b_has_dependencies;
        b_has_object_can_have_additional_properties = idata.b_has_can_have_additional_properties;

        if (p_object_additional_properties)
            delete p_object_additional_properties;
        
        if (idata.b_has_additional_properties)
            p_object_additional_properties = new SchemaItem(idata.additional_properties);
        else
            p_object_additional_properties = NULL;

        b_has_object_additional_properties = idata.b_has_additional_properties;

        if (p_object_property_names)
            delete p_object_property_names;
        
        if (idata.b_has_property_names)
            p_object_property_names = new SchemaItem(idata.property_names);
        else
            p_object_property_names = NULL;

        b_has_object_property_names = idata.b_has_property_names;

        if (b_has_object_can_have_additional_properties) b_object_can_have_additional_properties = idata.b_can_have_additional_properties;
        if (b_has_object_max_properties) object_n_max_properties = idata.max_properties;
        if (b_has_object_min_properties) object_n_min_properties = idata.min_properties;
        if (b_has_object_required) object_required = idata.required;
        if (b_has_object_properties) object_properties = idata.properties;
        if (b_has_object_pattern_properties) object_pattern_properties = idata.pattern_properties;
        if (b_has_object_dependencies) object_dependencies = idata.dependencies;

        return true;
    }

    bool SchemaItem::set_string_data(const ParsedItemData& idata)
    {
        b_has_str_content_encoding = idata.b_has_content_encoding;
        b_has_str_content_media_type = idata.b_has_content_media_type;
        b_has_str_n_max_length = idata.b_has_max_length;
        b_has_str_n_min_length = idata.b_has_min_length;
        b_has_str_pattern = idata.b_has_pattern;

        if (idata.b_has_content_encoding) str_content_encoding = idata.content_encoding;
        if (idata.b_has_content_media_type) str_content_media_type = idata.content_media_type;
        if (idata.b_has_max_length) str_n_max_length = idata.max_length;
        if (idata.b_has_min_length) str_n_min_length = idata.min_length;
        if (idata.b_has_pattern) str_pattern = idata.pattern;

        return true;
    }

#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get)
    /*  no macro body */

#   define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    /*  no macro body */

#   define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    const objtype& SchemaItem::func_get() const     \
    {                                               \
        std::cerr << "entering " << __FUNCTION__ << " " << this << std::endl;   \
        if (vname)                                  \
            return *vname;                          \
        else                                        \
            return _empty_##vname;                   \
    }

#   define DEF_FLAG(fname, value, func_set, func_clear)
    /* no macro bosy */

#   include "SchemaItem-vars.hh"
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG

#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
    void SchemaItem::func_set(vtype _##vname) \
    {                                           \
        if (typeid(*this) == typeid(_##vname))  \
            return;                             \
                                                \
        vname = _##vname;                       \
        flag_name = true;                       \
    };                                          \

#   define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    void SchemaItem::func_set(const objtype& _##vname) \
    {                                           \
        if (typeid(*this) == typeid(_##vname))  \
            return;                             \
                                                \
        vname = _##vname;                       \
        flag_name = true;                       \
    };                                          \

#   define DEF_OBJ_PTR(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
    void SchemaItem::func_set(const objtype& obj)    \
    {                                           \
        if (typeid(*this) == typeid(obj) && this == &obj)       \
            return;                             \
                                                \
        if (vname)                              \
            delete vname;                       \
                                                \
        vname = new objtype(obj);               \
        flag_name = true;                       \
    }                                           \

#   define DEF_FLAG(fname, value, func_set, func_clear)
    /* empty macro body */

#   include "SchemaItem-vars.hh"
#   undef DEF_VAR
#   undef DEF_OBJ
#   undef DEF_OBJ_PTR
#   undef DEF_FLAG


    std::string SchemaItem::emit_parser(SchemaData& sd,
                                        const std::string& start_state,
                                        const std::string& key_validation_state) const
    {
        ItemTypeSet::const_iterator c_it;
        std::string rule_tag;

        if (!key_validation_state.empty())
            std::cout << "\"" << get_key() << "\"" << " has key validation rules: \"" << key_validation_state << "\"" << std::endl;

        for (c_it = type_set.cbegin(); c_it != type_set.cend(); c_it++)
            switch (*c_it)
            {
                case ItemType::type_Array:
                    rule_tag = emit_array_parser_rules(sd,
                                                       start_state,
                                                       key_validation_state.empty()
                                                           ? "PARSE_ARRAY_KEY"
                                                           : key_validation_state);
                    break;

                case ItemType::type_Integer:
                    rule_tag = emit_integer_parser_rules(sd,
                                                         start_state,
                                                         key_validation_state.empty()
                                                            ? "PARSE_ITEM_KEY"
                                                            : key_validation_state);
                    break;

                case ItemType::type_Number:
                    rule_tag = emit_number_parser_rules(sd,
                                                        start_state,
                                                        key_validation_state.empty()
                                                            ? "PARSE_ITEM_KEY"
                                                            : key_validation_state);
                    break;

                case ItemType::type_Object:
                    rule_tag = emit_object_parser_rules(sd,
                                                        start_state,
                                                        key_validation_state.empty()
                                                            ? "PARSE_OBJECT_KEY"
                                                            : key_validation_state);
                    break;

                case ItemType::type_String:
                    rule_tag = emit_string_parser_rules(sd,
                                                        start_state,
                                                        key_validation_state.empty()
                                                            ? "PARSE_ITEM_KEY"
                                                            : key_validation_state);
                    break;

                default:
                    rule_tag = "";
                    break;
            }

        return rule_tag;
    }

    void SchemaItem::emit_default_rules(SchemaData& sd) const
    {
        std::string func_name;

        sd.add_token("COMMA",
                     "",
                     false,
                     "\",\"",
                     "",
                     "ITEM_ARRAY",
                     "",
                     false);        
        sd.add_token("RIGHT_BRACKET",
                     "",
                     false,
                     "\"]\"",
                     "",
                     "ITEM_ARRAY",
                     "",
                     true);        
        sd.add_lexer_rule("[[:space:]]", "ITEM_ARRAY", "", false, "");
        sd.add_lexer_rule(".", "ITEM_ARRAY", "ITEM_VALUE", false, "unput(*yytext);\n");
        sd.add_parser_rule("array",
                           "    empty_array\n"
                           "        {\n"
                           "            $$.clear();\n"
                           "        }\n"
                           "    | LEFT_BRACKET array_items RIGHT_BRACKET\n"
                           "        {\n"
                           "            $$.set_array($2);\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("array", sd.get_namespace() + "::JsonItem", true);
        sd.add_parser_rule("array_items",
                           "    array_item\n"
                           "        {\n"
                           "            $$.clear();\n"
                           "            $$.push_back($1);\n"
                           "        }\n"
                           "    | array_items COMMA array_item\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "            $$.push_back($3);\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("array_items", sd.get_namespace() + "::JsonItemVector", true);
        sd.add_parser_rule("array_item",
                           "    boolean\n"
                           "        {\n"
                           "            $$.set_boolean($1);\n"
                           "        }\n"
                           "    | number\n"
                           "        {\n"
                           "            $$ = $$.set_number($1);\n"
                           "        }\n"
                           "    | array\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "        }\n"
                           "    | object\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "        }\n"
                           "    | NULL_TOKEN\n"
                           "        {\n"
                           "            $$ = $$.set_null();\n"
                           "        }\n"
                           "    | QUOTED_STRING\n"
                           "        {\n"
                           "            $$ = $$.set_string($1);\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("array_item", sd.get_namespace() + "::JsonItem", true);
        sd.add_parser_rule("boolean",
                           "    B_FALSE\n"
                           "        {\n"
                           "            $$ = false;\n"
                           "        }\n"
                           "    | B_TRUE\n"
                           "        {\n"
                           "            $$ = true;\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("boolean", "bool", false);
        sd.add_parser_rule("object_items",
                           "    object_item\n"
                           "        {\n"
                           "            $$.clear();\n"
                           "            $$[$1.get_key()] = $1;\n"
                           "        }\n"
                           "    | object_items COMMA object_item\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "            $$[$3.get_key()] = $3;\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("object_items", sd.get_namespace() + "::JsonItemMap", true);
        sd.add_parser_rule("object",
                           "    empty_object\n"
                           "        {\n"
                           "            $$.clear();\n"
                           "        }\n"
                           "    | LEFT_BRACE object_items RIGHT_BRACE\n"
                           "        {\n"
                           "            $$.set_object($2);\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("object", sd.get_namespace() + "::JsonItem", true);
        sd.add_parser_rule("object_item",
                           "    QUOTED_STRING COLON QUOTED_STRING\n"
                           "        {\n"
                           "            $$.set_string($1, $3);\n"
                           "        }\n"
                           "    | QUOTED_STRING COLON number\n"
                           "        {\n"
                           "            $$.set_number($1, $3);\n"
                           "        }\n"
                           "    | QUOTED_STRING COLON boolean\n"
                           "        {\n"
                           "            $$.set_boolean($1, $3);\n"
                           "        }\n"
                           "    | QUOTED_STRING COLON array\n"
                           "        {\n"
                           "            $$ = $3;\n"
                           "            $$.set_key($1);\n"
                           "        }\n"
                           "    | QUOTED_STRING COLON object\n"
                           "        {\n"
                           "            $$ = $3;\n"
                           "            $$.set_key($1);\n"
                           "        }\n"
                           "    | QUOTED_STRING COLON NULL_TOKEN\n"
                           "        {\n"
                           "            $$.set_null($1);\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("object_item", sd.get_namespace() + "::JsonItem", true);
        sd.add_lexer_rule("[[:space:]]", "INITIAL", "", false, "");
        sd.add_lexer_rule("[[:space:]]", "ITEM_VALUE", "", false, "");
        sd.add_lexer_rule("\"\\\"\"", "ITEM_VALUE", "QUOTED", true, "yyextra->quoted_str.clear();");
        sd.add_token("B_FALSE", "", false, "\"false\"", "", "ITEM_VALUE", "", true);
        sd.add_token("B_TRUE", "", false, "\"true\"", "", "ITEM_VALUE", "", true);
        sd.add_token("NULL_TOKEN", "", false, "\"null\"", "", "ITEM_VALUE", "", true);
        sd.add_token("LEFT_BRACKET", "", false, "\"[\"", "", "ITEM_VALUE", "ITEM_ARRAY", false);
        sd.add_token("LEFT_BRACE", "", false, "\"{\"", "", "ITEM_VALUE", "ITEM_OBJECT", false);
        sd.add_token("NEG_INTEGER", "long", false, "-[0-9]+", "std::stol(yytext)", "ITEM_VALUE", "", true);
        sd.add_token("NON_NEG_INTEGER", "long", false, "[+]?[0-9]+", "std::stol(yytext)", "ITEM_VALUE", "", true);
        sd.add_token("FLOATING_POINT", "double", false, "[-+]?[0-9]+\\.[0-9]*", "std::stod(yytext)", "ITEM_VALUE", "", true);
        sd.add_lexer_rule("\"\\\\\\\"\"", "QUOTED", "", false, "yyextra->quoted->str += '\\\"';\n");
        sd.add_lexer_rule("\"\\\\\\\\\"", "QUOTED", "", false, "yyextra->quoted->str += '\\\\';\n");
        sd.add_lexer_rule("\"\\\\/\"", "QUOTED", "", false, "yyextra->quoted->str += '/';\n");
        sd.add_lexer_rule("\"\\\\b\"", "QUOTED", "", false, "yyextra->quoted->str += '\\b';\n");
        sd.add_lexer_rule("\"\\\\f\"", "QUOTED", "", false, "yyextra->quoted->str += '\\f';\n");
        sd.add_lexer_rule("\"\\\\n\"", "QUOTED", "", false, "yyextra->quoted->str += '\\n';\n");
        sd.add_lexer_rule("\"\\\\r\"", "QUOTED", "", false, "yyextra->quoted->str += '\\r';\n");
        sd.add_lexer_rule("\"\\\\t\"", "QUOTED", "", false, "yyextra->quoted->str += '\\t';\n");
        sd.add_lexer_rule("\\\\u[0-9a-fA-F]{4}",
                          "QUOTED",
                          "",
                          false,
                          "uint16_t uval;\n"
                          "\n"
                          "uval = ((yytext[2] <= '9') ? (yytext[2] - '0') : ((yytext[2] & 0x07) + 9)) << 12;\n"
                          "uval += ((yytext[3] <= '9') ? (yytext[3] - '0') : ((yytext[3] & 0x07) + 9)) << 8;\n"
                          "uval += ((yytext[4] <= '9') ? (yytext[4] - '0') : ((yytext[4] & 0x07) + 9)) << 4;\n"
                          "uval += ((yytext[5] <= '9') ? (yytext[5] - '0') : ((yytext[5] & 0x07) + 9));\n"
                          "\n"
                          "if (uval < 0x0080)\n"
                          "    str += uval & 0xff;\n"
                          "else if (uval < 0x0800)\n"
                          "{\n"
                          "    str += (uval >> 6) | 0xc0;\n"
                          "    str += (uval & 0x3f) | 0x80;\n"
                          "}\n"
                          "else\n"
                          "{\n"
                          "    str += (uval >> 12) | 0xe0;\n"
                          "    str += ((uval >> 6) & 0x3f) | 0x80;\n"
                          "    str += (uval & 0x3f) | 0x80;\n"
                          "}\n");
        sd.add_token("QUOTED_STRING", "std::string", true, "string", true, "\"\\\"\"", "yyextra->quoted_str", "QUOTED", "", true);
        sd.add_lexer_rule("\"\\\"\"", "PARSE_ITEM_KEY", "QUOTED", false, "");
        sd.add_token("COLON",
                     "",
                     false,
                     "[[:space:]]*:[[space:]]*",
                     "",
                     "PARSE_ITEM_KEY",
                     "",
                     true);
        sd.add_token("COMMA",
                     "",
                     false,
                     "\",\"",
                     "",
                     "ITEM_OBJECT",
                     "",
                     false);        
        sd.add_token("RIGHT_BRACE",
                     "",
                     false,
                     "\"}\"",
                     "",
                     "ITEM_OBJECT",
                     "",
                     true);        
        sd.add_lexer_rule("[[:space:]]", "ITEM_OBJECT", "", false, "");
        sd.add_lexer_rule("\"\\\"\"",
                          "ITEM_OBJECT",
                          "ITEM_VALUE",
                          false,
                          "unput(*yytext);\n"
                          "yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);\n");
        sd.add_token("COLON", "", false, "\":\"", "", "ITEM_OBJECT", "ITEM_VALUE", false);
        sd.add_parser_rule("number",
                           "    FLOATING_POINT\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "        }\n"
                           "    | NEG_INTEGER\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "        }\n"
                           "    | NON_NEG_INTEGER\n"
                           "        {\n"
                           "            $$ = $1;\n"
                           "        }\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.set_rule_type("number", "double", false);
        sd.add_parser_rule("empty_array",
                           "    LEFT_BRACKET RIGHT_BRACKET\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.add_parser_rule("empty_object",
                           "    LEFT_BRACE RIGHT_BRACE\n"
                           "    ;\n"
                           "\n",
                           false);
        sd.add_lexer_rule("\"\\\"\"", "PARSE_ARRAY_KEY", "QUOTED", false, "");
        sd.add_lexer_rule("[[:space:]]*:[[:space:]]*\"[\"",
                          "PARSE_ARRAY_KEY",
                          "",
                          true,
                          "");
        sd.add_lexer_rule("\"\\\"\"", "PARSE_OBJECT_KEY", "QUOTED", false, "");
        sd.add_lexer_rule("[[:space:]]*:[[:space:]]*\"{\"",
                          "PARSE_OBJECT_KEY",
                          "",
                          true,
                          "");
    }

    void SchemaItem::emit_array_rule(SchemaData& sd,
                                     std::string& rule_str,
                                     bool& first,
                                     const SchemaItem& item,
                                     const std::string& array_state,
                                     const std::string& item_tag) const
    {
        std::string prop_tag;
        const std::string& array_item_tag = item.is_vanilla()
                                                ? item_tag
                                                : empty_str;

        prop_tag = item.emit_parser(sd, array_state);

        if (first)
        {
            rule_str = "    " + array_item_tag + " " + prop_tag + "\n";
            first = false;
        }
        else
            rule_str += "    | " + array_item_tag + " " + prop_tag + "\n";

        if (prop_tag == "QUOTED_STRING")
            rule_str += "        {\n"
                        "            JsonItem jitem;\n"
                        "            jitem.set_string(" + (array_item_tag.empty()
                                                            ? std::string("$1")
                                                            : std::string("$2")) +");\n"
                        "            $$.append_array_item(jitem);\n"
                        "        }\n";
        else
            rule_str += "        {\n"
                        "            $$ = " + (array_item_tag.empty()
                                                ? std::string("$1;\n")
                                                : std::string("$2;\n")) +
                        "        }\n";
    }

    std::string SchemaItem::emit_array_parser_rules(SchemaData& sd,
                                                    const std::string& start_state,
                                                    const std::string& key_validation_state) const
    {
        bool first;
        const SchemaItem *p_sitem;
        SchemaItemList::const_iterator c_it;
        std::string array_state,
                    array_tag,
                    format_rule_str,
                    format_state,
                    item_tag,
                    prop_tag,
                    rule_body,
                    rule_str,
                    rule_tag,
                    validation_rule_str;
        unsigned array_tag_number = 0;

        array_state = get_array_properties().empty()
                        ? "ITEM_ARRAY"
                        : sd.new_start_state();

        if (sd.is_initial_start_state(start_state))
        {
            sd.add_token("LEFT_BRACKET",
                         "",
                         false,
                         "\"[\"",
                         "",
                         "INITIAL",
                         array_state,
                         false);
            sd.add_token("RIGHT_BRACKET",
                         "",
                         false,
                         "\"]\"",
                         "",
                         "INITIAL",
                         "",
                         true);
        }

        if (!get_key().empty())
        {
            array_tag = sd.add_token(sd.new_token_tag(),
                                     "",
                                     false,
                                     "\"\\\"" + get_key() + "\\\"\"[[:space]]*:[[:space:]]*\"[\"",
                                     "",
                                     start_state,
                                     array_state,
                                     false,
                                     sd.unput_string_func_name() + "(yyscanner, yytext);\n"
                                     "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
        }

        emit_default_rules(sd);

        if (get_array_properties().empty())
        {
            sd.add_lexer_rule(".", array_state, "ITEM_VALUE", false, "unput(*yytext);\n");
            return "array";
        }

        item_tag = sd.add_token(sd.new_token_tag(),
                                "",
                                false,
                                ".",
                                "",
                                array_state,
                                "ITEM_VALUE",
                                false,
                                "unput(*yytext);\n");

        first = true;

        if (!get_array_properties().empty())
        {
            c_it = get_array_properties().begin();

            if (c_it->is_array_singleton_item())
            {
                emit_array_rule(sd, rule_str, first, *c_it, array_state, item_tag);
            }
            else
            {            
                for (; c_it != get_array_properties().end(); c_it++)
                {
                    const std::string& array_item_tag = c_it->is_vanilla()
                                                            ? item_tag
                                                            : empty_str;
                    std::string array_tag;

                    prop_tag = c_it->emit_parser(sd, format_state.empty()
                                                        ? array_state
                                                        : format_state);

                    format_rule_str = "";
                    format_state = "";

                    if (c_it != (--get_array_properties().end()))
                    {
                        SchemaItemList::const_iterator c_it2;
                        c_it2 = c_it;
                        c_it2++;
                        p_sitem = &(*c_it2);
                    }
                    else if (has_p_array_additional_items())
                        p_sitem = &(get_array_additional_items());
                    else
                        p_sitem = NULL;

                    if (p_sitem)
                    {
                        if (p_sitem->has_format_type())
                        {   // implies string type
                            format_state = sd.new_start_state();
                            std::string format_start_state_func =
                                        p_sitem->is_additional_item()
                                            ? sd.helper_func_name("void",
                                                                  "set_format_start_state",
                                                                  "",
                                                                  "BEGIN " + format_state + ";\n",
                                                                  true)
                                            : sd.helper_func_name("void",
                                                                  "push_format_start_state",
                                                                  "",
                                                                  "yy_push_state(" + format_state + ", yyextra->scaninfo);\n",
                                                                  true);
                            format_rule_str = "            " + format_start_state_func + "();\n";
                            sd.add_token("COMMA", "", false, "\",\"", "", format_state);
                            sd.add_lexer_rule("[[:space:]]", format_state, "", false, "");

                            if (p_sitem->is_additional_item())
                            {
                                sd.add_token("RIGHT_BRACKET", "", false, "\"]\"", "", format_state, "", true, "");
                            }
                        }
                        else
                        {
                            format_rule_str = "";
                            format_state = "";
                        }
                    }

                    if (first)
                    {
                        first = false;
                        rule_body = "";
                        rule_str += "    LEFT_BRACKET " + array_item_tag + " " + prop_tag + "\n";
                        array_tag_number = array_item_tag.empty()
                                                ? 2
                                                : 3;
                    }
                    else
                    {
                        rule_str += "    COMMA " + array_item_tag + " " + prop_tag + "\n";
                        array_tag_number += array_item_tag.empty()
                                                ? 2
                                                : 3;
                    }

                    array_tag = "$" + std::to_string(array_tag_number);

                    if (prop_tag == "QUOTED_STRING")
                        rule_body += "            JsonItem jitem;\n"
                                     "            jitem.set_string(" + array_tag + ");\n"
                                     "            $$.append_array_item(jitem);\n";
                    else
                        rule_body += "            $$.append_array_item(" + array_tag + ");\n";

                    if (!has_p_array_additional_items()
                        && c_it == (--get_array_properties().end()))
                    {
                        std::string set_item_array_start_state_func =
                                        sd.helper_func_name("void",
                                                            "set_item_array_start_state",
                                                            "yyscan_t yyscanner",
                                                            "struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;\n"
                                                            "BEGIN ITEM_ARRAY;\n",
                                                            true);
                        rule_str += "        {\n"
                                    "            " + set_item_array_start_state_func + "();\n"
                                    "        }\n";
                        array_tag_number++;
                    }
                }
            }
        }

        sd.add_token("RIGHT_BRACKET", "", false, "\"]\"", "", array_state, "", true);
        sd.add_token("COMMA", "", false, "\",\"", "", array_state);
        sd.add_lexer_rule("[[:space:]]", array_state, "", false, "");

        validation_rule_str = "";

        if (has_array_n_max_items())
        {
            validation_rule_str += "            if ($$.get_array_size() > " + std::to_string(get_array_max_items()) + ")\n"
                                   "            {\n"
                                   "                std::cerr << \"validation error: array has more than " + std::to_string(get_array_max_items()) + " items\" << std::endl;\n"
                                   "                YYABORT;\n"
                                   "            }\n"
                                   "\n";
        }

        if (has_array_n_min_items())
        {
            validation_rule_str += "            if ($$.get_array_size() < " + std::to_string(get_array_min_items()) + ")\n"
                                   "            {\n"
                                   "                std::cerr << \"validation error: array has fewer than " + std::to_string(get_array_min_items()) + " items\" << std::endl;\n"
                                   "                YYABORT;\n"
                                   "            }\n"
                                   "\n";
        }

        if (has_array_b_unique() && get_array_unique())
        {
            validation_rule_str += "            std::set<JsonItem> iset($$.child_list.begin(), $$.child_list.end());\n"
                                   "\n"
                                   "            if (iset.size() != $$.child_list.size())\n"
                                   "            {\n"
                                   "                std::cerr << \"validation error: array items are not unique: \" << $$.child_list.size() - iset.size() << \" duplicate items found\" << std::endl\n"
                                   "                YYABORT;\n"
                                   "            }\n"
                                   "\n";
            sd.add_parser_include("set", true);
        }

        if (!get_array_properties().empty()
            && get_array_properties().begin()->is_array_singleton_item())
        {
            rule_tag = sd.add_parser_rule("array_item",
                                rule_str +
                                "    ;\n"
                                "\n");
            sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
        }
        else
        {
            if (has_p_array_additional_items())
            {
                std::string ai_rule_str;
                first = true;
                emit_array_rule(sd,
                                ai_rule_str,
                                first,
                                get_array_additional_items(),
                                get_array_additional_items().has_format_type()
                                    ? format_state
                                    : array_state,
                                item_tag);
                rule_tag = sd.add_parser_rule("array_item",
                                    ai_rule_str +
                                    "    ;\n"
                                    "\n");
                sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
                std::string items_tag = sd.new_symbol("array_items");
                sd.set_rule_type(items_tag, sd.get_namespace() + "::JsonItemVector", true);
                rule_tag = sd.add_parser_rule(items_tag,
                            "    %empty\n"
                            "        {\n"
                            "            $$.clear();\n"
                            "        }\n"
                            "    | " + rule_tag + "\n"
                            "        {\n"
                            "            $$.clear();\n"
                            "            $$.push_back($1);\n"
                            "        }\n"
                            "    | " + items_tag + " COMMA " + rule_tag + "\n"
                            "        {\n"
                            "            $$ = $1;\n"
                            "            $$.push_back($3);\n"
                            "        }\n"
                            "    ;\n"
                            "\n",
                            false);

                rule_tag = sd.add_parser_rule("array",
                                    rule_str +
                                    "    " + rule_tag + " RIGHT_BRACKET\n"
                                    "        {\n"
                                    + rule_body +
                                    "            $$.append_array($" + std::to_string(array_tag_number + 1) + ");\n"
                                    + (validation_rule_str.empty()
                                          ? ""
                                          : "\n"
                                            + validation_rule_str) +
                                    "        }\n"
                                    "    ;\n"
                                    "\n");
                sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
                return rule_tag;
            }
            else
            {
                rule_tag = sd.add_parser_rule("array",
                                              rule_str +
                                              "    array_items RIGHT_BRACKET\n"
                                              "        {\n"
                                              + rule_body +
                                              "            $$.append_array($" + std::to_string(array_tag_number + 1) + ");\n"
                                              + (validation_rule_str.empty()
                                                    ? ""
                                                    : "\n"
                                                      + validation_rule_str) +
                                              "        }\n"
                                              "    ;\n"
                                              "\n");
                sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
                return rule_tag;
            }
        }

        if (!(has_array_n_max_items() && get_array_max_items() == 1))
        {   
            std::string items_tag = sd.new_symbol("array_items");
            sd.set_rule_type(items_tag, sd.get_namespace() + "::JsonItemVector", true);
            rule_tag = sd.add_parser_rule(items_tag,
                            "    " + rule_tag + "\n"
                            "         {\n"
                            "             $$.clear();\n"
                            "             $$.push_back($1);\n"
                            "         }\n"
                            "    | " + items_tag + " COMMA " + rule_tag + "\n"
                            "         {\n"
                            "             $$ = $1;\n"
                            "             $$.push_back($3);\n"
                            "         }\n"
                            "    ;\n"
                            "\n",
                            false);
        }

        if (!(has_array_n_min_items() && get_array_min_items() > 0))
        {
            rule_str = "    empty_array\n"
                       "        {\n"
                       "            $$.clear();\n"
                       "        }\n"
                       "    | ";
        }
        else
            rule_str = "    ";

        rule_str += (array_tag.empty()
                       ? "LEFT_BRACKET"
                       : array_tag + " QUOTED_STRING")
                    + " " + rule_tag + " RIGHT_BRACKET\n"
                    "        {\n";

        rule_str += "            $$.set_array(" + (array_tag.empty()
                                                        ? std::string("$2")
                                                        : std::string("$2, $3"))
                                                 + ");\n"
                     + (validation_rule_str.empty()
                            ? ""
                            : "\n"
                              + validation_rule_str) +
                    "        }\n"
                    "    ;\n"
                    "\n";

        rule_tag = sd.add_parser_rule("array", rule_str);
        sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);

        return rule_tag;
    }

    void SchemaItem::emit_object_rule(SchemaData& sd,
                                      std::string& rule_str,
                                      bool& first,
                                      const SchemaItem& item,
                                      const std::string& object_state,
                                      const std::string& prop_names_state) const
    {
        std::string prop_tag;

        prop_tag = item.emit_parser(sd, object_state, prop_names_state);

        if (first)
        {
            rule_str = "    " + prop_tag + "\n";
            first = false;
        }
        else
            rule_str += "    | " + prop_tag + "\n";

        rule_str += "        {\n"
                    "            $$ = $1;\n"
                    "        }\n";
    }

    std::string SchemaItem::emit_object_parser_rules(SchemaData& sd,
                                                     const std::string& start_state,
                                                     const std::string& key_validation_state) const
    {
        bool default_rules,
             first;
        SchemaItemList::const_iterator c_it;
        std::string obj_state,
                    obj_tag,
                    object_items_tag,
                    prop_tag,
                    prop_names_state,
                    rule_str,
                    rule_tag,
                    token,
                    unput_string_func,
                    upper_key;
        StdStringList::const_iterator s_it;

        default_rules = get_object_additional_properties().empty()
                        && get_object_property_names().empty()
                        && !has_object_n_max_properties()
                        && !has_object_n_min_properties()
                        && get_object_required().empty()
                        && get_object_properties().empty()
                        && get_object_pattern_properties().empty()
                        && get_object_dependencies().empty();

        if (default_rules)
            obj_state = "ITEM_OBJECT";
        else
            obj_state = sd.new_start_state();

        if (sd.is_initial_start_state(start_state))
        {
            sd.add_token("LEFT_BRACE",
                         "",
                         false,
                         "\"{\"",
                         "",
                         "INITIAL",
                         obj_state,
                         false);
            sd.add_token("RIGHT_BRACE",
                         "",
                         false,
                         "\"}\"",
                         "",
                         "INITIAL",
                         "",
                         true);
        }

        if (!get_key().empty())
        {
            obj_tag = sd.add_token(sd.new_token_tag(),
                                   "",
                                   false,
                                   "\"\\\"" + get_key() + "\\\"\"[[:space]]*:[[:space:]]*\"{\"",
                                   "",
                                   start_state,
                                   obj_state,
                                   false,
                                   sd.unput_string_func_name()+ "(yyscanner, yytext);\n"
                                   "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
        }
        else
        {
            sd.add_token("LEFT_BRACE",
                         "",
                         false,
                         "\"{\"",
                         "",
                         start_state,
                         obj_state,
                         false,
                         "");
        }

        emit_default_rules(sd);

        if (default_rules)
            return "object";

        if (has_p_object_property_names())
        {
            prop_names_state = get_object_property_names().emit_parser(sd, obj_state, prop_names_state);
        }

        first = true;

        for (c_it = get_object_properties().begin(); c_it != get_object_properties().end(); c_it++)
        {
            emit_object_rule(sd, rule_str, first, *c_it, obj_state, prop_names_state);
        }

        for (c_it = get_object_pattern_properties().begin(); c_it != get_object_pattern_properties().end(); c_it++)
        {
            emit_object_rule(sd, rule_str, first, *c_it, obj_state, prop_names_state);
        }

        if (has_p_object_additional_properties())
        {
            emit_object_rule(sd,
                             rule_str,
                             first,
                             get_object_additional_properties(),
                             obj_state,
                             prop_names_state);
        }
        else
        {
            prop_tag = sd.add_token(sd.new_token_tag(),
                                    "",
                                    false,
                                    "\"\\\"\"",
                                    "",
                                    obj_state,
                                    "ITEM_VALUE",
                                    false,
                                    "unput(*yytext);\n"
                                    "yy_push_state(PARSE_ITEM_KEY, yyextra->scaninfo);\n");

            if (first)
            {
                rule_str += "    ";
                first = false;
            }
            else
                rule_str += "    | ";

            rule_str += prop_tag + " QUOTED_STRING COLON QUOTED_STRING\n"
                        "        {\n"
                        "            $$.set_string($2, $4);\n"
                        "        }\n"
                        "    | " + prop_tag + " QUOTED_STRING COLON number\n"
                        "        {\n"
                        "            $$.set_number($2, $4);\n"
                        "        }\n"
                        "    | " + prop_tag + " QUOTED_STRING COLON boolean\n"
                        "        {\n"
                        "            $$.set_boolean($2, $4);\n"
                        "        }\n"
                        "    | " + prop_tag + " QUOTED_STRING COLON array\n"
                        "        {\n"
                        "            $$ = $4;\n"
                        "            $$.set_key($2);\n"
                        "        }\n"
                        "    | " + prop_tag + " QUOTED_STRING COLON object\n"
                        "        {\n"
                        "            $$ = $4;\n"
                        "            $$.set_key($2);\n"
                        "        }\n"
                        "    | " + prop_tag + " QUOTED_STRING COLON NULL_TOKEN\n"
                        "        {\n"
                        "            $$.set_null($2);\n"
                        "        }\n";
        }

        rule_tag = sd.add_parser_rule("object_item",
                            rule_str +
                            "    ;\n"
                            "\n");

        sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
        sd.add_token("RIGHT_BRACE", "", false, "\"}\"", "", obj_state, "", true);
        sd.add_token("COMMA", "", false, "\",\"", "", obj_state);
        sd.add_lexer_rule("[[:space:]]",obj_state, "", false, "");

        if (((get_object_properties().size() + get_object_pattern_properties().size()) > 1)
            || !has_p_object_additional_properties()
            || get_object_required().size() > 1)
        {   
            std::string items_tag = sd.new_symbol("object_items");
            sd.set_rule_type(items_tag, sd.get_namespace() + "::JsonItemMap", true);
            rule_tag = sd.add_parser_rule(items_tag,
                            "    " + rule_tag + "\n"
                            "         {\n"
                            "             $$.clear();\n"
                            "             $$[$1.get_key()] = $1;\n"
                            "         }\n"
                            "    | " + items_tag + " COMMA " + rule_tag + "\n"
                            "         {\n"
                            "             $$ = $1;\n"
                            "             $$[$3.get_key()] = $3;\n"
                            "         }\n"
                            "    ;\n"
                            "\n",
                            false);
        }

        if (get_object_required().empty()
            && ((has_object_n_min_properties() && get_object_min_properties() == 0)
                || !has_object_n_min_properties()))
            rule_str = "    empty_object\n"
                       "        {\n"
                       "            $$.clear();\n"
                       "        }\n"
                       "    | ";
        else
            rule_str = "    ";

        rule_str += (obj_tag.empty()
                           ? "LEFT_BRACE"
                           : obj_tag + " QUOTED_STRING")
                    + " " + rule_tag + " RIGHT_BRACE\n"
                    "        {\n";

        object_items_tag = obj_tag.empty() ? "$2" : "$3";

        for (s_it = get_object_required().begin(); s_it != get_object_required().end(); s_it++)
        {
            rule_str += "            if (" + object_items_tag + ".find(\"" + *s_it + "\") == " + object_items_tag + ".end())\n"
                        "            {\n"
                        "                std::cerr << \"Object missing required object property: \\\"" + *s_it + "\\\"\" << std::endl;\n"
                        "                YYABORT;\n"
                        "            }\n"
                        "\n";
        }

        if (has_object_n_min_properties() && get_object_min_properties() > 0)
        {
            rule_str += "            if (" + object_items_tag + ".count() < " + std::to_string(get_object_min_properties()) + ")\n"
                        "            {\n"
                        "                std::cerr << \"Object must have at least " + std::to_string(get_object_min_properties()) + " properties, but only has \" << " + object_items_tag + ".count() << std::endl;\n"
                        "                YYABORT;\n"
                        "            }\n"
                        "\n";
        }

        if (has_object_n_max_properties() && get_object_max_properties() > 0)
        {
            rule_str += "            if (" + object_items_tag + ".count() > " + std::to_string(get_object_max_properties()) + ")\n"
                        "            {\n"
                        "                std::cerr << \"Object must have at most " + std::to_string(get_object_max_properties()) + " properties, but has \" << " + object_items_tag + ".count() << std::endl;\n"
                        "                YYABORT;\n"
                        "            }\n"
                        "\n";
        }

        for (c_it = get_object_dependencies().begin(); c_it != get_object_dependencies().end(); c_it++)
        {
            if (c_it->has_DependencyArray_type() && !c_it->get_dependency_array().empty())
            {
                std::cout << "\"" << get_key() << "\" has dependencies array" << std::endl;
                rule_str += "            if (" + object_items_tag + ".find(\"" + c_it->get_key() + "\") == " + object_items_tag + ".end())\n"
                            "            {\n";

                for (first = true, s_it = c_it->get_dependency_array().begin(); s_it != c_it->get_dependency_array().end(); s_it++)
                {
                    if (first)
                        first = false;
                    else
                        rule_str += "\n";

                    rule_str += "                if (" + object_items_tag + ".find(\"" + *s_it + "\") == " + object_items_tag + ".end())\n"
                                "                {\n"
                                "                    std::cerr << \"Object missing dependency object property: \\\"" + *s_it + "\\\"\" << std::endl;\n"
                                "                    YYABORT;\n"
                                "                }\n";
                }

                rule_str += "            }\n"
                            "\n";
            }
        }

        rule_str += "            $$.set_object(" + (obj_tag.empty()
                                                        ? std::string("$2")
                                                        : std::string("$2, $3"))
                                                 + ");\n"
                    "        }\n"
                    "    ;\n"
                    "\n";

        rule_tag = sd.add_parser_rule("object", rule_str);
        sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
        return rule_tag;
    }

    std::string SchemaItem::emit_string_parser_rules(SchemaData& sd,
                                                     const std::string& start_state,
                                                     const std::string& key_validation_state) const
    {
        std::string minmax_state,
                    key_token,
                    pattern = get_string_pattern(),
                    pattern_state,
                    regex,
                    str_tag,
                    rule_tag,
                    unput_string_func;
        // long default_minLength = 0,
        //      maxLength = get_string_max_length(),
        //      minLength = get_string_min_length();

        sd.add_token("QUOTED_STRING", "std::string", true, "string", true, "\"\\\"\"", "yyextra->quoted_str", "QUOTED", "", true);

        if (!(has_str_n_max_length()
              || has_str_n_min_length()
              || has_str_pattern()
              || has_format_type())
            && !is_property_names_schema())
        {
            if (get_key().empty())
            {
                Token t;

                if (sd.get_token(start_state, ".", t))
                    return "QUOTED_STRING";
                    // key_token = t.get_name();
                else
                    key_token = sd.add_token(sd.new_token_tag(),
                                             "",
                                             false,
                                             "\"\\\"\"",
                                             "",
                                             start_state,
                                             "QUOTED",
                                             false);

                rule_tag = sd.add_parser_rule("string",
                                "    " + key_token + " QUOTED_STRING\n"
                                "        {\n"
                                "            $$.set_string($2);\n"
                                "        }\n"
                                "    ;\n"
                                "\n");
                // return "QUOTED_STRING";
            }
            else
            {
                key_token = sd.add_token(sd.new_token_tag(),
                                         "",
                                         false,
                                         "\"\\\"" + get_key() + "\\\"\"",
                                         "",
                                         start_state,
                                         "ITEM_VALUE",
                                         false,
                                         sd.unput_string_func_name()+ "(yyscanner, yytext);\n"
                                         "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
                rule_tag = sd.add_parser_rule("string",
                                "    " + key_token + " QUOTED_STRING QUOTED_STRING\n"
                                "        {\n"
                                "            $$.set_string($2, $3);\n"
                                "        }\n"
                                "    ;\n"
                                "\n");
            }

            sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
            return rule_tag;
        }

        if (has_format_type())
        {
            pattern = "\\\"";

            switch (get_format_type())
            {
                case FormatType::type_Date:
                    pattern += "((([02468][048]|[13579][26])00|[0-9][0-9](0[48]|[2468][048]|[13579][26]))-02-29)|([0-9]{4}-(0[13578]|1[02])-31)|([0-9]{4}-(0[13456789]|1[012])-(0[1-9]|[12][0-9]|30))|([0-9]{4}-(0[1-9]|1[012])-(0[1-9]|1[0-9]|2[0-8]))\\\"";
                    break;

                case FormatType::type_DateTime:
                    pattern += "(((([02468][048]|[13579][26])00|[0-9][0-9](0[48]|[2468][048]|[13579][26]))-02-29)|([0-9]{4}-(0[13578]|1[02])-31)|([0-9]{4}-(0[13456789]|1[012])-(0[1-9]|[12][0-9]|30))|([0-9]{4}-(0[1-9]|1[012])-(0[1-9]|1[0-9]|2[0-8])))[tT](([01][0-9]|2[0-3]):[0-5][0-9]:([0-5][0-9]|60)(\\.[0-9])?([zZ]|[+-]([01][0-9]|2[0-3]):[0-5][0-9]))";
                    break;

                case FormatType::type_Email:
                    pattern += "((?>[a-zA-Z\\d!#$%&'*+\\-/=?^_`{|}~]+\x20*|\\\"((?=[\x01-\x7f])[^\\\"\\]|\\[\x01-\x7f])*\\\"\x20*)*(?<angle><))?((?!\\.)(?>\\.?[a-zA-Z\\d!#$%&'*+\\-/=?^_`{|}~]+)+|\\\"((?=[\x01-\x7f])[^\\\"\\]|\\[\x01-\x7f])*\\\")@(((?!-)[a-zA-Z\\d\\-]+(?<!-)\\.)+[a-zA-Z]{2,}|\\[(((?(?<!\\[)\\.)(25[0-5]|2[0-4]\\d|[01]?\\d?\\d)){4}|[a-zA-Z\\d\\-]*[a-zA-Z\\d]:((?=[\x01-\x7f])[^\\\\[\\]]|\\[\x01-\x7f])+)\\])(?(angle)>)";
                    break;

                case FormatType::type_Ipv4:
                    pattern += "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
                    break;

                case FormatType::type_Ipv6:
                    pattern += "((([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4}|:))|(([0-9A-Fa-f]{1,4}:){6}(:[0-9A-Fa-f]{1,4}|((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){5}(((:[0-9A-Fa-f]{1,4}){1,2})|:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){4}(((:[0-9A-Fa-f]{1,4}){1,3})|((:[0-9A-Fa-f]{1,4})?:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){3}(((:[0-9A-Fa-f]{1,4}){1,4})|((:[0-9A-Fa-f]{1,4}){0,2}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){2}(((:[0-9A-Fa-f]{1,4}){1,5})|((:[0-9A-Fa-f]{1,4}){0,3}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){1}(((:[0-9A-Fa-f]{1,4}){1,6})|((:[0-9A-Fa-f]{1,4}){0,4}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(:(((:[0-9A-Fa-f]{1,4}){1,7})|((:[0-9A-Fa-f]{1,4}){0,5}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:)))(%.+)?";
                    break;

                case FormatType::type_Time:
                    pattern += "(([01][0-9]|2[0-3]):[0-5][0-9]:([0-5][0-9]|60)(\\.[0-9])?([zZ]|[+-]([01][0-9]|2[0-3]):[0-5][0-9]))";
                    break;

                default :
                    pattern += "((\\\\b)|(\\\\\\\\)|(\\\\/)|(\\\\f)|(\\\\n)|(\\\\r)|(\\\\t)|(\\\\\\\")|(\\\\u[0-9a-fA-F]{4})|[^\\\"])*";
                    break;
            }

            pattern += "\\\"";
        }
        else if (has_str_pattern())
            pattern = "\\\"[^\\\"]*" + get_string_pattern() + "[^\\\"]*\\\"";
        else
            pattern = "\\\"((\\\\b)|(\\\\\\\\)|(\\\\/)|(\\\\f)|(\\\\n)|(\\\\r)|(\\\\t)|(\\\\\\\")|(\\\\u[0-9a-fA-F]{4})|[^\\\"])*\\\"";

        regex = "\"" + pattern + "\"";

        if (is_property_names_schema())
            pattern_state = sd.new_parse_key_state();
        else
            pattern_state = sd.new_start_state();

        if (has_str_n_min_length() || has_str_n_max_length())
        {
            minmax_state = sd.new_start_state();
            sd.add_lexer_rule("\"\\\"((\\\\b)|(\\\\\\\\)|(\\\\/)|(\\\\f)|(\\\\n)|(\\\\r)|(\\\\t)|(\\\\\\\")|(\\\\u[0-9a-fA-F]{4})|[^\\\"]){"
                                + (has_str_n_min_length() ? std::to_string(get_string_min_length()) : "0")
                                + ","
                                + (has_str_n_max_length() ? std::to_string(get_string_max_length()) : "")
                                + "}\\\"\"",
                              minmax_state,
                              pattern_state,
                              true,
                              sd.unput_string_func_name() + "(yyscanner, yytext);\n");
        }

        if (!get_key().empty())
        {
            key_token = sd.add_token(sd.new_token_tag(),
                                     "",
                                     false,
                                     "\"\\\"" + get_key() + "\\\"\"[[:space:]]*:[[:space:]]*",
                                     "",
                                     start_state,
                                     minmax_state.empty()
                                        ? pattern_state
                                        : minmax_state,
                                     false,
                                     sd.unput_string_func_name() + "(yyscanner, yytext);\n"
                                     "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
        }
        else if (is_additional_property())
        {
            key_token = sd.add_token(sd.new_token_tag(),
                                     "",
                                     false,
                                     "\"\\\"\"",
                                     "",
                                     start_state,
                                     minmax_state.empty()
                                        ? pattern_state
                                        : minmax_state,
                                     false,
                                     "unput(*yytext);\n"
                                     "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
        }
        else if (is_property_names_schema())
        {
            sd.add_lexer_rule(regex + "[[:space:]]*:[[:space:]]*",
                              pattern_state,
                              "PARSE_ITEM_KEY",
                              true,
                              sd.unput_string_func_name() + "(yyscanner, *yytext);\n");
            sd.add_lexer_rule(regex + "[[:space:]]*:[[:space:]]*\"{\"",
                              pattern_state,
                              "PARSE_OBJECT_KEY",
                              true,
                              sd.unput_string_func_name() + "(yyscanner, *yytext);\n");
            sd.add_lexer_rule(regex + "[[:space:]]*:[[:space:]]*\"[\"",
                              pattern_state,
                              "PARSE_ARRAY_KEY",
                              true,
                              sd.unput_string_func_name() + "(yyscanner, *yytext);\n");
        }

        if (!is_property_names_schema())
        {
            if (get_key().empty())
            {
                key_token = sd.new_token_tag();
                sd.add_token(key_token,
                             "",
                             false,
                             "\"\\\"\"",
                             "",
                             start_state,
                             minmax_state.empty()
                                ? pattern_state
                                : minmax_state,
                             has_format_type()
                                && !is_first_array_item()
                                && !is_additional_item(),
                             sd.unput_string_func_name() + "(yyscanner, yytext);\n");
            }

            sd.add_lexer_rule(regex,
                              pattern_state,
                              "ITEM_VALUE",
                              true,
                              sd.unput_string_func_name() + "(yyscanner, yytext);\n");
            rule_tag = sd.add_parser_rule("string",
                                "    " + key_token + ((get_key().empty() && !is_additional_property())
                                                        ? ""
                                                        : " QUOTED_STRING")
                                                   + " QUOTED_STRING\n"
                                "        {\n"
                                "            $$.set_string(" + ((get_key().empty() && !is_additional_property())
                                                                    ? "$2"
                                                                    : "$2, $3") + ");\n"
                                "        }\n"
                                "    ;\n"
                                "\n");
            sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
            return rule_tag;
        }
        else
            return pattern_state;
    }

    std::string SchemaItem::emit_integer_parser_rules(SchemaData& sd,
                                                      const std::string& start_state,
                                                      const std::string& key_validation_state) const
    {
        bool has_validation_rule;
        std::string enum_if_str,
                    enum_str,
                    exclusiveMaximum = std::to_string(get_int_exclusive_maximum()),
                    exclusiveMinimum = std::to_string(get_int_exclusive_minimum()),
                    helper_func,
                    helper_body,
                    int_tag,
                    lexer_body,
                    key_token,
                    maximum = std::to_string(get_int_maximum()),
                    minimum = std::to_string(get_int_minimum()),
                    multipleOf = std::to_string(get_int_multiple_of()),
                    new_start_state,
                    rule_tag,
                    unput_string_func;

        sd.add_token("NEG_INTEGER", "long", false, "-[0-9]+", "std::stol(yytext)", new_start_state, "", true, lexer_body);
        sd.add_token("NON_NEG_INTEGER", "long", false, "[+]?[0-9]+", "std::stol(yytext)", new_start_state, "", true, lexer_body);
        int_tag = sd.add_parser_rule("integer",
                            "    NEG_INTEGER\n"
                            "        {\n"
                            "            $$ = $1;\n"
                            "        }\n"
                            "    | NON_NEG_INTEGER\n"
                            "        {\n"
                            "            $$ = $1;\n"
                            "        }\n"
                            "    ;\n"
                            "\n",
                            false);
        sd.set_rule_type(int_tag, "long", false);
        // int_tag = sd.add_parser_rule("integer",
        //                     "    " + int_tag + "\n"
        //                     "        {\n"
        //                     "            $$.set_number($1);\n"
        //                     "        }\n"
        //                     "    ;\n"
        //                     "\n");
        // sd.set_rule_type(int_tag, sd.get_namespace() + "::JsonItem", true);

        has_validation_rule = has_int_multiple_of()
                              | has_int_maximum()
                              | has_int_minimum()
                              | has_int_exclusive_maximum()
                              | has_int_exclusive_minimum()
                              | has_enum_list();

        if (!has_validation_rule && get_key().empty())
        {
            rule_tag = sd.add_parser_rule("integer",
                            "    integer\n"
                            "        {\n"
                            "            $$.set_number($1);\n"
                            "        }\n"
                            "    ;\n"
                            "\n");
            sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
            return rule_tag;
        }

        if (has_enum_list())
        {
            bool first = true;
            const JsonItemList& elist = get_enum_list();
            JsonItemList::const_iterator c_it;
            enum_str = "";
            enum_if_str = "";

            for (c_it = elist.cbegin(); c_it != elist.cend(); c_it++)
            {
                if (c_it->is_number())
                {
                    if (first)
                        first = false;
                    else
                    {
                        enum_if_str += " || ";
                        enum_str += ", ";
                    }

                    enum_if_str += "value == " + std::to_string(c_it->num_value);
                    enum_str += std::to_string(c_it->num_value);
                }
            } 
        }

        new_start_state = has_validation_rule
                            ? sd.new_start_state()
                            : "";
        lexer_body = "";

        if (has_validation_rule)
        {
            if (has_int_multiple_of())
                helper_body += "if ((((long)((value/" + multipleOf + ")) * " + multipleOf + ") != value)\n"
                               "    {\n"
                               "            std::cerr << \"validation error: \" << yytext << \" is not a multiple of " + multipleOf + "\" << std::endl;\n"
                               "            return 0;\n"
                               "        }\n"
                               "        \n";

            if (has_int_maximum())
                helper_body += "if (value > " + maximum + ")\n"
                               "        {\n"
                               "            std::cerr << \"validation error: \" << yytext << \" is greater than " + maximum + "\" << std::endl;\n"
                               "            return 0;\n"
                               "        }\n"
                               "        \n";

            if (has_int_minimum())
                helper_body += "if (value < " + minimum + ")\n"
                               "        {\n"
                               "            std::cerr << \"validation error: \" << yytext << \" is less than " + minimum + "\" << std::endl;\n"
                               "            return 0;\n"
                               "        }\n"
                               "        \n";

            if (has_int_exclusive_maximum())
                helper_body += "if (value >= " + exclusiveMaximum + ")\n"
                               "        {\n"
                               "            std::cerr << \"validation error: \" << yytext << \" is not less than " + exclusiveMaximum + "\" << std::endl;\n"
                               "            return 0;\n"
                               "        }\n"
                               "        \n";

            if (has_int_exclusive_minimum())
                helper_body += "if (value <= " + exclusiveMinimum + ")\n"
                               "        {\n"
                               "            std::cerr << \"validation error: \" << yytext << \" is not greater than " + exclusiveMinimum + "\" << std::endl;\n"
                               "            return 0;\n"
                               "        }\n"
                               "        \n";

            if (!enum_if_str.empty())
                helper_body += "if (!(" + enum_if_str + "))\n"
                               "        {\n"
                               "            std::cerr << \"validation error: \" << yytext << \" is not one of " + enum_str + "\" << std::endl;\n"
                               "            return 0;\n"
                               "        }\n"
                               "        \n";

            helper_body += "return true;\n";
            helper_func = sd.helper_func_name("bool", "value_meets_constraints", "long value", helper_body, false);
            lexer_body = "\n"
                         "if (!" + helper_func + "(yylval->int_type))\n"
                         "    return false;\n"
                         "\n";
        }

        if (!get_key().empty())
        {
            key_token = sd.add_token(sd.new_token_tag(),
                                     "",
                                     false,
                                     "\"\\\"" + get_key() + "\\\"\"" + (has_validation_rule
                                                                        ? "[[:space:]]*:[[:space:]]*"
                                                                        : ""),
                                     "",
                                     start_state,
                                     new_start_state,
                                     false,
                                     sd.unput_string_func_name() + "(yyscanner, yytext);\n"
                                     "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
            rule_tag = sd.add_parser_rule("integer",
                               "    " + key_token + (has_validation_rule
                                                      ? " QUOTED_STRING "
                                                      : " QUOTED_STRING COLON ") + int_tag
                                      + "\n"
                               "        {\n"
                               "            $$.set_number($2, " + (has_validation_rule
                                                                    ? "$3"
                                                                    : "$4") + ");\n"
                               "        }\n"
                               "    ;\n"
                               "\n");
        }
        else
        {
            key_token = sd.new_token_tag();
            sd.add_token(key_token,
                         "",
                         false,
                         "[-+]?[0-9]+" + (has_validation_rule
                                        ? std::string("[[:space:]]*:[[:space:]]*")
                                        : std::string("")),
                         "",
                         start_state,
                         new_start_state,
                         false,
                         sd.unput_string_func_name() + "(yyscanner, yytext);\n");
            rule_tag = sd.add_parser_rule("integer",
                               "    " + key_token +  " " + int_tag + "\n"
                               "        {\n"
                               "            $$.set_number($2);\n"
                               "        }\n"
                               "    ;\n"
                               "\n");
        }

        sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
        return rule_tag;
    }

    std::string SchemaItem::emit_number_parser_rules(SchemaData& sd,
                                                     const std::string& start_state,
                                                     const std::string& key_validation_state) const
    {
        bool has_validation_rule;
        std::string enum_if_str,
                    enum_str,
                    exclusiveMaximum = std::to_string(get_num_exclusive_maximum()),
                    exclusiveMinimum = std::to_string(get_num_exclusive_minimum()),
                    helper_body,
                    helper_func,
                    key_token,
                    lexer_body,
                    maximum = std::to_string(get_num_maximum()),
                    minimum = std::to_string(get_num_minimum()),
                    multipleOf = std::to_string(get_num_multiple_of()),
                    new_start_state,
                    num_tag,
                    rule_tag,
                    unput_string_func;

        sd.add_token("NEG_INTEGER", "long", false, "-[0-9]+", "std::stol(yytext)", new_start_state, "", true, lexer_body);
        sd.add_token("NON_NEG_INTEGER", "long", false, "[+]?[0-9]+", "std::stol(yytext)", new_start_state, "", true, lexer_body);
        sd.add_token("FLOATING_POINT", "double", false, "[-+]?[0-9]+\\.[0-9]*", "std::stod(yytext)", new_start_state, "", true, lexer_body);
        num_tag = sd.add_parser_rule("number",
                            "    FLOATING_POINT\n"
                            "        {\n"
                            "            $$ = $1;\n"
                            "        }\n"
                            "    | NEG_INTEGER\n"
                            "        {\n"
                            "            $$ = $1;\n"
                            "        }\n"
                            "    | NON_NEG_INTEGER\n"
                            "        {\n"
                            "            $$ = $1;\n"
                            "        }\n"
                            "    ;\n"
                            "\n",
                            false);
        sd.set_rule_type(num_tag, "double", false);

        has_validation_rule = has_num_multiple_of()
                              | has_num_maximum()
                              | has_num_minimum()
                              | has_num_exclusive_maximum()
                              | has_num_exclusive_minimum()
                              | has_enum_list();

        if (!has_validation_rule && get_key().empty())
        {
            rule_tag = sd.add_parser_rule("number",
                            "    number\n"
                            "        {\n"
                            "            $$.set_number($1);\n"
                            "        }\n"
                            "    ;\n"
                            "\n");
            sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
            return rule_tag;
        }

        if (has_enum_list())
        {
            bool first = true;
            const JsonItemList& elist = get_enum_list();
            JsonItemList::const_iterator c_it;
            enum_str = "";
            enum_if_str = "";

            for (c_it = elist.cbegin(); c_it != elist.cend(); c_it++)
            {
                if (c_it->is_number())
                {
                    if (first)
                        first = false;
                    else
                    {
                        enum_if_str += " || ";
                        enum_str += ", ";
                    }

                    enum_if_str += "value == " + std::to_string(c_it->num_value);
                    enum_str += std::to_string(c_it->num_value);
                }
            } 
        }

        new_start_state = has_validation_rule
                            ? sd.new_start_state()
                            : "";
        lexer_body = "";

        if (has_validation_rule)
        {
            lexer_body = "\n";

            if (has_num_multiple_of())
                helper_body += "if ((double)((long)(value/" + multipleOf + ")) != (value/" + multipleOf + "))\n"
                               "{\n"
                               "    std::cerr << \"validation error: \" << yytext << \" is not a multiple of " + multipleOf + "\" << std::endl;\n"
                               "    return 0;\n"
                               "}\n"
                               "\n";

            if (has_num_maximum())
                helper_body += "if (value > " + maximum + ")\n"
                               "{\n"
                               "    std::cerr << \"validation error: \" << yytext << \" is greater than " + maximum + "\" << std::endl;\n"
                               "    return 0;\n"
                               "}\n"
                               "\n";
            if (has_num_minimum())
                helper_body += "if (value < " + minimum + ")\n"
                               "{\n"
                               "    std::cerr << \"validation error: \" << yytext << \" is less than " + minimum + "\" << std::endl;\n"
                               "    return 0;\n"
                               "}\n"
                               "\n";
            if (has_num_exclusive_maximum())
                helper_body += "if (value >= " + exclusiveMaximum + ")\n"
                               "{\n"
                               "    std::cerr << \"validation error: \" << yytext << \" is not less than " + exclusiveMaximum + "\" << std::endl;\n"
                               "    return 0;\n"
                               "}\n"
                               "\n";
            if (has_num_exclusive_minimum())
                helper_body += "if (value <= " + exclusiveMinimum + ")\n"
                               "{\n"
                               "    std::cerr << \"validation error: \" << yytext << \" is not greater than " + exclusiveMinimum + "\" << std::endl;\n"
                               "    return 0;\n"
                               "}\n"
                               "\n";
            if (!enum_if_str.empty())
                helper_body += "if (!(" + enum_if_str + "))\n"
                               "{\n"
                               "    std::cerr << \"validation error: \" << yytext << \" is not one of " + enum_str + "\" << std::endl;\n"
                               "    return 0;\n"
                               "}\n"
                               "\n";

            helper_body += "return true;\n";
            helper_func = sd.helper_func_name("bool", "value_meets_constraints", "double value", helper_body, false);
            lexer_body = "\n"
                         "if (!" + helper_func + "(yylval->int_type))\n"
                         "    return 0;\n"
                         "\n";
        }

        if (!get_key().empty())
        {
            key_token = sd.add_token(sd.new_token_tag(),
                                     "",
                                     false,
                                     "\"\\\"" + get_key() + "\\\"\"" + (has_validation_rule
                                                                        ? "[[:space:]]*:[[:space:]]*"
                                                                        : ""),
                                     "",
                                     start_state,
                                     new_start_state,
                                     false,
                                     sd.unput_string_func_name() + "(yyscanner, yytext);\n"
                                     "yy_push_state(" + key_validation_state + ", yyextra->scaninfo);\n");
            rule_tag = sd.add_parser_rule("number",
                               "    " + key_token + " QUOTED_STRING"
                                                    + (has_validation_rule
                                                          ? " "
                                                          : " COLON ") + num_tag
                                      + "\n"
                               "        {\n"
                               "            $$.set_number($2, " + (has_validation_rule
                                                                    ? "$3"
                                                                    : "$4") + ");\n"
                               "        }\n"
                               "    ;\n"
                               "\n");
        }
        else
        {
            key_token = sd.new_token_tag();
            sd.add_token(key_token,
                         "",
                         false,
                         "[-+]?[0-9]+(\\.[0-9]+)?"
                                    + (has_validation_rule
                                        ? std::string("[[:space:]]*:[[:space:]]*")
                                        : std::string("")),
                         "",
                         start_state,
                         new_start_state,
                         false,
                         sd.unput_string_func_name() + "(yyscanner, yytext);\n");
            rule_tag = sd.add_parser_rule("number",
                               "    " +  key_token + " " + num_tag + "\n"
                               "        {\n"
                               "            $$.set_number($2);\n"
                               "        }\n"
                               "    ;\n"
                               "\n");
        }

        sd.set_rule_type(rule_tag, sd.get_namespace() + "::JsonItem", true);
        return rule_tag;
    }

    bool SchemaItem::is_vanilla() const
    {
        return !(has_bool_one_of()
                    || has_bool_any_of()
                    || has_bool_all_of()
                    || has_p_bool_not_schema()
                    || has_p_bool_if_schema()
                    || has_p_bool_else_schema()
                    || has_p_bool_then_schema()
                    || has_enum_list()
                    || has_definitions_list()
                    || has_format_type()
                    || has_json_default_value()
                    || has_b_read_only()
                    || has_b_write_only()
                    || has_json_examples()
                    || (has_String_type()
                        && (has_str_content_encoding()
                            || has_str_content_media_type()
                            || has_str_n_max_length()
                            || has_str_n_min_length()
                            || has_str_pattern()))
                    || (has_Array_type()
                        && (has_p_array_additional_items()
                            || has_array_contains()
                            || has_array_n_max_items()
                            || has_array_n_min_items()
                            || has_array_properties()
                            || has_array_b_unique()))
                    || (has_Integer_type()
                        && (has_int_exclusive_maximum()
                            || has_int_exclusive_minimum()
                            || has_int_maximum()
                            || has_int_minimum()
                            || has_int_multiple_of()))
                    || (has_Number_type()
                        && (has_num_exclusive_maximum()
                            || has_num_exclusive_minimum()
                            || has_num_maximum()
                            || has_num_minimum()
                            || has_num_multiple_of()))
                    || (has_Object_type()
                        && (has_object_n_max_properties()
                            || has_object_n_min_properties()
                            || has_object_required()
                            || has_object_properties()
                            || has_object_pattern_properties()
                            || has_object_dependencies()
                            || has_b_object_can_have_additional_properties()
                            || has_p_object_additional_properties()
                            || has_p_object_property_names())));
    }
}
