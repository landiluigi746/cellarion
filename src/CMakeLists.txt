file(GLOB_RECURSE CELLARION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE CELLARION_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_executable(cellarion ${CELLARION_SOURCES} ${CELLARION_HEADERS})

target_include_directories(cellarion PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(
    cellarion
    PRIVATE raylib
    PRIVATE imgui
    PRIVATE rlImGui
)

if(${CELLARION_PARALLEL})
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

    target_compile_definitions(
        cellarion
        PRIVATE
        CELLARION_PARALLEL=1
    )

    if(MSVC)
        # We need this in order to use OpenMP 3.0 features
        target_compile_options(cellarion PRIVATE /openmp:llvm)
    endif()
else()
    target_compile_definitions(
        cellarion
        PRIVATE
        CELLARION_PARALLEL=0
    )
endif()

if(MSVC)
    set(OPTIONS_WARNINGS /W4)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(OPTIONS_OPTIMIZATION /O2)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(OPTIONS_OPTIMIZATION /Zi)
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(OPTIONS_OPTIMIZATION /O2 /Zi)
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        set(OPTIONS_OPTIMIZATION /Os)
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(OPTIONS_WARNINGS -Wall -Wpedantic)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(OPTIONS_OPTIMIZATION -O3)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(OPTIONS_OPTIMIZATION -g)
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(OPTIONS_OPTIMIZATION -O2 -g)
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        set(OPTIONS_OPTIMIZATION -Os)
    endif()
endif()

message(STATUS "Compiler options: " ${OPTIONS_WARNINGS} ${OPTIONS_OPTIMIZATION})

target_compile_options(cellarion PRIVATE ${OPTIONS_WARNINGS} ${OPTIONS_OPTIMIZATION})
