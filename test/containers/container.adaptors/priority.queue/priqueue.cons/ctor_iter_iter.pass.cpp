//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <queue>

// template <class InputIterator>
//   priority_queue(InputIterator first, InputIterator last);

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>
#include <cstddef>

#include "test_macros.h"

TEST_CASE("test pq ctor iter to iter", "")
{
    int a[] = {3, 5, 2, 0, 6, 8, 1};
    int *an = a + sizeof(a) / sizeof(a[0]);
    ddstl::priority_queue<int> q(a, an);
    assert(q.size() == static_cast<std::size_t>(an - a));
    assert(q.top() == 8);
}