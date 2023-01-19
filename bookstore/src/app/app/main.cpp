#include <iostream>

#include <iomanip>

#include <string>

#include <libstore/BookStore.hpp>

#include <libbook/Book.hpp>

using std::cin;
using std::cout;
using std::string;

int main()
{
    BookStore store;

    interactive_mode(cout, cin, store);

    // cout << std::setw(10) << "1\n"
    //      << std::setw(10) << "11\n"
    //      << std::setw(10) << "111\n"
    //      << std::setw(10) << "1111\n"
    //      << std::setw(10) << "11111\n"
    //      << std::setw(10) << "111111\n"
    //      << std::setw(10) << "1111111\n"
    //      << std::setw(10);

    return 0;
}