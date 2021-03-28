#ifndef MSTL_ALGORITHM_H
#define MSTL_ALGORITHM_H

#include <iterator>
#include <cstdio>
#include <cstring>
#include "utility.h"
#include "ops.h"
#include <algorithm>

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
    inline count_if(InputIt first, InputIt last, UnaryPredicate p) {
        return count_if_aux(first, last, ddstl::iter_pred_functor<UnaryPredicate>(p));
    }

    template<class InputIt, class T>
    typename std::iterator_traits<InputIt>::difference_type
    inline count(InputIt first, InputIt last, const T &value) {
        return count_if_aux(first, last, ddstl::iter_equal_value_functor<T>(value));
    }

    template<class InputIt, class UnaryPredicate>
    InputIt find_if_aux(InputIt first, InputIt last, UnaryPredicate p, bool negate) {
        while (first != last) {
            if (negate) {
                if (!p(first)) {
                    return first;
                }
            } else {
                if (p(first)) {
                    return first;
                }
            }
            ++first;
        }
        return first;
    }

    template<class InputIt, class T>
    inline InputIt find(InputIt first, InputIt last, const T &value) {
        return find_if_aux(first, last, ddstl::iter_equal_value_functor<T>(value), false);
    }

    template<class InputIt, class UnaryPredicate>
    inline InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
        return find_if_aux(first, last, ddstl::iter_pred_functor<UnaryPredicate>(p), false);
    }

    template<class InputIt, class UnaryPredicate>
    inline InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q) {
        return find_if_aux(first, last, ddstl::iter_pred_functor<UnaryPredicate>(q), true);
    }

    template<class ForwardIt1, class ForwardIt2>
    ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last) {
        for (; first != last; ++first) {
            for (ForwardIt2 iter = s_first; iter != s_last; ++iter) {
                if (*iter == *first) {
                    return first;
                }
            }
        }
        return last;
    }

    template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1
    find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p) {
        for (; first != last; ++first) {
            for (ForwardIt2 iter = s_first; iter != s_last; ++iter) {
                if (p(*first, *iter)) {
                    return first;
                }
            }
        }
        return last;
    }

    template<class ForwardIt1, class ForwardIt2>
    ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last);

    template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p);

    template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    bool range_equal_aux(ForwardIt1 first, ForwardIt1 last,
                         ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p) {
        for (; s_first != s_last; ++s_first) {
            if (first == last) {
                return false;
            }
            if (!p(first, s_first)) {
                return false;
            }
            ++first;
        }
        return true;
    }

    template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                      ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p) {
        for (; first != last; ++first) {
            if (range_equal_aux(first, last, s_first, s_last, ddstl::iter_bi_pred_functor<BinaryPredicate>(p))) {
                return first;
            }
        }
        return first;
    }

    template<class ForwardIt1, class ForwardIt2>
    inline ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                             ForwardIt2 s_first, ForwardIt2 s_last) {
        return search(first, last, s_first, s_last, ddstl::iter_bi_equal_functor());
    }

    template<class ForwardIt, class BinaryPredicate>
    ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p) {
        if (first == last) {
            return last;
        }
        ForwardIt prev(first);
        ++first;
        for (; first != last; ++first) {
            if (p(*prev, *first)) {
                return prev;
            }
            prev = first;
        }
        return last;
    }

    template<class ForwardIt>
    inline ForwardIt adjacent_find(ForwardIt first, ForwardIt last) {
        return adjacent_find(first, last, ddstl::iter_bi_equal_functor());
    }

    template<class ForwardIt, class Size, class T, class BinaryPredicate>
    ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value,
                       BinaryPredicate p) {
        if (count == 0) {
            return first;
        }
        typename std::iterator_traits<ForwardIt>::difference_type len(0);
        ForwardIt fast(first), slow(first);
        while (fast != last) {
            if (p(*fast, value)) {
                ++fast;
                ++len;
                if (len >= count) {
                    return slow;
                }
            } else {
                ++fast;
                slow = fast;
                len = 0;
            }
        }
        return len >= count ? slow : last;
    }

    template<class ForwardIt, class Size, class T>
    inline ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value) {
        return search_n(first, last, count, value, ddstl::iter_bi_equal_functor());
    }
}


#endif //MSTL_ALGORITHM_H
