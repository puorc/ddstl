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
//   constexpr Iter   // constexpr after C++17
//   find(Iter first, Iter last, const T& value);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

#if TEST_STD_VER > 17
TEST_CONSTEXPR bool test_constexpr() {
    int ia[] = {1, 3, 5, 2, 4, 6};
    int ib[] = {1, 2, 3, 4, 5, 6};
    return    (ddstl::find(ddstl::begin(ia), ddstl::end(ia), 5) == ia+2)
           && (ddstl::find(ddstl::begin(ib), ddstl::end(ib), 9) == ib+6)
           ;
    }
#endif

TEST_CASE("test stl::find pass") {
    int ia[] = {0, 1, 2, 3, 4, 5};
    const unsigned s = sizeof(ia) / sizeof(ia[0]);
    input_iterator<const int *> r = ddstl::find(input_iterator<const int *>(ia),
                                                input_iterator<const int *>(ia + s), 3);
    assert(*r == 3);
    r = ddstl::find(input_iterator<const int *>(ia), input_iterator<const int *>(ia + s), 10);
    assert(r == input_iterator<const int *>(ia + s));

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}