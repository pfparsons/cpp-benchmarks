include(${PROJECT_SOURCE_DIR}/cmake/build_config.cmake)


setup_thirdparty_lib_build(fmt
        CMAKE_ARGS
        -DCMAKE_CXX_STANDARD=20
        -DCMAKE_PROJECT_FMT_INCLUDE=${PROJECT_SOURCE_DIR}/cmake/thirdparty/set_fmt_vars.cmake
        -DFMT_TEST=OFF
        )

setup_thirdparty_lib_build(spdlog
        CMAKE_ARGS
        -DCMAKE_CXX_STANDARD=20
        -DSPDLOG_BUILD_EXAMPLE=OFF
        -DSPDLOG_FMT_EXTERNAL=ON
        -DSPDLOG_BUILD_SHARED=OFF
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=BOTH
        -DCMAKE_FIND_ROOT_PATH=${MG_INTERNAL_DEPS_INSTALL_PREFIX}
        )

setup_thirdparty_lib_build(Catch2
        CMAKE_ARGS
        -DCMAKE_CXX_STANDARD=20
        -DCMAKE_CXX_FLAGS="-Wno-psabi"
        -DCMAKE_BUILD_TYPE=Release
        )

setup_thirdparty_lib_build(GoogleBenchmark
        PACKAGE_NAME benchmark
        CMAKE_ARGS
        -DBENCHMARK_ENABLE_TESTING=OFF
        -DCMAKE_CXX_STANDARD=20
        -DCMAKE_BUILD_TYPE=Release
        -DTHREADS_PREFER_PTHREAD_FLAG=ON
        -DCMAKE_CXX_FLAGS="-Wno-psabi"
        )

setup_thirdparty_lib_build(tl-expected
        LIBRARY expected
        CMAKE_ARGS
        -DFETCHCONTENT_FULLY_DISCONNECTED=ON
        -DBUILD_TESTING=OFF
        )

setup_thirdparty_lib_build(tl-generator
        LIBRARY generator
        CMAKE_ARGS
        -DFETCHCONTENT_FULLY_DISCONNECTED=ON
        -DBUILD_TESTING=OFF
        )

setup_thirdparty_lib_build(tl-ranges
        LIBRARY generator
        CMAKE_ARGS
        -DFETCHCONTENT_FULLY_DISCONNECTED=ON
        -DBUILD_TESTING=OFF
        )

setup_thirdparty_lib_build(debug_assert
        CMAKE_ARGS
        )

setup_thirdparty_lib_build(type_safe
        CMAKE_ARGS
        -DTYPE_SAFE_BUILD_TEST_EXAMPLE=OFF
        )
