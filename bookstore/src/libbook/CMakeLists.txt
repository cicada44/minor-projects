set(target_name book)

add_library(
    ${target_name}
    STATIC
        libbook/Book.cpp
        libbook/Book.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)