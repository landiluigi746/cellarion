cmake_minimum_required(VERSION 3.12)

project(cellarion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/vendor" CACHE STRING "Dependencies directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(FetchOrFind)

FetchOrFind(raylib https://github.com/landiluigi746/raylib-minimal.git e437e09)
FetchOrFind(imgui https://github.com/landiluigi746/imgui-cmake.git 9396f0d)
FetchOrFind(rlImGui https://github.com/landiluigi746/rlImGui-cmake.git 2841540)

find_package(OpenMP)

if(NOT OpenMP_FOUND)
  set(CELLARION_PARALLEL FALSE)
else()
  set(CELLARION_PARALLEL TRUE)
endif()

add_subdirectory(src)
