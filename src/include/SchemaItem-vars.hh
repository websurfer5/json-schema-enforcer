// SchemaItem-vars.hh
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
//
// DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get)
// DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get)

DEF_VAR(bool,
        array_b_unique,
        false,
        true,
        b_has_array_unique,
        false,
        set_array_unique,
        get_array_unique)

DEF_VAR(double,
        num_exclusive_maximum,
        0,
        20.9,
        b_has_num_exclusive_maximum,
        false,
        set_num_exclusive_maximum,
        get_num_exclusive_maximum)

DEF_VAR(double,
        num_exclusive_minimum,
        0,
        0.9,
        b_has_num_exclusive_minimum,
        false,
        set_num_exclusive_minimum,
        get_num_exclusive_minimum)

DEF_VAR(double,
        num_maximum,
        0,
        20.5,
        b_has_num_maximum,
        false,
        set_num_maximum,
        get_num_maximum)

DEF_VAR(double,
        num_minimum,
        0,
        0.95,
        b_has_num_minimum,
        false,
        set_num_minimum,
        get_num_minimum)

DEF_VAR(double,
        num_multiple_of,
        0,
        5.5,
        b_has_num_multiple_of,
        false,
        set_num_multiple_of,
        get_num_multiple_of)

DEF_VAR(long,
        array_n_max_items,
        0,
        10,
        b_has_array_max_items,
        false,
        set_array_max_items,
        get_array_max_items)

DEF_VAR(long,
        array_n_min_items,
        0,
        1,
        b_has_array_min_items,
        false,
        set_array_min_items,
        get_array_min_items)

DEF_VAR(long,
        int_exclusive_maximum,
        0,
        11,
        b_has_int_exclusive_maximum,
        false,
        set_int_exclusive_maximum,
        get_int_exclusive_maximum)

DEF_VAR(long,
        int_exclusive_minimum,
        0,
        1,
        b_has_int_exclusive_minimum,
        false,
        set_int_exclusive_minimum,
        get_int_exclusive_minimum)

DEF_VAR(long,
        int_maximum,
        0,
        200,
        b_has_int_maximum,
        false,
        set_int_maximum,
        get_int_maximum)

DEF_VAR(long,
        int_minimum,
        0,
        -5,
        b_has_int_minimum,
        false,
        set_int_minimum,
        get_int_minimum)

DEF_VAR(long,
        int_multiple_of,
        0,
        4,
        b_has_int_multiple_of,
        false,
        set_int_multiple_of,
        get_int_multiple_of)

DEF_VAR(long,
        str_n_max_length,
        0,
        256,
        b_has_str_n_max_length,
        false,
        set_string_max_length,
        get_string_max_length)

DEF_VAR(long,
        str_n_min_length,
        0,
        100,
        b_has_str_n_min_length,
        false,
        set_string_min_length,
        get_string_min_length)

DEF_OBJ(SchemaItemList,
        array_properties,
        clear,
        empty,
        /**/,
        b_has_array_properties,
        false,
        set_array_properties,
        get_array_properties)

DEF_VAR(std::string,
        str_pattern,
        "",
        "foo[123]+",
        b_has_str_pattern,
        false,
        set_string_pattern,
        get_string_pattern)

DEF_OBJ(JsonItemList,
        array_contains,
        clear,
        empty,
        /**/,
        b_has_array_contains,
        false,
        set_array_contains,
        get_array_contains)

DEF_OBJ(JsonItemList,
        enum_list,
        clear,
        empty,
        /**/,
        b_has_enum,
        false,
        set_enum_list,
        get_enum_list)

DEF_VAR(std::string,
        key,
        "",
        "foo-key",
        b_has_key,
        false,
        set_key,
        get_key)

DEF_OBJ_PTR(SchemaItem,
            p_array_additional_items,
            clear,
            empty,
            /**/,
            b_has_array_additional_items,
            false,
            set_array_additional_items,
            get_array_additional_items)

DEF_OBJ_PTR(SchemaItem,
            p_object_additional_properties,
            clear,
            empty,
            /**/,
            b_has_object_additional_properties,
            false,
            set_object_additional_properties,
            get_object_additional_properties)

DEF_OBJ_PTR(SchemaItem,
            p_object_property_names,
            clear,
            empty,
            /**/,
            b_has_object_property_names,
            false,
            set_object_property_names,
            get_object_property_names)

DEF_OBJ_PTR(SchemaItem,
            p_bool_not_schema,
            clear,
            empty,
            /**/,
            b_has_bool_not_schema,
            false,
            set_bool_not_schema,
            get_bool_not_schema)

DEF_OBJ_PTR(SchemaItem,
            p_bool_else_schema,
            clear,
            empty,
            /**/,
            b_has_bool_else_schema,
            false,
            set_bool_else_schema,
            get_bool_else_schema)

DEF_OBJ_PTR(SchemaItem,
            p_bool_if_schema,
            clear,
            empty,
            /**/,
            b_has_bool_if_schema,
            false,
            set_bool_if_schema,
            get_bool_if_schema)

