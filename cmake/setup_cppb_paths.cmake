
set(MG_BASE ${PROJECT_SOURCE_DIR} CACHE INTERNAL "cpp benchmarks project basedir" FORCE)
set(MG_BINARY_DIR ${CMAKE_BINARY_DIR} CACHE INTERNAL "cpp benchmarks project basedir" FORCE)
set(MG_INTERNAL_DEPS_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/_deps CACHE INTERNAL "internal install location for libs and includes" FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MG_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MG_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MG_BINARY_DIR}/bin)
set(CMAKE_PREFIX_PATH ${MG_INTERNAL_DEPS_INSTALL_PREFIX};${MG_BINARY_DIR/thirdparty})