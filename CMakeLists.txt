cmake_minimum_required(VERSION 3.17)
project(mstl)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 11)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(mstl test/support/test_macros.h test/support/test_allocator.h test/support/test_iterators.h test/support/min_allocator.h test/support/asan_testing.h include/utility.h test/utility/test_move.cpp test/utility/test_move_if_noexcept.cpp test/utility/test_forward.cpp test/entry.cpp test/vector/test_access.cpp test/vector/test_push_back.cpp include/algorithm.h test/algorithm/test_copy.cpp include/ops.h test/algorithm/test_count.cpp test/algorithm/test_count_if.cpp test/algorithm/test_find.cpp test/algorithm/test_find_if.cpp test/algorithm/test_find_if_not.cpp include/iterator.h test/iterator/test_distance.cpp test/algorithm/test_find_first_of.cpp test/algorithm/test_find_if_of_pred.cpp test/algorithm/test_search.cpp test/algorithm/test_search_pred.cpp test/algorithm/test_adjacent_find.cpp test/algorithm/test_adjacent_find_pred.cpp test/algorithm/test_search_n.cpp test/algorithm/test_search_n_pred.cpp test/support/user_defined_integral.h)

target_link_libraries(mstl PRIVATE Catch2::Catch2)