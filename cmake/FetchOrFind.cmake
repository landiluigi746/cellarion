include(FetchContent)

function(FetchOrFind dep_name git_repo git_tag)
    find_package(${dep_name} QUIET)

    if(NOT ${dep_name}_FOUND)
        if(NOT git_tag)
            message(FATAL_ERROR "GIT_TAG must be specified for ${dep_name}.")
        endif()

        message(STATUS "Fetching ${dep_name}")

        FetchContent_Declare(
            ${dep_name}
            GIT_REPOSITORY  ${git_repo}
            GIT_TAG         ${git_tag}
        )

        FetchContent_MakeAvailable(${dep_name})
    else()
        message(STATUS "Using ${dep_name} installed version")
    endif()
endfunction()
