//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<InputIterator Iter1, ForwardIterator Iter2,
//          Predicate<auto, Iter1::value_type, Iter2::value_type> Pred>
//   requires CopyConstructible<Pred>
//   constexpr Iter1  // constexpr after C++17
//   find_first_of(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, Pred pred);

#include "algorithm.h"
#include "catch2/catch.hpp"
#include <functional>
#include <cassert>

#include "../support/test_macros.h"
#include "../support/test_iterators.h"

#if TEST_STD_VER > 17
constexpr bool test_constexpr() {
    int ia[] = {1, 2, 3};
    int ib[] = {7, 8, 9};
    int ic[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3};
    typedef forward_iterator<int*>       FI;
    typedef bidirectional_iterator<int*> BI;
    typedef random_access_iterator<int*> RI;
    ddstl::equal_to<int> eq{};
    return    (ddstl::find_first_of(FI(ddstl::begin(ic)), FI(ddstl::end(ic)), FI(ddstl::begin(ia)), FI(ddstl::end(ia)), eq) == FI(ic+1))
           && (ddstl::find_first_of(FI(ddstl::begin(ic)), FI(ddstl::end(ic)), FI(ddstl::begin(ib)), FI(ddstl::end(ib)), eq) == FI(ddstl::end(ic)))
           && (ddstl::find_first_of(BI(ddstl::begin(ic)), BI(ddstl::end(ic)), BI(ddstl::begin(ia)), BI(ddstl::end(ia)), eq) == BI(ic+1))
           && (ddstl::find_first_of(BI(ddstl::begin(ic)), BI(ddstl::end(ic)), BI(ddstl::begin(ib)), BI(ddstl::end(ib)), eq) == BI(ddstl::end(ic)))
           && (ddstl::find_first_of(RI(ddstl::begin(ic)), RI(ddstl::end(ic)), RI(ddstl::begin(ia)), RI(ddstl::end(ia)), eq) == RI(ic+1))
           && (ddstl::find_first_of(RI(ddstl::begin(ic)), RI(ddstl::end(ic)), RI(ddstl::begin(ib)), RI(ddstl::end(ib)), eq) == RI(ddstl::end(ic)))
           ;
    }
#endif

TEST_CASE("test find first of with pred pass", "") {
    int ia[] = {0, 1, 2, 3, 0, 1, 2, 3};
    const unsigned sa = sizeof(ia) / sizeof(ia[0]);
    int ib[] = {1, 3, 5, 7};
    const unsigned sb = sizeof(ib) / sizeof(ib[0]);
    assert(ddstl::find_first_of(input_iterator<const int *>(ia),
                                input_iterator<const int *>(ia + sa),
                                forward_iterator<const int *>(ib),
                                forward_iterator<const int *>(ib + sb),
                                std::equal_to<int>()) ==
           input_iterator<const int *>(ia + 1));
    int ic[] = {7};
    assert(ddstl::find_first_of(input_iterator<const int *>(ia),
                                input_iterator<const int *>(ia + sa),
                                forward_iterator<const int *>(ic),
                                forward_iterator<const int *>(ic + 1),
                                std::equal_to<int>()) ==
           input_iterator<const int *>(ia + sa));
    assert(ddstl::find_first_of(input_iterator<const int *>(ia),
                                input_iterator<const int *>(ia + sa),
                                forward_iterator<const int *>(ic),
                                forward_iterator<const int *>(ic),
                                std::equal_to<int>()) ==
           input_iterator<const int *>(ia + sa));
    assert(ddstl::find_first_of(input_iterator<const int *>(ia),
                                input_iterator<const int *>(ia),
                                forward_iterator<const int *>(ic),
                                forward_iterator<const int *>(ic + 1),
                                std::equal_to<int>()) ==
           input_iterator<const int *>(ia));

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}

