//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

#include <type_traits>
#include <cassert>
#include <catch2/catch.hpp>
#include "utility.h"

#include "../support/test_macros.h"

namespace test_forward {
    struct A {
    };

    A source()

    TEST_NOEXCEPT {
        return

                A();

    }

    const A csource()

    TEST_NOEXCEPT {
        return

                A();

    }
}

using namespace test_forward;


#if TEST_STD_VER > 11
constexpr bool test_constexpr_forward() {
    int x = 42;
    const int cx = 101;
    return ddstl::forward<int&>(x)        == 42
        && ddstl::forward<int>(x)         == 42
        && ddstl::forward<const int&>(x)  == 42
        && ddstl::forward<const int>(x)   == 42
        && ddstl::forward<int&&>(x)       == 42
        && ddstl::forward<const int&&>(x) == 42
        && ddstl::forward<const int&>(cx) == 101
        && ddstl::forward<const int>(cx)  == 101;
}
#endif

TEST_CASE("test std::forward", "") {
    A a;
    const A ca = A();

    ((void) a); // Prevent unused warning
    ((void) ca); // Prevent unused warning

    static_assert(std::is_same<decltype(ddstl::forward<A &>(a)), A &>::value, "");
    static_assert(std::is_same<decltype(ddstl::forward<A>(a)), A &&>::value, "");
    static_assert(std::is_same<decltype(ddstl::forward<A>(source())), A &&>::value, "");
    ASSERT_NOEXCEPT(ddstl::forward<A &>(a));
    ASSERT_NOEXCEPT(ddstl::forward<A>(a));
    ASSERT_NOEXCEPT(ddstl::forward<A>(source()));

    static_assert(std::is_same<decltype(ddstl::forward<const A &>(a)), const A &>::value, "");
    static_assert(std::is_same<decltype(ddstl::forward<const A>(a)), const A &&>::value, "");
    static_assert(std::is_same<decltype(ddstl::forward<const A>(source())), const A &&>::value, "");
    ASSERT_NOEXCEPT(ddstl::forward<const A &>(a));
    ASSERT_NOEXCEPT(ddstl::forward<const A>(a));
    ASSERT_NOEXCEPT(ddstl::forward<const A>(source()));

    static_assert(std::is_same<decltype(ddstl::forward<const A &>(ca)), const A &>::value, "");
    static_assert(std::is_same<decltype(ddstl::forward<const A>(ca)), const A &&>::value, "");
    static_assert(std::is_same<decltype(ddstl::forward<const A>(csource())), const A &&>::value, "");
    ASSERT_NOEXCEPT(ddstl::forward<const A &>(ca));
    ASSERT_NOEXCEPT(ddstl::forward<const A>(ca));
    ASSERT_NOEXCEPT(ddstl::forward<const A>(csource()));

#if TEST_STD_VER > 11
    {
    constexpr int i2 = ddstl::forward<int>(42);
    static_assert(ddstl::forward<int>(42) == 42, "");
    static_assert(ddstl::forward<const int&>(i2) == 42, "");
    static_assert(test_constexpr_forward(), "");
    }
#endif
#if TEST_STD_VER == 11 && defined(_LIBCPP_VERSION)
    // Test that ddstl::forward is constexpr in C++11. This is an extension
    // provided by both libc++ and libstdc++.
    {
    constexpr int i2 = ddstl::forward<int>(42);
    static_assert(ddstl::forward<int>(42) == 42, "" );
    static_assert(ddstl::forward<const int&>(i2) == 42, "");
    }
#endif
}