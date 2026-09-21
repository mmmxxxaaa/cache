#pragma once
#include <list>
#include <unordered_map>

template <typename T, typename KeyT = int>
struct SimpleLFU {
    size_t capacity;
    int min_frequency;


    struct LFU_node
    {
        T data;
        int frequency;
        typename std::list<KeyT>::iterator list_iterator;
    };

    std::unordered_map<KeyT, LFU_node>       hash_map; //основная хэш-таблица    : (ключ)  -> (нода со всей инфой)
    std::unordered_map<int, std::list<KeyT>> freq_map; // вспомогательная таблица: частота -> двусвязный список ключей страниц

    SimpleLFU(size_t sz) : capacity(sz), min_frequency(0) {} // конструктор

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) 
    {
        if (capacity == 0) return false;

        auto hit = hash_map.find(key);
        
        if (hit != hash_map.end())
        {
            LFU_node* node = &hit->second;
            freq_map[node->frequency].erase(node->list_iterator);
            if (node->frequency == min_frequency && freq_map[node->frequency].empty())
                min_frequency += 1;
            node->frequency += 1;

            freq_map[node->frequency].push_front(key);
            node->list_iterator = freq_map[node->frequency].begin();   
            
            return true;
        }

        T page = slow_get_page(key);

        if (hash_map.size() == capacity)
        {
            KeyT key_to_be_deleted = freq_map[min_frequency].back(); // самый старый из всех наименее встречающихся
            hash_map.erase(key_to_be_deleted);
            freq_map[min_frequency].pop_back();
        }   

        min_frequency = 1;
        freq_map[1].push_front(key);

        hash_map[key] = LFU_node{page, 1, freq_map[1].begin()};

        return false;
    }   
};