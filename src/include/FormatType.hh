// FormatType.hh
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

#ifndef __JSONSCHEMAENFORCER_FORMAT_TYPE_HH
#define __JSONSCHEMAENFORCER_FORMAT_TYPE_HH

#include <string>

namespace jsonschemaenforcer
{
    class FormatType
    {
    public:
#       define DEF_FLAG(fname, str_name) \
            type_##fname,

        typedef enum
        {
            type_Unknown = 0,
#           include "FormatType-vars.hh"
            type_last_enum
        } FormatTypeEnum;
#       undef DEF_FLAG

        FormatType();
        FormatType(const FormatType& ftype);
        FormatType(const FormatTypeEnum _type);
        FormatType(const std::string& str);

        inline FormatType& operator =(const FormatType& ftype) { type = ftype.type; return *this; };
        FormatType& operator =(const FormatTypeEnum _type) { type = _type; return *this; };
        FormatType& operator =(const std::string& str);
        inline bool operator ==(const FormatType& ftype) const { return (type == ftype.type); };
        inline bool operator ==(const FormatTypeEnum _type) const { return (type == _type); };
        bool operator ==(const std::string str) const;
        inline bool operator !=(const FormatType& ftype) const { return !this->operator ==(ftype); };
        inline bool operator !=(const FormatTypeEnum _type) const { return !this->operator ==(_type); };
        inline bool operator !=(const std::string str) const { return !this->operator ==(str); };
        inline operator int() const { return (int) type; };

        inline void clear() { type = type_Unknown; };
        inline FormatTypeEnum get_type() const { return type; };
        const std::string& get_type_name() const;
        inline bool is_Unknown() const { return (type == type_Unknown || type >= type_last_enum); }

#       define DEF_FLAG(fname, str_name) \
        inline bool is_##fname() const { return (type == type_##fname); };
#       include "FormatType-vars.hh"
#       undef DEF_FLAG
        inline bool is_unknown() const { return (type == type_Unknown || type >= type_last_enum); }

    protected:
        FormatTypeEnum type;
    };

    inline bool operator ==(const FormatType::FormatTypeEnum _type, const FormatType& ftype)
    {
        return ftype.operator ==(_type);
    };

    inline bool operator ==(const std::string& str, const FormatType& ftype)
    {
        return ftype.operator ==(str);
    }

    inline bool operator !=(const FormatType::FormatTypeEnum _type, const FormatType& ftype)
    {
        return ftype.operator !=(_type);
    };

    inline bool operator !=(const std::string& str, const FormatType& ftype)
    {
        return ftype.operator !=(str);
    }
}

#endif  // __JSONSCHEMAENFORCER_FORMAT_TYPE_HH
