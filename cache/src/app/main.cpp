#include "../cache/cache.hpp"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

template <typename T>
void print_cache(const caches::cache_t<T>& c)
{
    std::cout << "IN\n";
    for (const auto& c : c.in_cache_) {
        std::cout << c.first << " : " << c.second << '\n';
    }
    std::cout << '\n';

    std::cout << "OUT\n";
    for (const auto& c : c.out_cache_) {
        std::cout << c.first << " : " << c.second << '\n';
    }
    std::cout << '\n';

    std::cout << "HOT\n";
    for (const auto& c : c.hot_cache_) {
        std::cout << c.first << " : " << c.second << '\n';
    }
    std::cout << '\n';
}

int ret(int key)
{
    return key;
}

int main()
{
    caches::cache_t<int> cache(10);

    for (int x = 0; x != 10; ++x) {
        cache.lookup_update(x, ret);
    }

    print_cache(cache);

    for (int x = 15; x != 20; ++x) {
        std::cout << "Pushing " << x << "...";
        std::cout << "Result - " << cache.lookup_update(x, ret) << '\n';
        print_cache(cache);
        sleep(1);
        cache.lookup_update(x, ret);
    }

    for (int x = 0; x != 5; ++x) {
        std::cout << "Pushing " << x << "...";
        std::cout << "Result - " << cache.lookup_update(x, ret) << '\n';
        print_cache(cache);
        sleep(1);
        cache.lookup_update(x, ret);
    }

    // print_cache(cache);
}
