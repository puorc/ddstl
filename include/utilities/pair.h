#ifndef MSTL_UTILITY_PAIR
#define MSTL_UTILITY_PAIR

#include <type_traits>
#include "type_traits.h"

struct nonesuch
{
    ~nonesuch() = delete;
    nonesuch(nonesuch const &) = delete;
    void operator=(nonesuch const &) = delete;
};

namespace ddstl
{
    template <typename T1, typename T2>
    struct pair
    {
        using first_type = T1;
        using second_type = T2;

        first_type first;
        second_type second;

        template <typename U1 = T1, typename U2 = T2, typename std::enable_if<ddstl::and_trait<std::is_default_constructible<U1>, std::is_default_constructible<U2>>::value, bool>::type = false>
        constexpr pair() : first(), second() {}

        pair(const pair &p) = default;

        pair(pair &&p) = default;

        template <typename U1 = T1, typename U2 = T2,
                  typename std::enable_if<ddstl::and_trait<
                                              std::is_constructible<T1, const U1 &>,
                                              std::is_constructible<T2, const U2 &>>::value,
                                          bool>::type = false>
        pair(const T1 &x, const T2 &y) : first(x), second(y)
        {
        }

        template <typename U1, typename U2,
                  typename std::enable_if<
                      ddstl::and_trait<std::is_constructible<T1, U1 &&>,
                                       std::is_constructible<T2, U2 &&>>::value,
                      bool>::type = false>
        pair(U1 &&x, U2 &&y) : first(ddstl::forward<U1>(x)), second(ddstl::forward<U2>(y)) {}

        template <class U1, class U2>
        explicit pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        template <typename U1, typename U2, typename std::enable_if<ddstl::and_trait<std::is_constructible<T1, U1 &&>, std::is_constructible<T2, U2 &&>>::value, bool>::type = false>
        pair(pair<U1, U2> &&p) : first(ddstl::forward<U1>(p.first)), second(ddstl::forward<U2>(p.second)) {}

        pair &operator=(typename std::conditional<
                        ddstl::and_trait<
                            std::is_copy_assignable<T1>,
                            std::is_copy_assignable<T2>>::value,
                        const pair &, const nonesuch &>::type other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        pair &operator=(typename std::conditional<
                        and_trait<std::is_move_assignable<T1>,
                                  std::is_move_assignable<T2>>::value,
                        pair &&, nonesuch &&>::type
                            p) noexcept
        {
            first = ddstl::forward<first_type>(p.first);
            second = ddstl::forward<second_type>(p.second);
            return *this;
        }

        template <class U1, class U2>
        typename std::enable_if<ddstl::and_trait<
                                    std::is_assignable<T1 &, const U1 &>,
                                    std::is_assignable<T2 &, const U2 &>>::value,
                                pair &>::type
        operator=(const pair<U1, U2> &other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        template <class U1, class U2>
        typename std::enable_if<ddstl::and_trait<
                                    std::is_assignable<T1 &, U1 &&>,
                                    std::is_assignable<T2 &, U2 &&>>::value,
                                pair &>::type
        operator=(pair<U1, U2> &&other)
        {
            first = ddstl::forward<U1>(other.first);
            second = ddstl::forward<U2>(other.second);
            return *this;
        }

        void swap(pair &other) noexcept
        {
            ddstl::swap(first, other.first);
            ddstl::swap(second, other.second);
        }

    private:
        //         pair &operator=(pair &&other) noexcept
        // {
        //     first = other.first;
        //     second = other.second;
        //     return *this;
        // }
    };

    template <class T1, class T2>
    pair<std::decay<T1>, std::decay<T2>> make_pair(T1 &&t, T2 &&u)
    {
        return pair<T1, T2>(ddstl::forward<T1>(t), ddstl::forward<T2>(u));
    }
}

#endif