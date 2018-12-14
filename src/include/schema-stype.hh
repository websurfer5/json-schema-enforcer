// schema-stype.hh
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

#ifndef __JSONSCHEMAENFORCER_SCHEMA_STYPE_HH
#define __JSONSCHEMAENFORCER_SCHEMA_STYPE_HH

#include "config.h"
#include "FormatType.hh"
#include "ItemType.hh"
#include "JsonItem.hh"
#include "ParsedItemData.hh"
#include "SchemaItem.hh"
#include "SchemaObject.hh"
#include "stddefs.hh"
#include <string>

struct SCHEMA_PARSER_STYPE
{
    bool bval;
    double dval;
    jsonschemaenforcer::FormatType        format_type;
    jsonschemaenforcer::ItemType          itype;
    jsonschemaenforcer::JsonItem          jitem;
    jsonschemaenforcer::JsonItemList      jitem_list;
    jsonschemaenforcer::JsonItemMap       jitem_map;
    jsonschemaenforcer::ParsedItemData    idata;
    jsonschemaenforcer::SchemaItem        sitem;
    jsonschemaenforcer::SchemaItemList    sitemlist;
    jsonschemaenforcer::SchemaObject      sobject;
    jsonschemaenforcer::StdStringList     slist;
    long ival;
    std::string sval;
};

typedef struct SCHEMA_PARSER_STYPE SCHEMA_PARSER_STYPE;
#define SCHEMA_PARSER_STYPE_IS_DECLARED

#endif  // __JSONSCHEMAENFORCER_SCHEMA_STYPE_HH
