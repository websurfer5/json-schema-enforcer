// Token-vars.hh
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

DEF_VAR(std::string,
        token_name,
        "",
        "foo",
        b_has_name,
        false,
        set_name,
        get_name)

DEF_VAR(std::string,
        type,
        "",
        "bar",
        b_has_type,
        false,
        set_type,
        get_type)

DEF_VAR(std::string,
        pattern,
        "",
        "some-pattern",
        b_has_pattern,
        false,
        set_pattern,
        get_pattern)

DEF_VAR(std::string,
        input_string,
        "",
        "std::stol(yytext)",
        b_has_input_string,
        false,
        set_input_string,
        get_input_string)

DEF_VAR(std::string,
        start_state,
        "",
        "SomeState",
        b_has_start_state,
        false,
        set_start_state,
        get_start_state)

DEF_VAR(std::string,
        new_start_state,
        "",
        "SomeOtherState",
        b_has_new_start_state,
        false,
        set_new_start_state,
        get_new_start_state)

DEF_VAR(bool,
        pop_state,
        false,
        true,
        b_has_pop_state,
        false,
        set_pop_state,
        get_pop_state)

DEF_VAR(std::string,
        rule_body,
        "",
        "do { something(); } while (!busy); ",
        b_has_rule_body,
        false,
        set_rule_body,
        get_rule_body)