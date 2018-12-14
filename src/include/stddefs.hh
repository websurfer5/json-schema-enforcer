// stddefs.hh
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

#ifndef __JSONSCHEMAENFORCER_STDDEF_HH
#define __JSONSCHEMAENFORCER_STDDEF_HH

#include <list>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <utility>

namespace jsonschemaenforcer
{
    typedef std::list<std::string> StdStringList;
    typedef std::map<std::string, bool> StdStringBoolMap;
    typedef std::map<std::string, std::string> StdStringMap;
    typedef std::map<std::string, unsigned> StdStringUnsignedMap;
    typedef std::pair<std::string, std::string> StdStringPair;
    typedef std::set<std::string> StdStringSet;
    typedef std::tuple<std::string,
                       std::string,
                       std::string,
                       std::string,
                       bool> StdStringTuple5;
    typedef std::map<StdStringTuple5, std::string> StdStringTuple5StringMap;

    inline std::ostream& operator <<(std::ostream& os, const StdStringList& s_list)
    {
        StdStringList::const_iterator c_it;

        for (c_it = s_list.begin(); c_it != s_list.end(); c_it++)
            os << *c_it;

        return os;
    }
}

inline std::ostream& operator <<(std::ostream& os, const jsonschemaenforcer::StdStringList& s_list)
{
    jsonschemaenforcer::StdStringList::const_iterator c_it;

    for (c_it = s_list.begin(); c_it != s_list.end(); c_it++)
        os << *c_it;

    return os;
}

#endif
