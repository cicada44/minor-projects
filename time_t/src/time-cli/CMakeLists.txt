set(target_name time-cli)

add_executable(${target_name})

target_sources(
    ${target_name}
    PRIVATE
        time-cli/main.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/libcsc
)
