#include <iostream>

#include <libstore/BookStore.hpp>

#include <vector>

int main()
{
    std::vector<Book> vec
            = {{std::string("1-1-1-1-1"), "Joh Fluent I", 1000, 1300},
               {std::string("1-1-1-1-2"), "Joh Fluent II", 1001, 1301},
               {std::string("1-1-1-1-3"), "Joh Fluent III", 1002, 1302}};

    BookStore store(vec);

    std::cout << store.contains_book("1-1-1-1-2") << '\n';

    std::cout << store.find_book("1-1-1-1-3").value().get_author() << '\n';

    store.remove_book("1-1-1-1-2");

    std::cout << store.find_book("1-1-1-1-2").has_value() << '\n';

    return 0;
}
