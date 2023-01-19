cmake_minimum_required(VERSION 3.22)

project(
    BookStore
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# find_program(CLANG_TIDY_EXE )

add_subdirectory(src)
