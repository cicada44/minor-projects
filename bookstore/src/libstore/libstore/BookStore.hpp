#pragma once

#include <libbook/Book.hpp>

#include <algorithm>
#include <numeric>
#include <optional>

#include <iterator>
#include <vector>

#include <iostream>
#include <string>

class Store {
public:
    virtual double get_revenue() const = 0;

private:
};

class BookStore : public Store {
    friend std::ostream& operator<<(std::ostream& os, const BookStore& b);

public:
    BookStore(const std::initializer_list<Book>& books_);

    virtual double get_revenue() const override;

    /* If book.ISBN is unique of actual books list - insert to the end of the
     * actual list of books. */
    inline void add_book(const Book& book);

    bool remove_book(const std::string& ISBN);

    bool contains_book(const std::string& ISBN) const;

    std::optional<Book> find_book(const std::string& ISBN) const;

    inline bool contains(const std::string& ISBN) const;

    inline const Book& operator[](const size_t ind) const noexcept;

    const std::string most_frequent_author() const;
    size_t max_pages_book() const;

    double avg_price() const;

private:
    double revenue;

    std::vector<Book> books;

    inline std::vector<Book>::const_iterator
    get_pos(const std::string& ISBN) const;
};

std::ostream& operator<<(std::ostream& os, const BookStore& b);
