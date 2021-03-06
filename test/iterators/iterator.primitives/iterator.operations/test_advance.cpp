//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <iterator>

//   All of these became constexpr in C++17
//
// template <InputIterator Iter, class Distance>
//   constexpr void advance(Iter& i, Distance n);
//
// template <BidirectionalIterator Iter, class Distance>
//   constexpr void advance(Iter& i, Distance n);
//
// template <RandomAccessIterator Iter, class Distance>
//   constexpr void advance(Iter& i, Distance n);

// Make sure we catch forced conversions to the difference_type if they happen.
// ADDITIONAL_COMPILER_FLAGS: -Wsign-conversion

#include "iterator.h"
#include <catch2/catch.hpp>
#include <cassert>
#include <cstddef>
#include <type_traits>

#include "test_macros.h"
#include "test_iterators.h"

namespace test_advance {
    template<class Distance, class It>
    TEST_CONSTEXPR_CXX17
    void check_advance(It it, Distance n, It result) {
        static_assert(std::is_same<decltype(ddstl::advance(it, n)), void>::value, "");
        ddstl::advance(it, n);
        assert(it == result);
    }

    TEST_CONSTEXPR_CXX17 bool tests() {
        const char *s = "1234567890";
        typedef std::iterator_traits<const char *>::difference_type Distance;
        check_advance<Distance>(input_iterator<const char *>(s), 10, input_iterator<const char *>(s + 10));
        check_advance<Distance>(forward_iterator<const char *>(s), 10, forward_iterator<const char *>(s + 10));
        check_advance<Distance>(bidirectional_iterator<const char *>(s + 5), 5,
                                bidirectional_iterator<const char *>(s + 10));
        check_advance<Distance>(bidirectional_iterator<const char *>(s + 5), -5,
                                bidirectional_iterator<const char *>(s));
        check_advance<Distance>(random_access_iterator<const char *>(s + 5), 5,
                                random_access_iterator<const char *>(s + 10));
        check_advance<Distance>(random_access_iterator<const char *>(s + 5), -5,
                                random_access_iterator<const char *>(s));
        check_advance<Distance>(s + 5, 5, s + 10);
        check_advance<Distance>(s + 5, -5, s);

        // Also check with other distance types
        check_advance<std::size_t>(input_iterator<const char *>(s), 10u, input_iterator<const char *>(s + 10));
        check_advance<std::size_t>(forward_iterator<const char *>(s), 10u, forward_iterator<const char *>(s + 10));
        check_advance<std::size_t>(bidirectional_iterator<const char *>(s), 10u,
                                   bidirectional_iterator<const char *>(s + 10));
        check_advance<std::size_t>(random_access_iterator<const char *>(s), 10u,
                                   random_access_iterator<const char *>(s + 10));

        return true;
    }
}

TEST_CASE("test std::advance pass", "") {
    using namespace test_advance;

    tests();
#if TEST_STD_VER >= 17
    static_assert(tests(), "");
#endif
}
