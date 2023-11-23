//#define LRU_CACHE
//#define LFU_CACHE
//#define TESTS

#include <iostream>
#include <cassert>
#include <vector>

#ifdef LRU_CACHE
    #include "include/LRU_cache.hpp"
#endif

#ifdef LFU_CACHE
    #include "include/LFU_cache.hpp"
#endif

#ifdef TESTS
    #include "include/tests.hpp"
#endif

int slow_get_page_int(int key) 
{ 
    return key; 
}

int main ()
{
#ifdef TESTS
    tests(slow_get_page_int);
#else
    int hits = 0;

    size_t size_cache = 0;
    size_t number_elem = 0;

    std::cin >> size_cache >> number_elem;
    assert(std::cin.good());

#ifdef LRU_CACHE
    Cache::LRU<int> cache(size_cache);
#endif

#ifdef LFU_CACHE
    Cache::LFU<int> cache(size_cache);
#endif
    
    for (int i = 0; i < number_elem; i++)
    {
        int key = 0;
        std::cin >> key;
        assert(std::cin.good());

        if (cache.lookup_update(key, slow_get_page_int))
        {
            hits++;
        }
    }

    std::cout << hits << std::endl;
#endif

    return 0;
}