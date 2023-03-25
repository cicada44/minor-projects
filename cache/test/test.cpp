#include "../src/cache/cache.hpp"

#include <gtest/gtest.h>

#include <cstdlib>
#include <vector>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

#include <iostream>

int retSame(int key)
{
    return key;
}

void generate()
{
    std::string filename
            = "/home/cicada44/cicada-main/edu/minor-projects/cache/test/"
              "data";
    std::string postfix = ".txt";
    srand(time(nullptr));

    size_t num_of_tests = rand() % 100;

    for (int j = 0; j != 100; ++j) {
        std::fstream ofs(
                filename + postfix + std::to_string(j), std::ios_base::app);
        std::ostream_iterator<int> os_iter(ofs, "\n");
        size_t size = rand() % 100;
        *os_iter = size;
        for (size_t i = 0; i != size; ++i) {
            *os_iter = rand();
        }
    }
}

int main(int argc, char** argv)
{
    generate();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
