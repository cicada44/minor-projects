#pragma once

#include <string>

#include <iostream>

class Book {
    friend class BookStore;

    friend std::ostream& operator<<(std::ostream& os, const Book& b);
    friend bool ISBN_cmp(const Book& b1, const Book& b2);

public:
    Book(const std::string& ISBN,
         const std::string& author,
         const double price,
         const size_t pages)
        : ISBN(ISBN), author(author), price(price), pages(pages)
    {
    }

    /* Returns ISBN of book. */
    const std::string& get_isbn() const;

    /* Returns author of book. */
    const std::string& get_author() const;

    /* Returns price of book. */
    double get_price() const;

    /* Returns number of pages of book.  */
    double get_pages() const;

private:
    std::string ISBN;
    std::string author;

    double price;

    size_t pages;
};

/*  Print book in format:
 *       ISBN: <ISBN>   author: <author>   pages: <pages>    price: <price>
 */
std::ostream& operator<<(std::ostream& os, const Book& b);

/* Returns true if b1.ISBN == b2.ISBN.
   If not returns false. */
bool ISBN_cmp(const Book& b1, const Book& b2);
