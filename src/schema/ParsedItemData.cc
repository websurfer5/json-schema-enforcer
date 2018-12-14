// ParsedItemData.hh
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

#include "ParsedItemData.hh"

namespace jsonschemaenforcer
{
    ParsedItemData::ParsedItemData()
    {
        clear();
    }

    ParsedItemData::ParsedItemData(const ParsedItemData& idata)
    {
        this->operator =(idata);
    }

    ParsedItemData::~ParsedItemData()
    {
    }

    ParsedItemData& ParsedItemData::operator =(const ParsedItemData& idata)
    {
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
            vname = idata.vname; \
            flag_name = idata.flag_name;

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            vname = idata.vname; \
            flag_name = idata.flag_name;

#       define DEF_FLAG(fname, value, func_set, func_clear) \
            fname = idata.fname;

#       include "ParsedItemData-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG

        return *this;
    }

    ParsedItemData& ParsedItemData::operator |=(const ParsedItemData& idata)
    {
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
            if (idata.flag_name) \
                func_set(idata.vname);

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            if (idata.flag_name) \
                func_set(idata.vname);

#       define DEF_FLAG(fname, value, func_set, func_clear) \
            if (idata.is_##fname())                         \
                func_set();

#       include "ParsedItemData-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG

        return *this;
    }

    bool ParsedItemData::operator ==(const ParsedItemData& idata) const
    {
#       define DEF_FLAG(fname, value, func_set, func_clear) \
                && fname == idata.fname

#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
                && vname == idata.vname \
                && flag_name == idata.flag_name

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
                && vname == idata.vname \
                && flag_name == idata.flag_name

        return (true
#               include "ParsedItemData-vars.hh"
                );

#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG
    }

    void ParsedItemData::clear()
    {
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
            vname = value; \
            flag_name = flag_value;

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
            vname.initfunc(); \
            flag_name = flag_value;

#       define DEF_FLAG(fname, value, func_set, func_clear) \
            fname = value;

#       include "ParsedItemData-vars.hh"
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG
    }

    bool ParsedItemData::empty() const
    {
#       define DEF_VAR(vtype, vname, value, test_value, flag_name, flag_value, func_set, func_get) \
                || flag_name

#       define DEF_OBJ(objtype, vname, initfunc, emptyfunc, test_value, flag_name, flag_value, func_set, func_get) \
                || flag_name

#       define DEF_FLAG(fname, value, func_set, func_clear) \
                || fname

        return !(false
#               include "ParsedItemData-vars.hh"
               );
#       undef DEF_VAR
#       undef DEF_OBJ
#       undef DEF_FLAG
    }

    bool ParsedItemData::add_item_examples(const JsonItem &jitem)
    {
        bool success = false;

        if (jitem.is_array())
        {
            if (!b_has_examples)
            {
                success = true;
                set_item_examples(jitem);
            }
            else
                success = examples.append_array(jitem);
        }

        return success;
    }

    void ParsedItemData::set_item_type(const ItemType& _type)
    {
        b_has_type_set = true;
        type_set.clear();
        type_set.insert(_type);
    }
}
