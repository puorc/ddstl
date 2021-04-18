//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <queue>

// priority_queue(priority_queue&& q);

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "MoveOnly.h"

namespace test_pq_ctor_move
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

TEST_CASE("test pq ctor move pass", "")
{
    using namespace test_pq_ctor_move;
    ddstl::priority_queue<MoveOnly> qo(std::less<MoveOnly>(), make<std::vector<MoveOnly>>(5));
    ddstl::priority_queue<MoveOnly> q = std::move(qo);
    assert(q.size() == 5);
    assert(q.top() == MoveOnly(4));
}