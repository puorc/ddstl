//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<RandomAccessIterator Iter>
//   requires ShuffleIterator<Iter> && LessThanComparable<Iter::value_type>
//   constexpr void  // constexpr in C++20
//   pop_heap(Iter first, Iter last, Compare comp);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>
#include <functional>

#include "test_macros.h"
#include "test_iterators.h"
#include "MoveOnly.h"

namespace test_pop_heap_pred
{
    template <class T, class Iter>
    TEST_CONSTEXPR_CXX20 bool test()
    {
        T orig[15] = {1, 1, 2, 3, 3, 8, 4, 6, 5, 5, 5, 9, 9, 7, 9};
        T work[15] = {1, 1, 2, 3, 3, 8, 4, 6, 5, 5, 5, 9, 9, 7, 9};
        assert(std::is_heap(orig, orig + 15, std::greater<T>()));
        for (int i = 15; i >= 1; --i)
        {
            ddstl::pop_heap(Iter(work), Iter(work + i), std::greater<T>());
            assert(std::is_heap(work, work + i - 1, std::greater<T>()));
            assert(std::min_element(work, work + i - 1) == work);
            assert(std::is_permutation(work, work + 15, orig));
        }
        assert(std::is_sorted(work, work + 15, std::greater<T>()));

        {
            T input[] = {1, 2, 5, 4, 3};
            assert(std::is_heap(input, input + 5, std::greater<T>()));
            ddstl::pop_heap(Iter(input), Iter(input + 5), std::greater<T>());
            assert(input[4] == 1);
            ddstl::pop_heap(Iter(input), Iter(input + 4), std::greater<T>());
            assert(input[3] == 2);
            ddstl::pop_heap(Iter(input), Iter(input + 3), std::greater<T>());
            assert(input[2] == 3);
            ddstl::pop_heap(Iter(input), Iter(input + 2), std::greater<T>());
            assert(input[1] == 4);
            ddstl::pop_heap(Iter(input), Iter(input + 1), std::greater<T>());
            assert(input[0] == 5);
        }
        return true;
    }
}

TEST_CASE("test pop_heap with pred", "")
{
    using namespace test_pop_heap_pred;
    test<int, random_access_iterator<int *>>();
    test<int, int *>();

#if TEST_STD_VER >= 11
    test<MoveOnly, random_access_iterator<MoveOnly *>>();
    test<MoveOnly, MoveOnly *>();
#endif

#if TEST_STD_VER >= 20
    static_assert(test<int, random_access_iterator<int *>>());
    static_assert(test<int, int *>());
    static_assert(test<MoveOnly, random_access_iterator<MoveOnly *>>());
    static_assert(test<MoveOnly, MoveOnly *>());
#endif
}