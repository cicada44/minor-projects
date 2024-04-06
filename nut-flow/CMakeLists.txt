cmake_minimum_required(VERSION 3.17)

project(
    NutFlow
    LANGUAGES CXX
    VERSION 1.0
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_program(CLANG_LIDY_EXE NAMES "clang-tidy" REQUIRED)
find_package(OpenCV REQUIRED)

add_subdirectory(src)
