#ifndef __JSON_HH
#define __JSON_HH

#include <map>
#include <string>
#include <vector>

namespace foo
{
    class JsonItem;
    typedef std::vector<JsonItem> JsonItemVector;
    typedef std::map<std::string, JsonItem> JsonItemMap;

    class JsonItem
    {
    public:
        typedef enum
        {
            type_Array      = 0,
            type_Boolean    = 1,
            type_Null       = 2,
            type_Number     = 3,
            type_Object     = 4,
            type_String     = 5
        } ItemType;

        JsonItem();
        JsonItem(const JsonItem& jitem);
        JsonItem(bool b);
        JsonItem(double d);
        JsonItem(int n);
        JsonItem(long n);
        JsonItem(unsigned n);
        JsonItem(unsigned long n);
        JsonItem(const char *s);
        JsonItem(const std::string& s);

        bool operator ==(const JsonItem& jitem) const;
        JsonItem& operator =(const JsonItem& jitem);
        JsonItem& operator =(bool b);
        JsonItem& operator =(const char *s);
        JsonItem& operator =(double d);
        JsonItem& operator =(int n);
        JsonItem& operator =(long n);
        JsonItem& operator =(unsigned n);
        JsonItem& operator =(unsigned long n);
        JsonItem& operator =(const std::string& s);
        JsonItem& operator [](size_t n);
        // inline JsonItem& operator [](const char *s) { return this->operator [](std::string(s)); };
        JsonItem& operator [](const std::string& _key);

        JsonItem& append_array_item(const JsonItem& jitem);
        bool boolean() const;
        void clear();
        bool empty() const;
        bool is_array() const;
        bool is_boolean() const;
        bool is_null() const;
        bool is_number() const;
        bool is_object() const;
        bool is_string() const;
        double number() const;
        JsonItem& set_boolean(bool b);
        JsonItem& set_null();
        JsonItem& set_number(double d);
        JsonItem& set_string(const std::string& str);
        const std::string& string() const;

        ItemType type();

    protected:
        bool bool_value;
        double num_value;
        ItemType item_type;
        JsonItemMap child_map;
        JsonItemVector child_vector;
        std::string str_value;
    };
}

#endif  // __JSON_HH
