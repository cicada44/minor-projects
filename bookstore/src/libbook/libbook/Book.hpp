#ifndef __BOOK_H__
#define __BOOK_H__

#include <iostream>

#include <string>

#include <vector>

#include <iterator>

// #include <libstore/BookStore.hpp>

#include <algorithm>

class Book {
    friend class BookStore;

    friend std::ostream& operator<<(std::ostream& os, const Book& b);
    friend std::istream& operator>>(std::istream& is, Book& b);

public:
    Book() = default;

    Book(const std::string& ISBN,
         const std::string& author,
         const double price,
         const size_t pages)
        : ISBN(ISBN), author(author), price(price), pages(pages)
    {
    }

private:
    std::string ISBN;
    std::string author;

    double price;

    size_t pages;
};

std::ostream& operator<<(std::ostream& os, const Book& b);
std::istream& operator>>(std::istream& is, Book& b);

#endif // __BOOK_H__