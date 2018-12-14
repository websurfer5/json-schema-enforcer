// ParsedItemData-defs.hh
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
// DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set)
// DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set)

DEF_VAR(bool,
        b_unique,
        false,
        true,
        b_has_unique,
        false,
        set_item_unique_items,
        get_item_unique_items)

DEF_VAR(bool,
        b_can_have_additional_properties,
        true,
        false,
        b_has_can_have_additional_properties,
        false,
        set_item_can_have_additional_properties,
        get_item_can_have_additional_properties)

DEF_VAR(double,
        exclusive_maximum,
        0,
        20.1,
        b_has_exclusive_maximum,
        false,
        set_item_exclusive_maximum,
        get_item_exclusive_maximum)

DEF_VAR(double,
        exclusive_minimum,
        0,
        9.9,
        b_has_exclusive_minimum,
        false,
        set_item_exclusive_minimum,
        get_item_exclusive_minimum)

DEF_VAR(double,
        maximum,
        0,
        123456,
        b_has_maximum,
        false,
        set_item_maximum,
        get_item_maximum)

DEF_VAR(double,
        minimum,
        0,
        -50,
        b_has_minimum,
        false,
        set_item_minimum,
        get_item_minimum)

DEF_VAR(double,
        multiple_of,
        0,
        5,
        b_has_multiple_of,
        false,
        set_item_multiple_of,
        get_item_multiple_of)

// DEF_OBJ(ItemType,
//         item_type,
//         clear,
//         is_Unknown,
//         jsonschemaenforcer::ItemType::type_String,
//         b_has_item_type,
//         false,
//         set_item_type,
//         get_item_type)

DEF_OBJ(FormatType,
        format_type,
        clear,
        is_Unknown,
        jsonschemaenforcer::FormatType::type_Ipv4,
        b_has_format_type,
        false,
        set_item_format_type,
        get_item_format_type)

DEF_OBJ(JsonItemList,
        contains,
        clear,
        empty,
        /**/,
        b_has_contains,
        false,
        set_item_contains,
        get_item_contains)

DEF_OBJ(JsonItemList,
        enum_list,
        clear,
        empty,
        /**/,
        b_has_enum,
        false,
        set_item_enum,
        get_item_enum)

DEF_VAR(long,
        max_items,
        0,
        30,
        b_has_max_items,
        false,
        set_item_max_items,
        get_item_max_items)

DEF_VAR(long,
        max_length,
        0,
        256,
        b_has_max_length,
        false,
        set_item_max_length,
        get_item_max_lengthh)

DEF_VAR(long,
        max_properties,
        0,
        6,
        b_has_max_properties,
        false,
        set_item_max_properties,
        get_item_max_properties)

DEF_VAR(long,
        min_properties,
        0,
        6,
        b_has_min_properties,
        false,
        set_item_min_properties,
        get_item_min_properties)

DEF_VAR(long,
        min_items,
        0,
        1,
        b_has_min_items,
        false,
        set_item_min_items,
        get_item_min_items)

DEF_VAR(long,
        min_length,
        0,
        10,
        b_has_min_length,
        false,
        set_item_min_length,
        get_item_min_length)

DEF_OBJ(SchemaItem,
        additional_items,
        clear,
        empty,
        /**/,
        b_has_additional_items,
        false,
        set_item_additional_items,
        get_item_additional_items)

DEF_OBJ(SchemaItem,
        additional_properties,
        clear,
        empty,
        /**/,
        b_has_additional_properties,
        false,
        set_item_additional_properties,
        get_item_additional_properties)

DEF_OBJ(SchemaItem,
        property_names,
        clear,
        empty,
        /**/,
        b_has_property_names,
        false,
        set_item_property_names,
        get_item_property_names)

DEF_OBJ(SchemaItemList,
        array_properties,
        clear,
        empty,
        /**/,
        b_has_array_properties,
        false,
        set_array_properties,
        get_array_properties)

DEF_OBJ(SchemaItemList,
        properties,
        clear,
        empty,
        /**/,
        b_has_properties,
        false,
        set_item_properties,
        get_item_properties)

DEF_OBJ(SchemaItemList,
        pattern_properties,
        clear,
        empty,
        /**/,
        b_has_pattern_properties,
        false,
        set_item_pattern_properties,
        get_item_pattern_properties)

