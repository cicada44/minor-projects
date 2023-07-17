set(target test)

add_executable(${target})

include(CompileOptions)
set_compile_options(${target})

target_sources(
    ${target}
    PRIVATE
        test/test.cpp
)

find_package(GTest REQUIRED)
target_link_libraries(
    ${target}
    PRIVATE
        ${GTEST_LIBRARIES}
        pthread
)

target_include_directories(
    ${target}
    PRIVATE
        ${GTEST_INCLUDE_DIRS}
)
