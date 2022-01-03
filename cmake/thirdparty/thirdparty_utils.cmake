include(ExternalProject)
include(GNUInstallDirs)

set_property(DIRECTORY PROPERTY EP_STEP_TARGETS install)
set_property(DIRECTORY PROPERTY EP_BASE Dependencies)

set(TP_BYPRODUCTS "" CACHE INTERNAL " " FORCE)
set(TP_TARGETS "" CACHE INTERNAL " " FORCE)
set(TP_INSTALL_DIRS "" CACHE INTERNAL " " FORCE)
set(DEPENDENCIES "" CACHE INTERNAL " " FORCE)

function(add_external_project name)
    # -----------------------------------------------------------------------------------------------------------------#
    # Parse function arguments
    # -----------------------------------------------------------------------------------------------------------------#
    set(options DISABLE MAIN)
    set(scalar_args PACKAGE_NAME)
    set(list_args DEPENDS LIBRARIES CMAKE_ARGS)
    cmake_parse_arguments(ARGS "${options}" "${scalar_args}" "${list_args}" ${ARGN})

    # Default package name for find_package() to the name supplied if not explicitly specified
    if (NOT DEFINED ARGS_PACKAGE_NAME)
        set(ARGS_PACKAGE_NAME ${name})
    endif ()

    # -----------------------------------------------------------------------------------------------------------------#
    # Verbose Output
    # -----------------------------------------------------------------------------------------------------------------#
    message(" ")
    message("-----------------------------------------------------------")
    message("Adding External project ${name} with config:")
    message("   - DISABLED     ${ARGS_DISABLE}")
    message("   - DEPENDS      ${ARGS_DEPENDS}")
    message("   - BUILDTYPE    ${ARGS_BUILDTYPE}")
    message("   - PACKAGE_NAME ${ARGS_PACKAGE_NAME}")
    message("   - LIBRARIES:")
    foreach (LIB IN LISTS ARGS_LIBRARIES)
        message("       - ${LIB}")
    endforeach ()
    message("   - CMAKE_ARGS:")
    foreach (ARG IN LISTS ARGS_CMAKE_ARGS)
        message("       - ${ARG}")
    endforeach ()
    message(" ")

    # -----------------------------------------------------------------------------------------------------------------#
    # Add the external project if not disabled
    # -----------------------------------------------------------------------------------------------------------------#
    if (NOT ARGS_DISABLE AND NOT ARGS_MAIN)

        # -------------------------------------------------------------------------------------------------------------#
        # Check if git submodules have been initialized
        # -------------------------------------------------------------------------------------------------------------#
        check_submodule(${name})
        if (${ARGC} GREATER 1)
            math(EXPR last "${ARGC} - 1")
            foreach (n RANGE 1 ${last})
                list(APPEND ADDL_CM_ARGS ${ARGV${n}})
            endforeach ()
        endif ()

        # Clean semicolons from list variables
        string(REPLACE ";" " " ARGS_LIBRARIES "${ARGS_LIBRARIES}")

        # -------------------------------------------------------------------------------------------------------------#
        # This is where we add the external project
        # -------------------------------------------------------------------------------------------------------------#
        ExternalProject_Add(${name}
                SOURCE_DIR "${PROJECT_SOURCE_DIR}/thirdparty/${name}"
                DEPENDS ${ARGS_DEPENDS}
                PREFIX ${name}
                BUILD_BYPRODUCTS ${ARGS_LIBRARIES}
                CMAKE_ARGS ${ARGS_CMAKE_ARGS} -DCMAKE_INSTALL_PREFIX=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/thirdparty
                )

        ExternalProject_Get_Property(${name} INSTALL_DIR)

        set(TP_INSTALL_DIRS ${TP_INSTALL_DIRS} ${INSTALL_DIR} CACHE INTERNAL "thirdparty install dirs" FORCE)

        # -------------------------------------------------------------------------------------------------------------#
        # Put the thirdparty lib _DIR variable into the cache so we can find it with find_package later
        # -------------------------------------------------------------------------------------------------------------#
        set(${ARGS_PACKAGE_NAME}_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/thirdparty/${CMAKE_INSTALL_LIBDIR}/cmake/${ARGS_PACKAGE_NAME} CACHE INTERNAL "third party lib ${ARGS_PACKAGE_NAME}" FORCE)
        #
        message("Set ${ARGS_PACKAGE_NAME}_DIR = ${${ARGS_PACKAGE_NAME}_DIR} for find_package(${ARGS_PACKAGE_NAME})")

        # -------------------------------------------------------------------------------------------------------------#
        # Add install targets to a list for all external projects - will run these later
        # -------------------------------------------------------------------------------------------------------------#
        list(APPEND DEPENDENCIES ${name})
        set(DEPENDENCIES "${DEPENDENCIES}" CACHE INTERNAL "${name} dependency" FORCE)
        set(TP_TARGETS "${TP_TARGETS} ${name}-install" CACHE INTERNAL "${name} install target dependencies" FORCE)
        set(TP_BYPRODUCTS "${TP_BYPRODUCTS} ${ARGS_LIBRARIES}" CACHE INTERNAL "${name} libraries for Ninja" FORCE)

        message("Thirdpary Byproducts now: ${TP_BYPRODUCTS}")
    endif ()

    if (ARGS_MAIN)
        ExternalProject_Add(${name}
                DEPENDS ${DEPENDENCIES}
                SOURCE_DIR ${PROJECT_SOURCE_DIR}
                CMAKE_ARGS -DUSE_SUPERBUILD=OFF ${ARGS_CMAKE_ARGS}
                BINARY_DIR ${CMAKE_BINARY_DIR}
                INSTALL_COMMAND ""
                )
    endif ()

endfunction()

function(depend_on_thrirdparty name)
    foreach (TGT IN ITEMS ${TP_INSTALLS})
        add_dependencies($name $TGT)
        message("Adding build dependency for ${name} on ${TGT}")
    endforeach ()
endfunction()
