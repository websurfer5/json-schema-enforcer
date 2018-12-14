// SchemaData.cc
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

namespace jsonschemaenforcer
{
    class SchemaData;
}

#include "config.h"
#include "schema-stype.hh"
#include "schema-parser.hh"
#include "schema-lexer.hh"
#include "SchemaData.hh"
#include <cctype>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <string>

namespace jsonschemaenforcer
{
    SchemaData::SchemaData()
    {
        root_item.clear();
        integer_item.clear();
        integer_item.add_item_type(ItemType::type_Integer);
        number_item.clear();
        number_item.add_item_type(ItemType::type_Number);
        object_item.clear();
        object_item.add_item_type(ItemType::type_Object);
        string_item.clear();
        string_item.add_item_type(ItemType::type_String);
        input_bp = NULL;
        nesting_level = 0;
        qs_has_cr_or_lf = false;
        scaninfo = NULL;
        clear_gen_parser_vars();
    }

    bool SchemaData::parse_schema(const std::string& str)
    {
        bool success = false;
        char *scanbuffer;
        int i;

        if (schema_parser_lex_init_extra(this, &scaninfo))
        {
            std::cerr << "schema_parser_lex_init_extra failed" << strerror(errno) << std::endl;
            return false;
        }

        scanbuffer = new char[str.length()+2];
        strncpy(scanbuffer, str.c_str(), str.length());
        scanbuffer[str.length()+1] = '\0';

        if (!schema_parser_set_input_buffer(*this, scanbuffer))
        {
            std::cerr << "failed to set input buffer" << std::endl;
            delete scanbuffer;
            return false;
        }

        switch (i = schema_parser_parse(this))
        {
            case 0 :
                // success
                success = true;
                break;

            case 1 :
                std::cerr << "schema parsing stopped due to invalid input" << std::endl;
                break;

            case 2 :
                std::cerr << "schema parser exhausted memory" << std::endl;
                break;

            case 3 :
                std::cerr << "unknown schema parser error: " << i << std::endl;
                break;
        }

        schema_parser__delete_buffer((YY_BUFFER_STATE) input_bp, scaninfo);
        input_bp = NULL;
        schema_parser_lex_destroy(scaninfo);
        delete scanbuffer;

        return success;
    }

    void SchemaData::clear_gen_parser_vars()
    {
        class_namespace.clear();
        function_prefix.clear();
        helper_func_map.clear();
        next_symbol_number_map.clear();
        obj_type_map.clear();
        parser_include_map.clear();
        parser_rule_tag_map.clear();
        rule_type_map.clear();
        start_state_set.clear();
        stype_include_map.clear();
        token_map.clear();
        token_type_map.clear();
        var_type_map.clear();
    }

    void SchemaData::emit_type_definitions(StdStringList& parser_type_list,
                                           const std::string& func_prefix,
                                           const std::string& stype_header_fname)
    {
        StdStringBoolMap::const_iterator csb_it;
        StdStringMap::const_iterator c_it;
        std::string close_quote,
                    guard_macro,
                    open_quote,
                    upper_func_prefix;

        upper_func_prefix = toupper(func_prefix, false) + "STYPE";
        guard_macro = "__" + toupper(stype_header_fname, true);

        parser_type_list.push_back(
                "#ifndef " + guard_macro + "\n"
                "#define " + guard_macro + "\n"
                "\n");

        for (csb_it = stype_include_map.begin(); csb_it != stype_include_map.end(); csb_it++)
        {
            close_quote = csb_it->second ? '>' : '\"';
            open_quote = csb_it->second ? '<' : '\"';
            parser_type_list.push_back("#include " + open_quote + csb_it->first + close_quote + "\n");
        }

        parser_type_list.push_back(
                "\n"
                "struct " + upper_func_prefix + "\n"
                "{\n");

        for (c_it = var_type_map.begin(); c_it != var_type_map.end(); c_it++)
        {
            parser_type_list.push_back("    " + c_it->first + " " + c_it->second + ";\n");
        }

        for (c_it = obj_type_map.begin(); c_it != obj_type_map.end(); c_it++)
        {
            parser_type_list.push_back("    " + c_it->first + " " + c_it->second + ";\n");
        }

        parser_type_list.push_back(
                "};\n"
                "\n"
                "typedef struct " + upper_func_prefix + " " + upper_func_prefix + ";\n"
                "#endif  // " + guard_macro + "\n");
    }

