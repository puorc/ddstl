//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <queue>

// priority_queue& operator=(const priority_queue&) = default;

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>
#include <functional>

#include "test_macros.h"

namespace test_pq_assign_copy
{
    template <class C>
    C make(int n)
    {
        C c;
        for (int i = 0; i < n; ++i)
            c.push_back(i);
        return c;
    }
}

TEST_CASE("test pq assign copy pass", "")
{
    using namespace test_pq_assign_copy;
    std::vector<int> v = make<std::vector<int>>(5);
    ddstl::priority_queue<int, std::vector<int>, std::greater<int>> qo(std::greater<int>(), v);
    ddstl::priority_queue<int, std::vector<int>, std::greater<int>> q;
    q = qo;
    assert(q.size() == 5);
    assert(q.top() == 0);
}