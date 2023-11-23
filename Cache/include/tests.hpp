#ifndef TESTS_HPP
#define TESTS_HPP

#include <iostream>
#include <fstream>
#include <cassert>

#ifdef LRU_CACHE
    #include "LRU_cache.hpp"
#endif

#ifdef LFU_CACHE
    #include "LFU_cache.hpp"
#endif

template <typename Func> void tests(Func slow_get_page)
{
    std::ifstream test_data("test_data.txt");
    assert(test_data.good());

    int hits = 0;

    size_t size_cache = 0;
    size_t number_elem = 0;

    int index = 0;
    int correct_tests = 0;

    while (test_data >> size_cache)
    {
        test_data >> number_elem;

#ifdef LRU_CACHE
        Cache::LRU<int> cache(size_cache);
#endif

#ifdef LFU_CACHE
        Cache::LFU<int> cache(size_cache);
#endif

        for (int i = 0; i < number_elem; i++)
        {
            int key = 0;
            test_data >> key;
            assert(std::cin.good());

            if (cache.lookup_update(key, slow_get_page))
            {
                hits++;
            }
        }

        int right_hits = 0;
        test_data >> right_hits;

        std::cout << "TEST#" << index << " - ";

        if (right_hits == hits)
        {
            std::cout << "\e[32mSUCCESS\e[0m" << std::endl;
            correct_tests++;
        }
        else
        {
            std::cout << "\e[31mFALSE\e[0m" << std::endl;
        }

        index++;
        hits = 0;
    }

    std::cout << "==================" << std::endl;
    std::cout << "CORRECT TESTS: " << correct_tests << "/" << index << std::endl;

}

#endif //TESTS_HPP