    std::string SchemaData::indent_block(const std::string& prefix, const std::string& block) const
    {
        size_t pos1 = 0,
               pos2 = 0;
        std::string new_block;

        while (pos1 < block.length())
        {
            pos2 = block.find_first_of('\n', pos1);

            if (pos2 == std::string::npos)
                pos2 = block.length();

            new_block += prefix + "\t    " + block.substr(pos1, pos2-pos1) + "\n";
            pos1 = pos2 + 1;
        }

        return new_block;
    }

    void SchemaData::emit_lexer(StdStringList& lexer_list,
                                const std::string& name_space,
                                const std::string& class_name,
                                const std::string& func_prefix,
                                const std::string& lexer_header_fname,
                                const std::string& parser_header_fname,
                                const std::string& stype_header_fname)
    {
        std::string pattern,
                    rule,
                    spaces;
        StdStringSet::const_iterator s_it;
        StdStringTokenMap::const_iterator t_it;
        StdStringTuple5StringMap::const_iterator tm_it;

        if (!func_prefix.empty())
            lexer_list.push_back("%option prefix=\"" + func_prefix + "\"\n");

        lexer_list.push_back("%option extra-type=\"" +
                             (name_space.empty()
                                ? std::string()
                                : name_space + "::")
                             + class_name + " *\"\n");
        lexer_list.push_back("%option noyywrap nodefault yylineno reentrant bison-bridge stack\n"
                             "\n"
                             "%{\n");

        if (!name_space.empty())
            lexer_list.push_back("namespace " + name_space + "\n"
                                 "{\n"
                                 "    ");

        lexer_list.push_back("class " + class_name + ";\n");

        if (!name_space.empty())
            lexer_list.push_back("}\n"
                                 "\n");

        lexer_list.push_back("#include <string>\n"
                             "#include \"" + class_name + ".hh\"\n"
                             "#include \"" + stype_header_fname + "\"\n"
                             "#include \"" + parser_header_fname + "\"\n"
                             "\n");
        for (tm_it = helper_func_map.begin(); tm_it != helper_func_map.end(); tm_it++) 
            lexer_list.push_back((std::get<4>(tm_it->first)
                                            ? "   extern "
                                            : "   static ") + std::get<0>(tm_it->first) + " " + tm_it->second + "(" + std::get<2>(tm_it->first) + ");\n");

        lexer_list.push_back("%}\n"
                             "\n");

        for (s_it = start_state_set.begin(); s_it != start_state_set.end(); s_it++)
            lexer_list.push_back("%x " + *s_it + "\n");

        lexer_list.push_back("\n%%\n");

        for (t_it = token_map.begin(); t_it != token_map.end(); t_it++)
        {
            if (is_initial_start_state(t_it->second.get_start_state()))
                pattern = t_it->second.get_pattern();
            else
                pattern = '<' + t_it->second.get_start_state() + '>' + t_it->second.get_pattern();

            spaces = std::string(pattern.length()+2, ' ');
            rule = pattern + "  \t{\n";

            if (t_it->second.get_pop_state())
            {
                if (!t_it->second.get_new_start_state().empty())
                    rule += spaces + "\t    BEGIN " + t_it->second.get_new_start_state() + ";\n";
                else
                    rule += spaces + "\t    yy_pop_state(yyextra->scaninfo);\n";
            } else if (!t_it->second.get_new_start_state().empty())
                rule += spaces + "\t    yy_push_state(" + t_it->second.get_new_start_state() + ", yyextra->scaninfo);\n";

            if (!t_it->second.get_type().empty())
            {
                if (t_it->second.get_input_string().empty())
                    rule += spaces + "\t    yylval->" + t_it->second.get_type() + " = yytext;\n";
                else
                    rule += spaces + "\t    yylval->" + t_it->second.get_type() + " = " + t_it->second.get_input_string() + ";\n";
            }

            if (!t_it->second.get_rule_body().empty())
                rule += indent_block(spaces, t_it->second.get_rule_body());

            if (!t_it->second.get_name().empty())
                rule += spaces + "\t    return " + t_it->second.get_name() + ";\n";

            rule += spaces + "\t}\n";
            lexer_list.push_back(rule);
        }

        lexer_list.push_back("\n"
                             "%%\n"
                             "\n");

        for (tm_it = helper_func_map.begin(); tm_it != helper_func_map.end(); tm_it++) 
        {
            lexer_list.push_back((std::get<4>(tm_it->first)
                                    ? ""
                                    : "static ") + std::get<0>(tm_it->first) + " " + tm_it->second + "(" + std::get<2>(tm_it->first) + ")\n"
                                 + "{\n");
            lexer_list.push_back(indent_block("", std::get<3>(tm_it->first)));
            lexer_list.push_back("}\n"
                                 "\n");
        }
    }

