# Trivial bookstore

Bookstore is a C++ project that represents a simple bookstore management system. It consists of several header files that define classes and their member functions for handling books and the bookstore.

## Files

- [Book class](./src/libbook/libbook/Book.hpp)
- [BookStore class](./src/libstore/libstore/BookStore.hpp)

## Usage

To compile the [main](./src/app/app/main.cpp) file, execute the following command:

     cmake --preset release
     cmake --build --preset release
     ./build/release/bin/app

To run the [tests](./test/test/test.cpp), execute the following command:

     cmake --preset release
     cmake --build --preset release
     ./build/release/bin/test


