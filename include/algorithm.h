#ifndef MSTL_ALGORITHM_H
#define MSTL_ALGORITHM_H

#include <iterator>
#include <cstdio>
#include <cstring>
#include "utility.h"
#include <iostream>

namespace ddstl {
    struct __false_type {
    };

    // TODO: is this working?
    template<typename _Tp>
    struct __is_move_iterator {
        enum {
            __value = 0
        };
        typedef __false_type __type;
    };

    template<bool IsMove, bool IsSimple, typename Category>
    struct _copy {
        template<class InputIt, class OutputIt>
        static OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
            while (first != last) {
                *d_first = *first;
                ++d_first;
                ++first;
            }
            return d_first;
        }
    };

    template<bool IsSimple, typename Category>
    struct _copy<true, IsSimple, Category> {
        template<class InputIt, class OutputIt>
        static OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
            while (first != last) {
                *d_first = ddstl::move(*first);
                ++d_first;
                ++first;
            }
            return d_first;
        }
    };

    template<bool IsMove>
    struct _copy<IsMove, true, std::random_access_iterator_tag> {
        template<class T>
        static T *copy(const T *first, const T *last, T *d_first) {
            using assignable = std::conditional<IsMove, std::is_move_assignable<T>, std::is_copy_assignable<T>>;
            static_assert(assignable::type::value, "type is not assignable");
            std::ptrdiff_t count = last - first;
            if (count > 0) {
                memmove(d_first, first, sizeof(T) * count);
            }
            return d_first + count;
        }
    };

    template<class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
        typedef typename std::iterator_traits<InputIt>::value_type IValue;
        typedef typename std::iterator_traits<OutputIt>::value_type OValue;
        typedef typename std::iterator_traits<InputIt>::iterator_category category;
        const bool simple = (std::is_trivially_copyable<InputIt>::value
                             && std::is_pointer<InputIt>::value
                             && std::is_pointer<OutputIt>::value
                             && std::is_same<IValue, OValue>::value);
        return _copy<__is_move_iterator<InputIt>::__value, simple, category>::copy(first, last, d_first);
    }
}


#endif //MSTL_ALGORITHM_H
