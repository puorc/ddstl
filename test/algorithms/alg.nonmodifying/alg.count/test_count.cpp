//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithms>

// template<InputIterator Iter, class T>
//   requires HasEqualTo<Iter::value_type, T>
//   constexpr Iter::difference_type   // constexpr after C++17
//   count(Iter first, Iter last, const T& value);

#include "algorithm.h"
#include <cassert>

#include <catch2/catch.hpp>
#include "test_macros.h"
#include "test_iterators.h"

#if TEST_STD_VER > 17
TEST_CONSTEXPR bool test_constexpr() {
    int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
    int ib[] = {1, 2, 3, 4, 5, 6};
    return    (std::count(std::begin(ia), std::end(ia), 2) == 3)
           && (std::count(std::begin(ib), std::end(ib), 9) == 0)
           ;
    }
#endif

TEST_CASE("test std::count pass", "") {
    int ia[] = {0, 1, 2, 2, 0, 1, 2, 3};
    const unsigned sa = sizeof(ia) / sizeof(ia[0]);
    assert(ddstl::count(input_iterator<const int *>(ia),
                        input_iterator<const int *>(ia + sa), 2) == 3);
    assert(ddstl::count(input_iterator<const int *>(ia),
                        input_iterator<const int *>(ia + sa), 7) == 0);
    assert(ddstl::count(input_iterator<const int *>(ia),
                        input_iterator<const int *>(ia), 2) == 0);

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}
