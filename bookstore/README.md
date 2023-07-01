# Trivial bookstore

Bookstore is a C++ project that represents a simple bookstore management system. It consists of several header files that define classes and their member functions for handling books and the bookstore.

## Files

- [Book class](./src/libbook/libbook/Book.hpp)
- [BookStore class](./src/libstore/libstore/BookStore.hpp)

## Usage

To compile and all files, execute the following command:

     cmake --preset release
     cmake --build --preset release

To run the [tests](./test/test/test.cpp), execute the following command:

     ./build/release/bin/test

To run the [main](./src/app/app/main.cpp), execute the following command:

     ./build/release/bin/app
