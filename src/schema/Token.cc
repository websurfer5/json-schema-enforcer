// Token.cc
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
#include "Token.hh"

namespace jsonschemaenforcer
{
    Token::Token()
    {
        clear();
    }

    Token::Token(const Token& _token)
    {
        this->operator =(_token);
    }

    Token::Token(const std::string& _token_name,
                 const std::string& _type,
                 const std::string& _pattern,
                 const std::string& _input_string,
                 const std::string& _start_state,
                 const std::string& _new_start_state,
                 bool _pop_state,
                 const std::string& _rule_body)
    {
        clear();
        set_name(_token_name);
        set_type(_type);
        set_pattern(_pattern);
        set_input_string(_input_string);
        set_start_state(_start_state);
        set_new_start_state(_new_start_state);
        set_pop_state(_pop_state);
        set_rule_body(_rule_body);
    }

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        vname = value;  \
        flag_name = flag_value;

    void Token::clear()
    {
#       include "Token-vars.hh"
    }

#       undef DEF_VAR

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
                 || has_##vname()

    bool Token::empty()
    {
        return !(false
#                include "Token-vars.hh"
                 );
    }

#       undef DEF_VAR

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        vname = _token.vname;   \
        flag_name = _token.flag_name;

    Token& Token::operator =(const Token& _token)
    {
#       include "Token-vars.hh"
        return *this;
    }
#       undef DEF_VAR

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
                 && vname == _token.vname   \
                 && flag_name == _token.flag_name

    bool Token::operator ==(const Token& _token) const
    {
        return (true
#               include "Token-vars.hh"
                );
    }
#   undef DEF_VAR

#   define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
    void Token::func_set(const vtype& _##vname)             \
    {                                                       \
        flag_name = true;                                   \
        vname = _##vname;                                   \
    }

#   include "Token-vars.hh"
#   undef DEF_VAR
}
