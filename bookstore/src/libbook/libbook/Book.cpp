#include <libbook/Book.hpp>

#include <iostream>

const std::string& Book::get_isbn() const { return ISBN; }

const std::string& Book::get_author() const { return author; }

double Book::get_price() const { return price; }

double Book::get_pages() const { return pages; }

std::ostream& operator<<(std::ostream& os, const Book& b) {
    os << "ISBN: " << b.ISBN << '\t' << "author: " << b.author << '\t'
       << "pages: " << b.pages << '\t' << "price: " << b.price;
    return os;
}

bool ISBN_cmp(const Book& b1, const Book& b2) {
    return ((b1.ISBN == b2.ISBN) ? true : false);
}
