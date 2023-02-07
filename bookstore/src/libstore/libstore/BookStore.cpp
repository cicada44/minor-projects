#include <libbook/Book.hpp>

#include <libstore/BookStore.hpp>

#include <iostream>

double BookStore::get_revenue() const
{
    return revenue;
}

void BookStore::add_book(const Book& book)
{
    books.push_back(book);
    revenue += book.price;
}

bool BookStore::remove_book(const std::string& ISBN_to_delete)
{
    auto deleted_book = std::find_if(
            books.begin(), books.end(), [ISBN_to_delete](const Book& book) {
                return (ISBN_to_delete == book.ISBN);
            });

    if (deleted_book == books.end()) {
        return 0;
    }

    books.erase(deleted_book);

    return 1;
}

bool BookStore::contains_book(const std::string& isbn_to_find) const
{
    return std::find_if(
                   books.begin(),
                   books.end(),
                   [isbn_to_find](const Book& b) {
                       return b.ISBN == isbn_to_find;
                   })
            != books.end();
}

std::optional<Book> BookStore::find_book(const std::string& isbn_to_find) const
{
    auto book = std::find_if(
            books.begin(), books.end(), [isbn_to_find](const Book& b) {
                return b.ISBN == isbn_to_find;
            });
    return (book == books.end()) ? std::nullopt : std::optional<Book>(*book);
}

std::ostream& operator<<(std::ostream& os, const BookStore& b)
{
    std::copy(b.books.begin(), b.books.end(), std::ostream_iterator<Book>(os));
    return os;
}
