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
//   sort_heap(Iter first, Iter last, Compare comp);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

#include "test_macros.h"
#include "test_iterators.h"
#include "MoveOnly.h"

namespace test_sort_heap_comp
{
    template <class T, class Iter>
    TEST_CONSTEXPR_CXX20 bool test()
    {
        int orig[15] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};
        T work[15] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};
        for (int n = 0; n < 15; ++n)
        {
            std::make_heap(work, work + n, std::greater<T>());
            ddstl::sort_heap(Iter(work), Iter(work + n), std::greater<T>());
            assert(std::is_sorted(work, work + n, std::greater<T>()));
            assert(std::is_permutation(work, work + n, orig));
            std::copy(orig, orig + n, work);
        }

        {
            T input[] = {1, 3, 2, 5, 4};
            assert(std::is_heap(input, input + 5, std::greater<T>()));
            ddstl::sort_heap(Iter(input), Iter(input + 5), std::greater<T>());
            assert(input[0] == 5);
            assert(input[1] == 4);
            assert(input[2] == 3);
            assert(input[3] == 2);
            assert(input[4] == 1);
        }
        return true;
    }
}

TEST_CASE("test sort_heap with comp pass", "")
{
    using namespace test_sort_heap_comp;
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