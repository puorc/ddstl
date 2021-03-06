//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// test move
#include <type_traits>
#include <cassert>
#include <catch2/catch.hpp>
#include "utility.h"

#include "test_macros.h"

namespace test_move {
    class move_only {
        move_only(const move_only &);

        move_only &operator=(const move_only &);

    public:
        move_only(move_only &&) {}

        move_only &operator=(move_only &&) { return *this; }

        move_only() {}
    };

    move_only source() { return move_only(); }

    const move_only csource() { return move_only(); }

    void test(move_only) {}

    int x = 42;
    const int &cx = x;

    template<class QualInt>
    QualInt get() TEST_NOEXCEPT { return static_cast<QualInt>(x); }


    int copy_ctor = 0;
    int move_ctor = 0;

    struct A {
        A() {}

        A(const A &) { ++copy_ctor; }

        A(A &&) { ++move_ctor; }

        A &operator=(const A &) = delete;
    };

#if TEST_STD_VER > 11
    constexpr bool test_constexpr_move() {
    int y = 42;
    const int cy = y;
    return std::move(y) == 42
        && std::move(cy) == 42
        && std::move(static_cast<int&&>(y)) == 42
        && std::move(static_cast<int const&&>(y)) == 42;
}
#endif
}

TEST_CASE("test std::move", "") {
    using namespace test_move;

    { // Test return type and noexcept.
        static_assert(std::is_same<decltype(ddstl::move(x)), int &&>::value, "");
        ASSERT_NOEXCEPT(ddstl::move(x));
        static_assert(std::is_same<decltype(ddstl::move(cx)), const int &&>::value, "");
        ASSERT_NOEXCEPT(ddstl::move(cx));
        static_assert(std::is_same<decltype(ddstl::move(42)), int &&>::value, "");
        ASSERT_NOEXCEPT(ddstl::move(42));
        static_assert(std::is_same<decltype(ddstl::move(get<const int &&>())), const int &&>::value, "");
        ASSERT_NOEXCEPT(ddstl::move(get<int const &&>()));
    }
    { // test copy and move semantics
        A a;
        const A ca = A();

        assert(copy_ctor == 0);
        assert(move_ctor == 0);

        A a2 = a;
        (void) a2;
        assert(copy_ctor == 1);
        assert(move_ctor == 0);

        A a3 = ddstl::move(a);
        (void) a3;
        assert(copy_ctor == 1);
        assert(move_ctor == 1);

        A a4 = ca;
        (void) a4;
        assert(copy_ctor == 2);
        assert(move_ctor == 1);

        A a5 = ddstl::move(ca);
        (void) a5;
        assert(copy_ctor == 3);
        assert(move_ctor == 1);
    }
    { // test on a move only type
        move_only mo;
        test(ddstl::move(mo));
        test(source());
    }
#if TEST_STD_VER > 11
    {
        constexpr int y = 42;
        static_assert(ddstl::move(y) == 42, "");
        static_assert(test_constexpr_move(), "");
    }
#endif
#if TEST_STD_VER == 11 && defined(_LIBCPP_VERSION)
    // Test that std::forward is constexpr in C++11. This is an extension
    // provided by both libc++ and libstdc++.
    {
        constexpr int y = 42;
        static_assert(ddstl::move(y) == 42, "");
    }
#endif
}
