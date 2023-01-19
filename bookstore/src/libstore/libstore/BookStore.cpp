#include <libstore/BookStore.hpp>

#include <libbook/Book.hpp>

#include <functional>

#include <iostream>

#include <iomanip>

#include <map>

double BookStore::get_revenue() const
{
    return revenue;
}

void BookStore::add_book(const Book& book)
{
    books.push_back(book);
    revenue += book.price;
}

bool BookStore::remove_book(const std::string& ISBN_to_delete)
{
    bool flag = 0;
    books.erase(std::find_if(
            books.begin(), books.end(), [ISBN_to_delete](const Book& book) {
                // flag = 1;
                return (ISBN_to_delete == book.ISBN);
            }));

    return flag;
}

bool BookStore::find_book(const std::string& isbn_to_find)
{
    return (std::find_if(
                    books.begin(),
                    books.end(),
                    [isbn_to_find](Book& b) {
                        return (b.ISBN == isbn_to_find);
                    })
            != books.end())
            ? 1
            : 0;
}

void interactive_mode(std::ostream& os, std::istream& is, BookStore& store)
{
    using std::function;
    using std::map;
    using std::setfill;
    using std::setw;
    using std::string;

    int option;

    map<int, string> options
            = {{1, "ADD NEW BOOK"},
               {2, "DELETE BOOK"},
               {3, "FIND BOOK"},
               {4, "OUTPUT BOOKS"},
               {5, "EXIT"}};

    const int char_num_to_center = 50;
    const int padding_strings = 48;
    const int padding_numbers = 1;

    os << setfill('-') << setw(char_num_to_center) << "" << '\n';
    os << setfill(' ') << '|' << setw(char_num_to_center / 2) << "BOOKSTORE"
       << setfill(' ') << setw(char_num_to_center / 2) << "|\n";
    os << setfill('-') << setw(char_num_to_center) << ""
       << "\n\n";

    os << setfill(' ') << "OPTION" << setw(char_num_to_center - 5)
       << "OPERATION\n\n";

    for (const auto& c : options) {
        os << setfill(' ') << setw(padding_numbers) << setfill(' ') << c.first
           << setfill(' ') << setw(padding_strings) << setfill(' ') << c.second
           << setfill(' ') << '\n';
    }

    // std::istream_iterator<int> user_option(is);

    Book input_book;

    while (1) {
        os << "\nENTER THE OPTION ➯  ";
        is >> option;

        if (option == 1) {
            is >> input_book;
            store.add_book(input_book);
        } else if (option == 2) {
            string input_isbn;
            is >> input_isbn;
            store.remove_book(input_isbn);
        } else if (option == 3) {
            string input_isbn;
            is >> input_isbn;
            store.find_book(input_isbn);
        } else if (option == 4) {
            os << store;
        } else {
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const BookStore& b)
{
    std::copy(b.books.begin(), b.books.end(), std::ostream_iterator<Book>(os));
    return os;
}

std::istream& operator>>(std::istream& is, BookStore& b)
{
    std::istream_iterator<Book> is_iter(std::cin);

    while (is_iter != std::istream_iterator<Book>()) {
        b.books.push_back(*is_iter);
    }

    return is;
}
