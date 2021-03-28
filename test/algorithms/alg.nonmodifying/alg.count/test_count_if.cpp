//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithms>

// template<InputIterator Iter, Predicate<auto, Iter::value_type> Pred>
//   requires CopyConstructible<Pred>
//   constexpr Iter::difference_type   // constexpr after C++17
//   count_if(Iter first, Iter last, Pred pred);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

namespace test_count_if {
    struct eq {
        TEST_CONSTEXPR eq(int val) : v(val) {}

        TEST_CONSTEXPR bool operator()(int v2) const { return v == v2; }

        int v;
    };

#if TEST_STD_VER > 17
    TEST_CONSTEXPR bool test_constexpr() {
        int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
        int ib[] = {1, 2, 3, 4, 5, 6};
        return    (ddstl::count_if(ddstl::begin(ia), ddstl::end(ia), eq(2)) == 3)
               && (ddstl::count_if(ddstl::begin(ib), ddstl::end(ib), eq(9)) == 0)
               ;
        }
#endif
}

TEST_CASE("test count_if pass", "") {
    using namespace test_count_if;
    int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
    const unsigned sa = sizeof(ia) / sizeof(ia[0]);
    assert(ddstl::count_if(input_iterator<const int *>(ia),
                           input_iterator<const int *>(ia + sa),
                           eq(2)) == 3);
    assert(ddstl::count_if(input_iterator<const int *>(ia),
                           input_iterator<const int *>(ia + sa),
                           [](int x) { return x == 2; }) == 3);
    assert(ddstl::count_if(input_iterator<const int *>(ia),
                           input_iterator<const int *>(ia + sa),
                           eq(7)) == 0);
    assert(ddstl::count_if(input_iterator<const int *>(ia),
                           input_iterator<const int *>(ia),
                           eq(2)) == 0);

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}