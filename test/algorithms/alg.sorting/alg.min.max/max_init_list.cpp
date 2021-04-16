//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <algorithm>

// template <class T>
//   T
//   max(initializer_list<T> t);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"

TEST_CASE("test ddstl::max on init_list", "")
{
    int i = ddstl::max({2, 3, 1});
    assert(i == 3);
    i = ddstl::max({2, 1, 3});
    assert(i == 3);
    i = ddstl::max({3, 1, 2});
    assert(i == 3);
    i = ddstl::max({3, 2, 1});
    assert(i == 3);
    i = ddstl::max({1, 2, 3});
    assert(i == 3);
    i = ddstl::max({1, 3, 2});
    assert(i == 3);
#if TEST_STD_VER >= 14
    {
    static_assert(ddstl::max({1, 3, 2}) == 3, "");
    static_assert(ddstl::max({2, 1, 3}) == 3, "");
    static_assert(ddstl::max({3, 2, 1}) == 3, "");
    }
#endif
}