set(target_name cache)

add_library(
    ${target_name}
    STATIC
        cache.cpp
        cache.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

