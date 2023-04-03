cmake_minimum_required(VERSION 3.21)
project(CppUtils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_subdirectory(src/thread_pool)

if (DEFINED BUILD_TESTS)
    enable_testing()
    include(tests/fetch_gtest.cmake)

    add_subdirectory(tests/thread_pool)
endif()