    void SchemaData::emit_source_code(StdStringList& parser_list,
                                      StdStringList& lexer_list,
                                      StdStringList& parser_type_list,
                                      const std::string& name_space,
                                      const std::string& class_name,
                                      const std::string& func_prefix,
                                      const std::string& lexer_header_fname,
                                      const std::string& parser_header_fname,
                                      const std::string& stype_header_fname)
    {
        std::string start_rule;

        clear_gen_parser_vars();
        set_function_prefix(func_prefix);
        set_namespace(name_space);
        add_stype_include(class_name + ".hh", false);
        start_rule = root_item.emit_parser(*this, "INITIAL");
        emit_type_definitions(parser_type_list, func_prefix, stype_header_fname);
        emit_lexer(lexer_list,
                   name_space,
                   class_name,
                   func_prefix,
                   lexer_header_fname,
                   parser_header_fname,
                   stype_header_fname);
        emit_parser(parser_list,
                    name_space,
                    class_name,
                    func_prefix,
                    lexer_header_fname,
                    stype_header_fname,
                    start_rule);
    }

    void SchemaData::emit_parser(StdStringList& parser_list,
                                 const std::string& name_space,
                                 const std::string& class_name,
                                 const std::string& func_prefix,
                                 const std::string& lexer_header_fname,
                                 const std::string& stype_header_fname,
                                 const std::string& start_rule)
    {
        std::string rule_type;
        StdStringBoolMap::const_iterator sbm_it;
        StdStringMap::const_iterator c_it;
        StdStringTuple5StringMap::const_iterator tm_it;

        // emit_class_header();

        add_parser_include("string", true);
        parser_list.push_back("%{\n");

        if (!name_space.empty())
            parser_list.push_back("namespace " + name_space + "\n"
                                  "{\n"
                                  "    ");

        parser_list.push_back("class " + class_name + ";\n");

        if (!name_space.empty())
            parser_list.push_back("}\n");

        parser_list.push_back("%}\n"
                              "\n"
                              "%define api.prefix {" + func_prefix + "}\n"
                              "%define api.pure full\n"
                              "%define parse.lac full\n"
                              "%error-verbose\n"
                              "\n"
                              "%{\n");

        parser_list.push_back("#include \"" + stype_header_fname + "\"\n"
                              "#include \"" + lexer_header_fname + "\"\n"
                              "#include \"" + class_name + ".hh\"\n");

        for (sbm_it = parser_include_map.cbegin(); sbm_it != parser_include_map.cend(); sbm_it++)
        {
            parser_list.push_back(std::string("#include ")
                                              + (sbm_it->second
                                                    ? "<"
                                                    : "\"")
                                              + sbm_it->first
                                              + (sbm_it->second
                                                    ? ">"
                                                    : "\"")
                                              + "\n");
        }

        parser_list.push_back("\n");

        for (tm_it = helper_func_map.cbegin(); tm_it != helper_func_map.cend(); tm_it++)
        {
            if (std::get<4>(tm_it->first))
                parser_list.push_back("extern " + std::get<0>(tm_it->first) + " " + tm_it->second + "(" + std::get<2>(tm_it->first) + ");\n");
        }

        parser_list.push_back("%}\n"
                             "\n");

        for (c_it = token_type_map.begin(); c_it != token_type_map.end(); c_it++)
        {
            if (c_it->second.empty())
                parser_list.push_back("%token " + c_it->first + "\n");
            else
                parser_list.push_back("%token <" + c_it->second + "> " + c_it->first + "\n");
        }

        parser_list.push_back("\n");

        for (c_it = rule_type_map.begin(); c_it != rule_type_map.end(); c_it++)
        {
            parser_list.push_back("%type <" + c_it->second + "> " + c_it->first + "\n");
        }

        parser_list.push_back("\n");

        for (c_it = obj_type_map.begin(); c_it != obj_type_map.end(); c_it++)
        {
            parser_list.push_back("%destructor { $$.clear(); } <" + c_it->second + ">;\n");
        }

        parser_list.push_back("\n"
                              "%start " + start_rule + "\n");
        parser_list.push_back("\n"
                              "%%\n"
                              "\n");

        for (c_it = parser_rule_tag_map.begin(); c_it != parser_rule_tag_map.end(); c_it++)
        {
            parser_list.push_back(c_it->second + ":\n");
            parser_list.push_back(c_it->first);
        }
    }

    const std::string& SchemaData::add_parser_rule(const std::string& tag_prefix,
                                                   const std::string& rule_body,
                                                   bool generate_new_tag)
    {
        std::string rule_tag;
        StdStringMap::const_iterator c_it = parser_rule_tag_map.find(rule_body);

        if (c_it != parser_rule_tag_map.end())
            return c_it->second;

        if (generate_new_tag)
            rule_tag = new_symbol(tag_prefix);
        else
            rule_tag = tag_prefix;

        return (parser_rule_tag_map[rule_body] = rule_tag);
    }

