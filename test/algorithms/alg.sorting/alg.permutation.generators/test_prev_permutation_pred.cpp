//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<BidirectionalIterator Iter, StrictWeakOrder<auto, Iter::value_type> Compare>
//   requires ShuffleIterator<Iter>
//         && CopyConstructible<Compare>
//   constexpr bool  // constexpr in C++20
//   prev_permutation(Iter first, Iter last, Compare comp);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <functional>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

#include <cstdio>

namespace test_prev_permutation_pred {
    TEST_CONSTEXPR_CXX14 int factorial(int x) {
        int r = 1;
        for (; x; --x)
            r *= x;
        return r;
    }

    template<class Iter>
    TEST_CONSTEXPR_CXX20 bool
    test() {
        typedef std::greater<int> C;
        int ia[] = {1, 2, 3, 4, 5, 6};
        const int sa = sizeof(ia) / sizeof(ia[0]);
        int prev[sa];
        for (int e = 0; e <= sa; ++e) {
            int count = 0;
            bool x;
            do {
                std::copy(ia, ia + e, prev);
                x = ddstl::prev_permutation(Iter(ia), Iter(ia + e), C());
                if (e > 1) {
                    if (x)
                        assert(std::lexicographical_compare(ia, ia + e, prev, prev + e, C()));
                    else
                        assert(std::lexicographical_compare(prev, prev + e, ia, ia + e, C()));
                }
                ++count;
            } while (x);
            assert(count == factorial(e));
        }
        return true;
    }
}

TEST_CASE("test std::prev_permutation pred pass", "") {
    using namespace test_prev_permutation_pred;
    test<bidirectional_iterator<int *> >();
    test<random_access_iterator<int *> >();
    test<int *>();

#if TEST_STD_VER >= 20
    static_assert(test<bidirectional_iterator<int*>>());
    static_assert(test<random_access_iterator<int*>>());
    static_assert(test<int*>());
#endif
}