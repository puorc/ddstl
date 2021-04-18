//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <queue>

// explicit priority_queue(const Compare& comp, Container&& c); // before C++20
// priority_queue(const Compare& comp, Container&& c);          // C++20

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "MoveOnly.h"
#include "test_convertible.h"

namespace test_pq_ctor_comp_rcontainer
{
    template <class C>
    C make(int n)
    {
        C c;
        for (int i = 0; i < n; ++i)
            c.push_back(MoveOnly(i));
        return c;
    }
}

TEST_CASE("test pq ctor comp rcontainer pass", "")
{
    using namespace test_pq_ctor_comp_rcontainer;

    typedef std::vector<MoveOnly> Container;
    typedef std::less<MoveOnly> Compare;
    typedef ddstl::priority_queue<MoveOnly> Q;
    Q q(Compare(), make<Container>(5));
    assert(q.size() == 5);
    assert(q.top() == MoveOnly(4));

    static_assert(test_convertible<Q, const Compare &, Container &&>(), "");
}