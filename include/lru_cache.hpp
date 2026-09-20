#pragma once
#include <list>
#include <unordered_map>

// до внедрения шаблонов число-значение совпадало с числом-ключом, после внедрения нужно уже разделять и хранить их парой
template <typename T, typename KeyT = int>
struct SimpleLRU {
    size_t capacity;
    std::list<std::pair<T, KeyT>> cache_list;

    using ListIterator = typename std::list<std::pair<T, KeyT>>::iterator;
    // std::unordered_map<T, std::list<int>::iterator> hash_map;
    std::unordered_map<KeyT, ListIterator> hash_map;

    SimpleLRU(size_t sz) : capacity(sz) {} // конструктор

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) 
    {
        if (capacity == 0) return false;

        auto hit = hash_map.find(key); // в hit - "указатель" на конкретный узел двусвязного списка
        
        if (hit != hash_map.end())
        {
            auto ptr = hit->second;
            cache_list.splice(cache_list.begin(), cache_list, ptr);
            
            return true;
        }

        T page = slow_get_page(key);

        if (cache_list.size() == capacity)
        {
            // KeyT oldest_key = cache_list.back(); ключ теперь лежит во втором поле пары
            hash_map.erase(cache_list.back().second);
            cache_list.pop_back();
        }

        // cache_list.push_front(key); push_front требует передать ему уже готовую структуру данных
        cache_list.emplace_front(page, key); // принимает "сырые" аргументы и конструирует из них финальный объект 
        hash_map.emplace(key, cache_list.begin());
        return false;
    }   
};