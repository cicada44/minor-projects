#pragma once

#include <iostream>

#include <string>

class Book {
    friend class BookStore;

    friend std::ostream& operator<<(std::ostream& os, const Book& b);

public:
    Book(const std::string& ISBN,
         const std::string& author,
         const double price,
         const size_t pages)
        : ISBN(ISBN), author(author), price(price), pages(pages)
    {
    }

    const std::string& get_isbn() const;
    const std::string& get_author() const;
    double get_price() const;
    double get_pages() const;

private:
    std::string ISBN;
    std::string author;

    double price;

    size_t pages;
};

std::ostream& operator<<(std::ostream& os, const Book& b);
