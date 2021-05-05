//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <utility>

// template <class T> typename add_rvalue_reference<T>::type declval() noexcept;

#include "utility.h"
#include <catch2/catch.hpp>
#include <type_traits>

#include "test_macros.h"

namespace test_declval_pass
{
    class A
    {
        A(const A &);
        A &operator=(const A &);
    };
}

TEST_CASE("test declval pass")
{
    using namespace test_declval_pass;
    static_assert((std::is_same<decltype(ddstl::declval<A>()), A &&>::value), "");
}