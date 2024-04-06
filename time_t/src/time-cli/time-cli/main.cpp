#include <libcsc/time.h>

#include <iostream>

using namespace time_utils;
using namespace time_utils::literals;

int main() {
    const Time t1(12, 13, 14, 15);
    const Time t2(11, 12, 13, 14);

    std::cout << t1 << '\n';
    std::cout << t2 << '\n';
    std::cout << '\n';

    std::cout << "t1 + 1h = " << t1 + 3600_ss << '\n';
    std::cout << "t1 + 1d = " << t1 + 86400_ss << '\n';
    std::cout << "t2 + 1h = " << t2 + 3600_ss << '\n';
    std::cout << "t2 + 1d = " << t2 + 86400_ss << '\n';

    std::cout << "(t1 == t2): " << ((t1 <=> t2) == 0 ? "true" : "false") << "\n";
    std::cout << "But (t1 == t2 + 1d1h1m1s): "
              << ((t1 <=> t2 + TimeSpan(to_secs(1, 1, 1, 1))) == 0 ? "true" : "false")
              << "\n";
}
