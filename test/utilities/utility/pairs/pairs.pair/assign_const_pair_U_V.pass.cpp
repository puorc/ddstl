//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <utility>

// template <class T1, class T2> struct pair

// template<class U, class V> pair& operator=(const pair<U, V>& p);

#include "utility.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#if TEST_STD_VER >= 11
#include "archetypes.h"
#endif

namespace test_pair_assign_const_pair_U_V
{
    struct CopyAssignableInt
    {
        CopyAssignableInt &operator=(int &) { return *this; }
    };

    struct Unrelated
    {
    };

    TEST_CONSTEXPR_CXX20 bool test()
    {
        {
            typedef ddstl::pair<int, short> P1;
            typedef ddstl::pair<double, long> P2;
            P1 p1(3, static_cast<short>(4));
            P2 p2;
            p2 = p1;
            assert(p2.first == 3);
            assert(p2.second == 4);
        }
#if TEST_STD_VER >= 20
        {
            using C = ConstexprTestTypes::TestType;
            using P = ddstl::pair<int, C>;
            using T = ddstl::pair<long, C>;
            const T t(42, -42);
            P p(101, 101);
            p = t;
            assert(p.first == 42);
            assert(p.second.value == -42);
        }
#elif TEST_STD_VER >= 11
        {
            using C = TestTypes::TestType;
            using P = ddstl::pair<int, C>;
            using T = ddstl::pair<long, C>;
            const T t(42, -42);
            P p(101, 101);
            C::reset_constructors();
            p = t;
            assert(C::constructed == 0);
            assert(C::assigned == 1);
            assert(C::copy_assigned == 1);
            assert(C::move_assigned == 0);
            assert(p.first == 42);
            assert(p.second.value == -42);
        }
        { // test const requirement
            using T = ddstl::pair<CopyAssignableInt, CopyAssignableInt>;
            using P = ddstl::pair<int, int>;
            static_assert(!std::is_assignable<T &, P const>::value, "");
        }
        {
            using T = ddstl::pair<int, Unrelated>;
            using P = ddstl::pair<Unrelated, int>;

            static_assert(!std::is_assignable<T &, P &>::value, "");
            static_assert(!std::is_assignable<P &, T &>::value, "");
        }
#endif
        return true;
    }
}

TEST_CASE("test pair assign_const_pair_U_V")
{
    using namespace test_pair_assign_const_pair_U_V;
    test();
#if TEST_STD_VER >= 20
    static_assert(test());
#endif
}