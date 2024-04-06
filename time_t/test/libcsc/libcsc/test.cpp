#include <gtest/gtest.h>

#include <limits>
#include <tuple>

#include <libcsc/time.h>

using namespace time_utils;
using namespace time_utils::literals;

TEST(TimeProcessing, Initialization) {
    // Simple
    {
        const Time real({1, 1, 1, 1});
        const time_view expected{1, 1, 1, 1};
        ASSERT_TRUE(real.get_time() == expected);
    }

    // Only days
    {
        const Time real({1, 0, 0, 0});
        const time_view expected{1, 0, 0, 0};
        ASSERT_TRUE(real.get_time() == expected);
    }

    // Overloading
    {
        const Time real({10, 27, 130, 400});
        const time_view expected{11, 5, 16, 40};
        ASSERT_TRUE(real.get_time() == expected);
    }

    // Only seconds
    {
        const Time real({0, 0, 0, 912837});
        const time_view expected{10, 13, 33, 57};
        ASSERT_TRUE(real.get_time() == expected);
    }
}

TEST(TimeProcessing, Decreasing) {
    // Simple 1
    {
        const TimeSpan real = 2_d - 1_d;
        const TimeSpan expected = 86400_ss;
        ASSERT_TRUE(real.s_ == expected.s_);
    }

    // Simple 2
    {
        const TimeSpan real = 1000_s - 250_s;
        const TimeSpan expected = 750_ss;
        ASSERT_TRUE(real.s_ == expected.s_);
    }

    // Simple 3
    {
        const TimeSpan real = 129347_s - 27634_s;
        const TimeSpan expected = 101713_ss;
        ASSERT_TRUE(real.s_ == expected.s_);
    }

    // NAN
    {
        const TimeSpan real = 100_s - 10000_s;
        const TimeSpan expected = {
            std::numeric_limits<unsigned long long int>::quiet_NaN()};
        ASSERT_TRUE(real.s_ == expected.s_);
    }
}

TEST(TimeProcessing, increasing) {
    // Simple 1
    {
        const Time real = 1_s + 1_ss;
        const Time expected = 2_s;
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }

    // Simple 2
    {
        const Time real = 1_d + 2_sh + 3_sm + 4_ss;
        const Time expected(1, 2, 3, 4);
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }

    // Simple 3
    {
        const Time real = 1_d + 48_sh + 3_sm + 4_ss;
        const Time expected(3, 0, 3, 4);
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }
}

TEST(TimeProcessing, decreasing) {
    // Simple 1
    {
        const Time real = 1_d + 1_sh + 1_sm + 1_ss - 1_sd - 1_ss;
        const Time expected = 1_h + 1_sm;
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }

    // Simple 2
    {
        const Time real = 1_d + 1_sh + 1_sm + 1_ss - (1_sd + 1_sh + 1_sm + 1_ss);
        const Time expected;
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }

    // Simple 3
    {
        const Time real = 1_d + 1_sh + 1_sm - 1_sh - 1_sm;
        const Time expected = 1_d;
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }

    // NAN
    {
        const auto nan = std::numeric_limits<unsigned long long int>::quiet_NaN();
        const Time real = 1_d - 2_sd;
        const Time expected(nan, nan, nan, nan);
        ASSERT_TRUE(real.get_time() == expected.get_time());
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
