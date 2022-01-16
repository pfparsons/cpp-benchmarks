find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(tl-expected REQUIRED)
find_package(tl-ranges REQUIRED)
find_package(tl-generator REQUIRED)
find_package(type_safe REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/thirdparty/Catch2/extras)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

set(DSPDLOG_BUILD_SHARED OFF)

#-----------------------------------------------------------------------------------------------------------------------
# Allocators Tests
#-----------------------------------------------------------------------------------------------------------------------

add_executable(test
        allocator/test_allocators.cpp
        buffer/test_buffer.cpp
        io/test_chunker.cpp
        io/test_file.cpp
        )

target_include_directories(test
        PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        PRIVATE
        tl::ranges
        type_safe
)

target_link_libraries(test
        PRIVATE
        fmt::fmt
        spdlog::spdlog
        neo::neo
        tl::expected
        Catch2::Catch2WithMain
        )

configure_file(data/city_country.csv data/city_country.csv COPYONLY)
configure_file(data/first_names.txt data/first_names.txt COPYONLY)

catch_discover_tests(test)
