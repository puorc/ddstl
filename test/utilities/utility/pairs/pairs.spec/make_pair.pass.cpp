//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <utility>

// template <class T1, class T2> pair<V1, V2> make_pair(T1&&, T2&&);

#include "utility.h"
#include <catch2/catch.hpp>
#include <memory>
#include <cassert>

#include "test_macros.h"

TEST_CASE("test make_pair pass")
{
    {
        typedef ddstl::pair<int, short> P1;
        P1 p1 = ddstl::make_pair(3, static_cast<short>(4));
        assert(p1.first == 3);
        assert(p1.second == 4);
    }

#if TEST_STD_VER >= 11
    {
        typedef ddstl::pair<std::unique_ptr<int>, short> P1;
        P1 p1 = ddstl::make_pair(std::unique_ptr<int>(new int(3)), static_cast<short>(4));
        assert(*p1.first == 3);
        assert(p1.second == 4);
    }
    {
        typedef ddstl::pair<std::unique_ptr<int>, short> P1;
        P1 p1 = ddstl::make_pair(nullptr, static_cast<short>(4));
        assert(p1.first == nullptr);
        assert(p1.second == 4);
    }
#endif
#if TEST_STD_VER >= 14
    {
        typedef ddstl::pair<int, short> P1;
        constexpr P1 p1 = ddstl::make_pair(3, static_cast<short>(4));
        static_assert(p1.first == 3, "");
        static_assert(p1.second == 4, "");
    }
#endif
}