#pragma once

#include <libbook/Book.hpp>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

#include <iostream>

class Store {
public:
    virtual double get_revenue() const = 0;

private:
};

/* Each book in bookstore is unique and immutable. */
class BookStore : public Store {
    friend std::ostream& operator<<(std::ostream& os, const BookStore& b);

public:
    BookStore(const std::initializer_list<Book>& books_);

    /* Accessors */
    virtual double get_revenue() const override;
    size_t count() const;
    double avg_price() const;

    const std::string most_frequent_author() const;
    size_t max_pages() const;
    const Book max_pages_book() const;
    const Book& operator[](const size_t ind) const noexcept;

    /* Modifiers */
    void add_book(const Book& book);
    bool remove_book(const std::string& ISBN);

    /* Finders */
    bool contains(const std::string& ISBN) const;
    std::optional<Book> find_book(const std::string& ISBN) const;
    std::vector<Book> get_author_books(const std::string& auth);

private:
    double revenue;

    std::vector<Book> books;

    inline std::vector<Book>::const_iterator
    get_pos(const std::string& ISBN) const;
};

std::ostream& operator<<(std::ostream& os, const BookStore& b);
