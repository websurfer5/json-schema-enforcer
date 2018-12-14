// ItemType.hh
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

#ifndef __JSONSCHEMAENFORCER_ITEM_TYPE_HH
#define __JSONSCHEMAENFORCER_ITEM_TYPE_HH

#include <ostream>
#include <set>
#include <string>

namespace jsonschemaenforcer
{
    class ItemType
    {
    public:
#       define DEF_FLAG(fname, str_name) \
            type_##fname,
            
        typedef enum
        {
            type_Unknown    = 0,
#           include "ItemType-vars.hh"
            type_last_enum
        } JsonItemType;

#       undef DEF_FLAG

        ItemType();
        ItemType(const ItemType& itype);
        ItemType(const JsonItemType jtype);
        ItemType(const std::string& str);

        inline ItemType& operator =(const ItemType& itype) { type = itype.type; return *this; };
        ItemType& operator =(const JsonItemType jtype) { type = jtype; return *this; };
        ItemType& operator =(const std::string& str);
        inline bool operator ==(const ItemType& itype) const { return (type == itype.type); };
        inline bool operator ==(const JsonItemType jtype) const { return (type == jtype); };
        bool operator ==(const std::string str) const;
        inline bool operator !=(const ItemType& itype) const { return !this->operator ==(itype); };
        inline bool operator !=(const JsonItemType jtype) const { return !this->operator ==(jtype); };
        bool operator !=(const std::string str) const { return !this->operator ==(str); };
        inline operator int() const { return (int) type; };

        inline void clear() { type = type_Unknown; };
        inline JsonItemType get_type() const { return type; };
        const std::string& get_type_name() const;
        inline bool is_Unknown() const { return (type == type_Unknown || type >= type_last_enum); }

#       define DEF_FLAG(fname, str_name) \
        inline bool is_##fname() const { return (type == type_##fname); };

#       include "ItemType-vars.hh"
#       undef DEF_FLAG


    protected:
        JsonItemType type;
    };

    inline bool operator ==(const ItemType::JsonItemType jtype, const ItemType& itype)
    {
        return itype.operator ==(jtype);
    };

    inline bool operator ==(const std::string& str, const ItemType& itype)
    {
        return itype.operator ==(str);
    }

    inline bool operator !=(const ItemType::JsonItemType jtype, const ItemType& itype)
    {
        return itype.operator !=(jtype);
    };

    inline bool operator !=(const std::string& str, const ItemType& itype)
    {
        return itype.operator !=(str);
    }

    typedef std::set<ItemType> ItemTypeSet;

    inline std::ostream& operator <<(std::ostream& os, const ItemType& itype)
    {
        os << itype.get_type_name();
        return os;
    }

    inline std::ostream& operator <<(std::ostream& os, const ItemTypeSet& iset)
    {
        bool first = true;
        ItemTypeSet::const_iterator c_it;

        if (iset.size() > 1)
            os << "[";

        for (c_it = iset.begin(); c_it != iset.end(); c_it++)
        {
            if (first)
                first = false;
            else
                os << ", ";

            os << "\"" << c_it->get_type_name() << "\"";
        }

        if (iset.size() > 1)
            os << "]";

        return os;
    }
}

#endif  // __JSONSCHEMAENFORCER_ITEM_TYPE_HH
