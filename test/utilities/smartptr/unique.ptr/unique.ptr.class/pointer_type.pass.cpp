//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <memory>

// unique_ptr

// Test unique_ptr::pointer type

#include "memory.h"
#include <catch2/catch.hpp>
#include <type_traits>

#include "test_macros.h"

namespace pointer_type_pass {
    struct Deleter {
        struct pointer {
        };
    };

    struct D2 {
    private:
        typedef void pointer;
    };

    struct D3 {
        static long pointer;
    };

    template<bool IsArray>
    void test_basic() {
        typedef typename std::conditional<IsArray, int[], int>::type VT;
        {
            typedef ddstl::unique_ptr<VT> P;
            static_assert((std::is_same<typename P::pointer, int *>::value), "");
        }
        {
            typedef ddstl::unique_ptr<VT, Deleter> P;
            static_assert((std::is_same<typename P::pointer, Deleter::pointer>::value),
                          "");
        }
#if TEST_STD_VER >= 11
        {
            typedef ddstl::unique_ptr<VT, D2> P;
            static_assert(std::is_same<typename P::pointer, int *>::value, "");
        }
        {
            typedef ddstl::unique_ptr<VT, D3> P;
            static_assert(std::is_same<typename P::pointer, int *>::value, "");
        }
#endif
    }
}

TEST_CASE("test pointer_type pass", "") {
    using namespace pointer_type_pass;
    test_basic</*IsArray*/ false>();
//    test_basic<true>();
}