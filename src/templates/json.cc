#include "json.hh"
#include <algorithm>
#include <stdexcept>

namespace foo
{
    static std::string item_type_str[6] = {
                                            "array",
                                            "boolean",
                                            "null",
                                            "number",
                                            "object",
                                            "string"
                                          };
    JsonItem::JsonItem()
    {
        clear();
    }

    JsonItem::JsonItem(const JsonItem& jitem)
    {
        this->operator =(jitem);
    }

    JsonItem::JsonItem(const JsonItemVector& jvect)
    {
        clear();
        set_array(jvect);
    }

    JsonItem::JsonItem(bool b)
    {
        set_boolean(b);
    }

    JsonItem::JsonItem(double d)
    {
        set_number(d);
    }

    JsonItem::JsonItem(int n)
    {
        set_number(n);
    }

    JsonItem::JsonItem(long n)
    {
        set_number(n);
    }

    JsonItem::JsonItem(unsigned n)
    {
        set_number(n);
    }

    JsonItem::JsonItem(unsigned long n)
    {
        set_number(n);
    }

    JsonItem::JsonItem(const char *s)
    {
        set_string(s);
    }

    JsonItem::JsonItem(const std::string& s)
    {
        set_string(s);
    }

    bool JsonItem::operator ==(const JsonItem& jitem) const
    {
        return (item_type == jitem.item_type
                && bool_value == jitem.bool_value
                && std::equal(child_vector.begin(), child_vector.end(), jitem.child_vector.begin())
                && std::equal(child_map.begin(), child_map.end(), jitem.child_map.begin())
                && num_value == jitem.num_value
                && str_value == jitem.str_value);
    }

    JsonItem& JsonItem::operator =(const JsonItem& jitem)
    {
        bool_value = jitem.bool_value;
        num_value = jitem.num_value;
        child_vector = jitem.child_vector;
        child_map = jitem.child_map;
        item_type = jitem.item_type;
        str_value = jitem.str_value;
        return *this;
    }

    JsonItem& JsonItem::operator =(bool b)
    {
        return set_boolean(b);
    }

    JsonItem& JsonItem::operator =(const char *s)
    {
        return set_string(s);
    }

    JsonItem& JsonItem::operator =(double d)
    {
        return set_number(d);
    }

    JsonItem& JsonItem::operator =(int n)
    {
        return set_number(n);
    }

    JsonItem& JsonItem::operator =(long n)
    {
        return set_number(n);
    }

    JsonItem& JsonItem::operator =(unsigned n)
    {
        return set_number(n);
    }

    JsonItem& JsonItem::operator =(unsigned long n)
    {
        return set_number(n);
    }

    JsonItem& JsonItem::operator =(const std::string& s)
    {
        return set_string(s);
    }

    JsonItem& JsonItem::operator [](size_t n)
    {
        if (is_array())
            return child_vector.at(n);

        throw std::invalid_argument("[] operator is undefined for JSON item type " + item_type_str[item_type]);
    }

    JsonItem& JsonItem::operator [](const std::string& _key)
    {
        if (is_object())
            return child_map.at(_key);

        throw std::invalid_argument("[] operator is undefined for JSON item type " + item_type_str[item_type]);
    }

    JsonItem& JsonItem::append_array(const JsonItemVector& jvect)
    {
        if (!is_array())
            clear();

        child_vector.insert(child_vector.end(), jvect.begin(), jvect.end());
        item_type = type_Array;
        return *this;
    }

    JsonItem& JsonItem::append_array_item()
    {
        if (!is_array())
            clear();

        child_vector.push_back(JsonItem());
        item_type = type_Array;
        return *this;
    }

    JsonItem& JsonItem::append_array_item(const JsonItem& jitem)
    {
        if (!is_array())
            clear();

        child_vector.push_back(jitem);
        item_type = type_Array;
        return *this;
    }

    JsonItemVector& JsonItem::array()
    {
        if (!is_array())
            throw std::invalid_argument("cannot return array for JSON item type " + item_type_str[item_type]);

        return child_vector;
    }

    bool JsonItem::boolean() const
    {
        if (!is_boolean())
            throw std::invalid_argument("cannot return bool for JSON item type " + item_type_str[item_type]);

        return bool_value;
    }

    void JsonItem::clear()
    {
        bool_value = false;
        num_value = 0.0;
        child_vector.clear();
        child_map.clear();
        item_type = type_Null;
        str_value.clear();
    }

    bool JsonItem::empty() const
    {
        bool b;

        switch (item_type)
        {
            case type_Array:
                b = child_vector.empty();
                break;

            case type_Boolean:
                b = false;
                break;

            case type_Null:
                b = true;
                break;

            case type_Number:
                b = (num_value == 0.0);
                break;

            case type_Object:
                b = child_map.empty();
                break;

            case type_String:
                b = str_value.empty();
                break;
        }

        return b;
    }

    bool JsonItem::is_array() const
    {
        return (item_type == type_Array);
    }

    bool JsonItem::is_boolean() const
    {
        return (item_type == type_Boolean);
    }

    bool JsonItem::is_null() const
    {
        return (item_type == type_Null);
    }

    bool JsonItem::is_number() const
    {
        return (item_type == type_Number);
    }

    bool JsonItem::is_object() const
    {
        return (item_type == type_Object);
    }

    bool JsonItem::is_string() const
    {
        return (item_type == type_String);
    }

    double JsonItem::number() const
    {
        if (!is_number())
            throw std::invalid_argument("cannot return number for JSON item type " + item_type_str[item_type]);

        return num_value;
    }

    JsonItemMap& JsonItem::object()
    {
        if (!is_object())
            throw std::invalid_argument("cannot return object for JSON item type " + item_type_str[item_type]);

        return child_map;
    }

    JsonItem& JsonItem::set_array(const JsonItemVector& jvect)
    {
        if (!is_array())
            clear();

        child_vector = jvect;
        item_type = type_Array;
       return *this;
    }

    JsonItem& JsonItem::set_boolean(bool b)
    {
        if (!is_boolean())
            clear();

        item_type = type_Boolean;
        bool_value = b;
        return *this;
    }

    JsonItem& JsonItem::set_null()
    {
        clear();
        return *this;
    }

    JsonItem& JsonItem::set_number(double d)
    {
        if (!is_number())
            clear();

        item_type = type_Number;
        num_value = d;
        return *this;
    }

    JsonItem& JsonItem::set_object(const JsonItemMap& jmap)
    {
        if (!is_object())
            clear();

        child_map = jmap;
        item_type = type_Object;
        return *this;
    }

    JsonItem& JsonItem::set_object_item(const std::string& key, const JsonItem& jitem)
    {
        if (!is_object())
            clear();

        child_map[key] = jitem;
        item_type = type_Object;
        return *this;
    }

    JsonItem& JsonItem::set_object_item(const std::string& key, const JsonItemMap& jmap)
    {
        if (!is_object())
            clear();

        child_map[key].set_object(jmap);
        item_type = type_Object;
        return *this;
    }

    JsonItem& JsonItem::set_string(const std::string& str)
    {
        if (!is_string())
            clear();

        str_value = str;
        item_type = type_String;
        return *this;
    }

    const std::string& JsonItem::string() const
    {
        if (!is_string())
            throw std::invalid_argument("cannot return string for JSON item type " + item_type_str[item_type]);

        return str_value;
    }

    JsonItem::ItemType JsonItem::type()
    {
        return item_type;
    }
}
