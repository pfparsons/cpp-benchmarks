cmake_minimum_required(VERSION 3.14)
project(cpp-benchmarks)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#set(CMAKE_FIND_DEBUG_MODE ON)
set(CMAKE_POLICY_DEFAULT_CMP0063 NEW)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

option(MG_USE_BUNDLED_FMT "Use the bundled fmt library" ON)
option(MG_USE_BUNDLED_CATCH2 "Use the bundled Catch2 library" ON)
option(MG_USE_BUNDLED_BENCHMARK "Use the bundled GoogleBenchmark" ON)
option(MG_USE_BUNDLED_SPDLOG "Use the bundled spdlog library" ON)
option(MG_USE_BUNDLED_TL-EXPECTED "Use bundled tl-expected" ON)
option(MG_USE_BUNDLED_TL-GENERATOR "Use bundled tl-generator" ON)
option(MG_USE_BUNDLED_TL-RANGES "Use bundled tl-generator" ON)
option(MG_USE_BUNDLED_TYPE_SAFE "Use bundled type_safe" ON)
option(MG_USE_BUNDLED_DEBUG_ASSERT "Use bundled debug_assert" ON)

# TODO - may remove this
option(MG_USE_BUNDLED_NEO "Use bundled neo lib" ON)

include(setup_cppb_paths)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty)
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/type_safe)


add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/neo)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)



