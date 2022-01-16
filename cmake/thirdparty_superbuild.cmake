    add_external_project(GoogleBenchmark
            PACKAGE_NAME benchmark
            LIBRARIES
            libbenchmark.a
            libbenchmark_main.a
            CMAKE_ARGS
            -DCMAKE_CXX_STANDARD=20
            -DCMAKE_BUILD_TYPE=Release
            -DTHREADS_PREFER_PTHREAD_FLAG=ON
            -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
            -DCMAKE_CXX_FLAGS="-Wno-psabi"
            )
    add_external_project(fmt
            LIBRARIES
            libfmt.a
            CMAKE_ARGS
            -DCMAKE_CXX_STANDARD=20
            -DCMAKE_CXX_FLAGS="-Wno-psabi"
            )

    add_external_project(spdlog
            DEPENDS fmt
            LIBRARIES
            libspdlog.a
            CMAKE_ARGS
            -DCMAKE_CXX_STANDARD=20
            -DCMAKE_PROJECT_spdlog_INCLUDE=${PROJECT_SOURCE_DIR}/cmake/set_spdlog_vars.cmake
            -DSPDLOG_BUILD_EXAMPLE=OFF
            -DSPDLOG_FMT_EXTERNAL=ON
            -DSPDLOG_BUILD_SHARED=OFF
            -DCMAKE_BUILD_TYPE=Release
            )

    add_external_project(Catch2
            LIBRARIES
            libCatch2.a
            libCatch2Main.a
            CMAKE_ARGS
            -DCMAKE_CXX_STANDARD=20
            -DCMAKE_CXX_FLAGS="-Wno-psabi"
            -DCMAKE_BUILD_TYPE=Release
            )

    add_external_project(src MAIN)

    add_custom_target(clean-thirdparty
            COMMAND rm -Rf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/thirdparty ${TP_INSTALL_DIRS}
            )
