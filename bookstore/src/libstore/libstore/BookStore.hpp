#pragma once

#include <libbook/Book.hpp>

#include <iostream>

#include <string>

#include <vector>

#include <iterator>

#include <optional>

#include <numeric>

#include <algorithm>

class Store {
public:
    virtual double get_revenue() const = 0;

private:
};

class BookStore : public Store {
    friend std::ostream& operator<<(std::ostream& os, const BookStore& b);

public:
    BookStore(const std::vector<Book>& books_) : books(books_)
    {
        for (const auto& c : books_) {
            revenue += c.price;
        }
    }

    virtual double get_revenue() const override;

    void add_book(const Book& book);
    bool remove_book(const std::string& ISBN_to_delete);

    bool contains_book(const std::string& isbn_to_find) const;

    std::optional<Book> find_book(const std::string& isbn_to_find) const;

private:
    double revenue;

    std::vector<Book> books;
};

std::ostream& operator<<(std::ostream& os, const BookStore& b);
