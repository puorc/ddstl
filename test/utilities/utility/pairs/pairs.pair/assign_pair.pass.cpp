//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <utility>

// template <class T1, class T2> struct pair

// pair& operator=(pair const& p);

#include "utility.h"
#include <catch2/catch.hpp>
#include <memory>
#include <cassert>

#include "test_macros.h"
#include "archetypes.h"

namespace test_pair_assign_pair
{
    struct CountAssign
    {
        int copied = 0;
        int moved = 0;
        TEST_CONSTEXPR_CXX20 CountAssign() = default;
        TEST_CONSTEXPR_CXX20 CountAssign &operator=(CountAssign const &)
        {
            ++copied;
            return *this;
        }
        TEST_CONSTEXPR_CXX20 CountAssign &operator=(CountAssign &&)
        {
            ++moved;
            return *this;
        }
    };

    struct Incomplete;
    extern Incomplete inc_obj;

    TEST_CONSTEXPR_CXX20 bool test()
    {
        {
            typedef ddstl::pair<ConstexprTestTypes::CopyOnly, int> P;
            const P p1(ConstexprTestTypes::CopyOnly(), short{4});
            P p2;
            p2 = p1;
            assert(p2.second == 4);
        }
        {
            using P = ddstl::pair<int &, int &&>;
            int x = 42;
            int y = 101;
            int x2 = -1;
            int y2 = 300;
            P p1(x, std::move(y));
            P p2(x2, std::move(y2));
            p1 = p2;
            assert(p1.first == x2);
            assert(p1.second == y2);
        }
        {
            using P = ddstl::pair<int, ConstexprTestTypes::NonCopyable>;
            static_assert(!std::is_copy_assignable<P>::value, "");
        }
        {
            using P = ddstl::pair<CountAssign, ConstexprTestTypes::Copyable>;
            static_assert(std::is_copy_assignable<P>::value, "");
            P p;
            P p2;
            p = p2;
            assert(p.first.copied == 1);
            assert(p.first.moved == 0);
            assert(p2.first.copied == 0);
            assert(p2.first.moved == 0);
        }
        {
            using P = ddstl::pair<int, ConstexprTestTypes::MoveAssignOnly>;
            static_assert(!std::is_copy_assignable<P>::value, "");
        }
        {
            using P = ddstl::pair<int, std::unique_ptr<int>>;
            static_assert(!std::is_copy_assignable<P>::value, "");
        }

        return true;
    }
}
TEST_CASE("test pair assign pair pass")
{
    using namespace test_pair_assign_pair;
    test();
#if TEST_STD_VER >= 20
    static_assert(test());
#endif
}
