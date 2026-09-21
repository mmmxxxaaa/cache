
#include "tests.hpp"
#include "lru_cache.hpp"
#include "lfu_cache.hpp"
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

bool test_lru()
{
    bool lru_tests_finished_successful = true;

    SimpleLRU<int, int> lru_cache(2);
    std::vector<int> requests1 = {1, 2, 1, 2, 1, 2};
    int hits1 = 0;
    for (int req : requests1)
    {
        if (lru_cache.lookup_update(req, imitator_of_slow_get_page)) hits1++;
    }
    if (hits1 != 4)
    {
        std::cout << "First test failed";
        lru_tests_finished_successful = false;
    }

    SimpleLRU<page, int> lru_cache_struct(2);
    std::vector<int> requests2 = {10, 20, 30, 10};
    int hits2 = 0;

    for (int req : requests2)
    {
        if (lru_cache_struct.lookup_update(req, imitator_of_slow_get_page_struct)) hits2++;
    }
    if (hits2 != 0 || lru_cache_struct.cache_list.front().first.size != 4096)
    {
        std::cout << "Second test failed";
        lru_tests_finished_successful = false;
    }
    
    return lru_tests_finished_successful;
}

bool test_lfu()
{
    bool lfu_tests_finished_successful = true;

    SimpleLFU<int, int> lfu_cache(2);
    std::vector<int> requests_lfu = {1, 1, 2, 2, 3};
    int hits_lfu = 0;
    for (int req : requests_lfu)
    {
        if (lfu_cache.lookup_update(req, imitator_of_slow_get_page)) hits_lfu++;
    }
    if (hits_lfu != 2)
    {
        std::cout << "First lfu test failed";
        lfu_tests_finished_successful = false;
    }

    SimpleLFU<page, int> lfu_cache_struct(2);
    std::vector<int> requests_lfu_struct = {10, 20, 30, 10};
    int hits_lfu_struct = 0;

    for (int req : requests_lfu_struct)
    {
        if (lfu_cache_struct.lookup_update(req, imitator_of_slow_get_page_struct)) hits_lfu_struct++;
    }
    if (hits_lfu_struct != 0 || lfu_cache_struct.hash_map[30].data.size != 4096)
    {
        std::cout << "Second lfu test failed";
        lfu_tests_finished_successful = false;
    }
    
    return lfu_tests_finished_successful;
}

void run_tests() 
{
    bool all_tests_finished_successful = true;

    if (!test_lru()) all_tests_finished_successful = false;
    if (!test_lfu()) all_tests_finished_successful = false;

    if (all_tests_finished_successful)
        std::cout << "All unit tests passed successfully" << std::endl;
}