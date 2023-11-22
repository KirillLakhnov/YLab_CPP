//#define DEBUG

#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include <iostream>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT = int> struct LFU_cache_t
{
    size_t sz_;

    LFU_cache_t (size_t size_cache) : sz_(size_cache) {}

    std::list<std::pair<KeyT, std::pair<T, size_t>>> cache_;

    using ListIt = typename std::list<std::pair<KeyT, std::pair<T, size_t>>>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    bool full() const {return (sz_ == hash_.size());}

    void dump()
    {
        std::cout << "\e[31mcache_list: \e[0m";

        auto cache_elem = cache_.begin();
        auto cache_size = cache_.size();
        for (int i = 0; i < cache_size; i++)
        {
            std::cout << cache_elem->first << " ";
            cache_elem = std::next(cache_elem);
        }
        std::cout << std::endl;
    }

    template <typename Func> bool lookup_update (KeyT key, Func slow_get_page)
    {
        if (sz_ == 0) return false;
        
        auto hit = hash_.find(key);

        if (hit == hash_.end())
        {
            if (full())
            {
                hash_.erase(cache_.back().first);
                cache_.pop_back();
            }

            std::pair<KeyT, std::pair<T, size_t>> new_cache_page;
            new_cache_page.first = key;
            new_cache_page.second.first = slow_get_page(key);
            new_cache_page.second.second = 1;

            cache_.push_back(new_cache_page);
            hash_.emplace(key, std::prev(cache_.end()));

#ifdef DEBUG
            dump();
#endif
            return false;
        }

        auto eltit = hit->second;

        eltit->second.second++;

        if ((eltit != cache_.begin()) && 
            (eltit->second.second > std::prev(eltit)->second.second))
        {
            cache_.splice(std::prev(eltit), cache_, eltit, eltit);
        }

#ifdef DEBUG
        dump();
#endif
        return true;
    }
};

#endif //LFU_CACHE_HPP