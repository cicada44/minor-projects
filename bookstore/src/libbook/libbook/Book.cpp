#include <iostream>

#include <libbook/Book.hpp>

const std::string& Book::get_isbn() const
{
    return ISBN;
}

const std::string& Book::get_author() const
{
    return author;
}

double Book::get_price() const
{
    return price;
}

double Book::get_pages() const
{
    return pages;
}

std::ostream& operator<<(std::ostream& os, const Book& b)
{
    os << b.ISBN << ' ' << b.author << ' ' << b.pages << ' ' << b.price;
    return os;
}
