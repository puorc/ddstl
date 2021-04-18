//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <queue>

// template <class InputIterator>
//   priority_queue(InputIterator first, InputIterator last,
//                  const Compare& comp, container_type&& c);

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "MoveOnly.h"

TEST_CASE("test pq ctor iter iter comp rcont pass", "")
{
    int a[] = {3, 5, 2, 0, 6, 8, 1};
    const int n = sizeof(a) / sizeof(a[0]);
    ddstl::priority_queue<MoveOnly> q(a + n / 2, a + n,
                                      std::less<MoveOnly>(),
                                      std::vector<MoveOnly>(a, a + n / 2));
    assert(q.size() == n);
    assert(q.top() == MoveOnly(8));
}