#ifndef MSTL_ALGORITHM_H
#define MSTL_ALGORITHM_H

#include <iterator>
#include <cstdio>
#include <cstring>
#include "utility.h"
#include "ops.h"

namespace ddstl {
    template<bool IsSimple, typename Category>
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

    template<>
    struct _copy<true, std::random_access_iterator_tag> {
        template<class T>
        static T *copy(const T *first, const T *last, T *d_first) {
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
        return _copy<simple, category>::copy(first, last, d_first);
    }

    template<class InputIt, class UnaryPredicate>
    typename std::iterator_traits<InputIt>::difference_type
    count_if_aux(InputIt first, InputIt last, UnaryPredicate p) {
        typename std::iterator_traits<InputIt>::difference_type count = 0;
        while (first != last) {
            if (p(first)) {
                ++count;
            }
            ++first;
        }
        return count;
    }

    template<class InputIt, class UnaryPredicate>
    typename std::iterator_traits<InputIt>::difference_type
    count_if(InputIt first, InputIt last, UnaryPredicate p) {
        return count_if_aux(first, last, iter_pred_functor<UnaryPredicate>(p));
    }

    template<class InputIt, class T>
    typename std::iterator_traits<InputIt>::difference_type
    inline count(InputIt first, InputIt last, const T &value) {
        return count_if_aux(first, last, ddstl::iter_equal_value_functor<T>(value));
    }
}


#endif //MSTL_ALGORITHM_H
