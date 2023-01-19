set(target_name store)

add_library(
    ${target_name}
    STATIC
        libstore/BookStore.cpp   
        libstore/BookStore.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
  ${target_name}
  PUBLIC
    book
)

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)