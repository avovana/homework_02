#pragma once

#include <tuple>
#include <vector>
#include <cstdlib>

#include "utils.h"

enum class FILTER_MATCH { ANY_OF, IN_ORDER };

namespace _detail_
{
    template<int index, typename Callback, typename... Args>
    struct iterate_tuple 
    {
        static void next(std::tuple<Args...>& t, Callback callback) 
        {
            iterate_tuple<index - 1, Callback, Args...>::next(t, callback);

            callback(index, std::get<index>(t));
        }
    };
    
    template<typename Callback, typename... Args>
    struct iterate_tuple<0, Callback, Args...> 
    {
        static void next(std::tuple<Args...>& t, Callback callback) 
        {
            callback(0, std::get<0>(t));
        }
    };

    template<typename Callback, typename... Args>
    struct iterate_tuple<-1, Callback, Args...>
    {
        static void next(std::tuple<Args...>& t, Callback callback)
        {
            // ничего не делаем
        }
    };
}

template<typename Callback, typename... Args>
void for_each(std::tuple<Args...>& t, Callback callback) 
{
    int const t_size = std::tuple_size<std::tuple<Args...>>::value;
    
    _detail_::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
}


template<typename... Args>
bool match(const ip_adress& ip, FILTER_MATCH filterParametr, Args... args)
{
   auto tuple_ = std::make_tuple(std::forward<Args>(args)...);

   bool passedTest = true;

   auto callback = [ip, &passedTest](int index, auto&& t)
   {
        switch(index)
        {
             case 0:  
                 if(std::get<0>(ip) != t) passedTest = false;
             break;
             
             case 1:  
                 if(std::get<1>(ip) != t) passedTest = false;
             break;
             
             case 2:  
                 if(std::get<2>(ip) != t) passedTest = false;
             break;
             
             case 3:  
                 if(std::get<3>(ip) != t) passedTest = false;
             break;
             
             default:
             return;
        }
   };
    
   auto callback_any = [ip, &passedTest](int /*index*/, auto&& t)
   {
       bool test = false;
       
       if((t == std::get<0>(ip)) ||
          (t == std::get<1>(ip)) ||
          (t == std::get<2>(ip)) ||
          (t == std::get<3>(ip)))
           test = true;
        
    passedTest = test;
   };    

   if(filterParametr == FILTER_MATCH::IN_ORDER)
    for_each(tuple_, callback);
   if(filterParametr == FILTER_MATCH::ANY_OF)
    for_each(tuple_, callback_any);
    
   return passedTest;
}


template<typename... Args>
std::vector<ip_adress> ipFilter(const std::vector<ip_adress> &ip_pool, FILTER_MATCH filterParametr, Args... args)
{
    std::vector<ip_adress> filteredPool;
    filteredPool.reserve(ip_pool.size());
        
    for(const auto& ip : ip_pool)
        if(match(ip, filterParametr, std::forward<Args>(args)...))
            filteredPool.push_back(ip);
    
    return filteredPool;
}

