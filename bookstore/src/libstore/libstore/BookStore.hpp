// -----------------------------------------------------------------------------
//
// Header for class 'BookStore' in C++
//
// -----------------------------------------------------------------------------

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

    /* Returns revenue. */
    virtual double get_revenue() const override;

    /* Returns number of containing books. */
    size_t count() const;

    /* Returns average price for 1 book. */
    double avg_price() const;

    /* Returns most frequent author of the actual list of books (author with
     * largest number of books). */
    const std::string most_frequent_author() const;

    /* Returns largest number of pages of book in bookstore. */
    size_t max_pages() const;

    /* Returns book with largest number of pages in bookstore. */
    const Book max_pages_book() const;

    /* Returns constant reference to book containing on index ind. */
    const Book& operator[](const size_t ind) const noexcept;

    /* If book.ISBN is unique -- add book to the and of the list of books.
     * Otherwise - do nothing. */
    void add_book(const Book& book);

    /* If there is no such book with ISBN - do nothing. Otherwise - deletes book
     * from the list of books. Returns true if removal happened, otherwise -
     * return false.  */
    bool remove_book(const std::string& ISBN);

    /* Check the book with ISBN in list. If there is no such book returns false.
     * Otherwise returns true.  */
    bool contains(const std::string& ISBN) const;

    /* Finds book with ISBN in bokstore. Returns std::nullopt if book isn't in
     * container. Otherwise return std::optional<Book>. */
    std::optional<Book> find_book(const std::string& ISBN) const;

    /* Returns vector of books with author auth. If there isn't any books from
     * such author returns empty vector. */
    std::vector<Book> get_author_books(const std::string& auth);

private:
    double revenue;

    std::vector<Book> books;

    /* Returns constant iterator to first meeted book with ISBN. If there is no
     * such book returns cend() of the list. */
    inline std::vector<Book>::const_iterator get_pos(
        const std::string& ISBN) const;
};

/* Prints all books in the list to os. */
std::ostream& operator<<(std::ostream& os, const BookStore& b);
