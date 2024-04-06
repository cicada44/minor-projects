set(target_name app)

add_executable(${target_name} main.cpp)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
        soundex
        csv
        pugixml
)

target_link_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src/
        
)

include_directories(
    ${CMAKE_SOURCE_DIR}/${FolderSource}
    ${csv_SOURCE_DIR}/single_include
)

