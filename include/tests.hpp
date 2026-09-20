#pragma once

struct page {
    int index;
    int size;
    char *data;
};

int imitator_of_slow_get_page(int key);

page imitator_of_slow_get_page_struct(int key);

void run_tests();