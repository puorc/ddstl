//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<InputIterator Iter1, InputIterator Iter2>
//   requires HasEqualTo<Iter1::value_type, Iter2::value_type>
//   constexpr bool     // constexpr after c++17
//   equal(Iter1 first1, Iter1 last1, Iter2 first2);
//
// Introduced in C++14:
// template<InputIterator Iter1, InputIterator Iter2>
//   constexpr bool     // constexpr after c++17
//   equal(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2);

#include "algorithm.h"
#include <catch2/catch.hpp>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

namespace test_equal {
#if TEST_STD_VER > 17
    TEST_CONSTEXPR bool test_constexpr() {
        int ia[] = {1, 3, 6, 7};
        int ib[] = {1, 3};
        int ic[] = {1, 3, 5, 7};
        typedef input_iterator<int*>         II;
        typedef bidirectional_iterator<int*> BI;
    
        return !ddstl::equal(std::begin(ia), std::end(ia), std::begin(ic))
            && !ddstl::equal(std::begin(ia), std::end(ia), std::begin(ic), std::end(ic))
            &&  ddstl::equal(std::begin(ib), std::end(ib), std::begin(ic))
            && !ddstl::equal(std::begin(ib), std::end(ib), std::begin(ic), std::end(ic))
    
            &&  ddstl::equal(II(std::begin(ib)), II(std::end(ib)), II(std::begin(ic)))
            && !ddstl::equal(BI(std::begin(ib)), BI(std::end(ib)), BI(std::begin(ic)), BI(std::end(ic)))
            ;
        }
#endif
}


TEST_CASE("test std::equal pass", "") {
    int ia[] = {0, 1, 2, 3, 4, 5};
    const unsigned s = sizeof(ia) / sizeof(ia[0]);
    int ib[s] = {0, 1, 2, 5, 4, 5};
    assert(ddstl::equal(input_iterator<const int *>(ia),
                        input_iterator<const int *>(ia + s),
                        input_iterator<const int *>(ia)));
#if TEST_STD_VER >= 14
    assert(ddstl::equal(input_iterator<const int*>(ia),
                      input_iterator<const int*>(ia+s),
                      input_iterator<const int*>(ia),
                      input_iterator<const int*>(ia+s)));
    assert(ddstl::equal(random_access_iterator<const int*>(ia),
                      random_access_iterator<const int*>(ia+s),
                      random_access_iterator<const int*>(ia),
                      random_access_iterator<const int*>(ia+s)));
#endif
    assert(!ddstl::equal(input_iterator<const int *>(ia),
                         input_iterator<const int *>(ia + s),
                         input_iterator<const int *>(ib)));
#if TEST_STD_VER >= 14
    assert(!ddstl::equal(input_iterator<const int*>(ia),
                       input_iterator<const int*>(ia+s),
                       input_iterator<const int*>(ib),
                       input_iterator<const int*>(ib+s)));
    assert(!ddstl::equal(random_access_iterator<const int*>(ia),
                       random_access_iterator<const int*>(ia+s),
                       random_access_iterator<const int*>(ib),
                       random_access_iterator<const int*>(ib+s)));
    assert(!ddstl::equal(input_iterator<const int*>(ia),
                       input_iterator<const int*>(ia+s),
                       input_iterator<const int*>(ia),
                       input_iterator<const int*>(ia+s-1)));
    assert(!ddstl::equal(random_access_iterator<const int*>(ia),
                       random_access_iterator<const int*>(ia+s),
                       random_access_iterator<const int*>(ia),
                       random_access_iterator<const int*>(ia+s-1)));

#endif

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif
}