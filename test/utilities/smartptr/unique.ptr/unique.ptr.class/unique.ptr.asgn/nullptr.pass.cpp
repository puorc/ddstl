//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <memory>

// unique_ptr

// Test unique_ptr move assignment

#include "memory.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "unique_ptr_test_helper.h"

namespace null_pass {
// test assignment from null
    template<bool IsArray>
    void test_basic() {
        typedef typename std::conditional<IsArray, A[], A>::type VT;
        const int expect_alive = IsArray ? 5 : 1;
        {
            ddstl::unique_ptr<VT> s2(newValue<VT>(expect_alive));
            assert(A::count == expect_alive);
            s2 = NULL;
            assert(A::count == 0);
            assert(s2.get() == 0);
        }
        assert(A::count == 0);
    }
}
// test assignment from null
namespace nullptr_pass {

    template<bool IsArray>
    void test_basic() {
        typedef typename std::conditional<IsArray, A[], A>::type VT;
        const int expect_alive = IsArray ? 5 : 1;
        {
            ddstl::unique_ptr<VT> s2(newValue<VT>(expect_alive));
            assert(A::count == expect_alive);
            s2 = nullptr;
            assert(A::count == 0);
            assert(s2.get() == 0);
        }
        assert(A::count == 0);
    }
}

TEST_CASE("test unique_ptr null pass", "") {
    nullptr_pass::test_basic</*IsArray*/ false>();
    null_pass::test_basic</*IsArray*/ false>();
//    test_basic<true>();
}