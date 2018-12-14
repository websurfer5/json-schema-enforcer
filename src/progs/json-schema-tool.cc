// json-schema-tool.cc
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
#include "tests/include/json-strings.hh"
#include <fstream>
#include <iostream>

bool gen_files(const std::string path, const std::string suffix, const std::string& input_str)
{
    jsonschemaenforcer::SchemaData sd;
    jsonschemaenforcer::StdStringList lexer_list,
                                parser_list,
                                parser_type_list;
    std::ofstream f;
    std::string fname;

    std::cout << "----" << std::endl;

    if (!sd.parse_schema(input_str))
    {
        std::cout << "error processing " << suffix << std::endl;
        return false;
    }

    sd.emit_source_code(parser_list,
                        lexer_list,
                        parser_type_list,
                        "foo",
                        "Bar",
                        "foo_foo_",
                        "lexer-" + suffix + ".hh",
                        "parser-" + suffix + ".hh",
                        "stype-" + suffix + ".hh");
    // output_strings(lexer_list);
    // std::cout << parser_type_list << std::endl << "----" << std::endl;
    // std::cout << lexer_list << std::endl << "----" << std::endl;
    // std::cout << parser_list << std::endl << "----" << std::endl;

    f.exceptions(std::ios::failbit | std::ios::badbit);

    try
    {
        fname = path + "lexer-" + suffix + ".ll";
        f.open(fname, std::ofstream::trunc);
        f << lexer_list;
        f.close();

        fname = path + "stype-" + suffix + ".hh";
        f.open(fname, std::ofstream::trunc);
        f << parser_type_list;
        f.close();

        fname = path + "parser-" + suffix + ".yy";
        f.open(fname, std::ofstream::trunc);
        f << parser_list;
        f.close();
    }
    catch (std::ios_base::failure& e)
    {
        std::cerr << fname << e.code() << ": " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool gen_output(const std::string& input_str, const std::string& suffix)
{
    jsonschemaenforcer::SchemaData sd;
    jsonschemaenforcer::StdStringList lexer_list,
                                parser_list,
                                parser_type_list;
    std::ofstream f;
    std::string fname;

    std::cout << "----" << std::endl;

    if (!sd.parse_schema(input_str))
    {
        std::cout << "error processing " << suffix << std::endl;
        return false;
    }

    sd.emit_source_code(parser_list,
                        lexer_list,
                        parser_type_list,
                        "foo",
                        "Bar",
                        "foo_foo_",
                        "lexer-" + suffix + ".hh",
                        "parser-" + suffix + ".hh",
                        "stype-" + suffix + ".hh");
    std::cout << parser_type_list << std::endl << "----" << std::endl;
    std::cout << lexer_list << std::endl << "----" << std::endl;
    std::cout << parser_list << std::endl << "----" << std::endl;
    return true;
}

int main(int argc, char **argv, char **env)
{
    std::string path,
                suffix;

    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " testname destpath" << std::endl;
        return 1;
    }

    suffix = argv[1];

    for (size_t i=0; i < suffix.length(); i++)
        if (suffix[i] == '-')
            suffix[i] = '_';

    if (argc == 3)
    {
        path = argv[2];

        if (!path.empty())
        {
            if (*path.rbegin() != '/')
                path += "/";
        }

#   define DEF_TEXT_TEST(name)                  \
        if (suffix.compare(#name) == 0)         \
            if (!gen_files(path, argv[1], str_parser_input_json_##name))    \
                return 1;

#   include "def-emit-parser-json-input.hh"

/*
#   define DEF_TEXT_TEST(name)                                 \
        std::cout << #name << std::endl;

#   include "def-emit-parser-json-input.hh"

#   undef DEF_TEXT_TEST
#   define DEF_TEXT_TEST(name)                                 \
        suffix = #name;                                         \
                                                                \
        for (size_t i=0; i < suffix.length(); i++)              \
            if (suffix[i] == '_')                               \
                suffix[i] = '-';                                \
                                                                \
        if (!gen_files(path, suffix, str_parser_input_json_##name))  \
            return 1;

#   include "def-emit-parser-json-input.hh"
*/
    }
    else if (argc == 2)
    {
#   undef DEF_TEXT_TEST
#   define DEF_TEXT_TEST(name)                  \
        if (suffix.compare(#name) == 0)         \
            if (!gen_output(str_parser_input_json_##name, argv[1]))    \
                return 1;

#   include "def-emit-parser-json-input.hh"
    }

    return 0;
}
