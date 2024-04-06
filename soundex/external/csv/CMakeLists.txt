include(FetchContent)

FetchContent_Declare(
    csv
    GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser
    GIT_TAG master
)

FetchContent_MakeAvailable(csv)
