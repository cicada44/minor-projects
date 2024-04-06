set(target_name detector)

add_library(
    ${target_name}
    STATIC
        detector/detector.cpp
        detector/detector.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
        ${OpenCV_LIBS}
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
