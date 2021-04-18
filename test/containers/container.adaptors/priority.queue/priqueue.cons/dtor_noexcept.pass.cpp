//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <queue>

// ~priority_queue() // implied noexcept;

// UNSUPPORTED: c++03

#include "queue.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "MoveOnly.h"

TEST_CASE("test pq dtor no except pass", "")
{
    {
        typedef ddstl::priority_queue<MoveOnly> C;
        static_assert(std::is_nothrow_destructible<C>::value, "");
    }
}