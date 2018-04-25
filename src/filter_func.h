#pragma once

#include <tuple>
#include <vector>
#include <cstdlib>
#include <type_traits>

#include "utils.h"

namespace {

    template<int index, typename F, typename T>
    bool check(const ip_adress& ip, F compare, T value)
    {
        bool isCurrentEqual = std::get<index>(ip) == value ? true : false;
        return isCurrentEqual;
    }
    
    template<int index, typename F, typename T, typename... Args>
    bool check(const ip_adress& ip, F compare, T value, Args... args)
    {
        bool isCurrentEqual = std::get<index>(ip) == value ? true : false;
        
        const decltype(index) nextIndex = index + 1;
        
        return compare(isCurrentEqual, check<nextIndex>(ip, compare, args...));
    }
    
    template<typename... Args>
    auto match(const ip_adress& ip, FILTER_MATCH filterParametr, Args... args) -> typename std::enable_if<sizeof...(args) <= 4, bool>::type
    {
        bool match = false;
    
        auto matchInOrder = [](auto a, auto b) { return (a && b); };
        auto matchAny = [](auto a, auto b) { return (a || b); };
    
        if(filterParametr == FILTER_MATCH::IN_ORDER)
            match = check<0>(ip, matchInOrder, args...);
        if(filterParametr == FILTER_MATCH::ANY_OF)
            match = check<0>(ip, matchAny, args...);
         
        return match;
    }
}

template<typename... Args>
std::vector<ip_adress> ipFilter(const std::vector<ip_adress> &ip_pool, FILTER_MATCH filterParametr, Args... args)
{
    std::vector<ip_adress> filteredPool;
    filteredPool.reserve(ip_pool.size());
        
    for(const auto& ip : ip_pool)
    {
        if(match(ip, filterParametr, std::forward<Args>(args)...))
            filteredPool.push_back(ip);
    }
    
    return filteredPool;
}