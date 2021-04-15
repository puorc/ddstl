#ifndef MSTL_UTILITY_H
#define MSTL_UTILITY_H

#include <utility>
#include <type_traits>

namespace ddstl
{
    template <class T>
    typename std::remove_reference<T>::type &&move(T &&t) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type &&>(t);
    }

    template <class T>
    typename std::conditional<
        !std::is_nothrow_move_constructible<T>::value && std::is_copy_constructible<T>::value,
        const T &,
        T &&>::type
    move_if_noexcept(T &x) noexcept
    {
        return move(x);
    }

    template <class T>
    T &&forward(typename std::remove_reference<T>::type &t) noexcept
    {
        return static_cast<T &&>(t);
    }

    template <class T>
    T &&forward(typename std::remove_reference<T>::type &&t) noexcept
    {
        return static_cast<T &&>(t);
    }

    template <class T>
    typename std::enable_if<
        std::is_move_assignable<T>::value && std::is_move_constructible<T>::value>::type
    swap(T &a, T &b) noexcept(std::is_nothrow_move_assignable<T>::value &&
                                  std::is_nothrow_move_constructible<T>::value)
    {
        // FIXME why our own move not working.
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }

    template <typename T1, typename T2>
    struct pair
    {
        using first_type = T1;
        using second_type = T2;

        first_type first;
        second_type second;

        constexpr pair() : first(), second() {}

        pair(const pair &p) = default;

        pair(pair &&p) = default;

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}

        template <class U1, class U2>
        pair(U1 &&x, U2 &&y) : first(ddstl::forward<U1>(x)), second(ddstl::forward<U2>(y)) {}

        template <class U1, class U2>
        pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        template <class U1, class U2>
        pair(pair<U1, U2> &&p) : first(ddstl::forward<U1>(p.first)), second(ddstl::forward<U2>(p.second)) {}

        pair &operator=(const pair &other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        template <class U1, class U2>
        pair &operator=(const pair<U1, U2> &other);

        pair &operator=(pair &&other) noexcept
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        template <class U1, class U2>
        pair &operator=(pair<U1, U2> &&other);

        void swap(pair &other) noexcept
        {
            ddstl::swap(first, other.first);
            ddstl::swap(second, other.second);
        }
    };

    template <class T1, class T2>
    pair<std::decay<T1>, std::decay<T2>> make_pair(T1 &&t, T2 &&u)
    {
        return pair<T1, T2>(std::forward<T1>(t), std::forward<T2>(u));
    }
}
#endif //MSTL_UTILITY_H
