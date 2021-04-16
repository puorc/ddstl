cmake_minimum_required(VERSION 3.17)
project(mstl)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.1)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 11)

add_executable(mstl
        test/utilities/utility/forward/test_move.cpp
        test/utilities/utility/forward/test_move_if_noexcept.cpp
        test/utilities/utility/forward/test_forward.cpp
        test/entry.cpp
        test/vector/test_access.cpp
        test/vector/test_push_back.cpp
        test/algorithms/alg.modifying.operations/alg.copy/test_copy.cpp
        test/algorithms/alg.nonmodifying/alg.count/test_count.cpp
        test/algorithms/alg.nonmodifying/alg.count/test_count_if.cpp
        test/algorithms/alg.nonmodifying/alg.find/test_find.cpp
        test/algorithms/alg.nonmodifying/alg.find/test_find_if.cpp
        test/algorithms/alg.nonmodifying/alg.find/test_find_if_not.cpp
        test/iterators/iterator.primitives/iterator.operations/test_distance.cpp
        test/algorithms/alg.nonmodifying/alg.find.first.of/test_find_first_of.cpp
        test/algorithms/alg.nonmodifying/alg.find.first.of/test_find_first_of_pred.cpp
        test/algorithms/alg.nonmodifying/alg.search/test_search.cpp
        test/algorithms/alg.nonmodifying/alg.search/test_search_pred.cpp
        test/algorithms/alg.nonmodifying/alg.adjacent.find/test_adjacent_find.cpp
        test/algorithms/alg.nonmodifying/alg.adjacent.find/test_adjacent_find_pred.cpp
        test/algorithms/alg.nonmodifying/alg.search/test_search_n.cpp
        test/algorithms/alg.nonmodifying/alg.search/test_search_n_pred.cpp
        test/algorithms/alg.nonmodifying/alg.find.end/test_find_end.cpp
        test/algorithms/alg.nonmodifying/alg.find.end/test_find_end_pred.cpp 
        test/iterators/iterator.primitives/iterator.operations/test_advance.cpp 
        test/utilities/utility/utility.swap/test_swap.cpp 
        test/algorithms/alg.modifying.operations/alg.copy/test_copy_n.cpp 
        test/algorithms/alg.nonmodifying/alg.is_permutation/test_is_permutation.cpp 
        test/algorithms/alg.nonmodifying/alg.is_permutation/test_is_permutation_pred.cpp 
        test/algorithms/alg.sorting/alg.permutation.generators/test_next_permutation.cpp 
        test/algorithms/alg.sorting/alg.permutation.generators/test_next_permutation_pred.cpp 
        test/algorithms/alg.sorting/alg.permutation.generators/test_prev_permutation.cpp 
        test/algorithms/alg.sorting/alg.permutation.generators/test_prev_permutation_pred.cpp 
        test/algorithms/alg.sorting/alg.lex.comparison/test_lexicographical_compare.cpp 
        test/algorithms/alg.sorting/alg.lex.comparison/test_lexicographical_compare_pred.cpp 
        test/algorithms/alg.nonmodifying/alg.equal/test_equal.cpp 
        test/algorithms/alg.nonmodifying/alg.equal/test_equal_pred.cpp 
        test/utilities/smartptr/unique.ptr/unique.ptr.class/pointer_type.pass.cpp 
        test/utilities/smartptr/unique.ptr/unique.ptr.class/unique.ptr.asgn/move.pass.cpp 
        test/utilities/smartptr/unique.ptr/unique.ptr.class/unique.ptr.asgn/nullptr.pass.cpp 
        test/utilities/smartptr/unique.ptr/unique.ptr.class/unique.ptr.asgn/move_convert.pass.cpp
        test/utilities/utility/pairs/pairs.pair/default.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/max.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/max_comp.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/min.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/max_element.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/max_init_list.cpp
        test/algorithms/alg.sorting/alg.min.max/max_init_list_comp.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/min_comp.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/min_element.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/min_element_comp.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/min_init_list.pass.cpp
        test/algorithms/alg.sorting/alg.min.max/min_init_list_comp.pass.cpp
        test/algorithms/alg.modifying.operations/alg.reverse/reverse.pass.cpp
        )

target_include_directories(mstl
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/test/support
        )

target_link_libraries(mstl PRIVATE Catch2::Catch2)