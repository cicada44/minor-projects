#ifndef __BOOKSTORE_H__
#define __BOOKSTORE_H__

#include <iostream>

#include <string>

#include <vector>

#include <iterator>

#include <libbook/Book.hpp>

#include <algorithm>

class Store {
public:
    virtual double get_revenue() const = 0;

private:
};

class BookStore : public Store {
    friend void
    interactive_mode(std::ostream& os, std::istream& is, BookStore& store);

    friend std::ostream& operator<<(std::ostream& os, const BookStore& b);
    friend std::istream& operator>>(std::istream& is, BookStore& b);

public:
    BookStore() = default;

    BookStore(const std::vector<Book>& books) : books(books)
    {
        for (const auto& c : books) {
            revenue += c.price;
        }
    }

    virtual double get_revenue() const override;

    void add_book(const Book& book);
    bool remove_book(const std::string& ISBN_to_delete);

    bool check_book(const std::string& isbn_to_find);
    Book find_book(const std::string& isbn_to_find);

private:
    double revenue;

    std::vector<Book> books;
};

std::ostream& operator<<(std::ostream& os, const BookStore& b);
std::istream& operator>>(std::istream& is, BookStore& b);

void interactive_mode(std::ostream& os, std::istream& is, BookStore& store);

#endif // __BOOKSTORE_H__