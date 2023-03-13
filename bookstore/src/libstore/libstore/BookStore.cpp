#include <libbook/Book.hpp>
#include <libstore/BookStore.hpp>

#include <map>

#include <algorithm>

#include <optional>
#include <utility>

#include <iostream>

BookStore::BookStore(const std::initializer_list<Book>& il) : books(il)
{
    for (const auto& c : il) {
        revenue += c.price;
    }
}

inline double BookStore::get_revenue() const
{
    return revenue;
}

void BookStore::add_book(const Book& book)
{
    if (!contains(book.ISBN)) {
        books.push_back(book);
    }
    revenue += book.price;
}

bool BookStore::remove_book(const std::string& ISBN)
{
    auto deleteable = get_pos(ISBN);

    if (deleteable == books.end()) {
        return 0;
    }

    books.erase(deleteable);

    return 1;
}

std::optional<Book> BookStore::find_book(const std::string& ISBN) const
{
    auto book = get_pos(ISBN);
    return (book == books.end()) ? std::nullopt : std::optional<Book>(*book);
}

inline bool BookStore::contains(const std::string& ISBN) const
{
    return (get_pos(ISBN) != books.cend()) ? true : false;
}

inline std::vector<Book>::const_iterator
BookStore::get_pos(const std::string& ISBN) const
{
    return std::find_if(books.cbegin(), books.cend(), [&ISBN](const Book& b) {
        return ISBN == b.ISBN;
    });
}

const Book& BookStore::operator[](const size_t ind) const noexcept
{
    return books[ind];
}

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

double BookStore::avg_price() const
{
    return (revenue / books.size());
}

size_t BookStore::max_pages_book() const
{
    size_t max_pgs = 0;

    std::for_each(books.begin(), books.end(), [&max_pgs](const Book& b) {
        if (b.pages > max_pgs) {
            max_pgs += b.pages;
        }
    });

    return max_pgs;
}

std::ostream& operator<<(std::ostream& os, const BookStore& b)
{
    std::copy(b.books.begin(), b.books.end(), std::ostream_iterator<Book>(os));
    return os;
}
