set(target smart_pointers)

add_executable(${target})

include(CompileOptions)
set_compile_options(${target})

target_sources(
    ${target}
    PRIVATE
        src/main.cpp
)
