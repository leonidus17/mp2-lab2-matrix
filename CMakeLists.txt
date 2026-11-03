
cmake_minimum_required(VERSION 4.1)

project(lab2)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)


add_executable(sample_prog samples/sample_matrix.cpp)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)

set(gtest_force_shared_crt ON CACHE BOOL "Force shared CRT" FORCE)

set(BUILD_GMOCK OFF CACHE BOOL "Build GMock" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Install GTest" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_prog 
    test/test_main.cpp
    test/test_tmatrix.cpp
    test/test_tvector.cpp
)

target_link_libraries(test_prog PRIVATE GTest::gtest)