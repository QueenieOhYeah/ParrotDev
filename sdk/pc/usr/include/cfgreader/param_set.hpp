/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#ifndef CFGREADER_PARAM_SET_HPP_
#define CFGREADER_PARAM_SET_HPP_

#include <map>
#include <string>

#include "cfgreader-ulog.hpp"

namespace cfgreader {

template <typename T>
class ParamSet : public std::map<std::string, T>
{
public:
    std::string name;

    T& at(const std::string& key)
    {
        if (!exists(key)) {
            logC("%s doesn't exist in %s", key.c_str(), name.c_str());
            return this->begin()->second;
        } else
            return std::map<std::string, T>::at(key);
    }

    const T& at( const std::string& key) const
    {
        if (!exists(key)) {
            logC("%s doesn't exist in %s", key.c_str(), name.c_str());
            return this->begin()->second;
        } else
            return std::map<std::string, T>::at(key);
    }

    bool exists(const std::string& key) const
    {
        return this->find(key) != this->end();
    }

    void operator *= (const float& m)
    {
        for (auto it = this->begin(); it != this->end(); ++it)
            it->second *= m;
    }

    void pow2(void)
    {
        for (auto it = this->begin(); it != this->end(); ++it)
            it->second *= it->second;
    }
};
}
#endif
