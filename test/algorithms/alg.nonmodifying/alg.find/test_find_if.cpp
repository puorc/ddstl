//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithms>

// template<InputIterator Iter, Predicate<auto, Iter::value_type> Pred>
//   requires CopyConstructible<Pred>
//   constexpr Iter   // constexpr after C++17
//   find_if(Iter first, Iter last, Pred pred);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <functional>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

namespace test_find_if {
    struct eq {
        TEST_CONSTEXPR eq(int val) : v(val) {}

        TEST_CONSTEXPR bool operator()(int v2) const { return v == v2; }

        int v;
    };

#if TEST_STD_VER > 17
    TEST_CONSTEXPR bool test_constexpr() {
        int ia[] = {1, 3, 5, 2, 4, 6};
        int ib[] = {1, 2, 3, 7, 5, 6};
        eq c(4);
        return    (ddstl::find_if(ddstl::begin(ia), ddstl::end(ia), c) == ia+4)
               && (ddstl::find_if(ddstl::begin(ib), ddstl::end(ib), c) == ib+6)
               ;
        }
#endif
}

TEST_CASE("test std::find_if pass", "") {
    using namespace test_find_if;
    int ia[] = {0, 1, 2, 3, 4, 5};
    const unsigned s = sizeof(ia) / sizeof(ia[0]);
    input_iterator<const int *> r = ddstl::find_if(input_iterator<const int *>(ia),
                                                   input_iterator<const int *>(ia + s),
                                                   eq(3));
    assert(*r == 3);
    r = ddstl::find_if(input_iterator<const int *>(ia),
                       input_iterator<const int *>(ia + s),
                       eq(10));
    assert(r == input_iterator<const int *>(ia + s));

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}