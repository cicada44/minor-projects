#include <libbook/Book.hpp>
#include <libstore/BookStore.hpp>

#include <algorithm>
#include <map>
#include <optional>
#include <utility>

#include <iostream>

/* Initializer list constructor. */
BookStore::BookStore(const std::initializer_list<Book>& il)
{
    auto beg = il.begin();
    for (auto i = il.begin(); i != il.end(); ++i) {
        if (std::find_if(
                    beg,
                    i,
                    [&i](const Book& b) {
                        return (b.get_isbn() == i->get_isbn());
                    })
            == i) {
            books.push_back(*i);
            revenue += i->price;
        }
    }
}

/* Returns revenue. */
inline double BookStore::get_revenue() const
{
    return revenue;
}

/* If book.ISBN is unique -- add book to the and of the list of books.
 * Otherwise - do nothing. */
void BookStore::add_book(const Book& book)
{
    if (!contains(book.ISBN)) {
        books.push_back(book);
        revenue += book.price;
    }
}

/* If there is no such book with ISBN - do nothing. Otherwise - deletes book
 * from the list of books. Returns true if removal happened, otherwise - return
 * false.  */
bool BookStore::remove_book(const std::string& ISBN)
{
    auto deletable = get_pos(ISBN);

    if (deletable == books.end()) {
        return 0;
    }

    books.erase(deletable);
    revenue -= deletable->price;

    return 1;
}

/* Finds book with ISBN in bokstore. Returns std::nullopt if book isn't in
 * container. Otherwise return std::optional<Book>. */
std::optional<Book> BookStore::find_book(const std::string& ISBN) const
{
    auto book = get_pos(ISBN);
    return (book == books.end()) ? std::nullopt : std::optional<Book>(*book);
}

/* Check the book with ISBN in list. If there is no such book returns false.
 * Otherwise returns true.  */
bool BookStore::contains(const std::string& ISBN) const
{
    return (get_pos(ISBN) != books.cend()) ? true : false;
}

/* Returns constant iterator to first meeted book with ISBN. If there is no such
 * book returns cend() of the list. */
inline std::vector<Book>::const_iterator
BookStore::get_pos(const std::string& ISBN) const
{
    return std::find_if(books.cbegin(), books.cend(), [&ISBN](const Book& b) {
        return ISBN == b.ISBN;
    });
}

/* Returns constant reference to book containing on index ind. */
const Book& BookStore::operator[](const size_t ind) const noexcept
{
    return books[ind];
}

/* Returns most frequent author of the actual list of books (author with
 * largest number of books). */
const std::string BookStore::most_frequent_author() const
{
    std::map<std::string, size_t> book_on_auth;

    for (const auto& c : books) {
        ++book_on_auth[c.author];
    }

    std::string most_freq_a;
    size_t cnt_books = 0;

    std::for_each(
            book_on_auth.begin(),
            book_on_auth.end(),
            [&most_freq_a,
             &cnt_books](const std::pair<std::string, size_t>& p) {
                if (p.second > cnt_books) {
                    cnt_books = p.second;
                    most_freq_a = p.first;
                }
            });

    return most_freq_a;
}

/* Returns average price for 1 book. */
double BookStore::avg_price() const
{
    return (revenue / books.size());
}

/* Returns largest number of pages of book in bookstore. */
size_t BookStore::max_pages() const
{
    size_t max_pgs = 0;

    std::for_each(books.begin(), books.end(), [&max_pgs](const Book& b) {
        if (b.pages > max_pgs) {
            max_pgs = b.pages;
        }
    });

    return max_pgs;
}

/* Returns book with largest number of pages in bookstore. */
const Book BookStore::max_pages_book() const
{
    Book max_pgs_book(*books.begin());

    std::for_each(books.begin(), books.end(), [&max_pgs_book](const Book& b) {
        if (b.pages > max_pgs_book.pages) {
            max_pgs_book = b;
        }
    });

    return max_pgs_book;
}

/* Prints all books in the list to os. */
std::ostream& operator<<(std::ostream& os, const BookStore& b)
{
    std::copy(b.books.begin(), b.books.end(), std::ostream_iterator<Book>(os));
    return os;
}
