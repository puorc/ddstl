//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <queue>

// priority_queue();

// size_type size() const;

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"

TEST_CASE("test pq size pass", "")
{
    ddstl::priority_queue<int> q;
    assert(q.size() == 0);
    q.push(1);
    assert(q.size() == 1);
    q.pop();
    assert(q.size() == 0);
}