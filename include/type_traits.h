#ifndef MSTL_TYPE_TRAITS_H
#define MSTL_TYPE_TRAITS_H

#include <type_traits>

namespace ddstl {
    typedef std::integral_constant<bool, true> true_type;
    typedef std::integral_constant<bool, false> false_type;

    template<typename...>
    struct and_trait;

    template<>
    struct and_trait<> : public true_type {
    };

    template<typename T>
    struct and_trait<T>
            : public T {
    };

    template<typename B1, typename B2>
    struct and_trait<B1, B2>
            : public std::conditional<B1::value, B2, B1>::type {
    };

    template<typename B1, typename B2, typename B3, typename... Bn>
    struct and_trait<B1, B2, B3, Bn...>
            : public std::conditional<B1::value, and_trait<B2, B3, Bn...>, B1>::type {
    };

    template<bool V>
    using bool_constant = std::integral_constant<bool, V>;

    template<typename T>
    struct not_trait
            : public bool_constant<!bool(T::value)> {
    };

    template<typename... Cond>
    using Require = typename std::enable_if<and_trait<Cond...>::value>::type;
}


#endif //MSTL_TYPE_TRAITS_H
