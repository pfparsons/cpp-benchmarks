set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(TP_BUILD_TGT "build_all_thirdparty")
set(TP_CLEAN_TGT "clean_all_thirdparty")
set(TP_TGT_FOLDER "thirdparty")
add_custom_target(${TP_BUILD_TGT})
set_target_properties(${TP_BUILD_TGT} PROPERTIES FOLDER ${TP_TGT_FOLDER})
add_custom_target(${TP_CLEAN_TGT})
set_target_properties(${TP_CLEAN_TGT} PROPERTIES FOLDER ${TP_TGT_FOLDER})

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

function(setup_thirdparty_lib_build name)

    # Parse function arguments
    set(options DISABLE)
    set(scalar_args PACKAGE_NAME)
    set(list_args CMAKE_ARGS)
    cmake_parse_arguments(ARGS "${options}" "${scalar_args}" "${list_args}" ${ARGN})

    # Default package name for find_package() to the name supplied if not explicitly specified
    if (NOT DEFINED ARGS_PACKAGE_NAME)
        set(ARGS_PACKAGE_NAME ${name})
    endif ()

    # Try to find the package
    message("Looking for ${ARGS_PACKAGE_NAME}...")
    find_package(${ARGS_PACKAGE_NAME} CONFIG QUIET)

    # Var for checking the option to build from bundled src if needed
    string(TOUPPER ${ARGS_PACKAGE_NAME} LIB)

    # Handle result of find_package()
    if (NOT ${ARGS_PACKAGE_NAME}_FOUND AND NOT MG_USE_BUNDLED_${LIB})
        message(WARNING "${ARGS_PACKAGE_NAME} not found and MG_USE_BUNDLED_${LIB} set to ${MG_USE_BUNDLED_${LIB}}")
    elseif (NOT ${ARGS_PACKAGE_NAME}_FOUND AND MG_USE_BUNDLED_${LIB})
        message("Could not find ${ARGS_PACKAGE_NAME}. Building from bundled source...")

        # Set variable to the bundled package sources CMakeLists.txt
        set(CMAKELISTSDIR ${CMAKE_CURRENT_LIST_DIR}/${name})

        # Set variable to specify the build folder
        set(BUILD_DIR ${MG_BINARY_DIR}/thirdparty/${name})

        # Clean out previous build if it exists
        file(REMOVE_RECURSE ${BUILD_DIR})

        # Configure external project
        execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKELISTSDIR} -B ${BUILD_DIR} -G ${CMAKE_GENERATOR} -DCMAKE_INSTALL_PREFIX=${MG_INTERNAL_DEPS_INSTALL_PREFIX} ${ARGS_CMAKE_ARGS} )

        # Build
        execute_process(COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR})

        # Install in project build _deps folder
        execute_process(COMMAND ${CMAKE_COMMAND} --install ${BUILD_DIR})

        # Add some targets to allow rebuilding post-config
        #  Build package
        add_custom_target(build-${name} COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR})
        set_target_properties(build-${name} PROPERTIES FOLDER ${TP_TGT_FOLDER})
        add_custom_command(TARGET build-${name} POST_BUILD COMMAND ${CMAKE_COMMAND} --install ${BUILD_DIR})
        add_dependencies(${TP_BUILD_TGT} build-${name})
        #  Clean package
        add_custom_target(clean-${name} COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR} --target clean)
        set_target_properties(clean-${name} PROPERTIES FOLDER ${TP_TGT_FOLDER})
        add_dependencies(${TP_CLEAN_TGT} clean-${name})

        # Put the thirdparty lib _DIR variable into the cache so we can find it with find_package later
        set(${ARGS_PACKAGE_NAME}_DIR ${INSTALL_DIR} CACHE INTERNAL "third party lib ${ARGS_PACKAGE_NAME}" FORCE)

    elseif(${ARGS_PACKAGE_NAME}_FOUND)
        message("Found ${ARGS_PACKAGE_NAME}")
    else()
        message(FATAL_ERROR "Unable to find ${ARGS_PACKAGE_NAME} and could not build from bundled source - try manually installing / building")
    endif ()

endfunction()
