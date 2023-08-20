set(target_name nutflow)

add_executable(
    ${target_name}
)

target_sources(
    ${target_name}
    PRIVATE
        app/main.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
        ${OpenCV_LIBS}
        detector
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
