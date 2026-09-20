
#include "tests.hpp"
#include "lru_cache.hpp"
#include <iostream>
#include <cassert>
#include <vector>


int imitator_of_slow_get_page(int key) 
{
    // В реальной жизни здесь был бы поход на жесткий диск
    return key; 
}

page imitator_of_slow_get_page_struct(int key)
{
    return page{key, 4096, nullptr};
}

void run_tests() 
{
    bool all_tests_finished_successful = true;

    SimpleLRU<int, int> cache1(2);
    std::vector<int> requests1 = {1, 2, 1, 2, 1, 2};
    int hits1 = 0;
    for (int req : requests1)
    {
        if (cache1.lookup_update(req, imitator_of_slow_get_page)) hits1++;
    }
    if (hits1 != 4)
    {
        std::cout << "First test failed";
        all_tests_finished_successful = false;
    }

    SimpleLRU<page, int> cache_struct_1(2);
    std::vector<int> requests2 = {10, 20, 30, 10};
    int hits2 = 0;

    for (int req : requests2)
    {
        if (cache_struct_1.lookup_update(req, imitator_of_slow_get_page_struct)) hits2++;
    }
    if (hits2 != 0 || cache_struct_1.cache_list.front().first.size != 4096)
    {
        std::cout << "Second test failed";
        all_tests_finished_successful = false;
    }

    if (all_tests_finished_successful)
        std::cout << "All unit tests passed successfully" << std::endl;
}