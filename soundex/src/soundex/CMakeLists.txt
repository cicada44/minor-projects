set(target_name soundex)

add_library(${target_name} STATIC soundex.cpp soundex.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src/
)
