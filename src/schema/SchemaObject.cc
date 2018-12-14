// SchemaObject.cc
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
#include "SchemaObject.hh"

namespace jsonschemaenforcer
{
    SchemaObject::SchemaObject()
    {
        clear();   
    }

    SchemaObject::SchemaObject(const SchemaObject& s_obj)
    {
        this->operator =(s_obj);
    }

    SchemaObject& SchemaObject::operator =(const SchemaObject& s_obj)
    {
        item_list = s_obj.item_list;
        return *this;
    }

    bool SchemaObject::operator ==(const SchemaObject& s_obj) const
    {
        return (item_list == s_obj.item_list);
    }

    void SchemaObject::clear()
    {
        item_list.clear();
    }

    void SchemaObject::set_properties(const SchemaItemList& si_list)
    {
        item_list = si_list;
    }
}
