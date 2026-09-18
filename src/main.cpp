#include <iostream>
#include <list>
#include <unordered_map>

struct SimpleLRU {
    size_t capacity;
    std::list<int> cache_list;

    std::unordered_map<int, std::list<int>::iterator> hash_map;

    SimpleLRU(size_t sz) : capacity(sz) {} // конструктор

    bool lookup_update(int key) 
    {
        auto hit = hash_map.find(key); // в hit - "указатель" на конкретный узел двусвязного списка
        
        if (hit != hash_map.end())
        {
            auto ptr = hit->second;
            cache_list.splice(cache_list.begin(), cache_list, ptr);
            
            return true;
        }     
        
        if (cache_list.size() == capacity)
        {
            int oldest_key = cache_list.back();
            hash_map.erase(oldest_key);
            cache_list.pop_back();
        }

        cache_list.push_front(key);
        hash_map.emplace(key, cache_list.begin());
        return false;
    }   
};

int main() {
    size_t cache_capacity = 0, n_of_requests = 0;

    std::cin >> cache_capacity >> n_of_requests;

    SimpleLRU cache(cache_capacity);
    int hits = 0;

    for (int i = 0; i < n_of_requests; i++)
    {
        int page_id = 0;
        std::cin >> page_id;

        if (cache.lookup_update(page_id))
        {
            hits++;
        }
    }

    std::cout << hits << "\n";
    return 0;
}