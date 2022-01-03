
function(init_submodules)
    find_package(Git)
    if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        # Update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if (GIT_SUBMODULE)
            message(STATUS "Submodule update")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)

            if (NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif ()
        endif ()
    else()
        message(FATAL_ERROR "Unable to find git / or this is not a git repository")
    endif ()
endfunction()

function(check_submodule name)
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/${name}/CMakeLists.txt")
        message(WARNING "git submodules need initializing...")
        init_submodules()
    endif ()
endfunction()