// SchemaObject.hh
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

#ifndef __JSONSCHEMAENFORCER_SCHEMA_OBJECT_HH
#define __JSONSCHEMAENFORCER_SCHEMA_OBJECT_HH

namespace jsonschemaenforcer
{
    class SchemaObject;
    class ParsedItemData;
}

#include "config.h"
#include "SchemaItem.hh"
#include <list>

namespace jsonschemaenforcer
{
    class SchemaObject
    {
    public:
        SchemaObject();
        SchemaObject(const SchemaObject& s_obj);

        SchemaObject& operator =(const SchemaObject& s_obj);
        bool operator ==(const SchemaObject& s_obj) const;

        void clear();
        inline bool empty() const { return item_list.empty(); };
        void set_properties(const SchemaItemList& si_list);

    protected:
        SchemaItemList item_list;
    };

    typedef std::list<SchemaObject> SchemaObjectList;
}

#endif  // __JSONSCHEMAENFORCER_SCHEMA_OBJECT_HH