    std::string SchemaData::add_token(const std::string& pattern,
                                      const std::string& start_state,
                                      const std::string& new_start_state)
    {
        return add_token(new_token_tag(), "", false, pattern, "", start_state, new_start_state);
    }

    std::string SchemaData::add_token(const std::string& token_name,
                                      const std::string& token_type,
                                      bool data_is_object,
                                      const std::string& token_type_header,
                                      bool is_system_header,
                                      const std::string& pattern,
                                      const std::string& input_string,
                                      const std::string& start_state,
                                      const std::string& new_start_state,
                                      bool pop_state,
                                      const std::string& body)
    {
        std::string type;

        if (!token_type.empty())
        {
            type = token_type + "_type";

            for (std::string::iterator it = type.begin(); it != type.end(); it++)
                if (*it == ':')
                    *it = '_';

            if (!token_type.empty())
            {
                if (data_is_object)
                    obj_type_map[token_type] = type;
                else
                    var_type_map[token_type] = type;
            }
        }

        token_map[StdStringPair(start_state, pattern)] = Token(token_name,
                                                               type,
                                                               pattern,
                                                               input_string,
                                                               start_state,
                                                               new_start_state,
                                                               pop_state,
                                                               body);
        token_type_map[token_name] = type;
        add_start_state(start_state);
        add_start_state(new_start_state);
        add_stype_include(token_type_header, is_system_header);
        return token_name;
    }

    void SchemaData::set_rule_type(const std::string& rule_tag,
                                   const std::string& data_type,
                                   bool data_is_object,
                                   const std::string& header_file,
                                   bool is_system_header)
    {
        std::string type = data_type + "_type";

        for (std::string::iterator it = type.begin(); it != type.end(); it++)
            if (*it == ':')
                *it = '_';
        
        if (!data_type.empty())
        {
            if (data_is_object)
                obj_type_map[data_type] = type;
            else
                var_type_map[data_type] = type;
        }

        rule_type_map[rule_tag] = type;
        add_stype_include(header_file, is_system_header);
    }

    void SchemaData::add_lexer_rule(const std::string& pattern,
                                    const std::string& start_state,
                                    const std::string& new_start_state,
                                    bool pop_state,
                                    const std::string& body)
    {
        token_map[StdStringPair(start_state, pattern)] = Token("",
                                                               "",
                                                               pattern,
                                                               "",
                                                               start_state,
                                                               new_start_state,
                                                               pop_state,
                                                               body);
        add_start_state(start_state);
        add_start_state(new_start_state);
    }

    std::string SchemaData::helper_func_name(const std::string& return_type,
                                             const std::string& name_prefix,
                                             const std::string& params,
                                             const std::string& body,
                                             bool parser_prototype)
    {
        std::string name;
        StdStringTuple5 key(return_type, function_prefix + name_prefix, params, body, parser_prototype);
        StdStringTuple5StringMap::const_iterator c_it;

        c_it = helper_func_map.find(key);

        if (c_it != helper_func_map.end())
            return c_it->second;

        name = new_symbol(function_prefix + name_prefix);
        helper_func_map[key] = name;
        return name;
    }
    
    bool SchemaData::get_token(const std::string& start_state,
                               const std::string& pattern,
                               Token& t) const
    {
        bool found;
        StdStringTokenMap::const_iterator it;

        it = token_map.find(StdStringPair(start_state, pattern));
        found = (it != token_map.end());

        if (found)
            t = it->second;
        else
            t.clear();

        return found;
    }

    std::string SchemaData::new_symbol(const std::string& prefix)
    {
        return (prefix + "_" + std::to_string(next_symbol_number_map[prefix]++));
    }

    void SchemaData::add_parser_include(const std::string& header,
                                        bool b_system)
    {
        parser_include_map[header] = b_system;
    }

    void SchemaData::add_stype_include(const std::string& header,
                                       bool b_system)
    {
        if (!header.empty())
            stype_include_map[header] = b_system;
    }

    std::string SchemaData::toupper(const std::string lower, bool b_safe) const
    {
        size_t i;
        std::string upper;

        upper.reserve(lower.length());

        for (i=0; i < lower.length(); i++)
        {
            if (b_safe)
            {
                if (std::isalnum(lower[i]))
                    upper += std::toupper(lower[i]);
                else
                    upper += '_';
            }
            else
                upper += std::toupper(lower[i]);
        }

        return upper;
    }
}
