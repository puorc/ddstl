//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<ForwardIterator Iter>
//   requires EqualityComparable<Iter::value_type>
//   constexpr Iter  // constexpr after C++17
//   adjacent_find(Iter first, Iter last);

#include "algorithm.h"
#include "catch2/catch.hpp"
#include <cassert>

#include "../support/test_macros.h"
#include "../support/test_iterators.h"

#if TEST_STD_VER > 17
TEST_CONSTEXPR bool test_constexpr() {
    int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
    int ib[] = {0, 1, 2, 7, 0, 1, 2, 3};

    return  (ddstl::adjacent_find(std::begin(ia), std::end(ia)) == ia+2)
         && (ddstl::adjacent_find(std::begin(ib), std::end(ib)) == std::end(ib))
         ;
    }
#endif

TEST_CASE("test std::adjacent_find pass", "") {
    int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
    const unsigned sa = sizeof(ia) / sizeof(ia[0]);
    assert(ddstl::adjacent_find(forward_iterator<const int *>(ia),
                                forward_iterator<const int *>(ia + sa)) ==
           forward_iterator<const int *>(ia + 2));
    assert(ddstl::adjacent_find(forward_iterator<const int *>(ia),
                                forward_iterator<const int *>(ia)) ==
           forward_iterator<const int *>(ia));
    assert(ddstl::adjacent_find(forward_iterator<const int *>(ia + 3),
                                forward_iterator<const int *>(ia + sa)) ==
           forward_iterator<const int *>(ia + sa));

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}