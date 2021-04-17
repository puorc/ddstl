//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <algorithm>

// template<class T, class Compare>
//   T
//   max(initializer_list<T> t, Compare comp);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <functional>
#include <cassert>

#include "test_macros.h"

TEST_CASE("test ddstl::max on init_list with pred", "")
{
    int i = ddstl::max({2, 3, 1}, std::greater<int>());
    assert(i == 1);
    i = ddstl::max({2, 1, 3}, std::greater<int>());
    assert(i == 1);
    i = ddstl::max({3, 1, 2}, std::greater<int>());
    assert(i == 1);
    i = ddstl::max({3, 2, 1}, std::greater<int>());
    assert(i == 1);
    i = ddstl::max({1, 2, 3}, std::greater<int>());
    assert(i == 1);
    i = ddstl::max({1, 3, 2}, std::greater<int>());
    assert(i == 1);
#if TEST_STD_VER >= 14
    {
    static_assert(ddstl::max({1, 3, 2}, std::greater<int>()) == 1, "");
    static_assert(ddstl::max({2, 1, 3}, std::greater<int>()) == 1, "");
    static_assert(ddstl::max({3, 2, 1}, std::greater<int>()) == 1, "");
    }
#endif
}