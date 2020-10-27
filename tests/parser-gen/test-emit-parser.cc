// test-emit-parser.cc
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

#include <boost/test/unit_test.hpp>
#include "json-strings.hh"
#include "emit-parser-output-strings.hh"
#include "SchemaData.hh"
#include <sstream>
#include <utility>

BOOST_AUTO_TEST_SUITE( parser_gen_suite )

static bool check_output(jsonschemaenforcer::StdStringList& s_list, std::string ref)
{
    bool b_equal;
    std::ostringstream os;

    os << s_list;
    b_equal = (ref == os.str());
    BOOST_CHECK_EQUAL(ref.length(), os.str().length());

    if (!b_equal)
    {
        size_t len = std::min(ref.length(), os.str().length());

        for (size_t i=0; i < len; i++)
            if (ref[i] != os.str()[i])
            {
                BOOST_ERROR("Strings differ at position " + std::to_string(i) +  "\"" + ref + "\" != " + "\"" + os.str() +  "");
                break;
            }
    }

    return b_equal;
}

#define DEF_TEXT_TEST(fname, name)                                          \
BOOST_AUTO_TEST_CASE( test_parser_gen_##name )                              \
{                                                                           \
    jsonschemaenforcer::SchemaData sd;                                            \
    jsonschemaenforcer::StdStringList lexer_list,                                 \
                                parser_list,                                \
                                stype_list;                                 \
                                                                            \
    BOOST_REQUIRE(sd.parse_schema(str_parser_input_json_##name));           \
    sd.emit_source_code(parser_list,                                        \
                        lexer_list,                                         \
                        stype_list,                                         \
                        "foo",                                              \
                        "Bar",                                              \
                        "foo_foo_",                                         \
                        "lexer-" #fname ".hh",                              \
                        "parser-" #fname ".hh",                             \
                        "stype-" #fname ".hh");                             \
    BOOST_CHECK(check_output(lexer_list, str_output_text_lexer_##name));    \
    BOOST_CHECK(check_output(parser_list, str_output_text_parser_##name));  \
    BOOST_CHECK(check_output(stype_list, str_output_text_stype_##name));    \
}

#include "def-emit-parser-tests.hh"

BOOST_AUTO_TEST_SUITE_END()
