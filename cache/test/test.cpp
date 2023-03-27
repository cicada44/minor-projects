#include "../src/cache/cache.hpp"

#include <gtest/gtest.h>

#include <iostream>

#include <unistd.h>

int retSame(int key)
{
    return key;
}

void print_2q(const caches::cache_t<int>& c)
{
    std::cout << "IN\n";
    for (auto i = c.in_cache_.begin(); i != c.in_cache_.end(); ++i) {
        std::cout << i->first << '\n';
    }
    std::cout << '\n';
    std::cout << "OUT\n";
    for (auto i = c.out_cache_.begin(); i != c.out_cache_.end(); ++i) {
        std::cout << i->first << '\n';
    }
    std::cout << '\n';
    std::cout << "HOT\n";
    for (auto i = c.hot_cache_.begin(); i != c.hot_cache_.end(); ++i) {
        std::cout << i->first << '\n';
    }
    std::cout << '\n';
}

TEST(Cache, Cache2Q_0)
{
    caches::cache_t<int> cache(10);

    ASSERT_EQ(cache.in_sz_, 10);
    ASSERT_EQ(cache.out_sz_, 50);
    ASSERT_EQ(cache.hot_sz_, 2);

    ASSERT_EQ(cache.full_in(), false);
    ASSERT_EQ(cache.full_out(), false);
    ASSERT_EQ(cache.full_hot(), false);

    for (int i = 0; i != 10; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), false);
    }
    for (int i = 0; i != 10; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), true);
    }

    int cnter = 9;
    for (auto i = cache.in_cache_.begin(); i != cache.in_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);
}

TEST(Cache, Cache2Q_1)
{
    caches::cache_t<int> cache(5);

    ASSERT_EQ(cache.in_sz_, 5);
    ASSERT_EQ(cache.out_sz_, 25);
    ASSERT_EQ(cache.hot_sz_, 1);

    ASSERT_EQ(cache.full_in(), false);
    ASSERT_EQ(cache.full_out(), false);
    ASSERT_EQ(cache.full_hot(), false);

    for (int i = 0; i != 10; ++i) {
        if (i < 1) {
            ASSERT_EQ(cache.lookup_update(1, retSame), false);
        } else {
            ASSERT_EQ(cache.lookup_update(1, retSame), true);
        }
    }
    for (int i = 0; i != 10; ++i) {
        if (i < 1) {
            ASSERT_EQ(cache.lookup_update(2, retSame), false);
        } else {
            ASSERT_EQ(cache.lookup_update(2, retSame), true);
        }
    }

    int cnter = 2;
    for (auto i = cache.in_cache_.begin(); i != cache.in_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);
}

TEST(Cache, Cache2Q_2)
{
    caches::cache_t<int> cache(0);

    ASSERT_EQ(cache.in_cache_.empty(), true);
    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);

    ASSERT_EQ(cache.in_sz_, 0);
    ASSERT_EQ(cache.out_sz_, 0);
    ASSERT_EQ(cache.hot_sz_, 0);

    for (int i = 0; i != 10; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), false);
    }

    ASSERT_EQ(cache.in_cache_.empty(), true);
    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);
}

TEST(Cache, Cache2Q_3)
{
    caches::cache_t<int> cache(5);

    ASSERT_EQ(cache.in_cache_.empty(), true);
    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);

    ASSERT_EQ(cache.in_sz_, 5);
    ASSERT_EQ(cache.out_sz_, 25);
    ASSERT_EQ(cache.hot_sz_, 1);

    for (int i = 0; i != 15; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), false);
    }

    int cnter = 14;
    for (auto i = cache.in_cache_.begin(); i != cache.in_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }
    for (auto i = cache.out_cache_.begin(); i != cache.out_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    for (int i = 0; i != 25; ++i) {
        if (i < 15) {
            ASSERT_EQ(cache.lookup_update(i, retSame), true);
        } else {
            ASSERT_EQ(cache.lookup_update(i, retSame), false);
        }
        if (i < 10) {
            ASSERT_EQ(cache.hot_cache_.begin()->first, i);
        }
    }

    cnter = 24;
    for (auto i = cache.in_cache_.begin(); i != cache.in_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    cnter = 19;
    for (auto i = cache.out_cache_.begin(); i != cache.out_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }
}

TEST(Cache, Cache2Q_4)
{
    caches::cache_t<int> cache(1);

    ASSERT_EQ(cache.in_cache_.empty(), true);
    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);

    ASSERT_EQ(cache.in_sz_, 1);
    ASSERT_EQ(cache.out_sz_, 5);
    ASSERT_EQ(cache.hot_sz_, 1);

    for (int i = 0; i != 5; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), false);
    }

    ASSERT_EQ(cache.in_cache_.begin()->first, 4);

    int cnter = 3;
    for (auto i = cache.out_cache_.begin(); i != cache.out_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    for (int i = 0; i != 5; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), true);
    }

    ASSERT_EQ(cache.hot_cache_.begin()->first, 3);
    ASSERT_EQ(cache.in_cache_.begin()->first, 4);
    cnter = 3;
    for (auto i = cache.out_cache_.begin(); i != cache.out_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