DEF_OBJ_PTR(SchemaItem,
            p_bool_then_schema,
            clear,
            empty,
            /**/,
            b_has_bool_then_schema,
            false,
            set_bool_then_schema,
            get_bool_then_schema)

DEF_VAR(long,
        object_n_max_properties,
        0,
        6,
        b_has_object_max_properties,
        false,
        set_object_max_properties,
        get_object_max_properties)

DEF_VAR(long,
        object_n_min_properties,
        0,
        6,
        b_has_object_min_properties,
        false,
        set_object_min_properties,
        get_object_min_properties)

DEF_OBJ(StdStringList,
        object_required,
        clear,
        empty,
        /**/,
        b_has_object_required,
        false,
        set_object_required,
        get_object_required)

DEF_OBJ(StdStringList,
        dependency_array,
        clear,
        empty,
        /**/,
        b_has_dependency_array,
        false,
        set_dependency_array,
        get_dependency_array)

DEF_OBJ(SchemaItemList,
        object_properties,
        clear,
        empty,
        /**/,
        b_has_object_properties,
        false,
        set_object_properties,
        get_object_properties)

DEF_OBJ(SchemaItemList,
        object_pattern_properties,
        clear,
        empty,
        /**/,
        b_has_object_pattern_properties,
        false,
        set_object_pattern_properties,
        get_object_pattern_properties)

DEF_OBJ(SchemaItemList,
        object_dependencies,
        clear,
        empty,
        /**/,
        b_has_object_dependencies,
        false,
        set_object_dependencies,
        get_object_dependencies)

DEF_VAR(std::string,
        description,
        "",
        "some JSON item",
        b_has_description,
        false,
        set_description,
        get_description)

DEF_VAR(std::string,
        ref,
        "",
        "shchema ref",
        b_has_ref,
        false,
        set_ref,
        get_ref)

DEF_OBJ(SchemaItemList,
        bool_one_of,
        clear,
        empty,
        /**/,
        b_has_bool_one_of,
        false,
        set_bool_one_of,
        get_bool_one_of)

DEF_OBJ(SchemaItemList,
        bool_any_of,
        clear,
        empty,
        /**/,
        b_has_bool_any_of,
        false,
        set_bool_any_of,
        get_bool_any_of)

DEF_OBJ(SchemaItemList,
        bool_all_of,
        clear,
        empty,
        /**/,
        b_has_bool_all_of,
        false,
        set_bool_all_of,
        get_bool_all_of)

DEF_OBJ(SchemaItemList,
        definitions_list,
        clear,
        empty,
        /**/,
        b_has_definitions,
        false,
        set_definitions,
        get_item_definitions)

DEF_VAR(bool,
        b_object_can_have_additional_properties,
        true,
        false,
        b_has_object_can_have_additional_properties,
        false,
        set_can_object_additional_properties,
        get_can_object_additional_properties)

DEF_OBJ(FormatType,
        format_type,
        clear,
        is_Unknown,
        jsonschemaenforcer::FormatType::type_Ipv4,
        b_has_format_type,
        false,
        set_format_type,
        get_format_type)

DEF_VAR(std::string,
        str_content_encoding,
        "",
        "base64",
        b_has_str_content_encoding,
        false,
        set_string_content_encoding,
        get_string_content_encoding)

DEF_VAR(std::string,
        str_content_media_type,
        "",
        "base64",
        b_has_str_content_media_type,
        false,
        set_string_content_media_type,
        get_string_content_media_type)

DEF_OBJ(JsonItem,
        json_default_value,
        clear,
        is_null,
        /**/,
        b_has_json_default_value,
        false,
        set_json_default_value,
        get_json_default_value)

DEF_VAR(bool,
        b_read_only,
        false,
        true,
        b_has_bool_read_only,
        false,
        set_bool_read_only,
        get_bool_read_only)

DEF_VAR(bool,
        b_write_only,
        false,
        true,
        b_has_bool_write_only,
        false,
        set_bool_write_only,
        get_bool_write_only)

DEF_OBJ(JsonItem,
        json_examples,
        clear,
        is_null,
        /**/,
        b_has_json_examples,
        false,
        set_json_examples,
        get_json_examples)

DEF_OBJ(ItemTypeSet,
        type_set,
        clear,
        empty,
        /**/,
        b_has_type_set,
        false,
        set_type_set,
        get_type_set)

DEF_FLAG(always_true,
         false,
         set_always_true,
         clear_always_true)

DEF_FLAG(additional_property,
         false,
         set_additional_property,
         clear_additional_property)

DEF_FLAG(property_names_schema,
         false,
         set_property_names_schema,
         clear_property_names_schema)

DEF_FLAG(array_singleton_item,
         false,
         set_array_singleton_item,
         clear_array_singleton_item)

DEF_FLAG(first_array_item,
         false,
         set_first_array_item,
         clear_first_array_item)

DEF_FLAG(additional_item,
         false,
         set_additional_item,
         clear_additional_item)
