//#define DEBUG

#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <list>
#include <unordered_map>

namespace Cache {
template <typename T, typename KeyT = int> 
struct LRU
{
    size_t sz_;

    std::list<std::pair<KeyT, T>> cache_;

    using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    LRU (size_t size_cache) : sz_(size_cache) {}

    bool full() const {return (sz_ == hash_.size());}

#ifdef DEBUG
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
#endif

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
            cache_.emplace_front(key, slow_get_page(key));
            hash_.emplace(key, cache_.begin());

#ifdef DEBUG
            dump();
#endif
            return false;
        }

        auto eltit = hit->second;
        if (eltit != cache_.begin())
        {
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
        }

#ifdef DEBUG
        dump();
#endif
        return true;
    }
};
}

#endif //LRU_CACHE_HPP