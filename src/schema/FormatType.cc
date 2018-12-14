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

#include "FormatType.hh"
#include <map>

namespace jsonschemaenforcer
{
    class _StringFormatTypeMap : public std::map<std::string, FormatType::FormatTypeEnum>
    {
    public:
        _StringFormatTypeMap()
        {
#           define DEF_FLAG(fname, str_name) \
            (*this)[str_name] = FormatType::type_##fname;
#           include "FormatType-vars.hh"
#           undef DEF_FLAG
        }
    };

    static const _StringFormatTypeMap _item_type_map;

    class _FormatTypeNameMap : public std::map<FormatType::FormatTypeEnum, std::string>
    {
    public:
        _FormatTypeNameMap()
        {
            _StringFormatTypeMap::const_iterator it;

            for (it = _item_type_map.begin(); it != _item_type_map.end(); it++)
                (*this)[it->second] = it->first;
        }
    };

    static const _FormatTypeNameMap _type_name_map;
    static const std::string _str_Empty;

    FormatType::FormatType()
    {
        clear();
    }

    FormatType::FormatType(const FormatType& ftype)
        : type(ftype.type)
    {
    }

    FormatType::FormatType(const FormatTypeEnum _type)
        : type(_type)
    {
    }

    FormatType::FormatType(const std::string& str)
    {
        this->operator =(str);
    }
    
    FormatType& FormatType::operator =(const std::string& str)
    {
        _StringFormatTypeMap::const_iterator it = _item_type_map.find(str);

        if (it != _item_type_map.end())
            type = it->second;
        else
            type = type_Unknown;

        return *this;
    }

    bool FormatType::operator ==(const std::string str) const
    {
        _StringFormatTypeMap::const_iterator it = _item_type_map.find(str);

        if (it != _item_type_map.end())
            return (it->second == type);

        return false;
    }

    const std::string& FormatType::get_type_name() const
    {
        _FormatTypeNameMap::const_iterator it = _type_name_map.find(type);

        if (it != _type_name_map.end())
            return it->second;

        return _str_Empty;
    }
}
