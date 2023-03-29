#include "../src/cache/cache.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>

#include <fstream>

#include <unistd.h>

int retSame(int key)
{
    return key;
}

void print_2q(const caches::cache_t<int>& c)
{
    std::cout << "IN\n";
    for (auto i = c.in_cache_.begin(); i != c.in_cache_.end(); ++i) {
        std::cout << i->first << ' ';
    }
    std::cout << '\n';
    std::cout << "OUT\n";
    for (auto i = c.out_cache_.begin(); i != c.out_cache_.end(); ++i) {
        std::cout << i->first << ' ';
    }
    std::cout << '\n';
    std::cout << "HOT\n";
    for (auto i = c.hot_cache_.begin(); i != c.hot_cache_.end(); ++i) {
        std::cout << i->first << ' ';
    }
    std::cout << '\n';
}

/*

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

TEST(Cache, Cache2Q_5)
{
    caches::cache_t<int> cache(5);

    ASSERT_EQ(cache.in_cache_.empty(), true);
    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);

    ASSERT_EQ(cache.in_sz_, 5);
    ASSERT_EQ(cache.out_sz_, 25);
    ASSERT_EQ(cache.hot_sz_, 1);

    for (int i = 1; i != 31; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), false);
    }

    int cnter = 25;
    for (auto i = cache.out_cache_.begin(); i != cache.out_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    cnter = 30;
    for (auto i = cache.in_cache_.begin(); i != cache.in_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    for (int i = 1; i != 26; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), true);
        ASSERT_EQ(cache.hot_cache_.begin()->first, i);
        ASSERT_EQ(cache.hot_cache_.size(), 1);
    }
}

TEST(Cache, Cache2Q_6)
{
    caches::cache_t<int> cache(10);

    ASSERT_EQ(cache.in_cache_.empty(), true);
    ASSERT_EQ(cache.out_cache_.empty(), true);
    ASSERT_EQ(cache.hot_cache_.empty(), true);

    ASSERT_EQ(cache.in_sz_, 10);
    ASSERT_EQ(cache.out_sz_, 50);
    ASSERT_EQ(cache.hot_sz_, 2);

    for (int i = 1; i != 61; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), false);
    }

    int cnter = 50;
    for (auto i = cache.out_cache_.begin(); i != cache.out_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    cnter = 60;
    for (auto i = cache.in_cache_.begin(); i != cache.in_cache_.end(); ++i) {
        ASSERT_EQ(i->first, cnter--);
    }

    for (int i = 1; i != 51; ++i) {
        ASSERT_EQ(cache.lookup_update(i, retSame), true);
        ASSERT_EQ(cache.hot_cache_.begin()->first, i);
        if (i > 1) {
            ASSERT_EQ(std::next(cache.hot_cache_.begin())->first, i - 1);
        }
    }
}

*/

void generate()
{
    std::string filename
            = "/home/cicada44/cicada-main/edu/minor-projects/cache/test/"
              "dats/";
    std::string postfix = ".txt";
    srand(time(nullptr));

    size_t num_of_tests = rand() % 100;

    for (int j = 0; j != 100; ++j) {
        std::fstream ofs(
                filename + std::to_string(j) + postfix, std::ios_base::app);
        std::ostream_iterator<int> os_iter(ofs, "\n");
        *os_iter = 10 + rand() % 10;
        size_t size = rand() % 100;
        *os_iter = size;
        for (size_t i = 0; i != size; ++i) {
            *os_iter = rand() % 100;
        }
    }
}

/* Returns number of hits. */
size_t run_test(std::istream& is, std::ostream& os)
{
    size_t cache_size;
    is >> cache_size;

    caches::cache_t<int> cache(cache_size);

    size_t num_elements;
    is >> num_elements;

    size_t num_hits = 0;

    int tmp_element = 0;
    for (size_t i = 0; i != num_elements; ++i) {
        is >> tmp_element;

        size_t hit = cache.lookup_update(tmp_element, retSame);
        num_hits += hit;

        // num_hits += cache.lookup_update(tmp_element, retSame);
        print_2q(cache);
        std::cout << "HITS: " << num_hits << '\n';
        if (hit == true) {
            std::cout << "Hit of" << tmp_element << '\n';
            sleep(3);
        }
        sleep(1);
        system("clear");
    }

    return num_hits;
}

TEST(Cache2Q, Test)
{
    for (int j = 0; j != 100; ++j) {
        std::fstream ifs(
                std::string("/home/cicada44/cicada-main/edu/minor-projects/"
                            "cache/test/"
                            "dats/")
                + std::to_string(j) + std::string(".txt"));
        run_test(ifs, std::cout);
        // std::cout << '[' << j << ']' << " Hits: " << run_test(ifs, std::cout)
        //   << '\n';
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
