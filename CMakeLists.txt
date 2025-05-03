cmake_minimum_required(VERSION 3.20)

project(tsinghua_dsa VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (MSVC)
    add_compile_options("/utf-8")
endif ()

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "build type" FORCE)
endif ()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


add_library(dsa_objs OBJECT)
target_include_directories(dsa_objs
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
if (NOT WIN32)
    target_compile_options(dsa_objs PRIVATE -fPIC)
endif ()

add_library(dsa_static
        STATIC
        $<TARGET_OBJECTS:dsa_objs>
)
add_library(dsa_shared
        SHARED
        $<TARGET_OBJECTS:dsa_objs>
)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(oj)


#install dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
message(STATUS "Installed directory: ${CMAKE_INSTALL_PREFIX}")

set(dsa_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include(cmake/install.cmake)
install(FILES README.md LICENSE
DESTINATION doc)
