//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <utility>

// template<class T>
//   requires MoveAssignable<T> && MoveConstructible<T>
//   void
//   swap(T& a, T& b);

#include "utility.h"
#include <catch2/catch.hpp>
#include <cassert>
#include <memory>

#include "test_macros.h"

namespace test_swap {
#if TEST_STD_VER >= 11

    struct CopyOnly {
        CopyOnly() {}

        CopyOnly(CopyOnly const &) noexcept {}

        CopyOnly &operator=(CopyOnly const &) { return *this; }
    };

    struct MoveOnly {
        MoveOnly() {}

        MoveOnly(MoveOnly &&) {}

        MoveOnly &operator=(MoveOnly &&) noexcept { return *this; }
    };

    struct NoexceptMoveOnly {
        NoexceptMoveOnly() {}

        NoexceptMoveOnly(NoexceptMoveOnly &&) noexcept {}

        NoexceptMoveOnly &operator=(NoexceptMoveOnly &&) noexcept { return *this; }
    };

    struct NotMoveConstructible {
        NotMoveConstructible &operator=(NotMoveConstructible &&) { return *this; }

    private:
        NotMoveConstructible(NotMoveConstructible &&);
    };

    struct NotMoveAssignable {
        NotMoveAssignable(NotMoveAssignable &&);

    private:
        NotMoveAssignable &operator=(NotMoveAssignable &&);
    };

    template<class Tp>
    auto can_swap_test(int) -> decltype(ddstl::swap(std::declval<Tp>(), std::declval<Tp>()));

    template<class Tp>
    auto can_swap_test(...) -> std::false_type;

    template<class Tp>
    constexpr bool can_swap() {
        return std::is_same<decltype(can_swap_test<Tp>(0)), void>::value;
    }

#endif

#if TEST_STD_VER > 17
    constexpr bool test_swap_constexpr()
    {
        int i = 1;
        int j = 2;
        ddstl::swap(i, j);
        return i == 2 && j == 1;
    }
#endif // TEST_STD_VER > 17
}

TEST_CASE("test std::swap pass", "") {
    using namespace test_swap;
    {
        int i = 1;
        int j = 2;
        ddstl::swap(i, j);
        assert(i == 2);
        assert(j == 1);
    }
#if TEST_STD_VER >= 11
    {

        std::unique_ptr<int> i(new int(1));
        std::unique_ptr<int> j(new int(2));
        ddstl::swap(i, j);
        assert(*i == 2);
        assert(*j == 1);

    }
    {
        // test that the swap
        static_assert(can_swap<CopyOnly &>(), "");
        static_assert(can_swap<MoveOnly &>(), "");
        static_assert(can_swap<NoexceptMoveOnly &>(), "");

        static_assert(!can_swap<NotMoveConstructible &>(), "");
        static_assert(!can_swap<NotMoveAssignable &>(), "");

        CopyOnly c;
        MoveOnly m;
        NoexceptMoveOnly nm;
        static_assert(!noexcept(ddstl::swap(c, c)), "");
        static_assert(!noexcept(ddstl::swap(m, m)), "");
        static_assert(noexcept(ddstl::swap(nm, nm)), "");
    }
#endif

#if TEST_STD_VER > 17
    static_assert(test_swap_constexpr());
#endif // TEST_STD_VER > 17
}