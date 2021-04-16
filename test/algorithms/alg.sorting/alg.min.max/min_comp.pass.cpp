//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<class T, StrictWeakOrder<auto, T> Compare>
//   requires !SameType<T, Compare> && CopyConstructible<Compare>
//   const T&
//   min(const T& a, const T& b, Compare comp);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <functional>
#include <cassert>

#include "test_macros.h"

namespace test_min_comp
{
    template <class T, class C>
    void
    test(const T &a, const T &b, C c, const T &x)
    {
        assert(&ddstl::min(a, b, c) == &x);
    }
}

TEST_CASE("test std::min with comp", "")
{
    using namespace test_min_comp;
    {
        int x = 0;
        int y = 0;
        test(x, y, std::greater<int>(), x);
        test(y, x, std::greater<int>(), y);
    }
    {
        int x = 0;
        int y = 1;
        test(x, y, std::greater<int>(), y);
        test(y, x, std::greater<int>(), y);
    }
    {
        int x = 1;
        int y = 0;
        test(x, y, std::greater<int>(), x);
        test(y, x, std::greater<int>(), x);
    }
#if TEST_STD_VER >= 14
    {
        constexpr int x = 1;
        constexpr int y = 0;
        static_assert(std::min(x, y, std::greater<int>()) == x, "");
        static_assert(std::min(y, x, std::greater<int>()) == x, "");
    }
#endif
}