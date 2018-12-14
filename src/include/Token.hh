// Token.hh
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

#ifndef __JSONSCHEMAENFORCER_TOKEN_HH
#define __JSONSCHEMAENFORCER_TOKEN_HH

#include "config.h"
#include "stddefs.hh"
#include <map>
#include <string>

namespace jsonschemaenforcer
{
    class Token
    {
    public:
        Token();
        Token(const Token& _token);
        Token(const std::string& _token_name,
              const std::string& _type,
              const std::string& _pattern,
              const std::string& _input_string,
              const std::string& _start_state,
              const std::string& _new_start_state,
              bool _pop_state,
              const std::string& _rule_body);

        Token& operator =(const Token& _token);
        bool operator ==(const Token& _token) const;
        inline bool operator !=(const Token& _token) const { return !(operator ==(_token)); };

        void clear();
        bool empty();

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        void func_set(const vtype& _##vname);            \
        inline const vtype& func_get() const { return vname; }; \
        inline bool has_##vname() const { return flag_name; };

#       include "Token-vars.hh"
#       undef DEF_VAR

    // protected:
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
        vtype vname;    \
        bool flag_name;

#       include "Token-vars.hh"
#       undef DEF_VAR
    };

    typedef std::map<StdStringPair, Token> StdStringTokenMap;
}
#endif   // __JSONSCHEMAENFORCER_TOKEN_HH
