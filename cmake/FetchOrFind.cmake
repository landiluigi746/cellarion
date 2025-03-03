include(FetchContent)

function(FetchOrFind dep_name git_repo git_tag)
    if(NOT dep_name OR NOT git_repo OR NOT git_tag)
        message(FATAL_ERROR "Some parameters are missing!")
    endif()

    find_package(${dep_name} QUIET)

    if(NOT ${dep_name}_FOUND)
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
