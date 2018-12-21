// SchemaData.hh
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

#ifndef __JSONSCHEMAENFORCER_SCHEMA_DATA_HH
#define __JSONSCHEMAENFORCER_SCHEMA_DATA_HH

#include "config.h"
#include "ItemType.hh"
#include "SchemaItem.hh"
#include "stddefs.hh"
#include "Token.hh"
#include "yyscan.hh"
#include <string>

namespace jsonschemaenforcer
{
    class SchemaData{
    public:
        SchemaData();
        SchemaData(const SchemaData&) = delete;

        bool qs_has_cr_or_lf;
        int nesting_level;
        std::string last_key,
                    quoted_str;
        SchemaItem root_item;
        yyscan_t scaninfo;
        void *input_bp;

        void add_lexer_rule(const std::string& pattern,
                            const std::string& start_state,
                            const std::string& new_start_state,
                            bool pop_state,
                            const std::string& body);
        void add_lexer_include(const std::string& header,
                               bool b_system);
        void add_parser_include(const std::string& header,
                                bool b_system);
        void add_stype_include(const std::string& header,
                               bool b_system);
        const std::string&  add_parser_rule(const std::string& tag_prefix,
                                            const std::string& rule_body,
                                            bool generate_new_tag = true);
        inline void add_start_state(const std::string& start_state)
        {
            if (!start_state.empty() && start_state != "INITIAL")
                start_state_set.insert(start_state);
        };
        std::string add_token(const std::string& token_name,
                              const std::string& token_type,
                              bool data_is_object,
                              const std::string& token_type_header,
                              bool is_system_header,
                              const std::string& pattern,
                              const std::string& input_string,
                              const std::string& start_state = "INITIAL",
                              const std::string& new_start_state = "",
                              bool pop_state = false,
                              const std::string& body = "");
        inline std::string add_token(const std::string& token_name,
                                     const std::string& token_type,
                                     bool data_is_object,
                                     const std::string& pattern,
                                     const std::string& input_string,
                                     const std::string& start_state = "INITIAL",
                                     const std::string& new_start_state = "",
                                     bool pop_state = false,
                                     const std::string& body = "")
        {
            return add_token(token_name,
                             token_type,
                             data_is_object,
                             "",
                             false,
                             pattern,
                             input_string,
                             start_state,
                             new_start_state,
                             pop_state,
                             body);
        };
        std::string add_token(const std::string& pattern,
                              const std::string& start_state,
                              const std::string& new_start_state);
        void clear_gen_parser_vars();
        void emit_lexer(StdStringList& lexer_list,
                        const std::string& name_space,
                        const std::string& class_name,
                        const std::string& func_prefix,
                        const std::string& lexer_header_fname,
                        const std::string& parser_header_fname,
                        const std::string& stype_header_fname);
        void emit_type_definitions(StdStringList& parser_type_list,
                                   const std::string& func_prefix,
                                   const std::string& stype_header_fname);
        void emit_parser(StdStringList& parser_list,
                         const std::string& name_space,
                         const std::string& class_name,
                         const std::string& func_prefix,
                         const std::string& lexer_header_fname,
                         const std::string& stype_header_fname,
                         const std::string& start_rule);
        void emit_source_code(StdStringList& parser_list,
                              StdStringList& lexer_list,
                              StdStringList& parser_type_list,
                              const std::string& name_space,
                              const std::string& class_name,
                              const std::string& func_prefix,
                              const std::string& lexer_header_fname,
                              const std::string& parser_header_fname,
                              const std::string& stype_header_fname);
        inline const SchemaItem& get_integer_item() const { return integer_item; };
        inline const std::string& get_namespace() const { return class_namespace; };
        inline const SchemaItem& get_number_item() const { return number_item; };
        inline const SchemaItem& get_object_item() const { return object_item; };
        inline const SchemaItem& get_string_item() const { return string_item; };
        bool get_token(const std::string& start_state,
                       const std::string& pattern,
                       Token& t) const;
        std::string helper_func_name(const std::string& return_type,
                                     const std::string& name_prefix,
                                     const std::string& params,
                                     const std::string& body,
                                     bool parser_prototype);
        inline bool is_initial_start_state(const std::string& state) const { return (state.empty() || state == "INITIAL"); };
        // inline unsigned new_helper_func_number() { return next_helper_func_number++; };
        inline std::string new_parse_key_state() { std::string t = new_symbol("PARSE_KEY"); add_start_state(t); return t; };
        // inline std::string new_start_state() { std::string t = "SSTATE_" + std::to_string(new_start_state_number()); add_start_state(t); return t; };
        inline std::string new_start_state() { std::string t = new_symbol("SSTATE"); add_start_state(t); return t; };
        // inline unsigned new_start_state_number() { return next_start_state_number++; };
        std::string new_symbol(const std::string& prefix);
        // inline unsigned new_token_number() { return next_token_number++; };
        inline std::string new_token_tag(const std::string& t = std::string("TOKEN")) { return new_symbol(t); };
        bool parse_schema(const std::string& str);
        inline void set_function_prefix(const std::string& func_prefix) { function_prefix = func_prefix; };
        inline void set_namespace(const std::string& _name_space) { class_namespace = _name_space; };
        void set_root_item(const SchemaItem& sitem) { root_item = sitem; };
        inline void set_rule_type(const std::string& rule_tag,
                                  const std::string& data_type,
                                  bool data_is_object)
        {
                set_rule_type(rule_tag, data_type, data_is_object, "", false);
        };
        void set_rule_type(const std::string& rule_tag,
                           const std::string& data_type,
                           bool data_is_object,
                           const std::string& header_file,
                           bool is_system_header = false);
        std::string toupper(const std::string lower, bool b_safe) const;
        std::string unput_string_func_name();

    protected:
        std::string indent_block(const std::string& prefix, const std::string& block) const;

        SchemaItem integer_item,
                   number_item,
                   object_item,
                   string_item;
        std::string class_namespace,
                    function_prefix;
        StdStringBoolMap lexer_include_map,
                         parser_include_map,
                         stype_include_map;
        StdStringUnsignedMap next_symbol_number_map;
        StdStringMap obj_type_map,
                     parser_rule_tag_map,
                     rule_type_map,
                     token_type_map,
                     var_type_map;
        StdStringSet start_state_set;
        StdStringTokenMap token_map;
        StdStringTuple5StringMap helper_func_map;
        // unsigned next_helper_func_number,
                 // next_parse_key_state_number,
                 // next_start_state_number,
                 // next_token_number;
    };

    bool schema_parser_set_input_buffer(SchemaData& sd, const char *str);
}

#endif  // __JSONSCHEMAENFORCER_SCHEMA_DATA_HH