DEF_VAR(std::string,
        description,
        "",
        "some JSON item",
        b_has_description,
        false,
        set_item_description,
        get_item_description)

DEF_VAR(std::string,
        id,
        "",
        "$foo",
        b_has_id,
        false,
        set_item_id,
        get_item_id)

DEF_VAR(std::string,
        key,
        "",
        "foo",
        b_has_key,
        false,
        set_key,
        get_key)

DEF_VAR(std::string,
        pattern,
        "",
        "test[123]+",
        b_has_pattern,
        false,
        set_item_pattern,
        get_item_pattern)

DEF_VAR(std::string,
        ref,
        "",
        "shchema ref",
        b_has_ref,
        false,
        set_item_ref,
        get_item_ref)

DEF_VAR(std::string,
        schema,
        "",
        "http://foo.bar",
        b_has_schema,
        false,
        set_item_schema,
        get_item_schema)

DEF_VAR(std::string,
        title,
        "",
        "Duchess",
        b_has_title,
        false,
        set_title,
        get_title)

DEF_OBJ(SchemaItemList,
        dependencies,
        clear,
        empty,
        /**/,
        b_has_dependencies,
        false,
        set_item_dependencies,
        get_item_dependencies)

DEF_OBJ(StdStringList,
        required,
        clear,
        empty,
        /**/,
        b_has_required,
        false,
        set_item_required,
        get_item_required)

DEF_OBJ(SchemaItemList,
        one_of,
        clear,
        empty,
        /**/,
        b_has_one_of,
        false,
        set_item_one_of,
        get_item_one_of)

DEF_OBJ(SchemaItemList,
        any_of,
        clear,
        empty,
        /**/,
        b_has_any_of,
        false,
        set_item_any_of,
        get_item_any_of)

DEF_OBJ(SchemaItemList,
        all_of,
        clear,
        empty,
        /**/,
        b_has_all_of,
        false,
        set_item_all_of,
        get_item_all_of)

DEF_OBJ(SchemaItemList,
        definitions_list,
        clear,
        empty,
        /**/,
        b_has_definitions,
        false,
        set_item_definitions,
        get_item_definitions)

DEF_OBJ(SchemaItem,
        not_schema,
        clear,
        empty,
        /**/,
        b_has_not_schema,
        false,
        set_item_not_schema,
        get_item_not_schema)

DEF_OBJ(SchemaItem,
        if_schema,
        clear,
        empty,
        /**/,
        b_has_if_schema,
        false,
        set_item_if_schema,
        get_item_if_schema)

DEF_OBJ(SchemaItem,
        else_schema,
        clear,
        empty,
        /**/,
        b_has_else_schema,
        false,
        set_item_else_schema,
        get_item_else_schema)

DEF_OBJ(SchemaItem,
        then_schema,
        clear,
        empty,
        /**/,
        b_has_then_schema,
        false,
        set_item_then_schema,
        get_item_then_schema)

DEF_VAR(std::string,
        content_encoding,
        "",
        "base64",
        b_has_content_encoding,
        false,
        set_item_content_encoding,
        get_item_content_encoding)

DEF_VAR(std::string,
        content_media_type,
        "",
        "base64",
        b_has_content_media_type,
        false,
        set_item_content_media_type,
        get_item_content_media_type)

DEF_OBJ(JsonItem,
        default_value,
        clear,
        is_null,
        /**/,
        b_has_default_value,
        false,
        set_item_default_value,
        get_item_default_value)

DEF_VAR(bool,
        b_read_only,
        false,
        true,
        b_has_read_only,
        false,
        set_item_read_only,
        get_item_read_only)

DEF_VAR(bool,
        b_write_only,
        false,
        true,
        b_has_write_only,
        false,
        set_item_write_only,
        get_item_write_only)

DEF_OBJ(JsonItem,
        examples,
        clear,
        is_null,
        /**/,
        b_has_examples,
        false,
        set_item_examples,
        get_item_examples)

DEF_OBJ(StdStringList,
        type_list,
        clear,
        empty,
        /**/,
        b_has_type_list,
        false,
        set_item_type_list,
        get_item_type_list)

DEF_OBJ(ItemTypeSet,
        type_set,
        clear,
        empty,
        /**/,
        b_has_type_set,
        false,
        set_item_type_set,
        get_item_type_set)

DEF_FLAG(items_always_true,
         false,
         set_items_always_true,
         clear_items_always_true)
