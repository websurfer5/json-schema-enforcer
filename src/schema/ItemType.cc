// item-type.cc
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

#include "ItemType.hh"
#include <map>

namespace jsonschemaenforcer
{
#   define DEF_FLAG(fname, str_name) \
            (*this)[str_name] = ItemType::type_##fname;

    class _StringItemTypeMap : public std::map<std::string, ItemType::JsonItemType>
    {
    public:
        _StringItemTypeMap()
        {
#           include "ItemType-vars.hh"
        }
    };

#   undef DEF_FLAG

    static const _StringItemTypeMap _item_type_map;

    class _ItemTypeNameMap : public std::map<ItemType::JsonItemType, std::string>
    {
    public:
        _ItemTypeNameMap()
        {
            _StringItemTypeMap::const_iterator it;

            for (it = _item_type_map.begin(); it != _item_type_map.end(); it++)
                (*this)[it->second] = it->first;
        }
    };

    static const _ItemTypeNameMap _type_name_map;
    static const std::string _str_Empty;

    ItemType::ItemType()
    {
        clear();
    }

    ItemType::ItemType(const ItemType& itype)
        : type(itype.type)
    {
    }

    ItemType::ItemType(const JsonItemType jtype)
        : type(jtype)
    {
    }

    ItemType::ItemType(const std::string& str)
    {
        this->operator =(str);
    }
    
    ItemType& ItemType::operator =(const std::string& str)
    {
        _StringItemTypeMap::const_iterator it = _item_type_map.find(str);

        if (it != _item_type_map.end())
            type = it->second;
        else
            type = type_Unknown;

        return *this;
    }

    bool ItemType::operator ==(const std::string str) const
    {
        _StringItemTypeMap::const_iterator it = _item_type_map.find(str);

        if (it != _item_type_map.end())
            return (it->second == type);

        return false;
    }

    const std::string& ItemType::get_type_name() const
    {
        _ItemTypeNameMap::const_iterator it = _type_name_map.find(type);

        if (it != _type_name_map.end())
            return it->second;

        return _str_Empty;
    }
}
