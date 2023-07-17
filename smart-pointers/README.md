# Smart Pointers

This project provides the implementation of `unique_ptr` and `shared_ptr` classes in C++.

## Introduction

Smart pointers are C++ classes that provide automatic memory management. They are used to manage dynamically allocated objects and ensure proper cleanup and deallocation without the need for manual memory management.

This project implements two types of smart pointers:

- `unique_ptr`: A smart pointer that manages the ownership of an object exclusively. It ensures that only one `unique_ptr` instance can own the object at any given time.

- `shared_ptr`: A smart pointer that allows multiple instances of `shared_ptr` to share the ownership of an object. It keeps track of the number of references to the object and automatically deallocates it when there are no more references.

## Compilation and Running

To compile and run the project, follow these steps:

1. Building
   
        cmake --preset release

2. Running

        cmake --build --preset release

After the build is successful, you will find two binaries in the build directory:

    ./build/release/bin/test: Binary for running the test suite.
    ./build/release/bin/smart_pointers: Binary for running an example program using smart pointers.

Run the test suite:

    ./build/release/bin/test

This will execute the test suite to ensure that the smart pointer classes are working correctly.

Run the YOUR handwritten program:

    ./build/release/bin/smart_pointers


## Contributing

Contributions to this project are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.