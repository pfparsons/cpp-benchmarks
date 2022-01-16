set(BM_NAME "allocators_benchmark")

add_executable(${BM_NAME}
        allocaors_bench.cpp
        )
set(THREADS_PREFER_PTHREAD_FLAG ON)

message("************************* ${CMAKE_MODULE_PATH}")
message("************************* benchmark_DIR = ${benchmark_DIR}")
find_package(Threads REQUIRED)
find_package(benchmark)

target_include_directories(${BM_NAME}
        PRIVATE
        ${PROJECT_INCLUDES}
        )

target_link_libraries(${BM_NAME}
        PRIVATE
        neo::neo
        Threads::Threads
        benchmark::benchmark
)