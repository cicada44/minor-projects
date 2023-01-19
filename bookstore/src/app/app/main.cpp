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

    return 0;
}