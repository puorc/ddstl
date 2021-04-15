//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <utility>

// template <class T1, class T2> struct pair

// explicit(see-below) constexpr pair();

// NOTE: The SFINAE on the default constructor is tested in
//       default-sfinae.pass.cpp


#include "utility.h"
#include <catch2/catch.hpp>
#include <type_traits>
#include <cassert>

#include "test_macros.h"
#include "archetypes.h"

TEST_CASE("test pair default pass", "")
{
    {
        typedef ddstl::pair<float, short*> P;
        P p;
        assert(p.first == 0.0f);
        assert(p.second == nullptr);
    }
#if TEST_STD_VER >= 11
    // {
    //     typedef ddstl::pair<float, short*> P;
    //     constexpr P p;
    //     static_assert(p.first == 0.0f, "");
    //     static_assert(p.second == nullptr, "");
    // }
    // {
    //     using NoDefault = ImplicitTypes::NoDefault;
    //     using P = ddstl::pair<int, NoDefault>;
    //     static_assert(!std::is_default_constructible<P>::value, "");
    //     using P2 = ddstl::pair<NoDefault, int>;
    //     static_assert(!std::is_default_constructible<P2>::value, "");
    // }
    // {
    //     struct Base { };
    //     struct Derived : Base { protected: Derived() = default; };
    //     static_assert(!std::is_default_constructible<ddstl::pair<Derived, int> >::value, "");
    // }
#endif
}