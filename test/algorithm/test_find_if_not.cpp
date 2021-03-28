//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<InputIterator Iter, Predicate<auto, Iter::value_type> Pred>
//   requires CopyConstructible<Pred>
//   constexpr Iter   // constexpr after C++17
//   find_if_not(Iter first, Iter last, Pred pred);

#include "algorithm.h"
#include "catch2/catch.hpp"
#include <functional>
#include <cassert>

#include "../support/test_macros.h"
#include "../support/test_iterators.h"

namespace test_find_if_not {
    struct ne {
        TEST_CONSTEXPR ne(int val) : v(val) {}

        TEST_CONSTEXPR bool operator()(int v2) const { return v != v2; }

        int v;
    };

#if TEST_STD_VER > 17
    TEST_CONSTEXPR bool test_constexpr() {
        int ia[] = {1, 3, 5, 2, 4, 6};
        int ib[] = {1, 2, 3, 7, 5, 6};
        ne c(4);
        return    (ddstl::find_if_not(ddstl::begin(ia), ddstl::end(ia), c) == ia+4)
               && (ddstl::find_if_not(ddstl::begin(ib), ddstl::end(ib), c) == ib+6)
               ;
        }
#endif
}

TEST_CASE("test std::find_if_not pass") {
    using namespace test_find_if_not;
    int ia[] = {0, 1, 2, 3, 4, 5};
    const unsigned s = sizeof(ia) / sizeof(ia[0]);
    input_iterator<const int *> r = ddstl::find_if_not(input_iterator<const int *>(ia),
                                                       input_iterator<const int *>(ia + s),
                                                       ne(3));
    assert(*r == 3);
    r = ddstl::find_if_not(input_iterator<const int *>(ia),
                           input_iterator<const int *>(ia + s),
                           ne(10));
    assert(r == input_iterator<const int *>(ia + s));

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}