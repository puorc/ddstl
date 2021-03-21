cmake_minimum_required(VERSION 3.17)
project(mstl)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(mstl main.cpp test/test_vector.cpp test/test_macros.h test/test_allocator.h test/test_iterators.h test/min_allocator.h test/asan_testing.h include/utility.h)

target_link_libraries(mstl PRIVATE Catch2::Catch2)