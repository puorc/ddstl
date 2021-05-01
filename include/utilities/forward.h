#ifndef MSTL_UTILITY_FORWARD
#define MSTL_UTILITY_FORWARD

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
        T temp = ddstl::move(a);
        a = ddstl::move(b);
        b = ddstl::move(temp);
    }
}

#endif