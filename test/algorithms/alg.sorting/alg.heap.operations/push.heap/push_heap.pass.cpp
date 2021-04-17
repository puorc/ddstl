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
//   push_heap(Iter first, Iter last);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>
#include <functional>

#include "test_macros.h"
#include "test_iterators.h"
#include "MoveOnly.h"

namespace test_push_heap
{
    template <class T, class Iter>
    TEST_CONSTEXPR_CXX20 bool test()
    {
        T orig[15] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};
        T work[15] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};
        for (int i = 1; i < 15; ++i)
        {
            ddstl::push_heap(Iter(work), Iter(work + i));
            assert(std::is_permutation(work, work + i, orig));
            assert(ddstl::is_heap(work, work + i));
        }

        {
            T input[] = {1, 3, 2, 5, 4};
            ddstl::push_heap(Iter(input), Iter(input + 1));
            assert(input[0] == 1);
            ddstl::push_heap(Iter(input), Iter(input + 2));
            assert(input[0] == 3);
            ddstl::push_heap(Iter(input), Iter(input + 3));
            assert(input[0] == 3);
            ddstl::push_heap(Iter(input), Iter(input + 4));
            assert(input[0] == 5);
            ddstl::push_heap(Iter(input), Iter(input + 5));
            assert(input[0] == 5);
            assert(ddstl::is_heap(input, input + 5));
        }
        return true;
    }
}

TEST_CASE("test ddstl::push_heap pass", "")
{
    using namespace test_push_heap;
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