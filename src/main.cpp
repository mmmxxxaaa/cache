#include <iostream>
#include <list>
#include <unordered_map>

#include "lru_cache.hpp"
#include "tests.hpp"

int main() {
    size_t cache_capacity = 0, n_of_requests = 0;

    std::cin >> cache_capacity >> n_of_requests;

    SimpleLRU<int, int> cache(cache_capacity);
    int hits = 0;

    for (int i = 0; i < n_of_requests; i++)
    {
        int page_id = 0;
        std::cin >> page_id;

        if (cache.lookup_update(page_id, imitator_of_slow_get_page))
        {
            hits++;
        }
    }

    std::cout << hits << "\n";

    run_tests();
    
    return 0;
}