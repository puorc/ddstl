// //===----------------------------------------------------------------------===//
// //
// // Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// // See https://llvm.org/LICENSE.txt for license information.
// // SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// //
// //===----------------------------------------------------------------------===//

// // UNSUPPORTED: c++03

// // <memory>

// // unique_ptr

// // Test unique_ptr move assignment

// // test move assignment.  Should only require a MoveConstructible deleter, or if
// //    deleter is a reference, not even that.

// #include "memory.h"
// #include <catch2/catch.hpp>
// #include <utility>
// #include <cassert>

// #include "test_macros.h"
// #include "deleter_types.h"
// #include "unique_ptr_test_helper.h"

// namespace move_pass_cpp
// {

//     struct GenericDeleter
//     {
//         void operator()(void *) const;
//     };

//     template <bool IsArray>
//     void test_basic()
//     {
//         typedef typename std::conditional<IsArray, A[], A>::type VT;
//         const int expect_alive = IsArray ? 5 : 1;
//         {
//             ddstl::unique_ptr<VT> s1(newValue<VT>(expect_alive));
//             A *p = s1.get();
//             ddstl::unique_ptr<VT> s2(newValue<VT>(expect_alive));
//             assert(A::count == (expect_alive * 2));
//             s2 = std::move(s1);
//             assert(A::count == expect_alive);
//             assert(s2.get() == p);
//             assert(s1.get() == 0);
//         }
//         assert(A::count == 0);
//         {
//             ddstl::unique_ptr<VT, Deleter<VT>> s1(newValue<VT>(expect_alive),
//                                                   Deleter<VT>(5));
//             A *p = s1.get();
//             ddstl::unique_ptr<VT, Deleter<VT>> s2(newValue<VT>(expect_alive));
//             assert(A::count == (expect_alive * 2));
//             s2 = std::move(s1);
//             assert(s2.get() == p);
//             assert(s1.get() == 0);
//             assert(A::count == expect_alive);
//             assert(s2.get_deleter().state() == 5);
//             assert(s1.get_deleter().state() == 0);
//         }
//         assert(A::count == 0);
//         {
//             CDeleter<VT> d1(5);
//             ddstl::unique_ptr<VT, CDeleter<VT> &> s1(newValue<VT>(expect_alive), d1);
//             A *p = s1.get();
//             CDeleter<VT> d2(6);
//             ddstl::unique_ptr<VT, CDeleter<VT> &> s2(newValue<VT>(expect_alive), d2);
//             s2 = std::move(s1);
//             assert(s2.get() == p);
//             assert(s1.get() == 0);
//             assert(A::count == expect_alive);
//             assert(d1.state() == 5);
//             assert(d2.state() == 5);
//         }
//         assert(A::count == 0);
//     }

//     template <bool IsArray>
//     void test_sfinae()
//     {
//         typedef typename std::conditional<IsArray, int[], int>::type VT;
//         {
//             typedef ddstl::unique_ptr<VT> U;
//             static_assert(!std::is_assignable<U, U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &&>::value, "");
//             static_assert(std::is_nothrow_assignable<U, U &&>::value, "");
//         }
//         {
//             typedef ddstl::unique_ptr<VT, GenericDeleter> U;
//             static_assert(!std::is_assignable<U, U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &&>::value, "");
//             static_assert(std::is_nothrow_assignable<U, U &&>::value, "");
//         }
//         {
//             typedef ddstl::unique_ptr<VT, NCDeleter<VT> &> U;
//             static_assert(!std::is_assignable<U, U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &&>::value, "");
//             static_assert(std::is_nothrow_assignable<U, U &&>::value, "");
//         }
//         {
//             typedef ddstl::unique_ptr<VT, const NCDeleter<VT> &> U;
//             static_assert(!std::is_assignable<U, U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &>::value, "");
//             static_assert(!std::is_assignable<U, const U &&>::value, "");
//             static_assert(std::is_nothrow_assignable<U, U &&>::value, "");
//         }
//     }
// }

// TEST_CASE("test unique_ptr move pass", "")
// {
//     using namespace move_pass_cpp;
//     {
//         test_basic</*IsArray*/ false>();
//         test_sfinae<false>();
//     }
//     //    {
//     //        test_basic</*IsArray*/ true>();
//     //        test_sfinae<true>();
//     //    }
// }